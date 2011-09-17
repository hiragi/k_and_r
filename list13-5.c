/* 重みつきグラフのプログラム */
#include <stdio.h>

#define STATION_NUMBER 6

char* stations[] = {"横浜", "武蔵小杉", "品川", "渋谷", "新橋", "溜池山王"};

int adjacency_matrix[STATION_NUMBER][STATION_NUMBER] = {
	{0,12,28,0,0,0},
	{12,0,10,13,0,0},
	{28,10,0,11,7,0},
	{0,13,11,0,0,9},
	{0,0,7,0,0,4},
	{0,0,0,9,4,0}
};

int main(void)
{
	int i, j;
	for(i=0; i<STATION_NUMBER; i++){
		printf("%s:", stations[i]);
		for(j=0; j<STATION_NUMBER; j++){
			if(adjacency_matrix[i][j] > 0){
				printf("→%s(%d分) ", stations[j], adjacency_matrix[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}
