typedef struct ListNode {
	int val;
	struct ListNode *next;
} ListNode;

ListNode *newListNode(int val) {
	ListNode *node;
	node = (ListNode *)malloc(sizeof(ListNode));
	node->val = val;
	node->next = NULL;
	return node;
}

ListNode *arrToLinkedList(const int *arr, size_t size) {
	if (size <= 0) {
		return NULL;
	}

	ListNode *dummy = newListNode(0);
	ListNode *node = dummy;
	for (int i =0; i < size; i++) {
		node->next = newListNode(arr[i]);
		node = node->next;
	}
	return dummy->next;
}

void freeMemoryLinkdList(ListNode *cur) {
	ListNode *pre;
	while (cur != NULL) {
		pre = cur;
		cur = cur->next;
		free(pre);
	}
}
