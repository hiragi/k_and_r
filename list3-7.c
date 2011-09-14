#include <stdio.h>
#include <stdlib.h>

/* リストの要素(ノード)をあらわす構造体 */
typedef struct tagListNode{
	struct tagListNode *next;	/* 次の要素へのポインタ */
	int data;					/* この要素が持っているデータ */
}ListNode;

int main(void)
{
	int buf;
	ListNode *firstnode, *lastnode, *newnode, *thisnode, *tmpnode;

	firstnode = lastnode = NULL;

	do{
		printf("整数を入力してください(0:END):");
		scanf("%d", &buf);
		if(buf){	/* 新たな入力があったら */
			/* 新しいノードを作成 */
			newnode = (ListNode*)malloc(sizeof(ListNode));
			newnode->data = buf;
			newnode->next = NULL;

			if(lastnode != NULL){
				/* すでにあるリストの末尾に新しいノードをつなげる */
				lastnode->next = newnode;
				lastnode = newnode;
			}else{
				/* これが最初の要素だった場合 */
				firstnode = lastnode = newnode;
			}
		}
	}while(buf != 0);

	do{
		printf("現在の並び:\n");
		for(thisnode=firstnode; thisnode != NULL; thisnode=thisnode->next){
			printf("%d\t", thisnode->data);
		}

		/* 検索値を入力 */
		printf("\n検索する値を入力してください(0:END)");
		scanf("%d", &buf);

		if(buf!=0){
			/* 最初に検索した値のなかから検索 */
			for(thisnode=firstnode; thisnode!=NULL; tmpnode=thisnode, thisnode=thisnode->next){
				if(thisnode->data==buf){
					printf("入力された値のなかに%dが見つかりました\n", buf);
					if(thisnode!=firstnode){
						/* 検索で見つかったノードを先頭にもってくる */
						tmpnode->next = thisnode->next;

						if(lastnode==thisnode){
							lastnode=tmpnode;
						}

						thisnode->next = firstnode;
						firstnode = thisnode;
					}
					break;
				}
			}
			if(thisnode == NULL){
				printf("%d は入力されていませんでした\n", buf);
			}
		}
	}while(buf != 0);

	thisnode = firstnode;

	while(thisnode != NULL){
		tmpnode = thisnode->next;
		free(thisnode);
		thisnode = tmpnode;
	}

	return 0;
}
