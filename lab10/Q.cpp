#include<iostream>
#include"Q1.hpp"
#include<memory>
using namespace std;
int main(){
    shared_ptr<float> data=new float[4]{1.0,2.0,3.0,4.0};
    Matrix matrix(2,2,data);
    shared_ptr<float> data1=new float[4]{5.0,6.0,7.0,8.0};
    Matrix matrix1(2,2,data1);
    Matrix matrix2=new float[4]{};
    matrix.show();
    matrix1.show();
    matrix2=matrix+matrix1;
    matrix2.show();
    matrix2=matrix2*2.0f;
    matrix2.show();
    return 0;
}