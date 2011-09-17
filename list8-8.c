/* 方程式の解を求める */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* 解析したい関数 */
double func(double x)
{
	return x * x * x * x * x - 10.0 * x * x * x * x + 25.0 * x * x * x + 40.0 * x * x + 200.0 * x - 500.0;

}

/* 2文探索法(バイナリサーチ) */
double BinarySearch(void)
{
	double left, mid, right, epsilon;

	/*
	* 答えに非常に近いという範囲を定義する。
	* この値をいろいろとかえることで、答えの精度を調節できる。
	* ちなみに、あまり小さくしすぎると情報落ちの関係で
	* 答えが求まらなくなってしまうので注意。
	*/
	epsilon = 0.00001;

	/* leftとrightの間に確実に解がある、という範囲を指定する */
	left = 1.0;
	right = 3.0;

	/* 範囲をひたすら絞り込む */
	while(fabs(right-left) > epsilon && fabs(func(left)) > epsilon){
		mid = (left+right) / 2.0;

		/* func(left)とfunc(mid)が同じ符号なら */
		if(func(left) * func(mid) >= 0.0){
			left = mid;			/* leftの位置をmidにあわせる */
		}else{
			right = mid;		/* rightの位置をmidにあわせる */
		}
	}
	return left;
}

int main(void)
{
	double d;
	d = BinarySearch();
	printf("方程式の解は%1f. そのときのfunc(x)は%1fです。\n", d, func(d));
	return 0;
}
