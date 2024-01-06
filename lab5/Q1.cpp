#include<iostream>
using namespace std;
int main(){
int n=5;
int*p=new int[5]{1,2,3,4,5};
int*p1=NULL;
for(int i=4;i>=0;i--){
    p1=&p[i];
    cout<<*p1<<endl;
}
}
