#include <iostream>
#include "SortTestHelper.h"
#include "MergeSort.h"


using namespace std;

// 使用自底向上的归并排序算法
template <typename T>
void mergeSortBU(T arr[], int n){

    // Merge Sort Bottom Up 无优化版本
    for( int sz = 1; sz < n ; sz += sz )
        for( int i = 0 ; i + sz< n  ; i += sz+sz )
            // 对 arr[i...i+sz-1] 和 arr[i+sz...i+2*sz-1] 进行归并
            // i+sz<n, 是要保证第一个区间arr[i,i+sz-1]要存在
            // min（i+sz+sz-1,n-1)是防止i+sz+sz-1大于整个区间
            __merge(arr, i, i+sz-1, min(i+sz+sz-1,n-1) );


    // Merge Sort Bottom Up 优化
    // 对于小数组, 使用插入排序优化
//    for( int i = 0 ; i < n ; i += 16 )
//        insertionSort(arr,i,min(i+15,n-1));
//
//    for( int sz = 16; sz < n ; sz += sz )
//        for( int i = 0 ; i < n - sz ; i += sz+sz )
//            // 对于arr[mid] <= arr[mid+1]的情况,不进行merge
//            if( arr[i+sz-1] > arr[i+sz] )
//                __merge(arr, i, i+sz-1, min(i+sz+sz-1,n-1) );

    // Merge Sort BU 也是一个O(nlogn)复杂度的算法，虽然只使用两重for循环
    // 所以，Merge Sort BU也可以在1秒之内轻松处理100万数量级的数据
    // 注意：不要轻易根据循环层数来判断算法的复杂度，Merge Sort BU就是一个反例


}


// 比较Merge Sort和Merge Sort Bottom Up两种排序算法的性能效率
// 整体而言, 两种算法的效率是差不多的。但是如果进行仔细测试, 递归自顶向下的归并排序会略胜一筹。

int main() {

    int n = 1000000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Merge Sort Bottom Up", mergeSortBU, arr2, n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Merge Sort Bottom Up", mergeSortBU, arr2, n);

    delete[] arr1;
    delete[] arr2;

    return 0;
}

//**自底向上的mergeSort因为没有对数组进行索引所以可以对链表进行排序