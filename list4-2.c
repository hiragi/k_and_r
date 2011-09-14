/* 括弧の対応をスタックとポップで調べるプログラム */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 括弧の種類 */
#define STAPLE_SMALL 1
#define STAPLE_MEDIUM 2
#define STAPLE_LARGE 3

/* １つの括弧を示す構造体 */
typedef struct _tagstaple{
	int line;	/* 括弧のある行 */
	int column; /* 括弧のある行(行頭からの文字数 */
	int type;	/* 括弧の種類 */

	/* リストによるスタック構造 */
	struct _tagstaple *staple_next;
	struct _tagstaple *staple_prev;
}staple;

/* リストによるスタック構造 */
staple *staple_head = NULL;
staple *staple_last = NULL;

/* スタックへのpush */
void stack_push(int line, int column, int type){
	staple *staple_new;

	/* 新しい領域を確保 */
	staple_new = (staple*)malloc(sizeof(staple));
	if(staple_new == NULL){
		printf("オーバーフローです。メモリが足りません");
		exit(EXIT_FAILURE);
		return;
	}

	/* 渡された値をスタックに積む */
	staple_new->line = line;
	staple_new->column = column;
	staple_new->type = type;

	/* リストの最後に追加する */
	staple_new->staple_next = NULL;
	staple_new->staple_prev = staple_last;
	staple_last = staple_new;
	if(staple_head == NULL){
		staple_head = staple_new;
	}
}

/* スタックからpop */
int stack_pop(staple *ret){
	staple *temp_staple;

	if(staple_head == NULL){
		/* スタックには何もない：括弧の対応がとれていない */
		return 0;
	}

	/* いちばん最後にpushされた括弧の情報を返す */
	ret->line = staple_last->line;
	ret->column = staple_last->column;
	ret->type = staple_last->type;
	ret->staple_next = ret->staple_prev = NULL;
	temp_staple = staple_last;

	/* リストから削除する */
	if(staple_last->staple_prev == NULL){
		staple_head = NULL;
	}else{
		staple_last->staple_prev->staple_next = NULL;
	}

	staple_last = staple_last->staple_prev;

	free(temp_staple);

	return 1;	/* 成功 */
}

int main(void)
{
	char buffer[4096];
	int i, len, line=1, carryover=0;
	staple open;

	for(;;){
		if(fgets(buffer, 4096, stdin) == NULL){
			/* 終端まで読み込んだ */
			break;
		}
		len = strlen(buffer);
		if(len == 0){
			continue;
		}

		for(i = 0; i < len; i++){
			switch(buffer[i]){
				case '(':
					stack_push(line, carryover+i+1, STAPLE_SMALL);
					break;
				case '{':
					stack_push(line, carryover+i+1, STAPLE_MEDIUM);
					break;
				case '[':
					stack_push(line, carryover+i+1, STAPLE_LARGE);
					break;
				case ')':
					if(stack_pop(&open) == 0){
						printf("括弧の対応が取れていません\n");
						printf("%d行%d文字に対応する開き括弧がありません\n", line, carryover+i+1);
						return EXIT_FAILURE;
					}
					if(open.type!=STAPLE_SMALL){
						printf("括弧の対応がとれていません\n");
						printf("%d行%d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover+i+1);
						return EXIT_FAILURE;
					}
					break;
				case '}':
					if(stack_pop(&open) == 0){
						printf("括弧の対応がとれていません\n");
						printf("%d行%d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover+i+1);
						return EXIT_FAILURE;
					}
					break;
				case ']':
					if(stack_pop(&open) == 0){
						printf("括弧の対応がとれていません\n");
						printf("%d行%d文字に対応する括弧の種類が違います\n", open.line, open.column, line, carryover+i+1);
						return EXIT_FAILURE;
					}
					break;
			}
		}
		if(buffer[len-1] == '\n'){
			carryover = 0;
			line++;
		}else{
			/* 4096文字読み込んでも、改行に出会わなかった場合 */
			carryover += len;
		}
	}

	/* 完全に括弧の対応がとれていれば、スタックはからになっているはず */
	if(staple_head != NULL){
		/* 開き括弧が多い */
		printf("括弧の対応がとれていません\n");
		printf("開き括弧の数が多すぎます\n");
		return EXIT_FAILURE;
	}

	printf("括弧の対応は正しくとれています\n");
	return 0;
}
