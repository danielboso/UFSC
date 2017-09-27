#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

int size;
int size_squared;
int board_size;

int clues = 0;
int solution = 0;

int **constrainted_elements;
int **constraint_matrix;

int *remaining_choices;
int *choosen_constraint;


int main (int argc, char **argv) {

	assert(scanf("%u", &size) == 1);
	assert (size <= MAX_n);

	size_squared = size * size;
	board_size = size_squared * size_squared;

	int *buffer;

	buffer = read_grid();

	generate_matrix();

	print_grid(buffer);

	solution = solve(buffer);

	printf("Soluções: %02d", solution);

	destroy_matrix();

	free(buffer);

	return 0;
}

int *read_grid() {
	int *grid_buffer;

	grid_buffer = calloc(board_size, sizeof(int));

	int i;
	for (i = 0; i < board_size; i++) {
		if (scanf("%d", &grid_buffer[i]) != 1) {
			printf("error reading file (%d)\n", i);
			exit(1);
		}
	}

	return grid_buffer;
}

void print_grid(int buffer[]) {
	int i, index;
	for (i = 0; i < size_squared; i++) {
		for (int j = 0; j < size_squared; j++) {
			index = i * size_squared + j;
			printf("%02d ", buffer[i * size_squared + j]);
		}
	printf("\n");
	}
}

void generate_matrix() {
	int row = 0;
	int i, j, k;
	int ce_size = 4 * board_size;
	int cm_size = board_size * size_squared;

	constrainted_elements = calloc(ce_size, sizeof(int*));
	constraint_matrix = calloc(cm_size, sizeof(int*));

	for (i = 0; i < ce_size; ++i) constrainted_elements[i] = calloc(size_squared, sizeof(int));
	for (i = 0; i < cm_size; ++i) constraint_matrix[i] = calloc(4, sizeof(int));

	for (i = 0; i < size_squared; ++i) {        // Para cada linha
		for (j = 0; j < size_squared; ++j) {      // Para cada coluna
			for (k = 0; k < size_squared; ++k) {    // Para cada numero possivel
				constraint_matrix[row][0] = size_squared * i + j;                                          // celula
				constraint_matrix[row][1] = size_squared * (i/size*size + j/size) + k + board_size;   // caixa
				constraint_matrix[row][2] = size_squared * i + k + (board_size * 2);                       // linha
				constraint_matrix[row][3] = size_squared * j + k + (board_size * 3);                       // coluna
				++row;
			}
		}
	}

	int temp_vector[board_size * 4];
	int end_range;
	int temp;

	end_range = board_size * 4;
	for (i = 0; i < end_range; ++i) {
		temp_vector[i] = 0;
	}

	int constraint;
	end_range = board_size * size_squared;
	for (row = 0; row < end_range; ++row) {
		for (constraint = 0; constraint < 4; ++constraint) {
			temp = constraint_matrix[row][constraint];
			constrainted_elements[temp][temp_vector[temp]++] = row;
		}
	}

}

void destroy_matrix() {
	int ce_size = 4 * board_size;
	int cm_size = board_size * size_squared;

	int i;
	for (i = 0; i < ce_size; ++i) free(constrainted_elements[i]);
	for (i = 0; i < cm_size; ++i) free(constraint_matrix[i]);

	free(constraint_matrix);
	free(constrainted_elements);
}

