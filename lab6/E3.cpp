#include<iostream>
using namespace std;
#include"function1.h"
int main(){
    point a;
    point b;
    point c;
    Setvalues(a,b);
    cout<<a.x<<a.y<<b.y<<b.x<<endl;
    c=middle(a,b);
    cout<<c.x<<endl;
    cout<<c.y<<endl;
}