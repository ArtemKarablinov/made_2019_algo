/*
Найдите все вхождения шаблона в строку. 
Длина шаблона – p, длина строки ­– n. 
Время O(n + p), доп. память – O(p).

Вариант 1. С помощью префикс-функции (алгоритм Кнута-Морриса-Пратта).

Формат входного файла
Шаблон, символ перевода строки, строка.

Формат выходного файла
Позиции вхождения шаблона в строке.
*/

#include <iostream>
#include <string>
#include <vector>

using std::string;

std::vector<size_t> KMP(const string pattern,  const string text){

    std::vector<size_t> prefix(pattern.length(), 0);
    std::vector<size_t> result;

    int k = 0;
    for (int i=1; i<pattern.length(); ++i){
        while (k>0 && pattern[i]!=pattern[k]){
            k = prefix[k-1];
        }
        if (pattern[i] == pattern[k])
            k++;
        prefix[i] = k;
    }
    
    k = 0;
    for (int i=0; i<text.length(); ++i){
        while (k>0 && pattern[k] != text[i])
            k = prefix[k-1];
        if (pattern[k] == text[i])
            k++;
        if (k == pattern.length())
            result.push_back(i - pattern.length() + 1);
    }
    return result;
}

int main(){

    string pattern;
    std::getline(std::cin, pattern);
    string text;
    std::getline(std::cin, text);
    std::vector<size_t> positions = KMP(pattern, text);
    for (auto i:positions)
        std::cout << i << " ";
    return 0;
}

