/* KMP法による文字列検索 */

#include <stdio.h>
#include <stdlib.h>

#define PATTERN_LENGTH 13
unsigned char original_text[] = "a eighty-eighty-eighth key";
unsigned char original_pattern[PATTERN_LENGTH+1] = "eighty-eighth";

#define _SHOW_WORKING_

unsigned char *kmp_search(unsigned char *text, unsigned char *pattern)
{
	int table[PATTERN_LENGTH+1] = {0, 0};
	int text_index = 1, pattern_index = 0;
	int i = 0, j;


	/* まずkmpの検索に必要な情報を集め、テーブルとして保存する */
	while((pattern[text_index]) != '\0'){
		if(pattern[text_index] == pattern[pattern_index]){
			/* 一致したら再検索はpattern_index文字からはじめればよい */
			table[++text_index] = ++pattern_index;
		}else if(pattern_index == 0){
			/* パターン1文字目で不一致ならば、再建策は先頭から */
			table[++text_index] = 0;
		}else{
			/* パターン1文字目以外で不一致ならば、再検索の位置はtableから参照 */
			pattern_index = table[pattern_index];
		}
	}
	/* 以上でテーブルが完成。実際の検索にとりかかる */

	while((*text) != '\0'){
#ifdef _SHOW_WORKING_
	/* わかりやすいように、今何を比較しているか表示 */
		printf("	本文:%s \nパターン:", original_text);
		for(j=0; j<text-original_text; ++j){
			printf(" ");
		}
		printf("%c \n", pattern[i]);
#endif
		if((*text) == pattern[i]){
			/* テキストとパターンが一致していれば、１字ずつ比較を続ける */
			text++;
			if(pattern[++i] == '\0'){
				/* すべて一致すれば、正解 */
				return text-PATTERN_LENGTH;
			}
		}
		else if(i==0){
			/* パターンの最初の文字で失敗した場合は、比較場所を１つすすめる */
			text++;
		}else{
			/* 最初の文字でない場合は、テーブルから比較位置を取得する */
			i = table[i];
		}
	}

	return NULL;
}

int main(void)
{
	unsigned char *result;
	result = kmp_search(original_text, original_pattern);
	if(result == NULL){
		printf("見つかりませんでした\n");
	}else{
		printf("見つかりました\n");
	}

	return 0;
}
