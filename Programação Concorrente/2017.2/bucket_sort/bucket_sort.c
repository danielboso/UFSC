
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
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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

		int * vector = malloc(sizeof(int)*tamvet);
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

		// Id do bucket que será enviado
		int id_bucket_to_send = 0;
		// Quantidade de buckets que ainda devem ser enviadas para os processos
		int buckets_to_send = nbuckets;
		// Quantidade de buckets que se deve ficar esperando receber dos processos escravos
		int buckets_to_receive = nbuckets;
		// Flag que indica se posso continuar mandando buckets
		// Processo recebe essa variável e a interpreta como se deve continuar esperando mais buckets
		int flag_continue_sending = 1;

		//----------------------------------------------------------------------
		// Flags ---------------------------------------------------------------
		// 0 : Indica que todos os buckets já foram computados
		// 1 : Indica que ainda falta buckets para serem computados
		//----------------------------------------------------------------------

		// For que distribui primeira "leva" de buckets
		for(i = 1; i < size && remaining_buckets != 0; i++) {
			if(remaining_buckets == 0) {
				flag_continue_sending = 0;
			}

			int control[2];
			// -----------------------------------------------------------------
			// vetor control ---------------------------------------------------
			// 		Control[0] - id
			// 		Control[1] - size
			// -----------------------------------------------------------------
			control[0] = buckets[bucket_to_send].id;
			control[1] = buckets[bucket_to_send].size;

			// Envia a flag
			MPI_Send(&flag_continue_sending, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

			// Envia dados de controle
			MPI_Send(&control, 2, MPI_INT, i, 0, MPI_COMM_WORLD);

			// Envia vetor
			MPI_Send(buckets[bucket_to_send].bucket, control[1], MPI_INT, i, 0, MPI_COMM_WORLD);

			remaining_buckets--;
			bucket_to_send++;
		}

		while(1) {

			// Reconstrói vetor de controle
			int control[2];

			MPI_Status status;

			MPI_Recv(&control, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			MPI_Recv(&buckets[control[0].bucket], MPI_INT, control[1], status.MPI_Source, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if(buckets_to_send > 0) {

				control[0] = buckets[bucket_to_send].id;
				control[1] = buckets[bucket_to_send].size;

				// Envia a flag
				MPI_Send(&flag_continue_sending, 1, MPI_INT, status.MPI_Source, 0, MPI_COMM_WORLD);

				// Envia dados de controle
				MPI_Send(&control, 2, MPI_INT, status.MPI_Source, 0, MPI_COMM_WORLD);

				// Envia vetor
				MPI_Send(buckets[bucket_to_send].bucket, control[1], MPI_INT, status.MPI_Source, 0, MPI_COMM_WORLD);

				remaining_buckets--;
				buckets_to_send++;

			} else {
				// Manda mensagem para todos os processos pararem de aguardar mensagens
				flag_continue_sending = 0;
				MPI_Send(&flag_continue_sending, 1, MPI_INT, status.MPI_Source, 0, MPI_COMM_WORLD);
			}
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

	} else {

	// -------------------------------------------------------------------------
	// 		Escravo
	// -------------------------------------------------------------------------

		int flag_continue_receiving;
		while (1) {

			// Atualiza valor da flag
			MPI_Recv(&flag_continue_receiving, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			if(continue_receiving == 1) {

				// Aloca espaço para o bucket
				int control[2];

				// -------------------------------------------------------------
				// vetor ontrol ------------------------------------------------
				// 		Control[0] - id
				// 		Control[1] - size
				// -------------------------------------------------------------

				// Recebe variáveis de controle
				MPI_Recv(&control, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				// Realoca espaço para os elementos do bucket
				int * bucket = malloc(sizeof(int) * control[1])

				// Recebe vetor
				MPI_Recv(bucket.bucket, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				// Ordena o vetor usando quick sort
				qsort(bucket, control[1], sizeof(int), cmpfunc);

				// Envia struct com variáveis de controle para o processo mestre
				MPI_Send(&control, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD);

				// Envia os elementos do bucket para o processo mestre
				MPI_Send(bucket, control[1], MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD);

				free(bucket);
			} else {
				break;
			}
		}

	}

	MPI_Finalize();

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
