int digit(int num, int exp) {
	return (num / exp) % 10;
}

void countingSortDigit(int nums[], int size, int exp) {
	int *counter = (int *)malloc((sizeof(int) * 10);
	memset(counter, 0, sizeof(int) * 10);
	
	for(int i = 0; i < size; i++) {
		int d = digit(nums[i], exp);
		counter[d]++;
	}

	for(int i = 1; i < 10; i++) {
	counter[i] += counter[i - 1];
	}

	int *res = (int *)malloc(sizeof(int) * size);
	for (int i = size - 1; i >=0; i --) {
		int d = digit(nums[i], exp);
		int j = counter[d] - 1;
		res[j] = nums[i];
		counter[d]--;
	}

	for (int i = 0; i < size; i++){
		nums[i] = res[i];
	}

	free(res);
	free(counter);
}

void radixSort(int nums[], int size) {
	int max = INT32_MIN;
	for (int i = 0; i < size; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}

	for (int exp = 1; max >= exp; exp *= 10)
		countingSortDigit(nums, size, exp);
}

int main() {
	int nums[] = {10546151, 35663510, 42865989, 34862445, 81883077,
					88906420, 72429244, 30524779, 82060337, 63832996};
	int size = sizeof(nums) / sizeof(int);
	radixSort(nums, size);
	printf("基数排序完成后 nums = ");
	printArray(nums, size);
}
