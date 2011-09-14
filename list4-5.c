/* キューのプログラム例 */
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX (5+1)	/* キューのサイズ */
#define QUEUE_EMPTY -1

/* 配列によるキュー構造 */
int queue[QUEUE_MAX];
int queue_first = 0;	/* キューの先頭位置 */
int queue_last = 0;		/* キューの末尾位置 */

/* キューにデータを追加する */
void enqueue(int val){
	/* lastの次がfirstならば */
	if((queue_last+1) % QUEUE_MAX == queue_first){
		/* 現在配列の中身は、すべてキューの要素で埋まっている */
		printf("ジョブが満杯です\n");
	}else{
		/* キューに新しい値を入れる */
		queue[queue_last] = val;
		/* queue_lastを１つ後ろにずらす。もし、いちばん後ろの場合は、先頭にもってくる */
		queue_last = (queue_last+1) % QUEUE_MAX;
	}
}

/* キューからデータを取り出す */
int dequeue(void)
{
	int ret;

	if(queue_first == queue_last){
		/* 現在キューは1つもない */
		return QUEUE_EMPTY;
	}else{
		/* いちばん先頭のキューを返す準備 */
		ret = queue[queue_first];
		/* キューの先頭を次に移動する */
		queue_first = (queue_first+1) % QUEUE_MAX;
		return ret;
	}
}

/* キューの全内容を表示する */
void queue_print(void)
{
	int i;
	for(i = queue_first; i != queue_last; i = (i+1)%QUEUE_MAX){
		printf("%d ", queue[i]);
	}
}

int main(void)
{
	int i, j;
	do{
		printf("現在のキュー:");
		queue_print();
		printf("\nコマンド 0:終了 1:ジョブをためる 2:ジョブを実行\n>");
		scanf("%d", &i);
		switch(i){
			case 1:
				printf("ジョブの識別番号(1-1000)を適当に入力してください:");
				scanf("%d", &j);
				if(j >= 1 && j <= 1000){
					enqueue(j);
				}
				break;
			case 2:
				j = dequeue();
				if(j==QUEUE_EMPTY){
					printf("ジョブがありません\n");
				}else{
					printf("識別番号%dのジョブを実行中...\n", j);
				}
				break;
		
		}
	}while(i != 0);

	return 0;
}
