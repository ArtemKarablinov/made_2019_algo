//  main.cpp
//  hw2 Excersise 3_2
//
//  Created by KARABLINOV Artem on 06/11/2019.

/*
 3_2. Сортировка почти упорядоченной последовательности.
 Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Память O(k). Использовать слияние.

 */

#include <iostream>
#include <cstring>

// template<class TLess>
// struct IsLess
// {
//     bool operator () (TLess i1, TLess i2) const { return i1 < i2; }
// };


template<typename T>
void Merge(T* a, int firstLen, int secondLen);

template<typename T>
void MergeSort(T* a, int start,  int end){
    if (end<=start)
        return;
    
    unsigned int secondPart = (end + start)/2;
    
    MergeSort<int>(a, start, secondPart);
    MergeSort<int>(a, secondPart+1,  end);
    
    Merge(a+start, 1 + secondPart - start, end - secondPart);
};

template<typename T>
void Merge(T* a, int firstLen, int secondLen){
    
    T temp_arr[secondLen];
    std:: memcpy(temp_arr, a+firstLen, sizeof(T)*secondLen);
    int i = firstLen - 1;
    int j = secondLen - 1;
    int end = firstLen + secondLen - 1;
    while (j>=0){
        if (i >= 0 && a[i] > temp_arr[j]){
        //if (i>=0 && IsLess(temp_arr[j], a[i])){
            a[end] = a[i];
            i--;
        }
        else{
            a[end] = temp_arr[j];
            j--;
        }
        end--;
    }
};



int main() {
    int n, k;
    std::cin>> n >> k;
    int* arr = new int[n];
    for(int i=0; i<n; ++i){
        std:: cin>>arr[i];
    };
    
    for (int i = 0; i < n; i += k) {
        MergeSort<int>(arr, i, std:: min(i+ k-1, n-1));
        Merge<int>(arr + i - k, k, std:: min(k,n-i));
    }
    
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    
    return 0;
}

