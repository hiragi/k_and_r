#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N		  (10)

int linear_search(int x, int *a, int num)
{
	int n = 0;

	/* 配列の範囲内で目的の値を探す */
	while(n < num && a[n] != x){
		n++;
	}

	if(n < num){
		return n;
	}

	return NOT_FOUND;
}

int main(void)
{
	int i, r, array[N];

	srand((unsigned int)time(NULL));

	printf("array");
	for(i=0; i<N; i++){
		printf("[%d]:%d", i, array[i]=rand()%20);
	}

	printf("\n何を探しますか:");
	scanf("%d", &i);

	r = linear_search(i, array, N);

	if(r == NOT_FOUND){
		printf("%dは見つかりません\n", i);
	}else{
		printf("%dは%d番目です。\n", i, r+1);
	}

	return EXIT_SUCCESS;
}
