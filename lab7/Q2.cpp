#include <iostream>
#include<cmath>
using namespace std;

int* vabs(int* p,size_t n);
float*  vabs(float*p,float n);
double* vabs(double*p,double n);
int main(){
    int* p=new int [10];
    for(int a=0;a<10;a++){
        p[a]=a-5;
    }
    int* q=vabs(p,10);
    
    for (int i = 0; i < 10; i++)
    {
        cout<<q[i]<<" ";
    }
    delete[]p;

    

}
int* vabs(int* p,size_t n){
    for(int a=0;a<n;a++){
        if(p[a]<0){
            p[a]=-p[a];
        }
    }
    return p;
}
float*  vabs(float*p,float n){
    for(int a=0;a<n;a++){
        if(p[a]<0){
            p[a]=-p[a];
        }
    }
    return p;
}
double* vabs(double*p,double n){
        for(int a=0;a<n;a++){
        if(p[a]<0){
            p[a]=-p[a];
        }
    }
    return p;
}
