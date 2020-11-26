#include <cstdio>
#include <vector>
#include <chrono>
#include<algorithm>
#include <random>
#include <iostream>

#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"
#include "radixSort.h"

using SORT_FUNC=void(*)(std::vector<int>& a);

void testSort(SORT_FUNC func,std::vector<std::vector<int>> testcases){
    auto starttime=std::chrono::steady_clock::now();
    for(int i=0,len=testcases.size();i<len;++i){
        //for(auto& j:testcases[i])
        //    printf("%d ",j);
        func(testcases[i]);
        //printf("\n result:");
        //for(auto& j:testcases[i])
        //    printf("%d ",j);
    }
    auto dt=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-starttime).count();
    printf("time cost: %lld ms",dt);
}

std::vector<int> buildNormalRandomVector(double mean,double stddev,int num){

    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{mean,stddev}; 
    std::vector<int> ret(num); 
    for(auto& i:ret)
        i=d(gen);
    return ret;
}

std::vector<int> buildUniformRandomVector(int start,int end,int num){

    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::uniform_int_distribution<> d{start,end}; 
    std::vector<int> ret(num); 
    for(auto& i:ret)
        i=d(gen);
    return ret;
}

int main(){

    auto a=buildUniformRandomVector(0,1000,100);
    radixSort(a,16);
    for(auto i:a)
        printf("%d ",i);

    return 0;
    std::vector<std::vector<int>>  testcases(100,std::vector<int>());
    for(auto &ele:testcases)
        ele=buildNormalRandomVector(0,10,10000);


    auto testcases0=testcases;
    auto starttime=std::chrono::steady_clock::now();
    for(auto& i:testcases0){
        std::sort(i.begin(),i.end());
    }
    auto dt=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-starttime).count();
    printf("\nstl: %lld ms",dt);
    printf("\nquicksort:");testSort(quickSort,testcases);
//    printf("\nquicksort2:");testSort(quickSort2,testcases);    //stack overflow??
    printf("\ninsertionsort:");testSort(insertionSort,testcases);
    printf("\nmergesort:");testSort(mergeSort,testcases);

    return 0;
}

