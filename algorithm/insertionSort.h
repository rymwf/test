#pragma once
#include <cstdio>
#include <vector>
void insertionSort(std::vector<int>& arr){
    for(int i=1,len=arr.size();i<len;++i){
        int temp = arr[i];
        int j=i;
        while(--j>=0&&arr[j]>=temp){
            arr[j + 1] = arr[j];
        }
        arr[j+1]=temp;
    }
}