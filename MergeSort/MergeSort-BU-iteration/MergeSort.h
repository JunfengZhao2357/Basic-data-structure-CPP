//
// Created by z1551 on 2019/12/19.
//

#ifndef MERGESORT_FROM_BOTTOM_TO_UP_MERGESORT_H
#define MERGESORT_FROM_BOTTOM_TO_UP_MERGESORT_H

#include <iostream>
#include "SortTestHelper.h"


using namespace std;


// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename  T>
void __merge(T arr[], int l, int mid, int r){


    //* 使用new申请空间, 不要忘了在__merge函数的最后, delete掉申请的空间

    T *aux = new T[r-l+1];

    for( int i = l ; i <= r; i ++ )
        aux[i-l] = arr[i];          //arr的区间为[l,r]，but aux的区间为[0,r-l],会有偏移量l

    // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    int i = l, j = mid+1;
    for( int k = l ; k <= r; k ++ ){

        //首先应该考虑左右数组越界的问题

        if( i > mid ){                    // 如果左半部分元素已经全部处理完毕
            arr[k] = aux[j-l];
            j ++;
        }
        else if( j > r ){                 // 如果右半部分元素已经全部处理完毕
            arr[k] = aux[i-l];
            i ++;
        }

        else if( aux[i-l] < aux[j-l] ) {  // 左半部分所指元素 < 右半部分所指元素
            arr[k] = aux[i-l];
            i ++;
        }
        else{                             // 左半部分所指元素 >= 右半部分所指元素
            arr[k] = aux[j-l];
            j ++;
        }
    }

    delete[] aux;
}

// 递归使用归并排序,对arr[l...r]的范围进行排序,区间的开闭非常重要
template<typename T>
void __mergeSort(T arr[], int l, int r){

//    if(r-l <= 15){
//        insertionSort(arr,l,r);
//        return;
//    }
    // 上述if对于mergeSort当进行到非常小的数组时，就会近乎有序使用insertionSort会更好

    if( l >= r )           //首先考虑递归到底的情况
        return;

    int mid = (l+r)/2;     // 如果l和r是一个很大的int类型，l+r容易导致溢出
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    if(arr[mid]>arr[mid+1])         //增加一个判断对于近乎有序的数组一样很快
        __merge(arr, l, mid, r);
}

template<typename T>
void mergeSort(T arr[], int n){

    __mergeSort( arr , 0 , n-1 );
}



#endif //MERGESORT_FROM_BOTTOM_TO_UP_MERGESORT_H
