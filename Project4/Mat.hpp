#ifndef _MAT_H_
#define _MAT_H_

#include <iostream>
#include<string>
#include<memory>
#include<fstream>
using namespace std;



template<typename T>
class Mat{

public:
    typedef T value_type;

    //construct
    Mat();
    Mat(int i, int j,int k);

    // copy construct
    Mat(const Mat& m);

    // showMat
    void MatShow();


    // CinMat
    void CinMat();


    // ROI
    void ROI(int start_row,int start_col,int width,int height);

    // ==
    bool operator==(const Mat& m);

    // *
    Mat operator*(const Mat& m);
    Mat operator*(const T & x);

    // +=
    Mat& operator+=(const Mat& m);

    // -=
    Mat& operator-=(const Mat& m);

    //=
    Mat& operator=(const Mat& m);

    //lab13 codes
    T& operator()(int i, int j);
    T operator()(int i, int j) const;

    

    //destructor
    ~Mat();

public:
    int row,col,channel;
    std::shared_ptr<T*> data;
};

#endif  