#include <iostream>
#include "SortTestHelper.h"
#include "Student.h"
using namespace std;

template<typename T>
void selectionSort(T arr[], int n){

    for(int i = 0 ; i < n ; i ++){

        //从小到大进行排序， 寻找[i,n)区间里的最小值
        int minIndex = i;

        for( int j = i + 1 ; j < n ; j ++ )

            if( arr[j] < arr[minIndex] )
                minIndex = j;

        swap( arr[i] , arr[minIndex] );
    }
}

int main() {

    // 测试排序算法的运行时间
    int N = 20000;
    int *arr = SortTestHelper::generateRandomArray(N,0,100000);
    //    selectionSort(arr,N);
    //    SortTestHelper::printArray(arr,N);
    SortTestHelper::testSort("Slectionsort",selectionSort,arr,20000);
    delete[] arr;  //注意delete掉new的数组


    // 测试模板函数，传入整型数组
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    selectionSort( a , 10 );
    for( int i = 0 ; i < 10 ; i ++ )
        cout<<a[i]<<" ";
    cout<<endl;

    // 测试模板函数，传入浮点数数组
    float b[4] = {4.4,3.3,2.2,1.1};
    selectionSort(b,4);
    for( int i = 0 ; i < 4 ; i ++ )
        cout<<b[i]<<" ";
    cout<<endl;

    // 测试模板函数，传入字符串数组
    string c[4] = {"D","C","B","A"};
    selectionSort(c,4);
    for( int i = 0 ; i < 4 ; i ++ )
        cout<<c[i]<<" ";
    cout<<endl;

    // 测试模板函数，传入自定义结构体Student数组
    // 在student.h中重新定义了 "<" 分数高的排在前面
    Student d[4] = { {"D",90} , {"C",100} , {"B",95} , {"A",95} };
    selectionSort(d,4);
    for( int i = 0 ; i < 4 ; i ++ )
        cout<<d[i];
    cout<<endl;


    return 0;
}

// 选择排序无论在什么情况下，两层循环都会走完，所以就是O(n^2)级别的排序