/* ナップザック問題 */
#include <stdio.h>
#include <stdlib.h>

/* 商品の数と、それぞれの大きさ、価値 */
#define N 5
int size[N] = {2, 3, 5, 6, 9};
int value[N] = {2, 4, 7, 10, 14};

/* ナップザックの大きさ */
#define NAP_SIZE 16

int main(void)
{
	/* ナップザックの現時点での価値 */
	int nap_value[NAP_SIZE+1] = {0};
	int i, j, new_value;

	printf("ナップザックの大きさ:");
	for(i=1; i<NAP_SIZE+1; i++){
		printf("%3d", i);
	}
	printf("\n\n");

	/* 扱う品物を１つずつ増やしていく */
	for(i=0; i<N; i++){
		/* ナップザックの大きさがjのものに対して、品物i番を入れてみる */
		for(j = size[i]; j<NAP_SIZE+1; j++){
			/* 品物iを入れてみた場合、新しい価値はどう変わるか */
			new_value = nap_value[j-size[i]] + value[i];

			if(new_value > nap_value[j]){
				nap_value[j] = new_value;
			}
		}

		printf("	品物%dまで使う:", i+1);
		for(j=1; j<NAP_SIZE+1; j++){
			printf("%2d ", nap_value[j]);
		}
		printf("\n");
	}
	return 0;
}
