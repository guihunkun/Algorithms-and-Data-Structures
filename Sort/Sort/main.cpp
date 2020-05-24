//
//  main.cpp
//  Sort
//
//  Created by 曲晓昆 on 2020/5/24.
//  Copyright © 2020 曲晓昆. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "SortHelper.h"
#include "MergeSort.h"
#include "QuickSort.h"
using namespace std;
using namespace sortHelper;


/*
 * 选择排序
 */
template<typename T>
void selectionSort(vector<T>& nums)
{
    unsigned long n = nums.size();
    for(unsigned int i = 0 ; i < n ; i ++)
    {
        int minIndex = i;
        for(unsigned int j = i + 1 ; j < n ; j ++ )
            if(nums[j] < nums[minIndex])
                minIndex = j;
        swap(nums[i] , nums[minIndex]);
    }
}


/*
 * 插入排序
 */
template<typename T>
void insertionSort(vector<T>& nums)
{
    unsigned long n = nums.size();
    for(unsigned int i = 1; i < n; i ++)
    {
        // 寻找元素arr[i]合适的插入位置
        
        // method 1
        #if 0
        for(unsigned int j = i; j > 0; j--)
        {
            if(nums[j] < nums[j-1] )
            {
                swap(nums[j], nums[j-1]);
            }
            else
            {
                break;
            }
        }
        #endif
        
        // method 2
        #if 0
        for(unsigned int j = i; j > 0 && nums[j] < nums[j-1]; j --)
        {
            swap(nums[j], nums[j-1]);
        }
        #endif
        
        // method 3
        #if 1
        T e = nums[i];
        unsigned int j; // j保存元素e应该插入的位置
        for(j = i; j > 0 && nums[j-1] > e; j--)
        {
            nums[j] = nums[j-1];
        }
        nums[j] = e;
        #endif
    }
    return;
}

/*
 * 冒泡排序 method 1
 */
template<typename T>
void bubbleSort(vector<T>& nums)
{
    unsigned long n = nums.size();
    bool swapped;
    do
    {
        swapped = false;
        for(unsigned int i = 1; i < n; i ++)
        {
            if(nums[i-1] > nums[i])
            {
                swap(nums[i-1], nums[i]);
                swapped = true;
            }
        }
        // 优化, 每一趟Bubble Sort都将最大的元素放在了最后的位置
        // 所以下一次排序, 最后的元素可以不再考虑
        n--;
    }while(swapped);
}

/*
 * 冒泡排序 method 2 ：使用newn进行优化
 */
template<typename T>
void bubble2Sort(vector<T>& nums)
{
    unsigned long n = nums.size();
    int newn; // 使用newn进行优化
    do
    {
        newn = 0;
        for(unsigned int i = 1; i < n; i ++)
        {
            if(nums[i-1] > nums[i])
            {
                swap(nums[i-1], nums[i]);
                // 记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
                newn = i;
            }
        }
        n = newn;
    }while(newn > 0);
}

/*
 * 希尔排序
 */
template<typename T>
void shellSort(vector<T>& nums)
{

    unsigned long n = nums.size();
    // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    while(h < n/3)
    {
        h = 3 * h + 1;
    }

    while( h >= 1 )
    {
        // h-sort the array
        for(unsigned int i = h; i < n; i++)
        {
            // 对 nums[i], nums[i-h], nums[i-2*h], nums[i-3*h]... 使用插入排序
            T e = nums[i];
            int j;
            for(j = i; j >= h && e < nums[j-h]; j -= h)
            {
                nums[j] = nums[j-h];
            }
            nums[j] = e;
        }
        h /= 3;
    }
}



int main(int argc, const char * argv[])
{

    vector<int> nums;
    unsigned int n = 10000;
    int range_l = 0;
    int range_r = 1000000;
    clock_t startTime, endTime;
    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    selectionSort(nums);
    endTime = clock();
    cout<<"SelectionSort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);

    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    insertionSort(nums);
    endTime = clock();
    cout<<"InsertionSort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);
    
    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    bubbleSort(nums);
    endTime = clock();
    cout<<"BubbleSort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);
  
    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    bubble2Sort(nums);
    endTime = clock();
    cout<<"Bubble2Sort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);
    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    shellSort(nums);
    endTime = clock();
    cout<<"ShellSort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);
    
    
    nums.clear();
    generateRandomArray(nums, n, range_l, range_r);
    startTime = clock();
    mergeSort(nums);
    endTime = clock();
    cout<<"MergeSort : "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
    isSorted(nums);
    
    
    
    return 0;
}
