#include <cstdio>
#include <vector>
int insertionSort(std::vector<int>& arr){
    int count=0;
    for(int i=1;i<arr.size();++i){
        int temp = arr[i];
        int j=i;
        while(--j>=0&&arr[j]>=temp){
            arr[j + 1] = arr[j];
            count++;
        }
        arr[j+1]=temp;
    }
    return count;
}
int main(){
    std::vector<int> arr = {3, 4, 5, 6, 2, 2, 3, 34, 4, 1, 21, 1, 2, 23, 213, 43445, 4, 6, 4, 6, 67, 65, 3};
    int count=insertionSort(arr);
    for(auto& i:arr)
        printf("%d ",i);
    printf("count: %d\n",count);

}