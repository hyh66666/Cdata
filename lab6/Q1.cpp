#include<iostream>
using namespace std;
#include"function.h"
int main(){
    int a=1;
    int b=2;
    int& c=a;
    int& d=b;
    int*e=&a;
    int*f=&b;
    swap1(a,b);
    cout<<a<<endl;
    cout<<b<<endl;
    swap2(c,d);
    cout<<c<<endl;
    cout<<d<<endl;
    swap(e,f);
    cout<<*e<<endl;
    cout<<*f<<endl;
    return 0;

}