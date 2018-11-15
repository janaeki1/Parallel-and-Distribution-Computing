/***************************************************************
 * Sequential Matrix Multiplication (using Cannon's Algorithm)
 * Author: Jerome Anaeki
 * Date : 10/21/2018
 *
 * This program implements matrix multiplication of square
 * matrices sequentially using Cannon's Algorithm.
 *
 * compile string:
 * gcc canmatmult_seq.c -o canmatmult_seq
 ****************************************************************/


#include <stdio.h>
#include <stdlib.h>

 
int main(int argc, char *argv[]){
	
	int n, i, j, k, m, populate;
	int one[10][10], two[10][10], three[10][10];
  	int temp[10];
 
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
    
    printf("Original:\n");
    
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
      printf("\t|\n\n");
    }
    printf("\n");
    
    
    /**Executes Cannon's Algorithm**/
    
    // Skews the first matrix
    for(i = 0; i < n; i++) {
   		temp[i] = one[i][0];
   		temp[i+1] = one[i][1];
   		temp[i+2] = one[i][2];
   		temp[i+3] = one[i][3];
   		temp[i+4] = one[i][4];
   		temp[i+5] = one[i][5];
      for(j = 0; j < n - 1; j++) {
		  one[i][j] = one[i][j+i];
      }
      one[i][n-i] = temp[i];
      one[i][n-i+1] = temp[i+1];
      one[i][n-i+2] = temp[i+2];
      one[i][n-i+3] = temp[i+3];
      one[i][n-i+4] = temp[i+4];
      one[i][n-i+5] = temp[i+5];
    }

	// Skews the second matrix
	for(j = 0; j < n; j++) {
   		temp[j] = two[0][j];
   		temp[j+1] = two[1][j];
   		temp[j+2] = two[2][j];
   		temp[j+3] = two[3][j];
   		temp[j+4] = two[4][j];
   		temp[j+5] = two[5][j];
      for(i = 0; i < n - 1; i++) {
		  two[i][j] = two[i+j][j];
      }
      two[n-j][j] = temp[j];
      two[n-j+1][j] = temp[j+1];
      two[n-j+2][j] = temp[j+2];
      two[n-j+3][j] = temp[j+3];
      two[n-j+4][j] = temp[j+4];
      two[n-j+5][j] = temp[j+5];
    }
    
    printf("Skewed:\n");
    
    /* Displays the contents of the first skewed matrix */
    for (i = 0; i < n; i++){
    	printf("|\t");
      for (j = 0; j < n; j++){
        printf("%d\t", one[i][j]);
		}
      printf("\t|\n\n");
    }
    
    printf("\t\t*\n\n");
	
	/* Displays the contents of the second skewed matrix */
    for (i = 0; i < n; i++){
    	printf("|\t");
      for (j = 0; j < n; j++){
        printf("%d\t", two[i][j]);
		}
      printf("\t|\n\n");
    }
    
    for (k = 0; k < n - 1; k++){
	    /* Multiplies the first and second matrices */
	    for (i = 0; i < n; i++){
	      for (j = 0; j < n; j++){
	      	three[i][j] = 0;
	        for (m = 0; m < n; m++){
	          three[i][j] += one[i][m]*two[m][j];
	        }
	      }
	    }
	 
	 	/* Displays the contents of the resulting matrix */
	 	printf("\t\t=\n\n");
	 	
	    for (i = 0; i < n; i++){
	    	printf("|\t");
	      for (j = 0; j < n; j++){
	        printf("%d\t", three[i][j]);
			}
	      printf("\t|\n\n");
	    }   
	    printf("\n");
	    
	    /* Shifts the first matrix */
	    for(i = 0; i < n; i++) {
	   		temp[i] = one[i][0];
	      for(j = 0; j < n - 1; j++) {
			  one[i][j] = one[i][j+1];
	      }
	      one[i][n-1] = temp[i];
	    }
		
		/* Shifts the second matrix */
		for(j = 0; j < n; j++) {
	   		temp[j] = two[0][j];
	      for(i = 0; i < n - 1; i++) {
			  two[i][j] = two[i+1][j];
	      }
	      two[n-1][j] = temp[j];
	    }
	    
	    printf("shifted (k=%d):\n", k+1);
		
		/* Displays the contents of the first shifted matrix */
	    for (i = 0; i < n; i++){
	    	printf("|\t");
	      for (j = 0; j < n; j++){
	        printf("%d\t", one[i][j]);
			}
	      printf("\t|\n\n");
	    }
	    
	    printf("\t\t*\n\n");
		
		/* Displays the contents of the second shifted matrix */
	    for (i = 0; i < n; i++){
	    	printf("|\t");
	      for (j = 0; j < n; j++){
	        printf("%d\t", two[i][j]);
			}
	      printf("\t|\n\n");
	    }
	}
	/* Displays the contents of the resulting matrix */
	 	printf("\t\t=\n\n");
	 	
	    for (i = 0; i < n; i++){
	    	printf("|\t");
	      for (j = 0; j < n; j++){
	        printf("%d\t", three[i][j]);
			}
	      printf("\t|\n\n");
	    }   
	    printf("\n");

	return 0;
}

