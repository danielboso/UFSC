
#include <stdlib.h>
#include <stdio.h>
#include "bucket_sort.h"

unsigned int tamvet;
unsigned int nbuckets;
unsigned int nprocs;
int flag_print;

void generateVector(int *vector, int tamvet) {
	int i;
	int j = tamvet-1;

	for(i = 0; i < tamvet; i++) {
		vector[i] = j;
		j--;
	}
}

int getIndexBucket(int value) {
	float itens_bucket = (float)tamvet / (float)nbuckets;
	return value/itens_bucket;
}

int main(int argc, char** argv) {

	if(argc != 5) {
		printf("Número de parâmetros incorreto!\n");
		printf("Parâmetros:\n");
		printf("	Tamanho do vetor.\n");
		printf("	Número de buckets.\n");
		printf("	Número de processos.\n");
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

	// Imprime vetor a ser
	//for(i = 0; i < tamvet; i++) {
	//	printf("vector[%d] = %d \n", i, vector[i]);
	//}

	// ------ teste ------------------------------------------------------------
	//for(i = 0; i < tamvet; i++) {
	//	printf("Elemento %d irá para o bucket %d \n", vector[i], getIndexBucket(vector[i]));
	//}
	// ------ teste ------------------------------------------------------------

	Bucket * buckets = malloc(sizeof(Bucket) * nbuckets);

	for(i = 0; i < tamvet; i++) {
		int index = getIndexBucket(vector[i]);
		int size_bucket = buckets[index].size;
		buckets[index].bucket = realloc(buckets[index].bucket, sizeof(int) * (size_bucket+1));

		buckets[index].bucket[size_bucket] = vector[i];
		//printf("elemento %d entrou no bucket %d \n", vector[i], index);
		buckets[index].size++;
	}

	// ------ teste ------------------------------------------------------------
	//int j;
	//for(i = 0; i < nbuckets; i++) {
	//	for(j = 0; j < buckets[i].size; j++) {
	//		printf("Bucket %d, elemento %d.\n", i, buckets[i].bucket[j]);
	//	}
	//}
	// ------ teste ------------------------------------------------------------

	int * index_bucket_in_tamvet = malloc(sizeof(int)*nbuckets);
	int index = 0;
	for(i = 0; i < nbuckets; i++) {
		index_bucket_in_tamvet[i] = index;
		index += buckets[i].size;
	}

	for(i = 0; i < nbuckets; i++) {
		qsort(buckets[i].bucket, buckets[i].size, sizeof(int), cmpfunc);
	}

	// ------ teste ------------------------------------------------------------
	int j;
	for(i = 0; i < nbuckets; i++) {
		int index_bucket = index_bucket_in_tamvet[buckets[i].index];
		for(j = 0; j < buckets[i].size; j++) {
			vector[index_bucket] = buckets[i].bucket[j];
			index_bucket++;
		}
	}
	// ------ teste ------------------------------------------------------------

	// ------ teste ------------------------------------------------------------
	//for(i = 0; i < nbuckets; i++) {
	//	printf("Bucket %d começa na posição %d \n", i, index_bucket_in_tamvet[i]);
	//}
	// ------ teste ------------------------------------------------------------

	// O programa irá distribuir os buckets para os computadores os ordenem.
	//

	if(flag_print == 1) {
		printf("[");
		for(i = 0; i < tamvet; i++) {
			printf("%d ", vector[i]);
		}
		printf("]\n");
	}

	free(vector);
	free(buckets);

	return 0;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void inicialize_buckets(Bucket * buckets) {
	/* CRIAÇÃO DADOS DAS STRUCTS */

	int interval_numbers_bucket = tamvet / nprocs;
	int remaining_elements = tamvet % nprocs;

	int begin = 0;
	if(remaining_elements == 0) {
	  	int i;
	  	for(i = 0; i < nbuckets; i++) {
			//buckets[i].index = i;
			buckets[i].bucket = malloc(sizeof(int));
			buckets[i].size = 0;
			buckets[i].begin_range = begin;
			buckets[i].end_range = begin + interval_numbers_bucket;
			begin += interval_numbers_bucket;
	  	}

	} else {
	  	int i;
	  	for(i = 0; i < nbuckets; i++) {
			//buckets[i].index = i;
			buckets[i].bucket = malloc(sizeof(int));
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
