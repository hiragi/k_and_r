/* 配列からあふれるときに配列のサイズを大きくする */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(void)
{
	int buf, sum, count, n, size;
	int *array, *temp;

	/* 最初の配列のサイズは10 */
	size = 10;
	array = (int*)malloc(sizeof(int) * size);

	count = 0;
	do{
		printf("整数を入力してください(0:END)");
		scanf("%d", &buf);
		if(buf){
			array[count] = buf;
			count++;
			/* 配列が満杯になったら、倍の大きさに拡張する */
			if(count == size){
				/* 新しい大きなメモリブロックを確保して、
				 * 元の内容をコピー
				 * realloc() を使っても同様の作業が行われる */
				 temp = (int*)malloc(sizeof(int) * size * 2);
				 memcpy(temp, array, sizeof(int) * size);
				 free(array);
				 array = temp;
				 size *= 2;
			}
		}
	}while(buf != 0);

	/* 合計値を算出 */
	printf("--入力されたのは以下の数です。--\n");
	for(sum=n=0; n<count; n++){
		printf("%d\t", array[n]);
		sum += array[n];
	}
	printf("\n---\n以上の数の合計値は%dです。\n", sum);

	free(array);
	return 0;
}
