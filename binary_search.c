#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N		  (10)

int binary_search(int x, int *a, int left, int right)
{
	int mid;

	while(left <= right){
		mid = (left+right) / 2;
		if(a[mid] == x){
			return mid;
		}

		if(a[mid] < x){
			left = mid+1;	/* midより左にはxは存在しない */
		}else{
			right = mid-1;
		}
	}

	return NOT_FOUND;
}

int main(void)
{
	int i, r, array[N];

	srand((unsigned int)time(NULL));
	printf("array: ");
	printf("[0]:%d ", array[0]=rand()%20);

	for(i=1; i<N; i++){
		printf("[%d] : %d ", i, array[i]=array[i-1]+rand()%20);
	}

	printf("\n何を探しますか\n");
	scanf("%d", &i);

	r = binary_search(i, array, 0, N-1);

	if(r == NOT_FOUND){
		printf("見つかりませんでした\n");
	}else{
		printf("%d は %d 番目にあります。", i, r);
	}
	printf("\n");
	return 0;
}
