#include<iostream>
using namespace std;
#include"function1.h"
point middle(point a,point b){
    a.x=(a.x+b.x)/2;
    a.y=(a.y+b.y)/2;
    return a;
}