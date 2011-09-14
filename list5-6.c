/* 開き直り数を列挙するプログラム */
#include <stdio.h>
#include <stdlib.h>

/* 0-9 のべき乗を1度だけ計算して、下記の配列に結果を格納しておく。 (CheckNumber()関数のなかで仕様) */
unsigned long power[10] = {0};

/* 現在使用している数字群の個数 */
int number_using[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* numberのなかに、digit(0-9の1桁の整数)が何文字あるかを数える関数 */
int NumOfDigit(unsigned long number, unsigned long digit){
	int ret;
	ret = 0;

	/* 0桁ならば0を返す(何も含まれて居ない) */
	if(number == 0){
		return 0;
	}

	/* 1の位が digit であるかどうかのチェック */
	if(number % 10 == digit){
		ret = 1;	/* digit であれば、返り値に１つ足す */
	}

	/* 10で割ることによって次の桁移行のチェックを再帰的に行う */
	ret += NumOfDigit(number/10, digit);

	return ret;
}

void CheckNumber(void)
{
	/* 数字群を元に計算した結果の数字の個数が */
	/* 元の数字群と同じだけ使われているかどうかのチェック */
	/* 0は考慮しない */
	int i;
	unsigned long result;
	result = 0;

	/* 数字群を元に、計算結果を作成する */
	for(i=1; i<=9; i++){
		result += power[i] * number_using[i];
	}

	/* 計算結果の中の数字の個数が、数字群と同じかどうかチェックする */
	for(i=1; i<=9; i++){
		if(NumOfDigit(result, i) != number_using[i]){
			return;	/* １つでも違えば、それは解ではない */
		}
	}
	printf("%lu \n", result); /* 計算結果は、解である */
	return;
}

void MakeNumbers(int start, int kosuu)
{
	int i;

	/* 10桁を超えた数字に開き直り数は存在しない */
	if(kosuu > 10){
		return;
	}

	/* start-9 までの数を新たに生成する */
	for(i=start; i<=9; i++){
		/* 新しい数を末尾に追加する */
		number_using[i]++;
		/* それが開き直り数になるかどうかのチェック */
		CheckNumber();
		/* 追加した数の後ろにさらに1桁追加した場合を調べる */
		MakeNumbers(i, kosuu+1);
		/* 先ほど追加した数を消す */
		number_using[i]--;
	}
}

int main(void)
{
	unsigned long i, j, k;
	/* あらかじめべき乗数を計算して、power配列に保存する */
	/* 0の０乗は0なので、1から9まで計算すればよい */
	for(i=1; i<=9; i++){
		k = 1;
		for(j=0; j<i; j++){
			k *= i;
		}
		power[i] = k;
	}

	/* 1を1つ使うという条件からはじめる */
	MakeNumbers(1, 1);

	return 0;
}
