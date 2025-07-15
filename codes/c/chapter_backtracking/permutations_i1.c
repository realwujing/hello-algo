/**
 * backtrack - 回溯算法实现全排列 I
 * @state: 当前排列状态数组
 * @stateSize: 当前排列状态的长度
 * @choices: 可选的数字数组
 * @choicesSize: 可选数字的数量
 * @selected: 标记数组，记录数字是否已被选择
 * @res: 存储所有排列结果的二维数组
 * @resSize: 当前已找到的排列数量（指针，用于修改外部变量）
 *
 * 该函数使用回溯算法生成所有可能的排列组合，通过递归和剪枝避免重复选择。
 * 当排列长度等于输入数组长度时，记录当前排列。
 */
/* 回溯算法：全排列 I */
void backtrack(int *state, int stateSize, int *choices, int choicesSize, bool *selected, int **res, int *resSize) {
	// 当状态长度等于元素数量时，记录解
	if (stateSize == choicesSize) {
		res[*resSize] = (int *)malloc(choicesSize * sizeof(int));
		for (int i = 0; i < choicesSize; i++) {
			res[*resSize][i] = state[i];
		}
		(*resSize)++;
		return;
	}
	// 遍历所有选择
	for (int i = 0; i <choicesSize; i++) {
		int choice = choices[i];
		// 剪枝：不允许重复选择元素
		if (!selected[i]){
			// 尝试：做出选择，更新状态
			selected[i] = true;
			state[stateSize] = choice;
			// 进行下一轮选择
			backtrack(state, stateSize + 1, choices, choicesSize, selected, res, resSize);
			// 回退：撤销选择，恢复到之前的状态
			selected[i] = false;
		}
	}
}

/**
 * permutationsI - 生成输入数组的所有全排列
 * @nums: 输入数字数组
 * @numsSize: 输入数组的长度
 * @returnSize: 返回结果的数量（指针，用于修改外部变量）
 *
 * 返回值: 存储所有排列结果的二维数组，需由调用者释放内存。
 * 使用回溯算法生成全排列，避免重复排列。
 */
/* 全排列 I */
int **permutationsI(int *nums, int numsSize, int *returnSize) {
	int *state = (int *)malloc(numsSize * sizeof(int));
	bool *selected = (bool *)malloc(numsSize * sizeof(bool));
	for (int i = 0; i < numsSize; i++) {
		selected[i] = false;
	}
	int **res = (int **)malloc(MAX_SIZE * sizeof(int *));
	*resSize = 0;
	backtrack(state, 0, nums, numsSize, selected, res, returnSize);

	free(state);
	free(selected);

	return res;
}
