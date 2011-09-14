/* リストのなかのデータをサーチする方法
 * リニアサーチのみ可能 */

#include <stdio.h>
#include <stdlib.h>

/* リストの要素(ノード)をあらわす構造体 */
typedef struct tagListNode{
	struct tagListNode *prev;	/* 前の要素へのポインタ */
	struct tagListNode *next;	/* 次の要素へのポインタ */
	int data;					/* この要素が持っているデータ */
}ListNode;

int main(void)
{
	int buf;
	ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;

	firstnode = lastnode = NULL;

	do{
		printf("整数を入力してください(0:END)");
		scanf("%d", &buf);
		if(buf){	/* 新たな入力があったら */
			/* 新しいノードを作成 */
			newnode = (ListNode*)malloc(sizeof(ListNode));
			newnode->data = buf;
			newnode->next = NULL;

			if(lastnode != NULL){
				/* すでにあるリストの末尾に新しいノードをつなげる */
				lastnode->next = newnode;
				newnode->prev = lastnode;
				lastnode = newnode;
			}else{
				/* これが最初の要素だった場合 */
				firstnode = lastnode = newnode;
				newnode->prev = NULL;
			}
		}
	}while(buf != 0);

	/* 検索地を入力 */
	do{
		printf("検索する値を入力してください：");
		scanf("%d", &buf);

		if(buf != 0){
			/* 最初に入力した値のなかから検索し、みつかったら削除 */
			for(thisnode = firstnode; thisnode != NULL; thisnode = thisnode->next){
				if(thisnode->data==buf){
					printf("入力された値のなかに%dが見つかりました。ノードを削除します。\n", buf);

					if(thisnode->prev != NULL){
						thisnode->prev->next = thisnode->next;
					}else{
						firstnode = thisnode->next;
					}

					if(thisnode->next != NULL){
						thisnode->next->prev = thisnode->prev;
					}

					free(thisnode);
					break;
				}
			}
			if(thisnode == NULL){
				printf("%dは入力されていないか、あるいは既に削除されています。\n", buf);
			}
		}
	}while(buf != 0);

	/* 残ったノードをすべて削除 */
	for(thisnode = firstnode; thisnode != NULL;){
		removenode = thisnode;
		thisnode = thisnode->next;
		free(removenode);
	}

	return 0;
}
