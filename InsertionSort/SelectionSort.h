//
// Created by z1551 on 2019/12/18.
//

#ifndef INSERTION_SORT_SELECTIONSORT_H
#define INSERTION_SORT_SELECTIONSORT_H

#include <iostream>

using namespace std;


template<typename T>
void selectionSort(T arr[], int n){

    for(int i = 0 ; i < n ; i ++){

        int minIndex = i;
        for( int j = i + 1 ; j < n ; j ++ )
            if( arr[j] < arr[minIndex] )
                minIndex = j;

        swap( arr[i] , arr[minIndex] );
    }
}



#endif //INSERTION_SORT_SELECTIONSORT_H
