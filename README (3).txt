Assignment 2: Shared Memory and Semaphores
Name: Emma Boulay
Student Number: 101073617

Set-Up Instructions:
1. Extract the archived files in 101073617_Assignment2.tar.gz
	$ tar -xvzf 101073617_Assignment2.tar.gz
2. Run the makefile to compile:
	$ make
3. Run the program with hardcoded dataset 1 :
	$ ./FILTER
4. To run the program with hardcoded dataset 2
	$ ./FILTER data2
5. To run the program with random char array use the -r option:
	$ ./FILTER -r
6. To run the program with user inputed data set use the -u option:
	$ ./FILTER -u

/********** Discussion of Test Results ***********/
The output for both my test data and the given test data is given below. Through 
examining the output statements it can be seen that there is a slight time delay 
between each fork as the statement is “Process P0: No swapping” is printed multiple 
times until the other child processes are created. It can also be seen that after a 
process has released a lock it may be the next one to get the lock next. To make this 
more fair each process that wants to get a lock must enter a waiting queue where a
priority order can be determined. However using the concurrent processes, the 
character array is VERY quickly filtered and displayed to the user.

/********** Output for test data set 1 ***********/
Memory attached at 0x10a610000
Would you like to run in debug mode? yes/no: yes

The unsorted character array: 
[5, A, 9, M, W, 6, Z]

Process P0 is swapping 5 at 0 with A at 1
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P1 is swapping 9 at 2 with M at 3
Process P0: No swapping
Process P1 is swapping 9 at 3 with W at 4
Process P0 is swapping 5 at 1 with M at 2
Process P1 is swapping 5 at 2 with W at 3
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P2 is swapping 9 at 4 with 6 at 5
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P2 is swapping 9 at 5 with Z at 6
Process P0: No swapping
Process P2 is swapping 6 at 4 with Z at 5
Process P0: No swapping
Process P1: No swapping
Process P2: No swapping
Process P0: No swapping
Process P1 is swapping 5 at 3 with Z at 4
Process P2: No swapping
Process P0: No swapping

The sorted character array: 
[A, M, W, Z, 5, 6, 9]
Detaching and deleting shared memory

/********** Output for test data set 1 ***********/
Memory attached at 0x10904d000
Would you like to run in debug mode? yes/no: yes

The unsorted character array: 
[1, 2, 3, C, D, E, F]

Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P1 is swapping 3 at 2 with C at 3
Process P0: No swapping
Process P1 is swapping 3 at 3 with D at 4
Process P0 is swapping 2 at 1 with C at 2
Process P1 is swapping 2 at 2 with D at 3
Process P0 is swapping 1 at 0 with C at 1
Process P1: No swapping
Process P0 is swapping 1 at 1 with D at 2
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P2 is swapping 3 at 4 with E at 5
Process P0: No swapping
Process P1: No swapping
Process P2 is swapping 3 at 5 with F at 6
Process P0: No swapping
Process P1 is swapping 2 at 3 with E at 4
Process P2 is swapping 2 at 4 with F at 5
Process P1 is swapping 1 at 2 with E at 3
Process P0: No swapping
Process P1 is swapping 1 at 3 with F at 4
Process P2: No swapping
Process P0: No swapping

The sorted character array: 
[C, D, E, F, 1, 2, 3]
Detaching and deleting shared memory

/********** Output for my random test data ***********/
Memory attached at 0x10aae1000
Would you like to run in debug mode? yes/no: yes

The unsorted character array: 
[L, W, 9, X, G, Y, X]

Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P0: No swapping
Process P1 is swapping 9 at 2 with X at 3
Process P0: No swapping
Process P1 is swapping 9 at 3 with G at 4
Process P0: No swapping
Process P1 is swapping X at 2 with G at 3
Process P0: No swapping
Process P1: No swapping
Process P0 is swapping W at 1 with G at 2
Process P1: No swapping
Process P0 is swapping L at 0 with G at 1
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P1: No swapping
Process P0: No swapping
Process P2 is swapping 9 at 4 with Y at 5
Process P1: No swapping
Process P2 is swapping 9 at 5 with X at 6
Process P1: No swapping
Process P0: No swapping
Process P2 is swapping Y at 4 with X at 5
Process P1: No swapping
Process P0: No swapping

The sorted character array: 
[G, L, W, X, X, Y, 9]
Detaching and deleting shared memory
