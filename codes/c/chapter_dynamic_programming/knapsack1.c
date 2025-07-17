#include "../utils/common.h"
int myMax(int a, int b) {
	return a > b ? a: b;
}

/**
 * knapsackDFS - 暴力搜索解决0-1背包问题
 * @wgt: 物品重量数组（下标从0开始）
 * @val: 物品价值数组（与wgt一一对应）
 * @i: 当前待决策的物品编号（从n开始递减）
 * @c: 当前背包剩余容量
 *
 * 返回值: 前i个物品在容量c下的最大价值
 * 注意: 递归终止条件为i=0（无物品可选）或c=0（无剩余容量）
 */
/* 0-1 背包：暴力搜索 */
int knapsackDFS(int wgt[], int val[], int i, int c) {
	// 若已选完所有物品或背包无剩余容量，则返回价值 0 
	if (i == 0 || c ==0) {
		return 0;
	}
	// 若超过背包容量，则只能选择不放入背包
	if(wgt[i - 1] > c) {
		return knapsackDFS(wgt, val, i - 1, c);
	}
	// 计算不放入和放入物品 i 的最大价值
	int no = knapsackDFS(wgt, val, i - 1, c);
	int yes = knapsackDFS(wgt, val, i - 1, c - wgt[i - 1]) + val[i - 1];
	// 返回两者方案种价值更大的那一个
	return myMax(no, yes);
}

/**
 * knapsackDFSMem - 记忆化搜索解决0-1背包问题
 * @wgt: 物品重量数组（下标从0开始）
 * @val: 物品价值数组（与wgt一一对应）
 * @memCols: 记忆化表格的列数（即背包容量上限+1）
 * @mem: 二维记忆化数组，存储已计算的子问题解
 * @i: 当前待决策的物品编号（初始为物品总数n，递减至0）
 * @c: 当前背包剩余容量
 *
 * 返回值: 前i个物品在容量c下的最大价值
 * 注意: 使用记忆化避免重复计算，mem需初始化为-1
 */
/* 0-1 背包：记忆化搜索 */
int knapsackDFSMem(int wgt[], int val[], int memCols, int **mem, int i, int c) {
	// 若已选完所有物品或背包无剩余容量，则返回价值0
	if (i == 0 || c == 0) {
		return 0;
	}
	// 若已有记录，则直接返回
	if(mem[i][c] != -1) {
		return mem[i][c];
	}
	// 若超过背包容量，则只能选择不放入背包
	if(wgt[i - 1] > c) {
		return knapsackDFSMem(wgt, val, memCols, mem, i -1, c);
	}
	// 计算不放入和放入物品 i 的最大价值
	int no = knapsackDFSMem(wgt, val, memCols, mem, i - 1, c);
	int yes = knapsackDFSMem(wgt, val, memCols, mem, i - 1, c - wgt[i - 1]) + val[i - 1];
	// 记录并返回两种方案中价值更大的那一个
	mem[i][c] = myMax(no, yes);
	return mem[i][c];
}

/**
 * knapsackDP - 动态规划解决0-1背包问题
 * @wgt: 物品重量数组（下标从0开始）
 * @val: 物品价值数组（与wgt一一对应）
 * @cap: 背包总容量
 * @wgtSize: 物品数量（即数组wgt的长度）
 *
 * 返回值: 背包能装下的最大价值
 * 注意: 使用二维DP表，空间复杂度为O(n×cap)
 */
/* 0-1 背包：动态规划 */
int knapsackDP(int wgt[], int val[], int cap, int wgtSize) {
	int n = wgtSize;
	// 初始化 dp 表
	int **dp = malloc((n + 1) * sizeof(int *));
	for (int i  = 0; i <= n; i++) {
		dp[i] = calloc(cap + 1, sizeof(int));
	}
	// 状态转移
	for(int i = 1; i <= n; i++) {
		for (int c = 1; c <= cap; c++) {
			if (wgt[i - 1] > c) {
				// 若超过背包容量，则不选物品 i
				dp[i][c] = dp[i - 1][c];
			} else {
				// 不选和选物品 i 这两种方案的较大值
				dp[i][c] = myMax(dp[i - 1][c], dp[i - 1][c - wgt[i - 1]] + val[i - 1]);
			}
		}
	}
	int res = dp[n][cap];
	// 释放内存
	for (int i = 0; i <= n; i++) {
		free(dp[i]);
	}
	return res;
}

/**
 * knapsackDPComp - 空间优化后的动态规划解决0-1背包问题
 * @wgt: 物品重量数组（下标从0开始）
 * @val: 物品价值数组（与wgt一一对应）
 * @cap: 背包总容量
 * @wgtSize: 物品数量（即数组wgt的长度）
 *
 * 返回值: 背包能装下的最大价值
 * 注意: 使用一维DP表，空间复杂度优化至O(cap)
 */
/* 0-1 背包：空间优化后的动态规划 */
int knapsackDPComp(int wgt[], int val[], int cap, int wgtSize) {
	int n = wgtSize;
	// 初始化 dp 表
	int *dp = calloc(cap + 1, sizeof(int));
	// 状态转移
	for (int i = 1; i <= n; i++) {
		// 倒序遍历
		for (int c = cap; c>= 1; c--) {
			if(wgt[i - 1] <= c) {
				// 不选和选物品 i 这两种方案的较大值
				dp[c] = myMax(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
			}
		}
	}
	int res = dp[cap];
	// 释放内存
	free(dp);
	return res;
}

/* Driver Code */
int main() {
	int wgt[] = {10, 20,30, 40, 50};
	int val[] = {50, 120, 150, 210, 240};
	int cap = 50;
	int n = sizeof(wgt) / sizeof(wgt[0]);
	int wgtSize = n;

	// 暴力搜索
	int res = knapsackDFS(wgt, val, n, cap);
	printf("不超过背包容量的最大物品价值为 %d\n", res);

	// 记忆化搜索
	int **mem = malloc((n + 1) * sizeof(int *));
	for (int i = 0; i <= n; i++) {
		mem[i] = malloc((cap + 1) * sizeof(int *));
		memset(mem[i], -1, (cap + 1) * sizeof(int));
	}
	res = knapsackDFSMem(wgt, val, cap + 1, mem, n, cap);
	printf("不超过背包容量的最大物品价值为 %d\n", res);
	// 释放内存
	for(int i = 0; i <= n; i++) {
		free(mem[i]);
	}
	free(mem);

	// 动态规划
	res = knapsackDP(wgt, val, cap, wgtSize);
	printf("不超过背包容量的最大物品价值为 %d\n", res);

	// 空间优化后的动态规划
	res = knapsackDPComp(wgt, val, cap, wgtSize);
	printf("不超过背包容量的最大物品价值为 %d\n", res);

	return 0;
}
