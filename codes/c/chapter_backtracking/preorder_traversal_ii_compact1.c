void preOrder(TreeNode *root) {
	if (root == NULL) {
		return;
	}

	path[pathSize++] = root;
	if(root->val == 7) {
		for (int i = 0; i < pathSize; ++i) {
			res[resSize][i] = path[i];
		}
		resSize++;
	}
	preOrder(root->left);
	preOrder(root->right);
	pathSize--;
}
