/* The MIT License
   Copyright (c) 2011 by Attractive Chaos <attractor@live.co.uk>
   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:
   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

// This file implements an improved algorithm of Guenter Stertenbrink's suexco.c
// (http://magictour.free.fr/suexco.txt).

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/* For Sudoku, there are size_squaredxsize_squaredxsize_squared=board_size*size_squared possible choices (size_squared numbers to choose for
   each cell in a size_squaredxsize_squared grid), and 4xsize_squaredxsize_squared=board_size*4 constraints with each constraint
   representing a set of choices that are mutually conflictive with each other.
   The board_size*4 constraints are classified into 4 categories:
   1. row-column where each cell contains only one number
   2. box-number where each number appears only once in one sizexsize box
   size. row-number where each number appears only once in one row
   4. col-number where each number appears only once in one column
   Each category consists of board_size constraints. We number these constraints from 0
   to size2size. In this program, for example, constraint 0 requires that the (0,0)
   cell contains only one number; constraint board_size requires that number 1 appears
   only once in the upper-left sizexsize box; constraint 162 requires that number 1
   appears only once in row 1; constraint 24size requires that number 1 appears
   only once in column 1.

   Noting that a constraint is a subset of choices, we may represent a
   constraint with a binary vector of board_size*size_squared elements. Thus we have a board_size*size_squaredxboard_size*4
   binary matrix M with M(r,c)=1 indicating the constraint c involves choice r.
   Solving a Sudoku is reduced to finding a subset of choices such that no
   choices are present in the same constaint. This is equivalent to finding the
   minimal subset of choices intersecting all constraints, a minimum hitting
   set problem or a eqivalence of the exact cover problem.
   The board_size*size_squaredxboard_size*4 binary matrix is a sparse matrix, with each row containing 4
   non-zero elements and each column size_squared non-zero elements. In practical
   implementation, we store the coordinate of non-zero elements instead of
   the binary matrix itself. We use a binary row vector to indicate the
   constraints that have not been used and use a column vector to keep the
   number of times a choice has been forbidden. When we set a choice, we will
   use up 4 constraints and forbid other choices in the 4 constraints. When we
   make wrong choices, we will find an unused constraint with all choices
   forbidden, in which case, we have to backtrack to make new choices. Once we
   understand what the board_size*size_squaredxboard_size*4 matrix represents, the backtracking algorithm
   itself is easy.
   A major difference between the algorithm implemented here and Guenter
   Stertenbrink's suexco.c lies in how to count the number of the available
   choices for each constraint. Suexco.c computes the count with a loop, while
   the algorithm here keeps the count in an array. The latter is a little more
   complex to implement as we have to keep the counts synchronized all the time,
   but it is 50-100% faster, depending on the input.
 */

// the sparse representation of the binary matrix


int size = 4;
int size_squared = 16;
int board_size = 256;

typedef struct {
	uint16_t r[1024][16]; // M(r[c][i], c) is a non-zero element
	uint16_t c[4096][4]; // M(r, c[r][j]) is a non-zero element
} sdaux_t;



