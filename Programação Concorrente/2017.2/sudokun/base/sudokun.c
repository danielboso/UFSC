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
	int valid = 1;

	int constraint, row;
	for (constraint = 0; constraint < 4; ++constraint) {  // Para cada restrição associada a value
		int neighbor, neighbor_constraint, constrainted = constraint_matrix[value][constraint];
	    if (option > 0) {   // Atualiza valor
	  		for (neighbor = 0; neighbor < size_squared; ++neighbor) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
	    		row = constrainted_elements[constrainted][neighbor];
		        if (choosen_constraint[row]++ != 0) {
		        	continue;
		        }
				valid &= 1;
			}
	    } else {          // Desfaz modificações
			for (neighbor = 0; neighbor < size_squared; ++neighbor) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
				row = constrainted_elements[constrainted][neighbor];
				if (--choosen_constraint[row] != 0) {
					continue;
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

	int min = size_squared + 1, r2 = 0, c, cand = (size_squared+1)<<16;

	remaining_choices = calloc(board_size * 4, sizeof(int));
	choosen_constraint = calloc(board_size * size_squared, sizeof(int));

	for (index = 0; index < board_size * 4; ++index) remaining_choices[index] = size_squared;
	for (index = 0; index < board_size * size_squared; ++index) choosen_constraint[index] = 0;

	insert_clues(buffer);

	// int current_row[board_size];
	// int current_column[board_size];
	//
	// for (index = 0; index < board_size; ++index) {
	// 	current_row[index] = -1;
	// 	current_column[index] = -1;
	// }

	int testoutudo[board_size*size_squared];
	int current_row = 0;

	while(1) {
		while (1) {
			for(i = current_row; i < board_size*size_squared; ++i) { // procura primeiro numero/posicao disponivel
				if (testoutudo[i] == 0) break;
			}
			if (update(i, 1) == 1) {

			} else {

			}
		}
		// ++solution;
		// --i;
		// option = -1;
	}

	free(choosen_constraint);
	free(remaining_choices);

	return solution;
}

/*void *thread_solve() {
	// escolhe o menor numero possivel
	array de posicao cada uma guardando os numeros possiveis
	se existe numeros possiveis pode tentar ainda
	tenta colocar um valor, caso de certo adiciona no array e prossegue
	tenta colocar e faz o teste de forma paralela
	ao final verifica se ta tudo certo e avança
	//preciso saber que passei por todas as possibilidades;
	int testoutudo[board_size*size_squared];
	while (1) {
		for(i = 0; i < board_size*size_squared; ++i) { // procura primeiro numero/posicao disponivel
			if (testoutudo[i] == 0) break;
		}
		if (update(i, 1) == 1) {

		} else {

		}
	}
	// quando uma das threads voltar em recursão ele pode chamar mais threads com o numero da solução
	// loop: se for valido testa e tenta colocar o numero
	// se for invalido e for o ultimo da backtrack
}*/

int valid_position(int value) {
	int valid = 1;

	int constraint, row;
	for (constraint = 0; constraint < 4; ++constraint) {  // Para cada restrição associada a value
		int neighbor, neighbor_constraint, constrainted = constraint_matrix[value][constraint];
		for (neighbor = 0; neighbor < size_squared; ++neighbor) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
			row = constrainted_elements[constrainted][neighbor];
			if (choosen_constraint[row] == 0) {
				valid &= 1;
			} else {
				valid &= 0;
			}
		}
	}

	return valid;
}
