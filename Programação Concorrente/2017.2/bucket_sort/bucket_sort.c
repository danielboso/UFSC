
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "bucket_sort.h"
#include <mpi.h>

unsigned int tamvet;
unsigned int nbuckets;
unsigned int nprocs;
int flag_print;

int main(int argc, char** argv) {

	int size;
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(&size);
	MPI_Comm_rank(&rank);

// -----------------------------------------------------------------------------
// 		Mestre
// -----------------------------------------------------------------------------
	if(rank == 0) {

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

		int *vector = malloc(sizeof(int)*tamvet);
		generateVector(vector, tamvet);

		Bucket * buckets = malloc(sizeof(Bucket) * nbuckets);
		int bigger_number = vector[0];

		int i;

		for(i = 0; i < tamvet; i++) {
			if(vector[i] > bigger_number) {
				bigger_number = vector[i];
			}
		}

		for(i = 0; i < tamvet; i++) {
			int index = getIndexBucket(vector[i], bigger_number);
			if (index >= nbuckets) {
				index = nbuckets-1;
			}
			int size_bucket = buckets[index].size;
			buckets[index].bucket = realloc(buckets[index].bucket, sizeof(int) * (size_bucket+1));
			buckets[index].bucket[size_bucket] = vector[i];
			buckets[index].size++;
		}

		int * index_bucket_in_tamvet = malloc(sizeof(int)*nbuckets);
		int index = 0;
		for(i = 0; i < nbuckets; i++) {
			index_bucket_in_tamvet[i] = index;
			index += buckets[i].size;
			buckets[i].id = i;
		}

		int bucket_to_send = 0;
		int remaining_buckets = nbuckets;

		for(i = 1; i < size && remaining_buckets != 0; i++) {
			int * bucket = serializable_bucket(buckets[bucket_to_send]);

			MPI_Send();
			remaining_buckets--;
		}

		while(remaining_buckets != 0)  {

			remaining_buckets--;
		}

		// Pega os buckets e os coloca no vetor
		int j;
		for(i = 0; i < nbuckets; i++) {
			int index_bucket = index_bucket_in_tamvet[buckets[i].id];
			for(j = 0; j < buckets[i].size; j++) {
				if(buckets[i].size == 0) {
					continue;
				}
				vector[index_bucket] = buckets[i].bucket[j];
				index_bucket++;
			}
		}



		// ---------------------------------------------------------------------
		// 	A partir daqui, todas os bucket já devem estar ordenados e devolvidos
		// para o mestre.
		// ---------------------------------------------------------------------

		if(flag_print == 1) {
			printf("[");
			for(i = 0; i < tamvet; i++) {
				printf("%d ", vector[i]);
			}
			printf("]\n");
		}

		free(vector);
		free(buckets);

// -----------------------------------------------------------------------------
// 		Escravo
// -----------------------------------------------------------------------------
	} else { // Escravos

		qsort(buckets[i].bucket, buckets[i].size, sizeof(int), cmpfunc);
	}

	return 0;
}

void generateVector(int *vector, int tamvet) {
	int i;
	srand(time(NULL));
	for(i = 0; i < tamvet; i++) {
		vector[i] = rand() % tamvet;
	}
}

int getIndexBucket(int value, int bigger_number) {
	float itens_bucket = (float)bigger_number / (float)nbuckets;
	return value/itens_bucket;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int * serializable_bucket(Bucket * bucket) {
	int * bucket_serialized = malloc(sizeof(int)*(bucket.size + 2));
	bucket_serialized[0] = bucket.id;
	bucket_serialized[1] = bucket.size;
	int i;
	for(i = 0; i < bucket.size-1; i++) {
		bucket_serialized[i+2] = bucket[i];
	}
	return bucket_serialized;
}
