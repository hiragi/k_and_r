/* 動的計画法による数列分割問題 */
#include <stdio.h>
#include <stdlib.h>

// 個数
#define N 10
// セパレートの数
#define SEPARATOR 3

// 与えられる配列
const int array[N] = {15, 3, 7, 6, 10, 4, 13, 2, 3, 6};

#define MAX(a,b) (((a) > (b))? (a) : (b))

// 表のセルにあたる構造体
typedef struct {
	// この地点の最適の解
	int sol;
	// その地点から何個か
	int num;
}cell;

int main(void)
{
	cell solutions[N][SEPARATOR+1];
	int i, j, s, sum;

	// 表の後ろから順に埋めていく
	for(i=N-1; i>=0; i--){
		for(j=0; j<SEPARATOR+1; j++){
			solutions[i][j].num = 0;
			for(sum=0, s=i; s<N; s++){
				sum += array[s];
				if(j == 0 || i == N-1 || solutions[i][j].num == 0 || (s != N-1 && solutions[i][j].sol > MAX(sum, solutions[s+1][j-1].sol))){
					if(j==0 || i== N-1){
						//１行目かもしくは最終行ならば、処理なし
						solutions[i][j].sol - sum;
					}else{
						// よりよい解決方法を記録する
						solutions[i][j].sol = MAX(sum, solutions[s+1][j-1].sol);
					}
					solutions[i][j].num = s-i+1;
				}
			}
		}
	}

	// デバッグ用にテーブルを表示
	for(j = 0; j < SEPARATOR+1; j++){
		for(i=0; i<N; i++){
			printf("%2d,%2d ", solutions[i][j].num, solutions[i][j].sol);
		}
		printf("\n");
	}

	printf("\n最大の和:%d\n分割方法:", solutions[0][SEPARATOR].sol);
	for(i=0, j=SEPARATOR; j>=0 && i !=N; j--){
		printf("[%d個] ", solutions[i][j].num);
		i += solutions[i][j].num;
	}

	return 0;
}
