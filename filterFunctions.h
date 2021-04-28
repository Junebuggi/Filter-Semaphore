/**
 * The header file for the filterFunctions program
 *
 * Author: Emma Boulay
 */
#ifndef FILTERFUNCTIONS_H
#define FILTERFUNCTIONS_H

void copyMatrix(char dest[SIZE], char src[SIZE]);
void printArray(char arr[SIZE], int length);
int isNumber(char a);
int compare(char a, char b);
void swap(char arr[], int index1, int index2);
int isFiltered(char arr[], int length);
void randomCharArray(char arr[], int length);


#endif
