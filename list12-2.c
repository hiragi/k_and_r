/* 4つの数からすべての数式を作り出すプログラム */

#include <stdio.h>
#include <stdlib.h>

/* 与えられた数 */
char number[] = "1234";
char created_num[8];

void make_rpn(int num, int exp)
{
	static int isused[4] = {0, 0, 0, 0};
	/* RPNを作成する再帰関数 */
	int i;

	if(num+exp == 7){
		/* 全体で７文字あれば表示 */
		created_num[7] = '\0';
		printf("%s\n", created_num);
		return;
	}else{
		if(num - exp >= 2){
			/* 数字が演算子より２つ以上多ければ、演算子を入れても良い */
			created_num[num+exp] = '+';
			make_rpn(num, exp+1);
			created_num[num+exp] = '-';
			make_rpn(num, exp+1);
			created_num[num+exp] = '*';
			make_rpn(num, exp+1);
			created_num[num+exp] = '/';
			make_rpn(num, exp+1);
		}
		if(num <= 3){
			/* 数が３つ以下であれば、数をいれてもよい */
			for(i=0; i<4; i++){
				if(isused[i] == 0){
					isused[i] = 1;
					created_num[num+exp] = number[i];
					make_rpn(num+1, exp);
					isused[i] = 0;
				}
			}
		}
	}
}

int main(void)
{
	make_rpn(0, 0);
	return 0;
}
