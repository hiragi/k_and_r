tree_node* create_new_node(int num){
	tree_node *tree_new;

	/* 新しいnodeを作成して、初期化する */
	tree_new = (tree_node*)malloc(sizeof(tree_node));
	if(tree_new == NUL){
		exit(EXIT_FAILURE);
	}
	tree_new->left = NULL;
	tree_new->right = NULL;
	tree_new->value = num;

	return tree_new;
}

/* num:挿入する値 node:値を挿入するツリーの根を指すポインタ */
void insert_tree(int num, tree_node *node)
{
	/* １つも挿入されていない場合 */
	if(node == NULL){
		tree_root = create_new_node(num);
		return;
	}

	/* numが現在のnodeよりも小さい場合 */
	if(node->value > num){
		if(node->left != NULL){
			insert_tree(num, node->left);
		}else{
			/* 左側に追加する */
			node->left = create_new_node(num);
		}
	}else{
		/* numが現在のnodeの値以上の場合 */
		if(node->right != NULL){
			insert_tree(num, node->right);
		}else{
			/* 右側に追加する */
			node->right = create_new_node(num);
		}
	}
	return;
}
