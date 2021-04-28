/**
 * The header file for the filter file
 *
 * Author: Emma Boulay
 */

#ifndef FILTER_H
#define FILTER_H
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#if defined(__linux__)
union semun {
    int             val;            /* value for SETVAL */
    struct semid_ds *buf;           /* buffer for IPC_STAT & IPC_SET */
    unsigned short  *array;         /* array for GETALL & SETALL */
};
typedef union semun semun_t;
#endif

/* The size of the array to be filtered */
#define SIZE 7
/* The number of child processes */
#define N_PROCESS 3

static int set_semvalue(int sem_id);
static int semaphore_p(int sem_id);
static int semaphore_v(int sem_id);
static void del_semvalue(void);

static int sem_id[N_PROCESS-1];

/**
 * The shared data structure to hold the array and semaphore ids.
 */
struct shared_data_t {
    char B[SIZE];
};

#endif
