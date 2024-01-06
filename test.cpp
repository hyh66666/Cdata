#include<cstring>
#include<cmath>
#include<iostream>
#include<iomanip>
using namespace std;

class A{
    private:
    int weight;
    // A(int weight);
    public:
    ~A(){
        cout<<"A";
    }
};
class D:public A{
    public:
    int weight;
    // float A [2048*2048*2048];
    ~D(){
        cout<<"D";
    }

};
int main(){
    A * a=new A();
    D * d=(D*) (a);
    d->weight=10;
    cout<<d->weight<<endl;
    delete d;
    delete a;
    return 0; 
}