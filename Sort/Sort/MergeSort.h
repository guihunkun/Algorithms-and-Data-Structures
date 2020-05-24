//
//  MergeSort.h
//  Sort
//
//  Created by 曲晓昆 on 2020/5/24.
//  Copyright © 2020 曲晓昆. All rights reserved.
//

#ifndef MergeSort_h
#define MergeSort_h

#include <iostream>
#include <vector>
using namespace std;

// 将nums[l...mid]和nums[mid+1...r]两部分进行归并
template<typename  T>
void merge(vector<T>& nums, unsigned long l, unsigned long mid, unsigned long r)
{

    vector<T> aux(r-l+1);
    for(unsigned long i = l; i <= r; i ++)
    {
        aux[i-l] = nums[i];
    }

    // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    unsigned long i = l, j = mid+1;
    for(unsigned long k = l; k <= r; k ++)
    {
        if(i > mid)
        {
            // 如果左半部分元素已经全部处理完毕
            nums[k] = nums[j-l];
            j++;
        }
        else if(j > r)
        {
            // 如果右半部分元素已经全部处理完毕
            nums[k] = nums[i-l];
            i++;
        }
        else if(aux[i-l] < aux[j-l])
        {
            // 左半部分所指元素 < 右半部分所指元素
            nums[k] = nums[i-l];
            i++;
        }
        else
        {
            // 左半部分所指元素 >= 右半部分所指元素
            nums[k] = aux[j-l];
            j++;
        }
    }
}

// 递归使用归并排序,对nums[l...r]的范围进行排序
template<typename T>
void mergeSort(vector<T>& nums, unsigned long l, unsigned long r)
{

    if(l >= r)
    {
        return;
    }
    unsigned long mid = (l+r)/2;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid+1, r);
    merge(nums, l, mid, r);
}


template<typename T>
void mergeSort(vector<T>& nums)
{
    unsigned long n = nums.size();
    mergeSort(nums, 0, n-1);
}


#endif /* MergeSort_h */
