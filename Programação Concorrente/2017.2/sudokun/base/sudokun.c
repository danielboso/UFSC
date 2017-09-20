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

bool verify_row(char* grid, int row) {
	int i;
	int begin_row = row * MAX_n;
	int   end_row = begin_row + MAX_n;

	for(i = begin_row; i < end_row; i ++) {

		for(j =  begin_row; i < end_row; j++) {

			if ( (grid[i] == grid[j])  && (i != j) ) {
				return false;
			}
		}
	}
	return true;
}

bool verify_column(char* grid, int column) {
	int i;
	int begin_column = column;
	int   end_column = MAX_n * column;

	for(i = begin_column; i < end_column; i ++) {

		for(j = begin_column; i < end_column; j ++) {
			// Número fixo da coluna
			int position_fixed = i * MAX_n;

			// Posições a ser verificada se position_number_fixed é igual a position_to_verify
			int position_to_verify = i * j;

			bool number_equal = (position_fixed == position_to_verify);

			if ( (grid[position_fixed] == grid[position_to_verify]) && number_equal) {
				return false;
			}
		}
	}
	return true;
}

int verify_grid(char* grid) {}

int count_soutions(char* matrix) {
}

void print_grid(int buf[], int size) {
  int size_squared = size * size;

  for (int i = 0; i < size_squared; i++) {
    for (int j = 0; j < size_squared; j++)
      printf("%d ", buf[i * size_squared + j]);

    printf("\n");
  }
}
