#include "../utils/common.h"

#define MAX_SIZE 100

/**
 * backtrack - 回溯算法解决N皇后问题的核心函数
 * @row: 当前正在处理的行号（从0开始）
 * @n: 棋盘的总行数/列数（即N皇后问题中的N）
 * @state: 当前棋盘状态的二维数组，'Q'表示皇后，'#'表示空
 * @res: 用于存储所有合法解的指针数组（需预先分配内存）
 * @resSize: 当前已找到的解的数量（指针，用于修改外部变量）
 * @cols: 布尔数组，标记各列是否已被皇后占用
 * @diags1: 布尔数组，标记各主对角线是否已被占用（索引公式：row - col + n - 1）
 * @diags2: 布尔数组，标记各次对角线是否已被占用（索引公式：row + col）
 *
 * 功能描述：
 * 1. 递归尝试在棋盘的每一行放置皇后，确保不互相攻击。
 * 2. 使用列、主对角线、次对角线的标记数组进行剪枝。
 * 3. 当找到一个合法解时，将其深拷贝到res中。
 */
/* 回溯算法：n 皇后 */
void backtrack(int row, int n, char state[MAX_SIZE][MAX_SIZE], char ***res, int *resSize, bool cols[MAX_SIZE],
				bool diags1[2 * MAX_SIZE - 1], bool diags2[2 * MAX_SIZE - 1]) {
	// 当放置完所有行时，记录解
	if(row == n) {
		res[*resSize] = (char **)malloc(sizeof(char *) * n);
		for (int i = 0; i < n; ++i) {
			res[*resSize][i] = (char *)malloc(sizeof(char) * (n + 1));
			strcpy(res[*resSize][i], state[i]);
		}
		(*resSize)++;
		return;
	}
	// 遍历所有列
	for (int col = 0; col < n; col++) {
		// 计算该格子对应的主对角线和次对角线
		int diag1 = row - col + n - 1;
		int diag2 = row + col;
		// 剪枝：不允许该格子所在列、主对角线、次对角线上存在皇后
		if (!cols[col] && !diags1[diag1] && !diags2[diag2]) {
			// 尝试：将皇后放置在该格子
			state[row][col] = 'Q';
			cols[col] = diags1[diag1] = diags2[diag2] = true;
			// 放置下一行
			backtrack(row + 1, n, state, res, resSize, cols, diags1, diags2);
			// 回退：将该格子恢复为空
			state[row][col] = '#';
			cols[col] = diags1[diag1] = diags2[diag2] = false;
		}
	}
}

/**
 * nQueens - 求解N皇后问题的入口函数
 * @n: 棋盘的大小（N x N）及皇后的数量
 * @returnSize: 返回解的数量的指针（输出参数）
 *
 * 功能描述：
 * 1. 初始化棋盘状态和标记数组
 * 2. 分配结果存储空间
 * 3. 调用回溯算法求解所有合法布局
 * 4. 返回解数组
 *
 * 返回值:
 * 三维字符数组指针，存储所有合法的棋盘布局。
 * 每个解是一个二维字符数组，表示一个棋盘状态。
 * 调用者需负责释放返回的内存。
 *
 * 注意:
 * - 使用MAX_SIZE宏限制最大棋盘尺寸
 * - 棋盘初始化为全'#'（空位）
 * - 对角线数组大小为2n-1以覆盖所有可能对角线
 */
/* 求解 n 皇后 */
char ***nQueens(int n, int *returnSize) {
	char state[MAX_SIZE][MAX_SIZE];
	// 初始化 n*n 大小的棋盘，其中 'Q' 代表皇后，'#' 代表空位
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			state[i][j] = '#';
		}
		state[i][n] = '\0';
	}

	bool cols[MAX_SIZE] = {false};				// 记录列是否有皇后
	bool diags1[2 * MAX_SIZE - 1] = {false};	// 记录主对角线上是否有皇后
	bool diags2[2 * MAX_SIZE - 1] = {false};	// 记录次对角线上是否有皇后

	char ***res = (char ***)malloc(sizeof(char **) * MAX_SIZE);
	*returnSize = 0;
	backtrack(0, n, state, res, returnSize, cols, diags1, diags2);
	return res;
}

/* Driver Code */
int main(int argc, char **argv) {
	// int n = 4;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);  // 使用 argv[0] 显示程序名
		return 1;
	}

	int n = atoi(argv[1]);  // 使用 argv[1] 获取用户输入
	if (n <= 0) {
		fprintf(stderr, "Error: n must be positive\n");
		return 1;
	}

	int returnSize;
	char ***res = nQueens(n, &returnSize);

	printf("输入棋盘长宽为%d\n", n);
	printf("皇后放置方案共有 %d 种\n", returnSize);
	
	for(int i = 0; i < returnSize; ++i) {
		for (int j = 0; j < n; ++j){
			printf("[");
			for (int k = 0; res[i][j][k] != '\0'; ++k) {
				printf("%c", res[i][j][k]);
				if (res[i][j][k + 1] != '\0') {
					printf(", ");
				}
			}
			printf("]\n");
		}
		printf("---------------------\n");
	}

	// 释放内存
	for (int i = 0; i < returnSize; ++i) {
		for (int j = 0; j < n; ++j) {
			free(res[i][j]);
		}
		free(res[i]);
	}
	free(res);

	return 0;
}
