
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

	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

// -----------------------------------------------------------------------------
// 		Mestre
// -----------------------------------------------------------------------------
	if(rank == 0) {

		if(argc != 4) {
			printf("Número de parâmetros incorreto!\n");
			printf("Parâmetros:\n");
			printf("	Tamanho do vetor.\n");
			printf("	Número de buckets.\n");
			printf("	Imprimir? '0' para não imprimir e '1' para imprimir.\n");
			return 0;
		}

		tamvet = atoi(argv[1]);
		nbuckets = atoi(argv[2]);
		flag_print = atoi(argv[3]);

		int * vector = malloc(sizeof(int)*tamvet);
		generateVector(vector, tamvet);
		int bigger_number = vector[0];

		Bucket * buckets = malloc(sizeof(Bucket) * nbuckets);

		int i;
		for(i = 0; i < tamvet; i++) {
			if(vector[i] > bigger_number) {
				bigger_number = vector[i];
			}
		}

		int * index_bucket_in_tamvet = malloc(sizeof(int)*nbuckets);
		int index = 0;
		for(i = 0; i < nbuckets; i++) {
			index_bucket_in_tamvet[i] = index;
			index += buckets[i].size;
			buckets[i].id = i;
			buckets[i].size = 0;
			buckets[i].bucket = NULL;
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

		// Id do bucket que será enviado
		int id_bucket_to_send = 0;
		// Quantidade de buckets que ainda devem ser enviadas para os processos
		int amount_buckets_to_send = nbuckets;
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
		for(i = 1; i < nprocs && amount_buckets_to_send != 0; i++) {

			//int control[2];
			int * control = malloc(sizeof(int) *2);
			// -----------------------------------------------------------------
			// vetor control ---------------------------------------------------
			// 		Control[0] - id
			// 		Control[1] - size
			// -----------------------------------------------------------------
			control[0] = buckets[id_bucket_to_send].id;
			control[1] = buckets[id_bucket_to_send].size;

			// Envia a flag
			MPI_Send(&flag_continue_sending, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Message sent to process %d with flag %d\n", i, flag_continue_sending);

			// Envia dados de controle
			MPI_Send(control, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Message sent to process %d with bucket id %d \n", i, control[0]);
			printf("Message sent to process %d with bucket size %d\n", i, control[1]);

			// Envia vetor
			MPI_Send(buckets[id_bucket_to_send].bucket, control[1], MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Message sent to process %d with bucket \n", i);

			amount_buckets_to_send--;
			id_bucket_to_send++;
		}

		while(1) {
			// Reconstrói vetor de controle
			int * control = malloc(sizeof(int) * 2);

			MPI_Status status;

			MPI_Recv(control, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Message received from process %d with control id %d\n", status.MPI_SOURCE, control[0]);
			printf("Message received from process %d with contorl size%d\n", status.MPI_SOURCE, control[1]);

			fflush(stdout);
			MPI_Recv(buckets[control[0]].bucket, control[1], MPI_INT, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Message received from process %d with bucket \n", status.MPI_SOURCE);

			if(amount_buckets_to_send > 0) {
				printf("id_bucket_to_send %d\n", id_bucket_to_send);

				control[0] = buckets[id_bucket_to_send].id;
				control[1] = buckets[id_bucket_to_send].size;

				// Envia a flag
				MPI_Send(&flag_continue_sending, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
				printf("Message sent to process %d with flag %d\n", status.MPI_SOURCE, flag_continue_sending);

				// Envia dados de controle
				MPI_Send(control, 2, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
				printf("Message sent to process %d with bucket id %d\n", status.MPI_SOURCE, control[0]);
				printf("Message sent to process %d with bucket size %d\n", status.MPI_SOURCE, control[1]);

				// Envia vetor
				MPI_Send(buckets[id_bucket_to_send].bucket, control[1], MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
				printf("Message sent to process %d with bucket \n", status.MPI_SOURCE);

				amount_buckets_to_send--;
				id_bucket_to_send++;

			} else {
				// Manda mensagem para todos os processos pararem de aguardar mensagens
				flag_continue_sending = 0;
				MPI_Send(&flag_continue_sending, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
				break;
			}
			free(control);
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

		if(flag_print == 1) {
			printf("[");
			for(i = 0; i < tamvet; i++) {
				printf("%d ", vector[i]);
			}
			printf("]\n");
		}

		for(i = 0; i < nbuckets; i++) {
			free(buckets[i].bucket);
		}

		free(vector);
		free(buckets);
		free(index_bucket_in_tamvet);

	} else {

	// -------------------------------------------------------------------------
	// 		Escravo
	// -------------------------------------------------------------------------

		int flag_continue_receiving = 1;

		while(1) {

			// Atualiza valor da flag
			MPI_Recv(&flag_continue_receiving, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Message received from process 0 with flag %d\n", flag_continue_receiving);

			if(flag_continue_receiving == 1) {

				// Aloca espaço para o bucket
				int * control = (int *)malloc(sizeof(int) * 2);

				// -------------------------------------------------------------
				// vetor control -----------------------------------------------
				// 		Control[0] - id
				// 		Control[1] - size
				// -------------------------------------------------------------

				// Recebe variáveis de controle
				MPI_Recv(control, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("Message received from process %d with control id %d\n", 0, control[0]);
				printf("Message received from process %d with contorl size%d\n", 0, control[1]);

				// Realoca espaço para os elementos do bucket
				int * bucket = malloc(sizeof(int) * control[1]);

				// Recebe vetor
				MPI_Recv(bucket, control[1], MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("Message received from process %d with bucket \n", 0);
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//--------------------------------------------------------------
				//--------------------------------------------------------------

				// Ordena o vetor usando quick sort
				qsort(bucket, control[1], sizeof(int), cmpfunc);

				// Envia struct com variáveis de controle para o processo mestre
				MPI_Send(control, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);

				// Envia os elementos do bucket para o processo mestre
				MPI_Send(bucket, control[1], MPI_INT, 0, 0, MPI_COMM_WORLD);

				free(bucket);
				free(control);
			} else {
				printf("Escravo %d break\n", rank);
				fflush(stdout);
				break;
			}
		}
		printf("Processo escravo com rank %d terminou de executar while(1) \n", rank);
	}

	MPI_Finalize();

	printf("Processo %d finalizou\n", rank);
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
