#ifndef SUDOKUN_H_
#define SUDOKUN_H_

#include <stdint.h>

int *read_grid();

void print_grid(int buffer[]);

void generate_matrix();

void destroy_matrix();

int update(int value, int option);

void insert_clues(uint8_t buffer[]);

int solve();

//void *thread_solve();

int verify_row() {}

int verify_column() {}

int verify_grid() {}

//bool valid();

#endif
