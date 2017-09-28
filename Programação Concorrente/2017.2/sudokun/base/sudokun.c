#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define MAX_n 8

// Variaveis globais do Sudoku
int size;
int size_squared;
int board_size;

int clues = 0;
int solution = 0;
int count = 0;

int **constrainted_elements;
int **constraint_matrix;

int *remaining_choices;
int *choosen_constraint;

// Variaveis das threads
struct Range {
  unsigned id;
  unsigned initial_range;
  unsigned final_range;
};

pthread_mutex_t mutex;

unsigned num_threads;

int least_choices;

int reference_row;

int vector_size;

int *current_column;

int main (int argc, char **argv) {

	pthread_mutex_init(&mutex, NULL);

    unsigned num_threads = atoi(argv[1]);

	printf("NUMTHREADS: %02d\n", num_threads);

	assert(scanf("%u", &size) == 1);
	assert (size <= MAX_n);

	size_squared = size * size;
	board_size = size_squared * size_squared;
	vector_size = board_size * 4;

	int *buffer;

	buffer = read_grid();

	generate_matrix();

	print_grid(buffer);

	solution = solve(buffer);

	printf("Soluções: %02d\n", solution);
	printf("Count: %02d\n", count);

	destroy_matrix();

	pthread_mutex_destroy(&mutex);

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

void generate_matrix() {	// Lookup table
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
	int min_index = size_squared + 1;

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
					if (--remaining_choices[index] < min_index) {
						min_index = index;
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

	return min_index;
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

	int number, c, cand = (size_squared+1);

	least_choices = size_squared + 1;

	remaining_choices = calloc(board_size * 4, sizeof(int));	// Para cada bloco, linha, coluna - quantas possibilidades resta
	choosen_constraint = calloc(board_size * size_squared, sizeof(int));

	for (index = 0; index < board_size * 4; ++index) remaining_choices[index] = size_squared;
	for (index = 0; index < board_size * size_squared; ++index) choosen_constraint[index] = 0;

	insert_clues(buffer);

	int current_row[board_size];
	current_column = calloc(board_size, sizeof(int));

	for (index = 0; index < board_size; ++index) {
		current_row[index] = -1;
		current_column[index] = -1;
	}

	struct Range vector_range[num_threads];
    pthread_t thread[num_threads];

	while(1) {
		while (i >= 0 && i < board_size - clues) {
			if (option == 1) {
				current_column[i] = cand;
				least_choices = remaining_choices[cand];

				if (least_choices > 1) {
					unsigned portion = vector_size / num_threads;

					for (int k = 0; k != num_threads; ++k) {
				      vector_range[k].initial_range = k * portion;
				      vector_range[k].final_range = vector_range[k].initial_range + portion;
				      if (k == (num_threads - 1)) vector_range[k].final_range = vector_size;
				      pthread_create(&thread[i],	NULL,	Thread_solve,	&vector_range[k]);
				    }
				    for (int k = 0; k != num_threads; ++k) {
				      pthread_join(thread[i],	NULL);
				    }
					// for (c = 0; c < board_size * 4; ++c) { // para cada uma das restrições
					// 	if (remaining_choices[c] < least_choices) { // se a restrição for menor que least_choices, pego ela pois é a facil de resolver
					// 		least_choices = remaining_choices[c];
					// 		current_column[i] = c; // choose the top constraint - min = 9 (inicialmente) e cc[i] = c (0 inicialmente)
					// 		if (least_choices <= 1) {
					// 			break;
					// 		}
					// 	}
					// }
				}
				if (least_choices == 0 || least_choices == (size_squared + 1)) {	// Se fora da faixa, backtrack
					current_row[i--] = option = -1;
				}
			}
			reference_row = current_column[i];
			if (option == -1 && current_row[i] >= 0) {
				update(constrainted_elements[c][current_row[i]], -1);
			}
			for (number = current_row[i] + 1; number < size_squared; ++number) {	// procura proximo numero disponivel
				if (choosen_constraint[constrainted_elements[reference_row][number]] == 0) {
					break;
				}
			}
			if (number < size_squared) { // Pega o proximo numero disponivel e tenta
				cand = update(constrainted_elements[reference_row][number], 1); // set the choice
				current_row[i++] = number; option = 1; // Como deu certo, a linha escolhida = linha testada e dir = 1
			} else {
				current_row[i--] = option = -1; // Volta pra linha anterior e backtrack
			}
		}
		if (i < 0) {
			break;
		}
		++solution;
		--i;
		option = -1;
	}

	free(current_column);
	free(choosen_constraint);
	free(remaining_choices);

	return solution;
}

void *Thread_solve(void *arg) {
	struct Range vector_r = *(struct Range*)arg;

	int least_choices_temp = least_choices;
	int i;
	for (i = vector_r.initial_range; i < vector_r.final_range; ++i) { // para cada uma das restrições
		if (remaining_choices[i] < least_choices) { // se a restrição for menor que least_choices, pego ela pois é a facil de resolver
			least_choices_temp = remaining_choices[i];
			current_column[i] = i;
			if (least_choices <= 1) {
				break;
			}
		}
	}
	pthread_mutex_lock(&mutex);
	if (remaining_choices[i] < least_choices) {
		least_choices = least_choices_temp;
		reference_row = i;
	}
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}
