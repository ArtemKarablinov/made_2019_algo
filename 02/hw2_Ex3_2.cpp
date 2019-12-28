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

template<typename T>
struct isLess
{
    bool operator () (T i1, T i2) const { return i1 < i2; }
};


template<typename T, typename TLess>
void Merge(T* a, int firstLen, int secondLen, TLess isLess);

template<typename T, typename TLess>
void MergeSort(T* a, int start,  int end, TLess isLess){
    if (end<=start)
        return;
    
    unsigned int secondPart = (end + start)/2;
    
    MergeSort<int>(a, start, secondPart, isLess);
    MergeSort<int>(a, secondPart+1,  end, isLess);
    
    Merge(a+start, 1 + secondPart - start, end - secondPart, isLess);
}

template<typename T, typename TLess>
void Merge(T* a, int firstLen, int secondLen, TLess isLess){
    
    T temp_arr[secondLen];
    std:: memcpy(temp_arr, a+firstLen, sizeof(T)*secondLen);
    int i = firstLen - 1;
    int j = secondLen - 1;
    int end = firstLen + secondLen - 1;
    while (j>=0){
        if (i>=0 && isLess(temp_arr[j], a[i])){
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
        MergeSort<int>(arr, i, std:: min(i+ k-1, n-1), isLess<int>());
        Merge<int>(arr + i - k, k, std:: min(k,n-i), isLess<int>());
    }
    
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    
    return 0;
}

