//
// Created by z1551 on 2019/12/20.
//

#ifndef HEAPIFY_IN_PLACE_HEAPSORT_H
#define HEAPIFY_IN_PLACE_HEAPSORT_H

template<typename T>
void __shiftDown(T arr[], int n, int k){

    while( 2*k+1 < n ){       //此时数组从0开始索引，所以 parent(i) = (i-1)/2;
        int j = 2*k+1;                             // leftchild(i) = 2*i+1
        if( j+1 < n && arr[j+1] > arr[j] )         // rightchild(i) = 2*i+2
            j += 1;

        if( arr[k] >= arr[j] )break;

        swap( arr[k] , arr[j] );
        k = j;
    }
}



// 不使用一个额外的最大堆, 直接在原数组上进行原地的堆排序
template<typename T>
void heapSort(T arr[], int n){

    // Heapify
    // 注意，此时我们的堆是从0开始索引的
    // 从(最后一个元素的索引-1)/2开始
    // 最后一个元素的索引 = n-1
    for( int i = (n-1)/2 ; i >= 0 ; i -- )
        __shiftDown(arr, n, i);

    for( int i = n-1; i > 0 ; i-- ){
        swap( arr[0] , arr[i] );
        __shiftDown(arr, i, 0);      //这里要维护堆的大小，每次都要减一个1，即实时容量等于i
    }
}


#endif //HEAPIFY_IN_PLACE_HEAPSORT_H
