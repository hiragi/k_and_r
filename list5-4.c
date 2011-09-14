/* 3つ以上の整数の最大公約数を求めるプログラム */
#include <stdio.h>
#include <stdlib.h>

#define MAX 6
int N[MAX] = {98, 140, 84, 28, 42, 126};

int gcd(int a, int b){
	int i;
	for(i = a; i > 0; i--){
		if(a % i == 0 && b % i == 0){
			break;
		}
	}
	return i;
}

int multi_gcd(int n)
{
	/* n==1(数が２つしかない)の場合は、gcdを呼ぶ */
	if(n==1){
		return gcd(N[0], N[1]);
	}

	/* n > 1の場合は、N[n]と、N[0]..N[n-1]のgcdを呼び出す */
	return gcd(N[n], multi_gcd(n-1));
}

int main(void){
	printf("配列Nの最大公約数は%dです\n", multi_gcd(MAX-1));
	return 0;
}