// generate the sparse representation of the binary matrix
sdaux_t *sd_genmat()
{
	sdaux_t *a;
	int i, j, k, r, c, c2, r2;
	int8_t nr[board_size*4];
	a = calloc(1, sizeof(sdaux_t)); // aloca memoria e enche as posições com 0
	for (i = r = 0; i < size_squared; ++i) // generate c[board_size*size_squared][4]
		for (j = 0; j < size_squared; ++j) {
			for (k = 0; k < size_squared; ++k) { // this "size_squared" means each cell has size_squared possible numbers
				a->c[r][0] = size_squared * i + j;                  // row-column constraint
				a->c[r][1] = size_squared * (i/size*size + j/size) + k + board_size; // box-number constraint
				a->c[r][2] = size_squared * i + k + board_size*2;            // row-number constraint
				a->c[r][3] = size_squared * j + k + board_size*3;            // col-number constraint
				++r;
			}
		}
	for (c = 0; c < board_size*4; ++c) nr[c] = 0;
	for (r = 0; r < board_size*size_squared; ++r) { // generate r[][] from c[][]
		for (c2 = 0; c2 < 4; ++c2) {
			k = a->c[r][c2];	// Pega o valor de uma das restrições 0, board_size, 162, 24size
			a->r[k][nr[k]++] = r;
		}
	}
	return a;
}
// update the state vectors when we pick up choice r = numero de 0 a 8 + tamanho da linha(size_squared) * posição da celula; v=1 for setting choice; v=-1 for reverting
static inline int sd_update(const sdaux_t *aux, int8_t sr[], uint8_t sc[], int r, int v)
{
	int c2, min = size_squared+1, min_c = 0;

	for (c2 = 0; c2 < 4; ++c2) sc[aux->c[r][c2]] += v<<7; //

	for (c2 = 0; c2 < 4; ++c2) { // update # available choices
		int r2, rr, cc2, c = aux->c[r][c2]; // c = cada uma das 4 restrições
		if (v > 0) { // move forward
			for (r2 = 0; r2 < size_squared; ++r2) { // passa por cada celula que possivelmente pode conflitar
				//rr = aux->r[c][r2];
				if (sr[rr = aux->r[c][r2]]++ != 0) continue; // atualiza status da linha

				for (cc2 = 0; cc2 < 4; ++cc2) {
					int cc = aux->c[rr][cc2];
					if (--sc[cc] < min) {	// update # allowed choices
						min = sc[cc];
						min_c = cc; // register the minimum number
					}
				}
			}
		} else { // revert
			const uint16_t *p;
			for (r2 = 0; r2 < size_squared; ++r2) {
				if (--sr[rr = aux->r[c][r2]] != 0) continue; // update the row status

				p = aux->c[rr];
				++sc[p[0]];
				++sc[p[1]];
				++sc[p[2]];
				++sc[p[3]]; // update the count array
			}
		}
	}
	return min<<16 | min_c; // return the col that has been modified and with the minimal available choices
}
// solve a Sudoku; _s is the standard dot/number representation
int sd_solve(const sdaux_t *aux, int _s[])
{
	int i, j, r, c, r2, dir, cand, n = 0, min, hints = 0; // dir=1: forward; dir=-1: backtrack
	int8_t sr[board_size*size_squared]; // sr[r]: # times the row is forbidden by others
	int8_t cr[board_size];  // cr[i]: row chosen at step i - linha atualmente escolhida
	int16_t cc[board_size]; // cc[i]: col chosen at step i - coluna atualmente escolhida
	uint8_t sc[board_size*4]; // bit 1-7: # allowed choices; bit 8: the constraint has been used or not

	//char out[82];
	for (r = 0; r < board_size*size_squared; ++r) sr[r] = 0; // no row is forbidden
	//for (r = 0; r < board_size*size_squared; ++r) printf("Linha: %d - %d\n", r, sr[r]);
	for (c = 0; c < board_size*4; ++c) sc[c] = 0<<7|size_squared; // size_squared allowed choices; no constraint has been used - pode ser substituido por size_squared - cada restrição diminui esse numero até q se tenha um possivel
	//for (r = 0; r < board_size*4; ++r) printf("Linha: %d - %d\n", r, sc[r]);


	for (i = 0; i < board_size; ++i) {	// Passando pela tabela size_squaredxsize_squared e atualizando caso tenha valores
		int a;// = _s[i] >= '1' && _s[i] <= 'size_squared'? _s[i] - '1' : -1; // Se encontrar algum numero na tabela diminui em um pra deixar no padrao 0~8, senao fica -1
		if (_s[i] >= 1 && _s[i] <= size_squared) {
			a = _s[i] - 1;
		} else {
			a =-1;
		}
		if (a >= 0) sd_update(aux, sr, sc, i * size_squared + a, 1); // Caso tenha algo na posição insere na tabela
		if (a >= 0) ++hints; // Caso tenha algo na posição diminui o total de numeros possiveis
		cr[i] = cc[i] = -1;// out[i] = _s[i];	// Caso não tenha nada enche com -1
		//printf("%d \n", a);
	}
	for (int index = 0; index < 10; ++index) printf("SC[] linha %03d: %03d\n", index, sr[index]);
	//for (r = 0; r < board_size; ++r) printf("Linha: %d - %d\n", r, cr[r]);
	//for (r = 0; r < board_size; ++r) printf("Linha: %d - %d\n", r, cc[r]);
	printf("BOARD: %d\n", board_size);
	//for (int index = 0; index < board_size*size_squared; ++index) printf("SC[] linha %03d: %03d\n", index, sr[index]);

	for (i = 0, dir = 1, cand = (size_squared+1)<<16|0/*, out[board_size] = 0*/;;) {
		while (i >= 0 && i < board_size - hints) { // maximum board_size-hints steps - Verifica tabuleiro espaço total menos o preenchimento
			if (dir == 1) {	// se 1 continua , -1 backtrack
				min = cand>>16, cc[i] = cand&0xffff;	// Operação sobre mascara deixando apenas o valor do 16 menos significativos min = 10 e cc[i] = 0
				if (min > 1) { // Sempre entra uma vez, pois min > 0
					for (c = 0; c < board_size*4; ++c) { // para cada uma das restrições
						if (sc[c] < min) { // se a restrição for menor que min, min = restrição
							min = sc[c];
							cc[i] = c; // choose the top constraint - min = size_squared (inicialmente) e cc[i] = c (0 inicialmente)
							if (min <= 1) break; // this is for acceleration; slower without this line - Se min for igual a 1 ja chegou onde queria
						}
					}
				}
				if (min == 0 || min == (size_squared+1)) cr[i--] = dir = -1; // backtrack, pois sai da faixa 1~size_squared
			}
			c = cc[i];
			if (dir == -1 && cr[i] >= 0) { // Backtracking, desfaz a escolha
				sd_update(aux, sr, sc, aux->r[c][cr[i]], -1);
			}

			for (r2 = cr[i] + 1; r2 < size_squared; ++r2) {// search for the choice to make - pega o proximo numero disponivel
				if (sr[aux->r[c][r2]] == 0) break; // found if the state equals 0
			}
			if (r2 < size_squared) { // pega o proximo numero disponivel e tenta
				cand = sd_update(aux, sr, sc, aux->r[c][r2], 1); // set the choice
				cr[i++] = r2; dir = 1; // moving forward - como deu certo, a linha escolhida = linha testada e dir = 1
			} else cr[i--] = dir = -1; // backtrack - volta pra linha anterior e backtrack
		}
		if (i < 0) break;
		//for (j = 0; j < i; ++j) r = aux->r[cc[j]][cr[j]], out[r/size_squared] = r%size_squared + '1'; // print
		//puts(out);
		//printf("%d\n", hints);
		++n; --i; dir = -1; // backtrack
	}
	//for (r = 0; r < board_size*4; ++r) printf("Linha: %d - %d\n", r, sc[r]);
	//for (r = 0; r < board_size*size_squared; ++r) printf("Linha: %d - %d\n", r, sr[r]);
	//for (r = 0; r < board_size; ++r) printf("Linha: %d - %d\n", r, cc[r]);
	//for (r = 0; r < board_size; ++r) printf("Linha: %d - %d\n", r, cr[r]);
	//printf("AQU6DEPOIS\n");
	return n; // return the number of solutions
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
int size;
int main()
{
	assert(scanf("%u", &size) == 1);
	assert (size <= 8);

	sdaux_t *a = sd_genmat();
	int solutions = 0;

	int *buffer;
	buffer = read_grid();

	solutions = sd_solve(a, buffer);
	printf("Solutions (%d)\n", solutions);
	free(a);

	return 0;
}
