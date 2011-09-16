tree_node* find_value(tree_node* node, int val){
	/* 発見したtree_nodeのポインタを返す。ないばあいはNULL */

	/* 自分より小さい値ならば、左側 */
	if(node->value > val){
		if(node->left == NULL){	/* もし左側になければ、valはない */
			return NULL;
		}
		return find_value(node_left, val);
	}
	/* 自分より大きい値ならば、右側 */
	if(node->value < val){
		if(node->right == NULL){ /* もし右側になければ、valはない */
			return NULL;
		}
		return find_value(node->right, val);
	}

	/* 見つかれば、見つかった値を返す */
	return node;
}
