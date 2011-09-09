#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sort[N];

int compare(const void *arg1, const void *arg2)
{
	return (*((int *)arg1) - *((int *)arg2));
}

int main(void)
{
	int i;

	srand((unsigned int)time(NULL));

	printf("ソート準備\n");
	for(i=0; i<N; i++){
		sort[i] = rand() % 20;
		printf("%d ", sort[i]);
	}

	printf("ソート開始\n");

	qsort(sort, N, sizeof(sort[0]), compare);

	printf("ソート終了\n");

	for(i=0; i<N; i++){
		printf("%d ", sort[i]);
	}

	return EXIT_SUCCESS;
}
