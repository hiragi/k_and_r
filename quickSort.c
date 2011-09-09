#include <stdio.h>

void QSort(int x[], int left, int right);
void Swap(int x[], int i, int j);
void ShowData(int x[], int i);
void main(void);

/* start QuickSort */
void QSort(int x[], int left, int right)
{
	int i, j;
	int pivot;

	i = left;							/* ソートする配列の一番小さい要素の添え字 */
	j = right;							/* ソートする配列の一番大きな要素の添え字 */

	pivot = x[(left+right) / 2];		/* 基準値を配列の中央付近に取る */

	while(1){
		while(x[i] < pivot)				/* pivot より大きい値が出るまで */
			i++;						/* 増加 */

		while (pivot < x[j])			/* pivotより小さい値が出るまで */
			j--;						/* 減少させる */

		if(i >= j)						/* i >= j なら */
			break;						/* 無限ループから出る */

		Swap(x, i, j);					/* x[i] と x[j] を交換 */
		i++;							/* 次のデータ */
		j--;
	}
	ShowData(x, 10);					/* 途中経過を表示 */

	if (left < i-1)						/* 基準値の左に2以上要素があれば */
		QSort(x, left, i-1);			/* 左の配列を Qsort */
	if (j+1 < right)					/* 基準値の右に2以上要素があれば */
		QSort(x, j+1, right);			/* 右の配列を QSort */
}

void Swap(int x[], int i, int j)
{
	int temp;
	temp = x[i];
	x[i] = x[j];
	x[j] = temp;
}

void ShowData(int x[], int n)
{
	int i;

	for(i=0; i<n; i++){
		printf("%d ", x[i]);
	}
	printf("\n");
}

void main(void)
{
	int x[] = {6, 3, 1, 7, 0, 4, 8, 5, 2, 9};
	int n = 10;

	printf("ソート前\n");
	ShowData(x, n);

	printf("ソート中\n");
	QSort(x, 0, n-1);

	printf("ソート後\n");
	ShowData(x, n);
}
