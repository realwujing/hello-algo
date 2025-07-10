/**
 * dfs - 根据前序遍历和中序遍历递归构建二叉树
 * @preorder: 前序遍历数组指针
 * @inorderMap: 中序遍历值到索引的映射数组
 * @i: 当前子树在前序遍历数组中的根节点索引
 * @l: 当前子树在中序遍历数组中的左边界
 * @r: 当前子树在中序遍历数组中的右边界
 * @size: 树的总节点数（用于边界检查）
 *
 * 通过分治算法递归构建二叉树。前序遍历的第一个元素是根节点，在中序遍历中找到该根节点，
 * 将数组分为左右子树，然后递归处理。
 *
 * Return: 构建好的子树根节点指针，失败时返回NULL
 */
TreeNode *dfs(int *preorder, int *inorderMap, int i, int l, int r, int size) {
	if (r - l < 0) {
		return NULL;
	}

	TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
	root->val=preorder[i];
	root->left = NULL;
	root->right = NULL;
	int m = inorderMap[preorder[i]];
	root->left = dfs(preorder, inorderMap, i + 1, l, m - 1, size);
	root->right = dfs(preorder, inorderMap, i + 1 + m -l, m + 1, r, size);
	return root;
}

/**
 * buildTree - 根据前序遍历和中序遍历构建二叉树的主函数
 * @preorder: 前序遍历数组指针
 * @preorderSize: 前序遍历数组长度
 * @inorder: 中序遍历数组指针
 * @inorderSize: 中序遍历数组长度
 *
 * 该函数首先构建中序遍历的哈希映射，然后调用dfs()递归构建二叉树。
 * 调用者需确保preorder和inorder的有效性。
 *
 * Return: 构建好的二叉树根节点指针，失败时返回NULL
 */
TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize) {
	int *inorderMap = (int *)malloc(sizeof(int) * MAX_SIZE);
	for(int i = 0; i < inorderSize; i++) {
		inorderMap[inorder[i]] = i;
	}
	TreeNode *root = dfs(preorder, inorderMap, 0, 0, inorderSize - 1, inorderSize);
	free(inorderMap);
}
