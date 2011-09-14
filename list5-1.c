/* num of one (ver: for) */

#include <stdio.h>
#include <stdlib.h>

int num_of_one(int value)
{
	int ret;
	/* value を次々に 10で割って桁をずらしながら、再開の桁が1であるかどうかを調べていく */
	for(ret = 0; value > 0; value /= 10){
		if(value % 10 == 1){
			ret++;
		}
	}
	return ret;
}

int main(void)
{
	int i;

	printf("数を入力してkudasai");
	scanf("%d", &i);
	printf("%dの中に1は%d個含まれています\n", i, num_of_one(i));
	return 0;
}
