#include "FILTER.h"
#include "filterFunctions.h"

/**
 * This is the main function of the program. It will allocate the shared memory
 * segment and make this accessible to the program. The arrayToFilter is a 7 character
 * long alpha-numeric array that is sorted by 3 child processes (P0, P1, P2) whose
 * access to change the array is controlled by semaphores to enter and exit the
 * critical section.
 *
 * Author: Emma Boulay
 * Student Number: 101073617
 *
 */
int main(int argc, const char * argv[]) {
    /*The shared memory segment is created with a call to shmget*/
    void *shared_memory = (void *) 0;
    struct shared_data_t *shared_data;
    int shmid;
    int debug = 0;
    int lockArr[] = {0, 0, 1};
    
    srand((unsigned int) getpid());

    shmid = shmget((key_t) 1234, sizeof(struct shared_data_t), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    /* Makes the shared memory accessible to the program. */
    shared_memory = shmat(shmid, (void *) 0, 0);
    if (shared_memory == (void *) -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %p\n", shared_memory);
    shared_data = (struct shared_data_t *) shared_memory;

    //If using the cmd line arg "data2"
    if(argc > 1 && strcmp (argv[1], "data2") == 0){
        char arrToFilter[] = "123CDEF";
        copyMatrix(shared_data->B, arrToFilter);
    }
    //Random option used in command line
    else if(argc > 1 && strcmp (argv[1], "-r") == 0){
        randomCharArray(shared_data->B, SIZE);
    }
    //User option used in command line
    else if(argc > 1 && strcmp (argv[1], "-u") == 0){
        for(int i = 0; i < SIZE; i++){
            printf("Character %d: ", i+1);
            char* c;
            c = malloc(sizeof(char)*1);
            scanf("%s", c);
            shared_data->B[i] = *c;
            free(c);
        }
    }
    //Default data set
    else {
        char arrToFilter[] = "5A9MW6Z";
        copyMatrix(shared_data->B, arrToFilter);
    }

    int flag = 1;
    char* is_debug;
    is_debug = malloc(10);

    /* Ask the user if the want to run in debug mode */
    while(flag) { //Keep asking if answer is not yes or no
        printf("Would you like to run in debug mode? yes/no: ");
        scanf("%s", is_debug);
        if(strcmp(is_debug, "yes") == 0){
            debug = 1;
            flag = 0;
        }
        else if(strcmp(is_debug, "no") == 0){
            flag = 0;
        }
    }
    free(is_debug);

    printf("\nThe unsorted character array: \n");
    printArray(shared_data->B, SIZE);
    printf("\n");

    /* Instantiate the semaphores to access the character array */
    //Only 2 semaphores are needed
    for(int i = 0; i < N_PROCESS-1; i++){
        sem_id[i] = semget((key_t) (i+1), 1, 0666 | IPC_CREAT);
        if(!set_semvalue(sem_id[i])){
            fprintf(stderr, "Failed to initialize the semaphore\n");
            exit(EXIT_FAILURE);
        }
    }

    int nProcess = N_PROCESS;
    //Fork the process 3 times to create P0, P1, P2
    for (int i = 0; i < N_PROCESS; i++){
        int processNumber = i;
        pid_t pid = fork();
        switch(pid){
            case -1:
                perror("Fork failed!\n");
                exit(EXIT_FAILURE);
            /* Child Process */
            case 0:
                //Don't exit the child process until the array is filtered
                while(!isFiltered(shared_data->B, SIZE)){
                    /* Entering the critical section, waits until has lock */
                    //If the process is P1 it needs to get lock 1 and 2
                    if(processNumber == 1){
                        if(!semaphore_p(sem_id[0]) && !semaphore_p(sem_id[0])){
                            exit(EXIT_FAILURE);
                        }
                    }
                    else{ //Its P0 or P2 and only needs 1 lock
                        if(!semaphore_p(sem_id[lockArr[processNumber]])){
                            exit(EXIT_FAILURE);
                        }
                    }

                    /* Iterates over its array chunk and swaps necessary characters */
                    int swapped = 0; //Any swapping this iterations
                    for(int i = processNumber*2 ; i < processNumber*2+2; i++){
                        if(compare(shared_data->B[i], shared_data->B[i+1]) == -1){ //If arr[i] > arr [i+1] it will swap them
                            if(debug){
                                printf("Process P%d is swapping %c at %d with %c at %d\n", processNumber, shared_data->B[i], i, shared_data->B[i+1], i+1);
                            }
                            swapped = 1;
                            swap(shared_data->B, i, i+1);
                        }
                    }
                    //If it hasn't swapped this pass through
                    if(!swapped && debug){
                        printf("Process P%d: No swapping\n", processNumber);
                    }
                    /* Releases lock */
                    //If the process is P1 it needs to release lock 1 and 2
                    if(processNumber == 1){
                        if(!semaphore_v(sem_id[0]) && !semaphore_v(sem_id[1])){
                            exit(EXIT_FAILURE);
                        }
                    }
                    else{//It is process P0 or P2 and only needs to release 1 lock
                        if(!semaphore_v(sem_id[lockArr[processNumber]])){
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                exit(0);
            /* Parent Process */
            default:
                break;
        }
    }
    /* Wait until all child processes terminate */
    while(nProcess > 0){
        wait(NULL);
        --nProcess;
    }

    printf("\nThe sorted character array: \n");
    printArray(shared_data->B, SIZE);

    /* Detach and delete the shared memory */
    printf("Detaching and deleting shared memory\n");
    del_semvalue();
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, (struct shmid_ds *) NULL) < -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * This function initializes the semaphore using the SETVAL command
 * in a semctl call. This needs to be done before the semaphore can
 * be used.
 *
 * @param sem_id the semaphore ID
 * @return 1 if semctl call is successful, otherwise 0
 */
static int set_semvalue(int sem_id) {
    union semun sem_union;

    sem_union.val = 1;

    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        return (0);
    }
    return (1);
}

/**
 * This function decrements the semaphore by -1 using a semop call.
 * This acts as the wait function.
 *
 * @param sem_id the semaphore ID
 * @return 1 if semop call is successful, otherwise 0
 */
static int semaphore_p(int sem_id) {
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p failed\n");
        return (0);
    }
    return (1);
}

/**
 * This function sets the semop part of the sembuf structure to 1.
 * This acts as the "release" operation so that the semaphore becomes
 * available.
 *
 * @param sem_id the semaphore ID
 * @return 1 if semop call is successful, otherwise 0
 */
static int semaphore_v(int sem_id) {
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;

    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v failed\n");
        return (0);
    }
    return (1);
}

/**
 * This function makes a call to semctl using command IPC_RMID to remove
 * semaphore IDs
 */
static void del_semvalue(void){
    union semun sem_union;
    for(int i = 0; i < N_PROCESS-1; i++) {
        if (semctl(sem_id[i], 0, IPC_RMID, sem_union) == -1)
            fprintf(stderr, "Failed to delete semaphore\n");
    }
}
