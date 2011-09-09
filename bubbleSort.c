#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int sort[N];

void BubbleSort(void){
	int i, j, flag;

	do{
		flag = 0;
		for(i=0; i<N-1; i++){
			if(sort[i] > sort[i+1]){
				flag = 1;
				j = sort[i];
				sort[i] = sort[i+1];
				sort[i+1] = j;
			}
		}
	}while(flag == 1);
}

int main(void){
	int i;

	srand((unsigned int)time(NULL));

	printf("\nソート準備\n");
	for(i=0; i<N; i++){
		sort[i] = rand() % 20;
		printf("%d ", sort[i]);
	}


	printf("\nソート開始\n");

	BubbleSort();

	printf("\nソート終了\n");

	for(i=0; i<N; i++){
		printf("%d ", sort[i]);
	}

	return 0;
}
