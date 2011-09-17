/* テンパズル */
#include <stdio.h>
#include <stdlib.h>

/* make_numによって作られた4つの数字 */
char created_num[5];

/* make_rpnによって作られたrpn */
char created_rpn[8];

/* solveに使われる仮想分散構造体 */
typedef struct tagBUNSUU{
	int bunbo;
	int bunsi;
}BUNSUU;
BUNSUU stack_array[4];

/* スタックの上限は４ */
int stack_top = 0;

void stack_push(BUNSUU * value)
{
	/* スタックにBUNSUUをプッシュする */
	stack_array[stack_top].bunbo = value->bunbo;
	stack_array[stack_top].bunsi = value->bunsi;
	stack_top++;
}

void stack_pop(BUNSUU *ret)
{
	/* スタックからBUNSUUをとってくる */
	stack_top--;
	ret->bunbo = stack_array[stack_top].bunbo;
	ret->bunsi = stack_array[stack_top].bunsi;
	return;
}

int solve(void)
{
	int c;
	BUNSUU st1, st2;

	stack_top = 0;
	c = 0;
	while(created_rpn[c] != '\0'){
		if(created_rpn[c] >= '0' && created_rpn[c] <= '9'){
			/* 数字だった場合は、その数字をそのままスタックに入れる */
			st1.bunbo = 1;
			st1.bunsi = created_rpn[c] - '0';
			stack_push(&st1);
		}else{
			/* 数字でなかった場合は、スタックの上2つをとってきて演算する */
			stack_pop(&st1);
			stack_pop(&st2);
			if(created_rpn[c] == '+'){
				st2.bunsi = st2.bunsi * st1.bunbo + st1.bunsi * st2.bunbo;
				st2.bunbo = st1.bunbo * st2.bunbo;
				stack_push(&st2);
			}else if(created_rpn[c] == '-'){
				st2.bunsi = st2.bunsi * st1.bunbo - st1.bunsi * st2.bunbo;
				st2.bunbo = st1.bunbo * st2.bunbo;
				stack_push(&st2);
			}else if(created_rpn[c] == '*'){
				st2.bunsi = st2.bunsi * st1.bunsi;
				st2.bunbo = st1.bunbo * st2.bunbo;
				stack_push(&st2);
			}else if(created_rpn[c] == '/'){
				st2.bunsi = st2.bunsi * st1.bunbo;
				st2.bunbo = st2.bunbo * st1.bunsi;
				if(st2.bunbo == 0){
					/* 0で割り算してしまった */
					return 0;
				}
				stack_push(&st2);

			}
		}
		c++;
	}
	stack_pop(&st1);

	if(st1.bunbo * 10 == st1.bunsi){
		return 1;
	}

	return 0;
}

int make_rpn(int num, int exp)
{
	/* RPNを作成する再帰関数 */
	static int isused[4] = {0,0,0,0};
	int i;

	if(num+exp == 7){
		created_rpn[7] = '\0';
		if(solve()){
			return 1;
			/* 計算結果が０になれば、それ以後の再帰をとめる */
		}
		return 0;
	}else{
		if(num-exp >= 2){
			/* 数字が演算子より2つ以上多ければ、演算子を入れてもよい */
			created_rpn[num+exp] = '+';
			if(make_rpn(num, exp+1)){
				return 1;
			}
			created_rpn[num+exp] = '-';
			if(make_rpn(num, exp+1)){
				return 1;
			}
			created_rpn[num+exp] = '*';
			if(make_rpn(num, exp+1)){
				return 1;
			}
			created_rpn[num+exp] = '/';
			if(make_rpn(num, exp+1)){
				return 1;
			}
		}
		if(num <= 3){
			/* 数が3つ以下であれば、数をいれてもよい */
			for(i=0; i<4; i++){
				if(isused[i] == 0){
					isused[i] = 1;
					created_rpn[num+exp] = created_num[i];
					if(make_rpn(num+1, exp)){
						isused[i] = 0;
						return 1;
					}
					isused[i] = 0;
				}
			}
		}
	}
	return 0;
}

void make_num(int keta, int num)
{
	/* 数の組み合わせを作る再帰関数 */
	int i;
	if(keta == 4){
		created_num[4] = '\0';
		/* 数が4桁になったらRPNを作成する */
		if(make_rpn(0,0)){
			printf("%s:%s\n", created_num, created_rpn);
		}else{
			printf("%s:解けません\n", created_num);
		}
		return;
	}
	for(i=num; i<=9; i++){
		created_num[keta] = i + '0';
		make_num(keta+1, i);
	}
}

int main(void)
{
	make_num(0,0);
	return 0;
}

