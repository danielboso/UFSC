#ifndef SUDOKUN_H_
#define SUDOKUN_H_

#include <stdint.h>

uint8_t *read_grid();

void print_grid(uint8_t buffer[]);

void generate_matrix();

void destroy_matrix();

int update(int value, int option);

void insert_clues(uint8_t buffer[]);

void solve();

//void *thread_solve()

//bool valid();

#endif
