/* プログラムコードによる駅の路線図 */

#include <stdio.h>

#define MAX_STATION 10

typedef struct TAG_STATION{
	char name[256];
	struct TAG_STATION *transitions[MAX_STATION];
	/* 今回は1駅に付き10駅までと制限 */
}STATION;

void init_station(STATION* station, char* name)
{
	int i;
	for(i=0; i<MAX_STATION; i++){
		/* 最初はどの駅ともつながっていない */
		station->transitions[i] = NULL;
	}
	strncpy(station->name, name, sizeof(station->name)-1);
	station->name[sizeof(station->name)-1] = '\0';
}

void add_station(STATION* station, STATION* transition)
{
	int i;
	/* transitions でまだ登録されていない場所を探す */
	for(i=0; i<MAX_STATION; i++){
		if(station->transitions[i] == NULL){
			break;
		}
		/* すでに登録されているので、何もせずに終了する */
		if(station->transitions[i] ==transition){
			return;
		}
	}
	/* 10駅すべて登録されていたら何もしない */
	if(i == MAX_STATION){
		return;
	}
	/* 新しい乗換駅を登録する */
	station->transitions[i] = transition;
}

void print_station(STATION* station)
{
	int i;
	printf("%s:", station->name);
	for(i=0; i<MAX_STATION; i++){
		if(station->transitions[i] == NULL){
			break;
		}
		printf("→ %s ", station->transitions[i]->name);
	}
	printf("\n");
}

int main(void)
{
	int i;
	STATION station[6];
	init_station(&station[0], "鎌倉");
	init_station(&station[1], "藤沢");
	init_station(&station[2], "横浜");
	init_station(&station[3], "横須賀");
	init_station(&station[4], "茅ヶ崎");
	init_station(&station[5], "東京");

	/* 鎌倉 */
	add_station(&station[0], &station[3]);
	add_station(&station[0], &station[1]);
	add_station(&station[0], &station[2]);
	/* 藤沢 */
	add_station(&station[1], &station[0]);
	add_station(&station[1], &station[4]);
	add_station(&station[1], &station[2]);
	/* 横浜 */
	add_station(&station[2], &station[1]);
	add_station(&station[2], &station[0]);
	add_station(&station[2], &station[5]);
	/* 横須賀・茅ヶ崎・東京 */
	add_station(&station[3], &station[0]);
	add_station(&station[4], &station[1]);
	add_station(&station[5], &station[2]);

	/* グラフ構造を表示 */
	for(i=0; i<6; i++){
		print_station(&station[i]);
	}
	return 0;
}
