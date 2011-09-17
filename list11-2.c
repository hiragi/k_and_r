/* バックトラック法による数列分割問題 */
#include <stdio.h>
#include <stdlib.h>

/* 与えられた値と、その分割方法 */
#define N 10
#define SEPARATOR 3
int value[N] = {15, 3, 7, 6, 10, 4, 13, 2, 3, 6};
int sep_pos[SEPARATOR] = {0};

/* 最適な分割と、そのなかのグループの最大和 */
int best_sep_pos[SEPARATOR] = {0};
int best_sep_max_value = 9999;

/* 分割を実装する再帰関数 */
void separate(int pos, int num)
{
	int i, j, k, start, end, max;

	/* 新しい分割場所を設定 */
	sep_pos[num++] = pos;

	/* 分割がすべて決まったら */
	if(num == SEPARATOR){
		max = 0;

		/* 設定された分割で、最大のグループ和を算出する */
		for(i=0; i<=SEPARATOR; i++){
			start = (i==0)? 0 : sep_pos[i-1];
			end = (i == SEPARATOR)? N : sep_pos[i];
			k = 0;
			for(j = start; j < end; j++){
				k += value[j];
			}
			if(k>max){
				max = k;
			}
		}

		/* 最大のグループ和が保存されている和より小さければ */
		if(max < best_sep_max_value){
			/* 現在の分割を保存する */
			best_sep_max_value = max;
			for(i=0; i<SEPARATOR; i++){
				best_sep_pos[i] = sep_pos[i];
			}
		}
		return;
	}

	/* 次の分割場所を設定する */
	for(i=pos+1; i<N-SEPARATOR+num+1; i++){
		separate(i, num);
	}
}

int main(void)
{
	int i, j, start, end;

	/* 最初の分割場所を設定して再帰を呼び出す */
	for(i=0; i<N-SEPARATOR; i++){
		separate(i, 0);
	}

	/* 保存された分割場所を表示する */
	for(i=0; i<=SEPARATOR; i++){
		start = (i==0)? 0: best_sep_pos[i];
		end = (i == SEPARATOR)? N : best_sep_pos[i];
		for(j=start; j<end; j++){
			printf("%d ", value[j]);
		}
		if(end != N){
			printf("|");
		}
	}

	return 0;
}
