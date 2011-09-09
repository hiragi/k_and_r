#include <stdio.h>

#define MAX_DATA 10

int temp[MAX_DATA];					/* 最小でも配列と同じサイズの領域が必要 */

void MergeSort(int x[], int left, int right);
void main(void);

/* 配列 x[] の left から right の要素のマージソートをおこなう */
void MergeSort(int x[], int left, int right)
{
	int mid, i, j, k;

	if(left >= right){				/* 配列の要素が１つなら */
		return;						/* 何もしないでもどる */
	}
	
	/* ここより分割 */
	mid = (left + right) / 2;		/* 中央の値より */
	MergeSort(x, left, mid);		/* 左を再帰呼び出し */
	MergeSort(x, mid+1, right);		/* 右を再帰呼び出し */

	/* x[left] から x[mid] を作業領域にコピー */
	for(i=left; i<= mid; i++){
		temp[i] = x[i];
	}

	/* x[mid+1] から x[right] は逆順にコピー */
	for(i=mid+1, j=right; i<=right; i++, j--){
		temp[i] = x[i];
	}

	i = left;						/* i と j は作業領域のデータを */
	j = right;						/* k は配列の要素をさしている */

	for(k=left; k<=right; k++){
		if(temp[i] <= temp[j])
			x[k] = temp[i++];
		else
			x[k] = temp[j--];
	}
}

void main(void)
{
	int i;
	int x[] = {9, 4, 6, 2, 1, 8, 0, 3, 7, 5};

	printf("ソート前\n");
	for(i=0; i<MAX_DATA; i++){
		printf("%d ", x[i]);
	}

	printf("ソート開始\n");

	MergeSort(x, 0, MAX_DATA);

	printf("ソート終了\n");
	for(i=0; i<MAX_DATA; i++){
		printf("%d ", x[i]);
	}
	printf("\n");
}
