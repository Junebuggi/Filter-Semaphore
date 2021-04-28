#include <sys/time.h>
#include "FILTER.h"
#include "filterFunctions.h"

/**
 * The filterFunctions file contains helpful functions to complete the assignment.
 * It contains functions to compare and swap characters and to print the array.
 *
 * Author: Emma Boulay
 * Student Number: 101073617
 */

/**
 * This function copies each element of the src matrix into the
 * dest matrix
 * @param dest The matrix to hold the copy of src
 * @param src The matrix to be copied
 */
void copyMatrix(char dest[SIZE], char src[SIZE]){
    for(int i = 0; i < SIZE; i++){
        dest[i] = src[i];
    }
}

/**
 * This function will print a character array in the proper format
 *
 * @param arr The array to be printed
 * @param length The length of the array
 */
void printArray(char arr[SIZE], int length){
    printf("[");
    for(int i = 0; i < length-1; i++){
        printf("%c, ", arr[i]);
    }
    printf("%c]\n", arr[length-1]);
}

/**
 * This function swaps two variables in an array
 *
 * @param arr The array to be manipulated
 * @param index1 the index of the first element
 * @param index2 the index of the second element
 */
void swap(char arr[], int index1, int index2){
    char temp = arr[index2]; //
    arr[index2] = arr[index1];
    arr[index1] = temp;
    return;
}

/**
 * This function checks if the array is filtered
 *
 * @param arr The array to be computed on
 * @param length The length of the array
 * @return 0 if the array is not filtered, 1 if the array is filtered
 */
int isFiltered(char arr[], int length){
    for(int i = 0; i < length-1; i++){
        if(compare(arr[i], arr[i+1]) == -1){ //If arr[i] > arr[i+1] the array is not filtered
            return 0;
        }
    }
    return 1; //The array is filtered :)
}

/**
 * This function compares two characters to determine which one is larger.
 * It also accounts for integers, as an integer will go after a letter. If
 * the function returns -1, than the two characters should be swapped. This function's
 * logic is based on the integer representation of ASCII characters.
 * @param a
 * @param b
 * @return 0 if the same, 1 if a > b, and -1 if a < b
 */
int compare(char a, char b){
    if(a == b)
        return 0;
    else if(isNumber(a)) { //If a is a number
        if (isNumber(b)) { //If b is also a number
            if (a < b) {
                return 1;
            } else
                return -1;
        } else //b is a letter than and greater than a
            return -1;
    } else {  //a is a letter
        if (isNumber(b))
            return 1;
        else { //b is a letter
            if (a < b)
                return 1;
            else
                return -1;
        }
    }
}

/**
 * This function fills the array with random alpha-numeric characters
 *
 * @param arr The array to be randomized
 * @param length The length of the array
 */
void randomCharArray(char arr[], int length){
    srand(time(0));
    for(int i = 0; i < length; i++){
        arr[i] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"[rand() % 36];
    }
}

/**
 * This function checks if the characters is a number
 *
 * @param a The character
 * @return 1 if a number, 0 otherwise
 */
int isNumber(char a){
    if(a >= 48 && a <= 57)
        return 1;
    else
        return 0;
}