
#include <stdlib.h>
#include <stdio.h>
#include "bucket_sort.h"

unsigned int tamvet;
unsigned int nbuckets;
unsigned int nprocs;
int flag_print;

void generateVector(int *vector, int tamvet) {
	int i;
	int j = tamvet;

	for(i = 0; i < tamvet; i++) {
		vector[i] = j;
		j--;
	}
}

int getIndexBucket(int value) {
	return value/(tamvet/nbuckets);
}

int main(int argc, char** argv) {

	if(argc != 5) {
		printf("Número de parâmetros incorreto!\n");
		printf("Parâmetros:\n");
		printf("	Tamanho do vetor.\n");
		printf("	Número de buckets.\n");
		printf("	Imprimir? '0' para não imprimir e '1' para imprimir.\n");
		return 0;
	}

	tamvet = atoi(argv[1]);
	nbuckets = atoi(argv[2]);
	nprocs = atoi(argv[3]);
	flag_print = atoi(argv[4]);

	// ------ teste ------------------------------------------------------------
	printf("tamvet %d\n", tamvet);
	printf("nbuckets %d\n", nbuckets);
	printf("nprocs %d\n", nprocs);
	printf("flag_imprimir %d\n", flag_print);

	int *vector = malloc(sizeof(int)*tamvet);
	generateVector(vector, tamvet);

	int i;
	for(i = 0; i < tamvet; i++) {
		printf("vector[%d] = %d \n", i, vector[i]);
	}

	for(i = 0; i < tamvet; i++) {
		printf("Elemento %d irá para o bucket %d \n", vector[i], getIndexBucket(vector[i]));
	}

	// CREATE BUCKETS
	struct Bucket ** buckets;
	for(i = 0; i < nbuckets; i++) {
		Bucket *bucket;
		buckets[i] = bucket;
	}

	for(i = 0; i < tamvet; i++) {
		int index = getIndexBucket(vector[i]);
		int size_bucket = &&buckets[index].size;
		printf("size_bucket: %d\n", size_bucket);
		buckets[index]->bucket[size_bucket] = vector[i];
		buckets[index]->size++;
	}

	int j;
	for(i = 0; i < nbuckets; i++) {
		for(j = 0; j < buckets[i]->size; j++) {
			printf("Bucket %d, elemento %d.\n", i, buckets[i]->bucket[j]);
		}
	}
	// ------ teste ------------------------------------------------------------

	return 0;
}

void inicialize_buckets(Bucket buckets[]) {
	/* CRIAÇÃO DADOS DAS STRUCTS */

	int interval_numbers_bucket = tamvet / nprocs;
	int remaining_elements = tamvet % nprocs;

	int begin = 0;
	if(remaining_elements == 0) {
	  int i;
	  for(i = 0; i < nbuckets; i++) {

		buckets[i].size = 0;
		buckets[i].begin_range = begin;
		buckets[i].end_range = begin + interval_numbers_bucket;
		begin += interval_numbers_bucket;

	  }

	} else {
	  int i;
	  for(i = 0; i < nbuckets; i++) {
		buckets[i].size = 0;
		if((nprocs - remaining_elements-1) < i) {

		  buckets[i].begin_range = begin;
		  buckets[i].end_range = begin + interval_numbers_bucket+1;
		  begin += interval_numbers_bucket+1;

		} else {

		  buckets[i].begin_range = begin;
		  buckets[i].end_range = begin + interval_numbers_bucket;
		  begin += interval_numbers_bucket;

		}
	  }
	}
}
