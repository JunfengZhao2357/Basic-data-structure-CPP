#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"
// This is the github test
using namespace std;

template<typename T>
void insertionSort(T arr[], int n){

    for( int i = 1 ; i < n ; i ++ ) {

        // 寻找元素arr[i]合适的插入位置
        // 写法1
//        for( int j = i ; j > 0 ; j-- )
//            if( arr[j] < arr[j-1] )
//                swap( arr[j] , arr[j-1] );
//            else
//                break;

        // 写法2
//        for( int j = i ; j > 0 && arr[j] < arr[j-1] ; j -- )
//            swap( arr[j] , arr[j-1] );

        // 写法3：improved algorithm 将“swap”改成“赋值语句”进行优化
        T e = arr[i];       //寻找arr[i]应该放入的位置
        int j;              //j为元素e应该插入的位置
        for(j = i; j > 0 && arr[j-1] > e; j--){
            arr[j]=arr[j-1];
        }
        arr[j] = e;

    }

    return;
}

// 比较SelectionSort和InsertionSort两种排序算法的性能效率

int main() {

    int n = 20000;

    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int *arr1 = SortTestHelper::generateRandomArray(n,0,3);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort,arr1,n);
    SortTestHelper::testSort("Selection Sort", selectionSort,arr2,n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;

    return 0;
}

//最坏的情况下，插入排序仍然是O(n^2)，但是插入排序可以提前结束比较。
//对于近乎有序的序列，插入排序几乎就是O(n)的算法