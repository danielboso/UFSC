#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

int size;
uint16_t size_squared;
uint16_t board_size;

uint16_t clues = 0;
int solutions = 0;

uint16_t **constrainted_elements;
uint16_t **constraint_matrix;

int16_t *remaining_choices;
int16_t *choosen_constraint;


int main (int argc, char **argv) {
	int solution;

	assert(scanf("%u", &size) == 1);
	assert (size <= MAX_n);
	//size = 2;

	size_squared = size * size;
	board_size = size_squared * size_squared;

	int *buffer;

	buffer = read_grid();

	generate_matrix();

	solution = solve(buffer);

	printf("Soluções: %02d", solutions);

	print_grid(buffer);

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
	for (int i = 0; i < size_squared; i++) {
	for (int j = 0; j < size_squared; j++)
		printf("%02d ", buffer[i * size_squared + j]);

	printf("\n");
	}
}

void generate_matrix() {
	int row = 0;
	int i, j, k;
	int ce_size = 4 * board_size;
	int cm_size = board_size * size_squared;

	constrainted_elements = calloc(ce_size, sizeof(uint16_t*));
	constraint_matrix = calloc(cm_size, sizeof(uint16_t*));

	for (i = 0; i < ce_size; ++i) constrainted_elements[i] = calloc(size_squared, sizeof(uint16_t));
	for (i = 0; i < cm_size; ++i) constraint_matrix[i] = calloc(4, sizeof(uint16_t));

	for (i = 0; i < size_squared; ++i) {        // Para cada linha
		for (j = 0; j < size_squared; ++j) {      // Para cada coluna
			for (k = 0; k < size_squared; ++k) {    // Para cada numero possivel
				//printf("Linha: %03u -", row);
				constraint_matrix[row][0] = size_squared * i + j;                                          // celula
				constraint_matrix[row][1] = size_squared * (i/size*size + j/size) + k + board_size;   // caixa
				constraint_matrix[row][2] = size_squared * i + k + (board_size * 2);                       // linha
				constraint_matrix[row][3] = size_squared * j + k + (board_size * 3);                       // coluna
				/*printf(" %03u", constraint_matrix[row][0]);
				printf(" %03u", constraint_matrix[row][1]);
				printf(" %03u", constraint_matrix[row][2]);
				printf(" %03u\n", constraint_matrix[row][3]);*/
				++row;
			}
		}
	}
	//printf("\n");

	uint8_t temp_vector[board_size * 4];
	uint32_t end_range;
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
/*
	end_range = board_size * 4;
	for (row = 0; row < end_range; ++row) {
		printf("Linha: %03u -", row);
		for (constraint = 0; constraint < size_squared; ++constraint) {
			printf(" %03u", constrainted_elements[row][constraint]);
		}
		printf("\n");
	}*/

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
	uint8_t row;

	int constraint;
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
			uint16_t *p;
			for (neighbor = 0; neighbor < size_squared; ++size_squared) {   // Para cada vizinho do numero e.g. linha, coluna, caixa
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

void insert_clues(uint8_t buffer[]) {
	int i, j, number;

	for (i = 0; i < size_squared; ++i) {
		for (j = 0; j < size_squared; ++j) {
			if (buffer[i * size_squared + j] >= 1 && buffer[i * size_squared + j] <= size_squared) {  // Se o número esta dentro da faixa
				number = buffer[i * size_squared + j] - 1;
			} else {
				number = -1;
			}
			if (number >= 0) {
				update(i * size_squared + number, 1);
				++clues;
			}
		}
	}
}

int solve(uint8_t buffer[]) {
	int i = 0, index, option = 1;
	int solution = 0;

	int min = 10, r2 = 0, c, cand = 10<<16;

	remaining_choices = calloc(board_size * 4, sizeof(uint16_t));
	choosen_constraint = calloc(board_size * size_squared, sizeof(uint16_t));

	for (index = 0; index < board_size * 4; ++index) remaining_choices[index] = size_squared;
	for (index = 0; index < board_size * size_squared; ++index) choosen_constraint[index] = 0;

	//for (index = 0; index < board_size * 4; ++index) printf("SC=REMAININGCHOICES %d\n", remaining_choices[index]);

	insert_clues(buffer);

	int current_row[board_size];
	int current_collum[board_size];

	for (index = 0; index < board_size; ++index) {
		current_row[index] = -1;
		current_collum[index] = -1;
	}

	while(1) {
		while (i < board_size - clues) {
			if (option == 1) {
				printf("MIN %d\n", min);
				min = cand>>16;
				current_collum[i] = cand&0xffff;
				printf("MIN %d\n", min);
				printf("CAND %d\n", cand);
				printf("Current Col %d\n", current_collum[i]);
				if (min>1) {
					for (c = 0; c < (board_size*4); ++c) { // para cada uma das restrições
						printf("AQUIIII1\n");
						printf("C %d\n", c);
						printf("REMAINING CHOICES %d\n", remaining_choices[c]);
						if (remaining_choices[c] < min) { // se a restrição for menor que min, min = restrição
							printf("REMAINING CHOICES %d\n", remaining_choices[c]);
							min = remaining_choices[c];
							current_collum[i] = c; // choose the top constraint - min = 9 (inicialmente) e cc[i] = c (0 inicialmente)
							printf("AQUIIII2\n");
							if (min <= 1) {
								printf("AQUIIII3\n");
								break; // this is for acceleration; slower without this line - Se min for igual a 1 ja chegou onde queria
							}
						}
					}
				}
				if (min == 0 || min == size_squared+1) {
					printf("AQUIIII4\n");
					current_row[i--] = option = -1; // backtrack, pois sai da faixa 1~9
				}
			}
			printf("MIN %d\n", min);
			printf("Current Col %d\n", current_collum[i]);
			c = current_collum[i];
			if (option == -1 && current_row[i] >= 0) {
				update(constrainted_elements[c][current_row[i]], -1);
				printf("%d\n", current_row[i]);
			}
			printf("%d\n", current_collum[i]);

			for (r2 = current_row[i] + 1; r2 < size_squared; ++r2) {// search for the choice to make - pega o proximo numero disponivel
				printf("%d\n", current_row[i]);
				if (choosen_constraint[constrainted_elements[c][r2]] == 0) break; // found if the state equals 0
			}
			printf("AQUI\n");
			printf("%d\n", r2);

			if (r2 < size_squared) { // pega o proximo numero disponivel e tenta
				printf("AQUI\n");
				cand = update(constrainted_elements[c][r2], 1); // set the choice
				printf("AQUI\n");
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
