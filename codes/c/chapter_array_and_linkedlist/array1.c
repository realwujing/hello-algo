/**
* File: array.c
* Created Time: 2022-12-20
* Author: MolDuM (moldum@163.com)
*/

#include "../utils/common.h"

int randomAcess(int *nums, int size) {
	int randomIndex = rand() % size;
	int randomNum = nums[randomIndex];
	return randomNum;
}

int *extend(int *nums, int size, int enlarge) {
	int *res = (int *)malloc(sizeof(int)* (size + enlarge));
	for (int i = 0; i < size; i ++) {
		res[i] = nums[i];
	}
	for (int i = size; i < size + enlarge; i++) {
		res[i] = 0;
	}
	return res;
}

void insert(int *nums, int size, int num, int index) {
	for (int i = size - 1; i > index; i--) {
		nums[i] = nums[i -1];
	}
	nums[index] = num;
}

void removeItem(int *nums, int size, int index) {
	for (int i = index; i < size - 1; i++) {
		nums[i] = nums[i + 1];
	}
}

void traverse(int *nums, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		count +=nums[i];
	}
}

int find(int *nums, int size, int target) {
	for (int i = 0; i < size; i++) {
		if (nums[i] == target)
			return i;
	}
	return -1;
}

int main() {
	int size =5;
	int arr[5];
	printf("数组 arr = ");
	printfArray(arr, size);

	int nums[] = {1, 3, 2, 5, 4};
	printf("数组 nums = ");
	printfArray(nums, size);
	
	int randomNum = randomAcess(nums, size);
	printf("在 nums 中获取随机元素 %d", randomNum);

	int enlarge = 3;
	int *res = extend(nums, size, enlarge);
	size += enlarge;
	printf("将数组长度扩展至 8 , 得到 nums = ");
	printfArray(res, size);

	insert(res, size, 6, 3);
	printf("在索引 3 处插入数字 6 ，得到 nums =");
	printArray(res, size);

	removeItem(res, size, 2);
	printf("删除索引 2 处 的元素，得到 nums =");
	printArray(res, size);

	traverse(res, size);

	int index = find(res, size, 3);
	printf("在 res 中查找元素 3，得到索引 = %d\n", index);

	free(res);
	return 0;
}

