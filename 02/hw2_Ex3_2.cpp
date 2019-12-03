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

void Merge(int* a, int firstLen, int secondLen);


template<class T, class TLess>
void MergeSort(T* a, int start,  int end, TLess is_less){
    if (end<=start)
        return;
    
    unsigned int secondPart = (end + start)/2;
    
    MergeSort(a, start, secondPart, is_less);
    MergeSort(a, secondPart+1,  end, is_less);
    
    Merge(a+start, 1 + secondPart - start, end - secondPart);
};

void Merge(int* a, int firstLen, int secondLen){
    
    int temp_arr[secondLen];
    std:: memcpy(temp_arr, a+firstLen, sizeof(int)*secondLen);
    int i = firstLen - 1;
    int j = secondLen - 1;
    int end = firstLen + secondLen - 1;
    while (j>=0){
        if (i >= 0 && a[i] > temp_arr[j]){
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
        MergeSort(arr, i, std:: min(i+ k-1, n-1));
        Merge(arr + i - k, k, std:: min(k,n-i));
    }
    
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }
    
    return 0;
}

