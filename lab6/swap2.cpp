#include<iostream>
#include"function.h"
using namespace std;
void swap2(int& num,int& num1){
    int c;
    c=num1;
    num1=num;
    num=c;
}