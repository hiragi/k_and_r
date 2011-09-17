/* エイト・クイーン問題 */
#include <stdio.h>
#include <stdlib.h>

int board[8][8];	/* チェスの盤面 */

/* (x, y)にクイーンをおけるかどうかをチェックする関数 */
int check(int x, int y){
	int p, q;
	/* 左方向にすでにクイーンがあるかどうかをチェック(右側には絶対に存在しない) */
	for(p=0; p<x; p++){
		if(board[p][y]==1){
			return 0;
		}
	}

	/* 左上方向をチェック */
	p = x; q = y;
	while(p > 0 && q > 0){
		if(board[--p][--q] == 1){
			return 0;
		}
	}

	/* 左下方向をチェック */
	p = x; q = y;
	while(p > 0 && q < 7){
		if(board[--p][++q] == 1){
			return 0;
		}
	}

	return 1;
}

/* 現在の盤面を表示 */
void showboard(void){
	int x, y;
	for(y=0; y<8; y++){
		for(x=0; x<8; x++){
			printf("%c ", board[x][y]? 'Q' : '.');
		}
		printf("\n");
	}
}

int solve(int x)
{
	int i;

	if(x == 8){	/* すべての列にクイーンをおけたら */
		return 1;	/* 成功 */
	}

	for(i=0; i<8; i++){
		if(check(x, i)){
			/*(x, i)にクイーンが置けたら、実際におく */
			board[x][i] = 1;
			/* 次の列に置く */
			if(solve(x+1)){			/* 次の列以降が成功なら */
				return 1;			/* この列も成功 */
			}else{					/* 次の列以降が失敗なら */
				board[x][i] = 0;	/* クイーンを置きなおす */
			}
		}
	}
	return 0;
}

int main(void){
	if(solve(0)){		/* 最初の列からスタート */
		showboard();
	}
	return 0;
}
