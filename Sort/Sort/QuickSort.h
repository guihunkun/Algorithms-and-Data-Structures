//
//  QuickSort.h
//  Sort
//
//  Created by 曲晓昆 on 2020/5/24.
//  Copyright © 2020 曲晓昆. All rights reserved.
//

#ifndef QuickSort_h
#define QuickSort_h

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;


// 双路快速排序的partition2
// 返回p, 使得nums[l...p-1] < nums[p] ; nums[p+1...r] > nums[p]
template <typename T>
unsigned long partition2(vector<T>& nums, long long l, long long r)
{
    // 随机在nums[l...r]的范围中, 选择一个数值作为标定点pivot
    srand((unsigned)time(NULL));
    long long pivot = rand() % (r-l+1) + l;
    swap(nums[l], nums[pivot]);
    T v = nums[l];

    // nums[l+1...i) <= v; nums(j...r] >= v
    long long i = l+1, j = r;
    while(true)
    {
        while(i <= r && nums[i] < v)
            i++;
        while(j >= l+1 && nums[j] > v)
            j--;
		if(i > j)
            break;
 
        swap(nums[i], nums[j]);
        i++;
        j--;
    }
	
    swap(nums[l], nums[j]);
    return j;
}



template <typename T>
unsigned long partition(vector<T>& nums, long long l, long long r)
{

    T v = nums[l];
    long long j = l; // nums[l+1...j] < v ; nums[j+1...i) > v
    for(long long i = l + 1; i <= r; i ++)
    {
        if(nums[i] < v )
        {
            j ++;
            swap(nums[j] , nums[i]);
        }
    }
    swap(nums[l] , nums[j]);
    return j;
}

// 对nums[l...r]部分进行快速排序
template <typename T>
void quickSort(vector<T>& nums, long long l, long long r)
{
    if(l >= r)
        return;
    long long p = partition2(nums, l, r);
    if(p == 0 || l+1 == p || p + 1 == r)
        return;
    quickSort(nums, l, p-1);
    quickSort(nums, p+1, r);
}

#if 0
template <typename T>
void quickSort(vector<T>& nums)
{
    srand((unsigned)time(NULL));
    long long n = nums.size();
    quickSort(nums, 0, n-1);
}
#endif


#if 1
// 递归的三路快速排序算法
template <typename T>
void quickSort3Ways(vector<T>& nums, long long l, long long r)
{
    if(l >= r)
        return;
    // 随机在nums[l...r]的范围中, 选择一个数值作为标定点pivot
    swap(nums[l], nums[rand()%(r-l+1)+l] );
    T v = nums[l];
    
    long long lt = l;     // nums[l+1...lt] < v
    long long gt = r + 1; // nums[gt...r] > v
    long long i = l+1;    // nums[lt+1...i) == v
    while(i < gt)
    {
        if(nums[i] < v )
        {
            swap(nums[i], nums[lt+1]);
            i ++;
            lt ++;
        }
        else if(nums[i] > v )
        {
            swap(nums[i], nums[gt-1]);
            gt --;
        }
        else
        { // nums[i] == v
            i ++;
        }
    }
    swap(nums[l], nums[lt] );
    quickSort3Ways(nums, l, lt-1);
    quickSort3Ways(nums, gt, r);
}


template <typename T>
void quickSort(vector<T>& nums)
{
    srand((unsigned)time(NULL));
    long long n = nums.size();
    quickSort3Ways(nums, 0, n-1);
}
#endif


#endif /* QuickSort_h */
