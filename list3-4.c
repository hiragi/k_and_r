#include <stdio.h>
#include <stdlib.h>

/* リストの要素(ノード)をあらわす構造体 */
typedef struct tagListNode{
	struct tagListNode *prev;	/* 前の要素へのポインタ */
	struct tagListNode *next;	/* 次の要素へのポインタ */
	int data;					/* この要素がもっているデータ */
} ListNode;

int main(void)
{
	int buf, sum;
	ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;

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
				newnode->prev = lastnode;
				lastnode = newnode;
			}else{
				/* これが最初の要素だった場合 */
				firstnode = lastnode = newnode;
				newnode->prev = NULL;
			}
		}
	}while(buf != 0);

	/* 合計値を算出 */
	printf("--入力されたのは以下の数です--\n");
	sum = 0;
	for(thisnode = firstnode; thisnode != NULL; thisnode = thisnode->next){
		printf("%d\t", thisnode->data);
		sum += thisnode->data;
	}
	printf("\n---\n以上の数の合計値は%dです。\n", sum);

	/* リストの全ノードを削除 */
	for(thisnode = firstnode; thisnode != NULL;){
		removenode = thisnode;
		thisnode = thisnode->next;
		free(removenode);
	}

	return 0;
}
