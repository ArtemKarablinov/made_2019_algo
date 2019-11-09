//
//  main.cpp
//  hw2-4_2
//
//  Created by KARABLINOV Artem on 09/11/2019.
//  Copyright © 2019 KARABLINOV Artem. All rights reserved.
//
/*
 Задание
 Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
 Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
 Напишите нерекурсивный алгоритм.
 Требования к дополнительной памяти: O(n).
 Требуемое среднее время работы: O(n).
 Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 Описание для случая прохода от начала массива к концу:
 Выбирается опорный элемент.
 Опорный элемент меняется с последним элементом массива.
 Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
 Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
 */

#include <iostream>

int get_median_of_three(int* a, int size){
    if (size < 3){
        return 0;
    };
    
    if (a[0] > a[size/2]){
        if (a[0]<a[size-1])
            return 0;
        else{
            return (a[size-1] < a[0] ? (size - 1) : 0);
        }
    }
    else
        if (a[size/2] < a[size - 1]) {
            return size/2;
        }
        else
            return (a[size - 1] < a[0] ? 0 : (size - 1));
};

int get_median_of_rnd(int* a, int size){
    int a1 = std:: rand() % (size);
    int b2 = std:: rand() % (size);
    int c3 = std:: rand() % (size);
    if (a[a1] > a[b2]){
        if (a[a1]<a[c3])
            return 0;
        else{
            return (a[c3] < a[a1] ? (c3) : a1);
        }
    }
    else
        if (a[b2] < a[c3]) {
            return b2;
        }
        else
            return (a[c3] < a[a1] ? a1 : (c3));
}

int Partition(int* a, int size){
    int i=0;
    int j=0;
    int pivot = std:: rand() % (size);
    std:: swap(a[pivot], a[size-1]);
    while(i < size-1){
        if(a[i] <= a[size-1]){
            std:: swap(a[j], a[i]);
            j++;
        }
        i++;
    }
    std:: swap(a[j], a[size-1]);
    return j;
};

int find_k(int* a, int size, int k){
    int left_ptr = 0;
    int right_ptr = size;
    int pivot_p = Partition(a, size);
    int temp_pivot_pos = pivot_p;
    
    while(temp_pivot_pos != k){
        if (temp_pivot_pos > k){
            right_ptr = left_ptr + pivot_p;
        }
        else {
            left_ptr = left_ptr + pivot_p + 1;
        }
        pivot_p = Partition(a + left_ptr, right_ptr - left_ptr);
        temp_pivot_pos = left_ptr + pivot_p;
    }
    return a[k];
};

int main(){
    int n, k;
    std:: cin >> n >> k;
    if (k>n && k<0)
        return -1;

    int* arr = new int[n];
    for (int i=0; i<n; i++){
        std:: cin >> arr[i];
    }
    int result = find_k(arr, n, k);
    std:: cout << result;

    delete [] arr;
    return 0;
}

