//
//  SortHelper.h
//  Sort
//
//  Created by 曲晓昆 on 2020/5/24.
//  Copyright © 2020 曲晓昆. All rights reserved.
//

#ifndef SortHelper_h
#define SortHelper_h


#include <iostream>
#include <vector>
using namespace std;

namespace sortHelper
{


/*
 * 生成有n个元素的随机数组,每个元素的随机范围为[rangeL, rangeR]
 */
template<typename T>
bool generateRandomArray(vector<T>& nums, unsigned int n, T range_l, T range_r)
{
    nums.clear();
    srand((unsigned)time(NULL));
    for(unsigned int i = 0; i < n; i++)
    {
        T num =rand() % (range_r - range_l + 1) + range_l;
        nums.push_back(num);
    }
    return true;
}


/*
 * 生成一个近乎有序的数组
 * 首先生成一个含有[0...n-1]的完全有序数组, 之后随机交换swapTimes对数据
 * swapTimes定义了数组的无序程度:
 * swapTimes == 0 时, 数组完全有序
 * swapTimes 越大, 数组越趋向于无序
 */
template<typename T>
bool generateNearlyOrderedArray(vector<T>& nums, unsigned int n, int swapTimes)
{
    nums.resize(n);
    for(int i = 0 ; i < n ; i ++)
    {
        nums[i] = i;
    }
    srand((unsigned)time(NULL));
    for(unsigned int i = 0 ; i < swapTimes ; i ++)
    {
        int posx = rand()%n;
        int posy = rand()%n;
        swap(nums[posx] , nums[posy]);
    }
    return true;
}


/*
 * 打印arr数组的所有内容
 */
template<typename T>
void printArray(vector<T>& nums)
{
    unsigned int n = nums.size();
    for(unsigned int i = 0; i < n; i++)
    {
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    return;
}

/*
 * 判断arr数组是否有序
 */
template<typename T>
bool isSorted(vector<T>& nums)
{
    unsigned long n = nums.size();
    for(unsigned int i = 0; i < n - 1; i++)
    {
        if(nums[i] > nums[i + 1])
        {
            return false;
        }
    }
    return true;
}

};

#endif /* SortHelper_h */
