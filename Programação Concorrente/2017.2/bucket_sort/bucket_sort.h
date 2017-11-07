
typedef struct bucket {
	int id;
	int size;
	int begin_range;
	int end_range;
	int * bucket;
} Bucket;

void generateVector(int *vector, int tamvet);

void inicialize_buckets(Bucket * buckets, int bigger_number);

int getIndexBucket(int value, int bigger_number);

int cmpfunc (const void * a, const void * b);
