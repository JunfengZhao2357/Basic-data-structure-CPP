#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"

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


// 比较InsertionSort和MergeSort两种排序算法的性能效率
// 整体而言, MergeSort的性能最优, 对于近乎有序的数组的特殊情况, 见测试2的详细注释
int main() {

    // Merge Sort是一个O(nlogn)复杂度的算法
    // 可以在1秒之内轻松处理100万数量级的数据
    // 注意：不要轻易尝试使用SelectionSort, InsertionSort或者BubbleSort处理100万级的数据
    // 否则，见识了O(n^2)的算法和O(nlogn)算法的本质差异
    int n = 50000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);

    delete[] arr1;
    delete[] arr2;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    // 对于近乎有序的数组, 数组越有序, InsertionSort的时间性能越趋近于O(n)
    // 所以可以尝试, 当swapTimes比较大时, MergeSort更快
    // 但是当swapTimes小到一定程度, InsertionSort变得比MergeSort快
    int swapTimes = 10;
    assert( swapTimes >= 0 );

    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);

    delete[] arr1;
    delete[] arr2;

    return 0;
}

//对于区间的开和闭[l,r]，左闭和右闭的区间容器大小为l-r+1
//对于左闭右开[l,r)，容器大小为l-r
//对于近乎有序的数组，InsertionSort比MergeSort还要快
//MergeSort无法退化成一个O(n)级别的算法，始终是一个O(nlogn)级别的算法