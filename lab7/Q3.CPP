#include <iostream>
#include <string>
#include <cstring>
using namespace std;
template<typename T>
T minimum(T x,T y){
    if(x<y){
        return x;
    }
    if(y<=x){
        return y;
    }
}
int main(){
    float a=1.5,b=9.6;
    double c=6.33,d=59.5;
    cout<<minimum<int>(3,5)<<endl;
    cout<<minimum<float>(a,b)<<endl;
    cout<<minimum<double>(c,d)<<endl;
}