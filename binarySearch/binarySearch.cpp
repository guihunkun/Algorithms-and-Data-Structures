#include <iostream>
#include <string>
#include "vector"
#include "map"
#include "set"
#include "queue"
#include "stack"
#include "algorithm"
using namespace std;


#if 0
二分查找也称折半查找（Binary Search），它是一种效率较高的查找方法。
二分查找需要满足两个前提条件：1）必须采用顺序存储结构。2）元素按关键字有序排列。
关键需要明白查找的区间是"[]"还是"[)"； 以及查找的数据不等于目标元素时，目标元素所在的区间。

#endif


/*
 * 1
 * LeetCode 剑指 Offer 11 ： 旋转数组的最小数字
 * https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/
 */
int minArray(vector<int>& numbers)
{
    int left = 0;
    int right = numbers.size()-1;
    while(left < right)
    {
        int mid = left + (right - left)/2;
        if(numbers[mid] < numbers[right]) {
            right = mid;
        } else if(numbers[mid] > numbers[right]) {
            left = mid + 1;
        } else {
            right -= 1;
        }
    }
    return numbers[left];
}


/*
 * 2
 * LeetCode 面试题 10.05 : 稀疏数组搜索
 * https://leetcode-cn.com/problems/sparse-array-search-lcci/
 */
int findString(vector<string>& words, string s)
{
    int l = 0, r = words.size() - 1;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        while(mid < r && words[mid] == "")
            mid ++; //跳过空格
        if(mid == r)
        {
            r = (l + r) >> 1;
            continue;
        } //若是跳过空格，mid == r, 则二分后赋值给r
        if(words[mid] == s)
            return mid; //标准二分法
        else if(words[mid] < s)
            l = mid + 1;
        else
            r = mid;
    }
    return words[r] == s ? r : -1;
}


/*
 * 3
 * LeetCode 378 : 有序矩阵中第K小的元素
 * https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/
 */
int kthSmallest(vector<vector<int>>& matrix, int k)
{
    int n = matrix.size(),l = matrix[0][0], r = matrix[n-1][n-1];
    int mid = l;
    while(l < r)
    {
        mid=l + (r-l)/2;
        int cnt = 0, cnt2 = 0;
        for(int i = 0; i < n; i++)
        {
            auto &v = matrix[i];
            cnt += lower_bound(v.begin(), v.end(),mid) - v.begin();
            cnt2 += upper_bound(v.begin(), v.end(),mid) - v.begin();
        }
        if(cnt < k && cnt2 >= k)
            return mid;
        if(cnt<k)
            l = mid+1;
        else
            r = mid;
    }
    return mid;
}


/*
 * 4
 * LeetCode 面试题 10.09 : 排序矩阵查找
 * https://leetcode-cn.com/problems/sorted-matrix-search-lcci/
 */
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    if(matrix.empty())
        return false;
    int row = 0;
    int column = matrix[0].size() - 1;
    while(row <= matrix.size() - 1 && column >= 0)
    {
        if(matrix[row][column] == target)
            return true;
        if(matrix[row][column] > target)
            --column;
        else
            ++row;
    }
    return false;
}


/*
 * 5
 * LeetCode 34 : 在排序数组中查找元素的第一个和最后一个位置
 * https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 */
vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> res(2, -1);
    if(nums.size() == 0)
        return res;
    //find front
    int start = 0, end = nums.size() - 1;
    while(start + 1 < end)
    {
        int mid = start + (end - start)/2;
        if(nums[mid] >= target)
            end = mid;
        else
            start = mid;
    }
    if(nums[start] == target)
        res[0] = start;
    else if(nums[end] == target)
        res[0] = end;

    //find back
    start = 0; end = nums.size() - 1;
    while(start + 1 < end)
    {
        int mid = start + (end - start)/2;
        if(nums[mid] <= target)
            start = mid;
        else
            end = mid;
    }
    if(nums[end] == target)
        res[1] = end;
    else if(nums[start] == target)
        res[1] = start;

    return res;
}


/*
 * 6
 * LeetCode 852 : 山脉数组的峰顶索引
 * https://leetcode-cn.com/problems/peak-index-in-a-mountain-array/
 */
int peakIndexInMountainArray(vector<int>& A)
{
    assert(A.size() >= 3);
    int left = 0;
    int right = A.size() - 1;
    while(left < right)
    {
        int mid = left + (right - left) / 2;
        if(A[mid] < A[mid + 1])
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}


/*
 * 7
 * LeetCode 33 : 搜索旋转排序数组
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
 */
int search(vector<int>& nums, int target)
{
    if(nums.empty()) {
        return -1;
    }
    int n = nums.size();
    if(n == 1) {
        return nums[0] == target ? 0 : -1;
    }
    int l = 0, r = n - 1;
    while(l <= r)
    {
        int mid = l + (r-l)/2;
        if(nums[mid] == target)
            return mid;
        if(nums[0] <= nums[mid]) {
            if(nums[0] <= target && target < nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if(nums[mid] < target && target <= nums[n - 1]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}


/*
 * 8
 * LeetCode 704 : 二分查找
 * https://leetcode-cn.com/problems/binary-search/
 */
#if 0
int search(vector<int>& nums, int target)
{
    if(nums.empty())
        return -1;
    int start = 0, end = nums.size()-1;
    while(start <= end)
    {
        int mid = start + (end-start)/2;
        if(nums[mid] == target)
            return mid;
        else if(nums[mid] < target)
            start = mid+1;
        else
            end = mid-1;
    }
    return -1;
}
#endif


#if 0
int binarySearch(vector<T>& nums, T target)
{
    int left = 0, right = ...;
    while(...)
    {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target) {
            ...
        } else if(nums[mid] < target) {
            left = ...
        } else if(nums[mid] > target) {
            right = ...
        }
    }
    return ...;
}
#endif


int main()
{
    cout<<"Binary Search"<<endl;
    return 0;
}
