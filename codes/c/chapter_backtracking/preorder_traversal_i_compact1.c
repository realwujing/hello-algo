void preOrder(TreeNode *root) {
	if (root == NULL) {
		return;
	}

	if (root->val == 7) {
		res[resSize++] == root;
	}

	preOrder(root->left);
	preOrder(root->right);
}
