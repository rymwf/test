#include <cstdio>
#include <vector>
#include <chrono>
#include<algorithm>
#include <random>

#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"

using SORT_FUNC=void(*)(std::vector<int>& a);

void testSort(SORT_FUNC func,std::vector<std::vector<int>> testcases){
    auto starttime=std::chrono::steady_clock::now();
    for(int i=0;i<testcases.size();++i){
        //for(auto& j:testcases[i])
        //    printf("%d ",j);
        func(testcases[i]);
        //printf("\n result:");
        //for(auto& j:testcases[i])
        //    printf("%d ",j);
    }
    auto dt=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-starttime).count();
    printf("time cost: %d ms",dt);
}

int main(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    std::vector<std::vector<int>>  testcases(100,std::vector<int>(10000,0));
    std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);
    for(auto&i:testcases){
        for(auto& j:i)
            j=distrib(gen);
    }
    auto testcases0=testcases;
    auto starttime=std::chrono::steady_clock::now();
    for(auto& i:testcases0){
        std::sort(i.begin(),i.end());
    }
    auto dt=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-starttime).count();
    printf("\nstl: %d ms",dt);
    printf("\nquicksort:");testSort(quickSort,testcases);
//    printf("\nquicksort2:");testSort(quickSort2,testcases);    //stack overflow??
    printf("\ninsertionsort:");testSort(insertionSort,testcases);
    printf("\nmergesort:");testSort(mergeSort,testcases);

    return 0;
}

