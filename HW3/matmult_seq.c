/********************************************************
 * Sequential Matrix Multiplication
 * Author: Jerome Anaeki
 * Date : 10/17/2018
 *
 * This program implements matrix multiplication of square
 * matrices sequentially.
 *
 * compile string:
 * gcc matmult_seq.c -o matmult_seq
 *********************************************************/


#include <stdio.h>
#include <stdlib.h>

 
int main(int argc, char *argv[]){
	
	int n, i, j, k, populate;
  	int one[10][10], two[10][10], three[10][10];
 
 	n = atoi(argv[1]); // converts the string in argument to integer
 
 	/* Populates the first matrix */
	populate = 1; // initialized for first element
  	for (i = 0; i < n; i++){
  		for (j = 0; j < n; j++){
  			one[i][j] = populate; // assigns the elements in the first matrix
  			populate++; // increments the counter for the matrix elements
		}
	}
 
 	/* Populates the second matrix */
    populate = 1; // initialized for first element
  	for (i = 0; i < n; i++){
  		for (j = 0; j < n; j++){
  			two[i][j] = populate; // assigns the elements in the first matrix
  			populate++; // increments the counter for the matrix elements
		}
	}
 
 	/* Multiplies the first and second matrices */
    for (i = 0; i < n; i++){
      for (j = 0; j < n; j++){
      	three[i][j] = 0;
        for (k = 0; k < n; k++){
          three[i][j] += one[i][k]*two[k][j];
        }
      }
    }
    
    /* Displays the contents of the first matrix */
    for (i = 0; i < n; i++){
    	printf("|\t");
      for (j = 0; j < n; j++){
        printf("%d\t", one[i][j]);
		}
      printf("\t|\n\n");
    }
    
    printf("\t\t*\n\n");
	
	/* Displays the contents of the second matrix */
    for (i = 0; i < n; i++){
    	printf("|\t");
      for (j = 0; j < n; j++){
        printf("%d\t", two[i][j]);
		}
      printf("\t|\n\n");
    }
 
    printf("\t\t=\n\n");
 
 	/* Displays the contents of the resulting matrix */
    for (i = 0; i < n; i++){
    	printf("|\t");
      for (j = 0; j < n; j++){
        printf("%d\t", three[i][j]);
		}
      printf("\t|\n");
    }

	return 0;
}

