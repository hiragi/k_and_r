/* 7パズルを解く */
#include <stdio.h>
#include <stdlib.h>

/* いままでに現れた局面を記録する配列。この配列は、キュー代わりにも使われる。 */
typedef struct tagPATTERN{
	unsigned long hash;
	int pattern_from;
} PATTERN;
PATTERN *history;

int history_count = 0;		/* 現在のパターンの個数 */
int queue_bottom;			/* キューの末尾位置を表す添え字 */


/* 局面と対応する数字を作り出す関数 */
unsigned long make_hash(char* pattern)
{
	unsigned long hash;
	int i;

	hash = 0;
	for(i=0; i<8; i++){
		hash |= ((unsigned long)(pattern[7-i])) << (i*4);
	}
	return hash;
}

/* 数字から局面を復元する関数 */
void pattern_from_hash(char* pattern, unsigned long hash)
{
	int i;
	for(i=0; i<8; i++){
		pattern[7-i] = (char)((hash >> (i*4)) & 0xf);
	}
}

void save_history(char* pattern, int pattern_from)
{
	int i;
	unsigned long hash;

	hash = make_hash(pattern);
	/* いままでの局面と比較する */
	for(i=0; i<history_count; i++){
		if(history[i].hash == hash){
			return;
		}
	}

	/* 新しく出てきた局面を保存 */
	history_count++;
	history = (PATTERN*)realloc(history, sizeof(PATTERN) * (history_count));
	if(history == NULL){
		printf("メモリが足りません");
		exit(EXIT_FAILURE);
	}
	history[history_count-1].hash = hash;
	history[history_count-1].pattern_from = pattern_from;
}

int solve_7puzzle(void)
{
	int blank_pos;
	unsigned long hash;
	char pattern[9];		/* パネル配置 */
	/*	添え字と場所の対応は次のとおり
		0 1 2 3
		4 5 6 7 */

	queue_bottom = 0;
	/* キューがからになるまで繰り返す */
	while(queue_bottom != history_count){
		/* キューから１つ取得する */
		hash = history[queue_bottom].hash;

		if(hash == 0x012345670){
			/* 解にたどり着いたら終了 */
			return 1;
		}
		pattern_from_hash(pattern, hash);
		for(blank_pos=0; blank_pos<8; blank_pos++){
			if(pattern[blank_pos] == 0){
				break;
			}
		}

		if(blank_pos > 3){
			/* 上からあいている場所へ移動 */
			pattern[blank_pos] = pattern[blank_pos-4];
			pattern[blank_pos-4] = 0;
			/* 新しいパネル配置を保存したあと、元の配置に戻す */
			save_history(pattern, queue_bottom);
			pattern_from_hash(pattern, hash);
		}
		if(blank_pos < 4){
			/* 下からあいている場所へ移動 */
			pattern[blank_pos] = pattern[blank_pos+4];
			pattern[blank_pos+4] = 0;
			save_history(pattern, queue_bottom);
			pattern_from_hash(pattern, hash);
		}
		if(blank_pos != 0 && blank_pos != 4){
			/* 左からあいている場所へ移動 */
			pattern[blank_pos] = pattern[blank_pos-1];
			pattern[blank_pos-1] = 0;
			save_history(pattern, queue_bottom);
			pattern_from_hash(pattern, hash);
		}
		if(blank_pos != 3 && blank_pos != 7){
			/* 右からあいている場所へ移動 */
			pattern[blank_pos] = pattern[blank_pos+1];
			pattern[blank_pos+1] = 0;
			save_history(pattern, queue_bottom);
		}
		queue_bottom++;
	}
	return 0;		/* 解が見つからなかった場合 */
}

int main(void)
{
	int last, i;
	char pattern[8] = {2, 7, 1, 4, 5, 0, 3, 6};

	history = NULL;
	/* 最初の１つ目のパターンを記録 */
	save_history(pattern, -1);

	if(solve_7puzzle() == 0){
		printf("全パターンを試しましたが、解が見つかりませんでした\n");
	}else{
		/* 解を表示する */
		last = -1;
		while(last != queue_bottom){
			/* 最初の解から表示していく */
			for(i=queue_bottom; history[i].pattern_from != last;){
				i = history[i].pattern_from;
			}
			last = i;

			/* パネルの配置を表示 */
			pattern_from_hash(pattern, history[last].hash);
			for(i=0; i<8; i++){
				printf("%c ", pattern[i]? pattern[i]+'0' : ' ');
				if(i % 4 == 3){
					printf("\n");
				}
			}
			getchar();	/* リターンキーで次を表示 */
		}
	}

	free(history);
	return 0;
}
