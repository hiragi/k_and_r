/* ダイクストラ法のプログラム */

#include <stdio.h>

#define STATION_NUMBER 6
#define START_STATION 0

char* stations[] =
	{"横浜", "武蔵小杉", "品川", "渋谷", "新橋", "溜池山王"};

int current_cost[STATION_NUMBER];
int fix[STATION_NUMBER];

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
	int i, min_station, min_time, new_time;

	/* 初期化する */
	for(i=0; i<STATION_NUMBER; i++){
		current_cost[i] = -1;	/* 無限大 */
		fix[i] = 0;
	}
	/* スタート地点(横浜)の所要時間を0とする */
	current_cost[0] = 0;

	for(;;){
		min_time = -1;
		for(i=0; i<STATION_NUMBER; i++){
			if(fix[i] == 0 && current_cost[i] != -1){
				if(min_time == -1 || min_time > current_cost[i]){
					/* 確定しておらず、もっとも所要時間の小さい駅を調べる */
					min_time = current_cost[i];
					min_station = i;
				}
			}
		}
		if(min_time == -1){
			/* すべての駅が確定したか、最小の所要時間が無限大だったので終了 */
			break;
		}

		/* 自分の駅から伸びているすべての駅の所要時間を調べる */
		for(i=0; i<STATION_NUMBER; i++){
			if(fix[i] == 0 && adjacency_matrix[min_station][i] > 0){
				new_time = min_time + adjacency_matrix[min_station][i];
				/* 自分の駅経由で移動する場合の必要時間 */
				if(current_cost[i] == -1 || current_cost[i] > new_time){
					/* いま登録されている時間よりも、この駅経由で移動した時間が早いので、
					   新しい時間を登録する */
					current_cost[i] = new_time;
				}
			}
		}
		/* 自分の駅を確定する */
		fix[min_station] = 1;
	}

	for(i=0; i<STATION_NUMBER; i++){
		printf("%s→%s:%d分\n", stations[START_STATION], stations[i], current_cost[i]);
	}
	return 0;
}
