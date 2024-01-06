#include<iostream>
using namespace std;
int main(){
    char* p =new char[3]{'a','b','c'};
    for(int i=0;i<3;i++){
         string s(1,p[i]);
         cout<<s<<endl;
    }
    p[1]=1000000000;
    cout<<p[1]<<endl;
}