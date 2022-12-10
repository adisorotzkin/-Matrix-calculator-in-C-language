#include "mat.h"

void add_mat(matrix m1, matrix m2, matrix result){  
	int i,j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			result[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

void sub_mat(matrix m1, matrix m2, matrix result){ 
	int i,j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			result[i][j] = m1[i][j] - m2[i][j];
		}
	}
}

void mul_scalar(matrix m1, double scalar, matrix result){  
	int i,j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			result[i][j] = m1[i][j] * scalar;
		}
	}
}

void mul_mat(matrix m1, matrix m2, matrix result){ 
	int i,j,k;
	for (k = 0; k < SIZE; ++k) {
    	for (i = 0; i < SIZE; ++i) {
        	for (j = 0; j < SIZE; ++j) {
            	result[k][i] += m1[k][j] * m2[j][i];
         	}
      	}
	}
}
			
void trans_mat(matrix m1, matrix result){ 
	int i,j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			result[i][j] = m1[j][i];
		}
	}
}

