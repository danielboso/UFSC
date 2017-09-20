		#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

int main (int argc, char **argv) {
	int size;
	assert(scanf("%d", &size) == 1);
	assert (size <= MAX_n);
	
	int buf_size = size * size * size * size;
	int buf[buf_size];

	for (int i = 0; i < buf_size; i++) {
		if (scanf("%d", &buf[i]) != 1) {
    		printf("error reading file (%d)\n", i);
      		exit(1);
  		}
  	}

	print_grid(buf, size);

	return 0;
}

int chek_row(int buf[], int row) {
	int i;
	int begin_row = row * MAX_n;
	int   end_row = begin_row + MAX_n;

	for(i = begin_row; i < end_row; i ++) {
		int j;
		for(j =  begin_row; i < end_row; j++) {

			if ( (buf[i] == buf[j])  && (i != j) ) {
				return 0;
			}
		}
	}
	return 1;
}

int check_column(int buf[], int column) {
	int i;
	int begin_column = column;
	int   end_column = MAX_n * column;

	for(i = begin_column; i < end_column; i ++) {
		int j;
		for(j = begin_column; i < end_column; j ++) {
			// Número fixo da coluna
			int position_fixed = i * MAX_n;

			// Posições a ser verificada se position_number_fixed é igual a position_to_verify
			int position_to_verify = i * j;

			int number_equal = (position_fixed == position_to_verify);

			if ( (buf[position_fixed] == buf[position_to_verify]) && number_equal) {
				return 0;
			}
		}
	}
	return 1;
}

int check_region(int buf[]) {

}

void print_grid(int buf[], int size) {
  int size_squared = size * size;

  for (int i = 0; i < size_squared; i++) {
    for (int j = 0; j < size_squared; j++)
      printf("%d ", buf[i * size_squared + j]);

    printf("\n");
  }
}
