//
// Created by ingebrigt on 27.01.2022.
//

#ifndef FILTER_FINDER_ARRAYS_H
#define FILTER_FINDER_ARRAYS_H


#include <array>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>


template <typename T>
class SquareArray {
public:
    SquareArray(int outer, int inner);
    explicit SquareArray(std::vector<std::vector<T>> x);
    std::vector<std::vector<T>> arr;
    size_t size();
    void flat(std::vector<float> &out);
    friend SquareArray operator*(double x, SquareArray y);
    // todo does this need to be friend?
    friend SquareArray operator+=(std::vector<std::vector<T>> x, SquareArray y);
    SquareArray operator-(SquareArray x);
    SquareArray operator*(T y);
    std::vector<T> operator[](size_t i);
    SquareArray operator-(std::vector<std::vector<T>> y);
    friend SquareArray operator+(int x, SquareArray<T> y);

    void print();
};

template <typename T>
class CubeArray {
public:
    CubeArray(bool zero, int outer, int middle, int inner);
    explicit CubeArray(std::vector<std::vector<std::vector<T>>> cube_);
    size_t size();
    std::vector<std::vector<std::vector<T>>> cube;
    double calc(SquareArray<T> x, size_t outer);
    SquareArray<T> operator[](size_t i) const; //
    CubeArray<T> operator/(double y);
    CubeArray<T> operator+=(CubeArray y);
    friend CubeArray<T> operator*(T y, CubeArray x);

    void print();
};


#endif //FILTER_FINDER_ARRAYS_H
