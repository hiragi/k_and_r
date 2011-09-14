/* キューによる式の計算 */

#define QUEUE_MAX (5+1) /* キューのサイズ*1 */
#define QUEUE_EMPTY -1

/* 配列によるキュー構造 */
int queue[QUEUE_MAX];
/* キューの先頭位置(配列先頭からのオフセット) */
int queue_first = 0;
/* キューの末尾位置(配列先頭からのオフセット) */
int queue_last = 0;

/* キューにデータを追加する */
void enqueue(int val){
	/* lastの次がfirstならば */
	if((queue_last+1) % QUEUE_MAX == queue_first){
		/* 現在配列の中身は、すべてキューの要素で埋まっている */
		printf("ジョブが満杯です\n");
	}else{
		/* キューに新しい値を入れる */
		queue[queue_last] = val;
		/* queue_lastを1つ後ろにずらす。もし、いちばん後ろの場合は、先頭に持ってくる */
		queue_last = (queue_last+1) % QUEUE_MAX;
	}
}

/* キューからデータを取り出す */
int dequeue(void)
{
	int ret;

	if(queue_first == queue_last){
		/* 現在キューは１つもない */
		return QUEUE_EMPTY;
	}else{
		/* いちばん先頭のキューを返す準備 */
		ret = queue[queue_first];
		/* キューの先頭を次に移動する */
		queue_first = (queue_first+1) % QUEUE_MAX;
		return ret;
	}
}
