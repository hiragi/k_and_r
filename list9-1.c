/* 単純な文字列検索 */
#include <stdio.h>
#include <stdlib.h>

unsigned char original_text[] = "Team Swift";
unsigned char original_pattern[] = "if";

#define _SHOW_WORKING_

unsigned char * simple_search(unsigned char * text, unsigned char *pattern)
{
	int i;
	while((*text) != '\0'){
#ifdef _SHOW_WORKING_
		/* わかりやすいように、いま何を比較しているか表示 */
		printf("	本文:%s \nパターン:", original_text);
		for(i=0; i<text-original_text; i++){
			printf("  ");
		}
		printf("%s \n", pattern);
#endif

		/* パターンの先頭から比較を始める */
		for(i=0; pattern[i] != '\0'; i++){
			if(pattern[i] != text[i]){
				break;		/* 一致しなかった */
			}
		}
		if(pattern[i] == '\0'){
			return text;	/* 一致した */
		}

		/* 一致しなかったので、テキストを1つずらして再度挑戦 */
		text++;
	}

	return NULL;
}

int main(void)
{
	unsigned char *result;
	result = simple_search(original_text, original_pattern);
	if(result == NULL){
		printf("見つかりませんでした\n");
	}else{
		printf("見つかりました\n");
	}

	return 0;
}
