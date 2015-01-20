/*
 * =====================================================================================
 *
 *       Filename:  inserSort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年01月16日 17时34分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gaoyuan, sishuiliunian0710@gmail.com
 *        Company:  Class 1204 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void insertSort(int array[], int length){
	int i, j;
	int key;

	for (j = 1; j < length; j++){
		key = array[j];
		i = j - 1;

		while (i >= 0 && array[i] > key){
			array[i + 1] = array[i];
			i--;
		}
		array[i + 1] = key;
	}
}
void merge(int *array, int p, int q, int r){
	int num1 = q - p + 1;
	int num2 = r - q;

	int *left = (int *)malloc(sizeof(int) * num1);
	int *right = (int *)malloc(sizeof(int) * num2);
	int i, j, k;
	
	printf("Before Merge start with %d middle is %d end with %d:", p, q, r);
	for (i = p; i <= r; i++){
		printf(" array[%d] %d  ", i, array[i]);
	}
	printf("\n");
	
	for (i = p; i < q + 1; i++){
		*(left + i - p) = array[i];
		printf("left[%d] = array[%d] = %d\n",i - p, i, array[i]);
	}
	for (j = q + 1; j <= r; j++){
		*(right + j - q - 1) = array[j];
		printf("right[%d] = array[%d] = %d\n", j - q - 1, j, array[j]);
	}
	i = j = 0;
	k = p;

	printf ("left[0] = %d, right[0] = %d\n", left[0], right[0]);
	while ((i < num1) && (j < num2)){
		printf ("cmp left[%d] %d right[%d] %d ", i,left[i], j, right[j]);
		if ((*(left + i)) < (*(right + j))){
			array[k++] = *(left + (i++));
		}
		else{
			array[k++] = *(right + (j++));
		}
		printf ("array[%d] = %d\n", k - 1, array[k - 1]);
	}
	while (i < num1){
		array[k++] = *(left + (i++));
	}
	while (j < num2){
		array[k++] = *(right + (j++));
	}

	printf("After Merge:");
	for (i = p; i <= r; i++){
		printf(" %d  ", array[i]);
	}
	printf("\n");
	

}

void mergeSort(int *array, int begin, int end){
	int i;


	if (begin < end){
		int middle = (begin + end) / 2;

		mergeSort(array, begin, middle);
		mergeSort(array, middle + 1, end);
		merge(array, begin, middle, end);
	}
}
int main(int argc, char *argv[])
{
	int array[10] = {15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
	int i;

	mergeSort(array, 0, 9);

	for(i = 0; i < 10; i++){
		printf("%d    ", array[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}

