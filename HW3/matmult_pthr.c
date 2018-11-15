/********************************************************
 * Parallel Matrix Multiplication
 * Author: Jerome Anaeki
 * Date : 10/17/2018
 *
 * This program implements matrix multiplication of square
 * matrices in parallel using pthreads.
 *
 * compile string:
 * gcc -lpthread matmult_pthr.c -o matmult_pthr
 *
 * pthreads requires the addition of the -lpthread switch
 *********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int one[10][10], two[10][10], three[10][10];

/* Populates the matrices */
void popMatrix(int mat[10][10], int n){
	int i, j;
	int populate = 1; // initialized for first element
  	for (i = 0; i < n; i++){
  		for (j = 0; j < n; j++){
  			mat[i][j] = populate; // assigns the elements in the first matrix
  			populate++; // increments the counter for the matrix elements
		}
	}
}

struct position {
   int row;
   int column;
};

int main(int argc, char *argv[]) {

   int n, i, j, checkVar;
   
   n = atoi(argv[1]); // converts the string in argument to integer
   
	/* Multiplies the first and second matrices */
	void *multiply(void *param) {
   		struct position *info = param;
   		int i, sum = 0;

   		for(i = 0; i< n; i++){
      		sum += one[info->row][i] * two[i][info->column];
   		}
   		three[info->row][info->column] = sum;
   		
	   	pthread_exit(0);
	}
   
   popMatrix(one, n); // Populates the first matrix
   popMatrix(two, n); // Populates the second matrix
   
   for(i = 0; i < n; i++) {
      for(j = 0; j < n; j++) {
         struct position *info = (struct position *) malloc(sizeof(struct position));
         info->row = i;
         info->column = j;
         pthread_t id;
         checkVar = pthread_create(&id,NULL,multiply,info);
         if(checkVar){
         	printf("ERROR. Code returned: %d\n", checkVar);
		 }
         pthread_join(id, NULL);
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
      
}

