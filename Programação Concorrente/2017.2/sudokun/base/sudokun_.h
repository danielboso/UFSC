#ifndef SUDOKUN_H_
#define SUDOKUN_H_

int check_row(int buf[], int row);

int check_column(int buf[], int column);

int check_region(int buf[]);

void print_grid(int buf[], int size);

#endif
