#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N		  (10)

int search(int x, int *a, int num){
	int n = 0, t;

	/* 最後の値を x に入れ替える(番兵) */
	t = a[num-1];
	a[num-1] = x;

	/* 目的の値を探す */
	while(a[n] != x){
		n++;
	}

	/* 配列の最後の値を元に戻す */
	a[num-1] = t;
	/* 一番最後以外で一致 */
	if(n < num-1){
		return n;
	}
	/* 一番最後で一致 */
	if (x == t){
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
		array[i] = rand() % 20;
		printf("[%d] : %d", i, array[i]);
	}

	printf("\n 何を探しますか\n");
	scanf("%d", &i);

	r = search(i, array, N);
	if(r == NOT_FOUND){
		printf("%dは見つかりませんでした\n", i);
	}else{
		printf("%d は %d 番目にありました\n", i, r+1);
	}

	return 0;
}
