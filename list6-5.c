/* 2分木のデータ追加、サーチ、削除 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 文字列の2分木。strcmp()関数を使って文字列の大小関係を判別できる。 */
typedef struct _tag_tree_node{
	char *key;						/* このnodeがもつキー */
	char *val;						/* キーに対応する値 */
	struct _tag_tree_node *left;	/* 自分より小さい値のnode */
	struct _tag_tree_node *right;	/* 自分より大きい値のnode */
}tree_node;

tree_node *tree_root = NULL;

tree_node* create_new_node(char *key, char *val)
{
	tree_node *tree_new;

	/* 新しいnodeを作成して、初期化する */
	tree_new = (tree_node*)malloc(sizeof(tree_node));
	if(tree_new == NULL){
		exit(EXIT_FAILURE);
	}
	tree_new->left = NULL;
	tree_new->right = NULL;
	/* keyとvalの文字列を新しいノードにコピー */
	tree_new->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
	tree_new->val = (char*)malloc(sizeof(char) * strlen(val) + 1);
	if(tree_new->key == NULL || tree_new->val == NULL){
		exit(EXIT_FAILURE);
	}
	strcpy(tree_new->key, key);
	strcpy(tree_new->val, val);
	
	return tree_new;
}

void insert_tree(char *key, char *val, tree_node *node)
{
	/* １つも挿入されていない場合 */
	if(node == NULL){
		tree_root = create_new_node(key, val);
		return;
	}

	/* numが現在のnodeの値よりも小さい場合 (strcmp()関数で文字列の大小関係を比較) */
	if(strcmp(node->key, key) > 0){
		if(node->left != NULL){
			insert_tree(key, val, node->left);
		}else{
			/* 左側に追加する */
			node->left = create_new_node(key, val);
		}
	}else{
		/* numが現在のnodeの値以上の場合 */
		if(node->right != NULL){
			insert_tree(key, val, node->right);
		}else{
			/* 右側に追加する */
			node->right = create_new_node(key, val);
		}
	}

	return;
}

tree_node* find_key(tree_node* node, char* val)
{
	/* 発見したtree_nodeのポインタを返す。ない場合はNULL */

	int cmp = strcmp(node->key, val);
	/* 自分より小さい値ならば、左側 */
	if(cmp > 0){
		if(node->left == NULL){
			return NULL;	/* もし左側になければ、valはない */
		}
		return find_key(node->left, val);
	}
	/* 自分より大きい値ならば、右側 */
	if(cmp < 0){
		if(node->right == NULL){
			return NULL;
		}
		return find_key(node->right, val);
	}

	/* 見つかれば、見つかった値を返す */
	return node;
}

int delete_tree(char *val)
{
	/* valを削除する。せいこうすれば1、失敗すれば0を返す */

	tree_node *node = tree_root;
	tree_node *parent_node = NULL;
	tree_node *left_biggest;
	int direction = 0;
	int cmp;
	
	/* while文で削除すべき対象を見つける(find_keyと同じ) */
	while(node != NULL && (cmp = strcmp(node->key, val)) != 0){
		if(cmp > 0){
			parent_node = node;
			node = node->left;
			direction = -1;		/* 親の左側 */
		}else{
			parent_node = node;
			node = node->right;
			direction = 1;		/* 親の右側 */
		}
	}
	if(node == NULL){
		return 0;
	}

	if(node->left == NULL || node->right == NULL){
		/* 左か右、どちらかがNULLであった場合 */
		if(node->left == NULL){
			/* 親のポインタを変更する */
			if(direction == -1){
				parent_node->left = node->right;
			}
			if(direction == 1){
				parent_node->right = node->right;
			}
			if(direction == 0){
				tree_root = node->right;
			}
		}else{
			/* 親のポインタを変更する */
			if(direction == -1){
				parent_node->left = node->left;
			}
			if(direction == 1){
				parent_node->right = node->left;
			}
			if(direction == 0){
				tree_root = node->left;
			}
		}

		free(node->key);
		free(node);
	}else{
		/* 両者ともNULLでなかった場合 */
		/* node の左側の、もっとも大きな値(もっとも右の値)を取得する */
		left_biggest = node->left;
		parent_node = node;
		direction = -1;
		while(left_biggest->right != NULL){
			parent_node = left_biggest;
			left_biggest = left_biggest->right;
			direction = 1;
		}

		/* left_biggestの値をnodeに代入し、left_biggestは左側の枝をいれる */
		free(node->key);
		node->key = left_biggest->key;

		if(direction == -1){
			parent_node->left = left_biggest->left;
		}else{
			parent_node->right = left_biggest->left;
		}
		free(left_biggest);
	}

	return 1;
}

void print_tree(int depth, tree_node* node)
{
	int i;

	if(node == NULL){
		return;
	}
	print_tree(depth+1, node->left);
	for(i=0; i<depth; i++){
		printf("");
	}
	printf("%s :%s \n", node->key, node->val);
	print_tree(depth+1, node->right);
}

void free_tree(tree_node* node)
{
	if(node == NULL){
		return;
	}
	/* まず子nodeのメモリを開放する */
	free_tree(node->left);
	free_tree(node->right);

	/* 自分自身を解放 */
	free(node->key);
	free(node->val);
	free(node);
}

int main(void)
{
	int i;
	char tmp[256], tmpval[256];
	tree_node *node_found;

	for(;;){
		print_tree(0, tree_root);
		printf("0:終了 1:挿入 2:探索 3:削除>");
		scanf("%d", &i);
		if(i == 0){
			break;
		}
		switch(i){
			case 1:
				printf("挿入する文字列(キー):>");
				scanf("%s", tmp);
				printf("キーに対応させる値:>");
				scanf("%s", tmpval);
				insert_tree(tmp, tmpval, tree_root);
				break;

			case 2:
				printf("探索する文字列:>");
				scanf("%s", tmp);
				node_found = find_key(tree_root, tmp);
				if(node_found != NULL){
					printf("対応する値は%sです\n", node_found->val);
				}else{
					printf("見つかりませんでした。\n");
				}
				break;

			case 3:
				printf("削除する文字列:>");
				scanf("%s", tmp);
				if(delete_tree(tmp) == 1){
					printf("削除しました\n");
				}else{
					printf("見つかりませんでした\n");
				}
				break;
		}
	}
	free_tree(tree_root);
	return 0;
}
