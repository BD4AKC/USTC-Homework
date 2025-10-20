/* P8.寻找集合中未出现的数
 *
 * 题目描述：
 * 读入一个未排序int型数组nums，
 * 请找出其中没有出现的最小正整数。
 * 数组长度不超过10^5，数字大小[-2^31, 2^31-1]。
 *
 * 要求：时间复杂度为O(n)，且只使用常数级别的额外存储空间。
 *
 * 输入形式：
 * 第一行n
 * 第二行输入n个数，空格分割
 *
 * 输出形式：
 * 集合中未出现的最小正整数
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *nums = (int *)malloc(n * sizeof(int));

    // 读取输入
    for (int i = 0; i < n; i++)
    {
        scanf("%d", nums + i);
    }

    // 置换位置，使得nums[i] = i + 1
    for (int i = 0; i < n; i++)
    {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
        {
            // 交换nums[i]和nums[nums[i] - 1]
            int temp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = temp;
        }
    }

    // 找出第一个不符合条件的位置
    for (int i = 0; i < n; i++)
    {
        if (nums[i] != i + 1)
        {
            printf("%d\n", i + 1);
            free(nums);
            return 0;
        }
    }

    // 如果所有位置都符合条件，返回n + 1
    printf("%d\n", n + 1);
    free(nums);
    return 0;
}