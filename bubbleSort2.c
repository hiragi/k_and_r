#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sort[N];

void bubbleSort()
{
	int i, j, flag, k;

	k = 0;
	do{
		flag = 0;
		for(i=0; i<N-1-k; i++){
			if(sort[i] > sort[i+1]){
				flag = 1;
				j = sort[i];
				sort[i] = sort[i+1];
				sort[i+1] = j;
			}
		}
		k++;
	}while(flag == 1);
}

int main(void)
{
	int i;
	srand((unsigned int)time(NULL));

	printf("\n準備中\n");

	for(i=0; i<N; i++){
		sort[i] = rand() % 20;
		printf("%d ", sort[i]);
	}

	printf("\nソート開始\n");

	bubbleSort();

	printf("\nソート終了\n");

	for(i=0; i<N; i++){
		printf("%d ", sort[i]);
	}
	printf("\n");

	return 0;
}
