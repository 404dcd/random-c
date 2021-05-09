#include <stdlib.h>
#include <stdio.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    *returnSize = 2;
    int* ret = malloc(2 * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        int match = target - nums[i];
        for (int j = i+1; j < numsSize; j++) {
            if (nums[j] == match) {
                ret[0] = i;
                ret[1] = j;
                return ret;
            }
        }
    }
    return ret;
}

void runTest(int* nums, int numsSize, int target) {
    int lenout;
    int* out;
    int x;
    out = twoSum(nums, numsSize, target, &lenout);
    printf("Input: nums = [");
    for (x = 0; x < numsSize; x++) {
        printf("%d ", nums[x]);
    }
    printf("\b], target = %d\nOutput: [", target);
    for (x = 0; x < lenout; x++) {
        printf("%d ", out[x]);
    }
    printf("\b]\n\n");
    free(out);
    return;
}

int main() {
    int* nums = (int[4]) {2, 7, 11, 15};
    runTest(nums, 4, 9);

    nums = (int[3]) {3, 2, 4};
    runTest(nums, 3, 6);

    nums = (int[2]) {3, 3};
    runTest(nums, 2, 6);

    return 0;
}