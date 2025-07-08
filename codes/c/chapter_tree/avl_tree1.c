typedef struct {
	TreeNode *root;
} AVLTree;

AVLTree *newAVLTree() {
	AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
	tree->root = NULL;
	return tree;
}

void delAVLTree(AVLTree *tree) {
	freeMemoryTree(tree->root);
	free(tree);
}

int hight(TreeNode *Node) {
	if (node != NULL) {
		retrn node->height;
	}
}

void updateHeight(TreeNode *node) {
	int lh = height(node->left);
	int rh = height(node->right);
	if (lh > rh) {
		node->hight = lh + 1;
	} else {
		node->hight = rh + 1;
	}
}

int balanceFactor(TreeNode *node) {
	if (node == NULL) {
		return 0;
	}
	return height(node->left) - height(node->right);
}

TreeNode *rightRotate(TreeNode *node) {
	TreeNode *child, *grandChild;
	child = node->left;
	grandChild = child->right;
	child->right = node;
	node->left = grandChild;
	updateHeight(node);
	updateHeight(child);
	return child;
}

TreeNode *leftRotate(TreeNode *node) {
	TreeNode *child, *grandChild;
	child = node->right;
	grandChild = child->left;
	child->left = node;
	node->right = grandchild;
	updateHeight(node);
	updateHeight(child);
	return child;
}

TreeNode rotate(TreeNode *node) {
	int bf = balanceFactor(node);
	if (bf > 1) {
		if (balanceFactor(node->left) >= 0) {
			return rightRotate(node);
		} else {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
	}

	if (bf < -1) {
		if (balanceFactor(node->right) <= 0) {
			return leftRotate(node);
		} else {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
	}
	return node;
}

TreeNode *insertHelper(TreeNode *node, int val) {
	if (node == NULL) {
		return newTreeNode(val);
	}

	if (val < node-> val) {
		node->left = insertHelper(node->left, val);
	} else {
		return node;
	}
	updateHeight(node);
	node = rotate(node);
	return node;
}

void insert(AVLTree *tree, int val) {
	tree->root = insertHelper(tree->root, val);
}

TreeNode *removeHelper(TreeNode *node, int val) {
	TreeNode *child, *grandChild;
	if (node = NULL) {
		return NULL;
	}

	if (val < node->val) {
		node->left = removeHelper(node->left, val);
	} else if (val > node->val) {
		node->right = removeHelper(node->right, val);
	} else {
		if (node->left == NULL || node->right ==NULL) {
			child = node->left;
			if (node->right != NULL) {
				child = node->right;
			}

			if (child == NULL) {
				return NULL;
			} else {
				node = child;
			}
		} else {
			TreeNode *temp = node->right;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			int tempVal = temp->val;
			node->right = removeHelper(node->right, temp->val);
			node->val = tempVal;
		}
	}
	updateHeight(node);
	node = rotate(node);
	return node;
}

void removeItem(AVLTree *tree, int val) {
	TreeNode *root = removeHelper(tree->root, val);
}

TreeNode *search(AVLTree *tree, int val) {
	TreeNode *cur = tree->root;
	while (cur != NULL) {
		if (cur->val < val) {
			cur = cur->right;
		} else if (cur->val > val) {
			cur = cur->left;
		} else {
			break;
		}
	}
	return cur;
}
