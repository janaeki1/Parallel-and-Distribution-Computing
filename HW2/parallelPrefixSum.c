/********************************************************
 * Parallel Prefix Sum Using PThreads
 * Author: Jerome Anaeki
 * Date : 09/30/2018
 *
 * This program computes prefix sum.
 *
 * compile string:
 * gcc -lpthread parallelPrefixSum.c -o parallelPrefixSum
 *
 * pthreads requires the addition of the -lpthreads switch
 *********************************************************/
 
 
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	
    int x[] = {3, 1, 4, 0, 2, 7, 5, 8}; //initialization of original array
	int length = sizeof(x) / sizeof(x[0]); //calculates length of array
    int i;
    int prefix[length];
    
    //Displays contents of original array
    printf("Original Array: ");
    for (i = 0; i < length; i++){
    	printf("%d ", x[i]);
	}
	printf("\n");
  
  	prefix[0] = x[0]; //sets the first element in the prefix array equal to the original array
  	
  	//Current element in original array is added to previous element in prefix array
    for (i = 1; i < length; i++){
    	prefix[i] = prefix[i-1] + x[i];
	}
	
	//Displays contents of prefix array
    printf("Prefix Sum: ");
    for (i = 0; i < length; i++){
    	printf("%d ", prefix[i]);
	} 
        
	return 0;      
} 