int update(int value, int option) {  // Se option = 1 continua, se option = -1 backtracking
	int min_high = 10, min_low = 0;

	int constraint, row;
	for (constraint = 0; constraint < 4; ++constraint) remaining_choices[constraint_matrix[value][constraint]] += option<<7; // importante pra solve

	for (constraint = 0; constraint < 4; ++constraint) {  // Para cada restrição associada a value
		int neighbor, neighbor_constraint, constrainted = constraint_matrix[value][constraint];
	    if (option > 0) {   // Atualiza valor
	  		for (neighbor = 0; neighbor < size_squared; ++neighbor) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
	    		row = constrainted_elements[constrainted][neighbor];
		        if (choosen_constraint[row]++ != 0) {
		        	continue;
		        }

				for (neighbor_constraint = 0; neighbor_constraint < 4; ++neighbor_constraint) {
					int index = constraint_matrix[row][neighbor_constraint];
					if (--remaining_choices[index] < min_high) {
						min_high = remaining_choices[index];
						min_low = index;
					}
				}
			}
	    } else {          // Desfaz modificações
			const int *p;
			for (neighbor = 0; neighbor < size_squared; ++neighbor) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
				row = constrainted_elements[constrainted][neighbor];
				if (--choosen_constraint[row] != 0) {
					continue;
				}
				p = constraint_matrix[row];
				++remaining_choices[p[0]];
				++remaining_choices[p[1]];
				++remaining_choices[p[2]];
				++remaining_choices[p[3]];
			}
		}
	}

	return min_high << 16 | min_low;
}

void insert_clues(int buffer[]) {
	int i, j, index, number;

	for (i = 0; i < board_size; ++i) {
		if (buffer[i] >= 1 && buffer[i] <= size_squared) {  // Se o número esta dentro da faixa
			number = buffer[i] - 1;
		} else {
			number = -1;
		}
		if (number >= 0) {
			update(i * size_squared + number, 1);
			++clues;
		}
	}
}

int solve(int buffer[]) {
	int i = 0, index, option = 1;
	int solution = 0;

	int min = 10, r2 = 0, c, cand = 10<<16;

	remaining_choices = calloc(board_size * 4, sizeof(int));
	choosen_constraint = calloc(board_size * size_squared, sizeof(int));

	for (index = 0; index < board_size * 4; ++index) remaining_choices[index] = size_squared;
	for (index = 0; index < board_size * size_squared; ++index) choosen_constraint[index] = 0;

	insert_clues(buffer);

	int current_row[board_size];
	int current_column[board_size];

	for (index = 0; index < board_size; ++index) {
		current_row[index] = -1;
		current_column[index] = -1;
	}

	while(1) {
		while (i >= 0 && i < board_size - clues) {
			if (option == 1) {

				min = cand>>16;
				current_column[i] = cand&0xffff;
				if (min>1) {
					for (c = 0; c < (board_size*4); ++c) { // para cada uma das restrições
						if (remaining_choices[c] < min) { // se a restrição for menor que min, min = restrição
							min = remaining_choices[c];
							current_column[i] = c; // choose the top constraint - min = 9 (inicialmente) e cc[i] = c (0 inicialmente)
							if (min <= 1) {
								break; // this is for acceleration; slower without this line - Se min for igual a 1 ja chegou onde queria
							}
						}
					}
				}
				if (min == 0 || min == (size_squared+1)) {
					current_row[i--] = option = -1; // backtrack, pois sai da faixa 1~9
				}
			}
			c = current_column[i];
			if (option == -1 && current_row[i] >= 0) {
				update(constrainted_elements[c][current_row[i]], -1);
			}

			for (r2 = current_row[i] + 1; r2 < size_squared; ++r2) {// search for the choice to make - pega o proximo numero disponivel
				if (choosen_constraint[constrainted_elements[c][r2]] == 0) {
					break; // found if the state equals 0
				}
			}

			if (r2 < size_squared) { // pega o proximo numero disponivel e tenta
				cand = update(constrainted_elements[c][r2], 1); // set the choice
				current_row[i++] = r2; option = 1; // moving forward - como deu certo, a linha escolhida = linha testada e dir = 1
			} else current_row[i--] = option = -1; // backtrack - volta pra linha anterior e backtrack
		}
		if (i < 0) {
			break;
		}
		++solution;
		--i;
		option = -1;
	}

	free(choosen_constraint);
	free(remaining_choices);

	return solution;
}

/*void *thread_solve() {
	// recursive
	// escolhe o menor numero possivel
	// loop: se for valido testa e tenta colocar o numero
	// se for invalido e for o ultimo da backtrack
}*/

/*bool valid() {

}*/
