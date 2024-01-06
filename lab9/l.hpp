#pragma once
#include<iostream>
#include <cstring>
using namespace std;
class l
{
private:
    double real;
    double imag;
public:
    l():real(0),imag(0)
    {

    }
    l( double n , double m ):real(n),imag(m){

    }
    l( const l& l1 ) : real(l1.real), imag(l1.imag) {
        cout<<"666"<<endl;
    }
    void setReal(double real){
        this->real=real;
    }
    void setImag(double imag){
        this->imag=imag;
    }
    double getReal(){
        return real;
    }
    double getImag(){
        return imag;
    }

    l operator+(l& complex2){
        return l(real+complex2.real,imag+complex2.imag);
    }
    l operator-(l& complex){
        return l(real-complex.real,imag-complex.imag);
    }
    void operator=(l& complex){
        real=complex.real;
        imag=complex.imag;
    }
    l operator*(l& complex){
        return l(real*complex.real-imag*complex.imag,real*complex.imag+imag*complex.real);
    }
    bool operator==(l &complex){
        if(real==complex.real&&imag==complex.imag){
            return true;
        }
        else {
            return false;
        }
    }
    friend std::ostream& operator<<(std::ostream& os,const l& r){
        if(r.imag>0){
            cout<<r.real<<"+"<<r.imag<<+"i";
        }
        if(r.imag==0){
            cout<<r.real;
        }
        if(r.imag<0){
            cout<<r.real<<r.imag<<+"i";
        }
        return os;
    }

    // void show(){
    //     if(imag>0){
    //         cout<<real<<"+"<<imag<<+"i"<<endl;
    //     }
    //     if(imag==0){
    //         cout<<real<<endl;
    //     }
    //     if(imag<0){
    //         cout<<real<<imag<<+"i"<<endl;

    //     }
    // }



    // l add(l complex1,l complex2){
    //     l complex3;
    //     complex3.setImag(complex1.getImag()+complex2.getImag());
    //     complex3.setReal(complex1.getReal()+complex2.getReal());
    //     return complex3;
    // }
    // l subtract(l complex1,l complex2){
    //     l complex3;
    //     complex3.setImag(complex1.getImag()-complex2.getImag());
    //     complex3.setReal(complex1.getReal()-complex2.getReal());
    //     return complex3;
    // }
    // void printfo(l complex){
    //     if(complex.getImag()>0){
    //         cout<<complex.getReal()<<"+"<<complex.getImag()<<+"i"<<endl;
    //     }
    //     if(complex.getImag()<0){
    //         cout<<complex.getReal()<<complex.getImag()<<+"i"<<endl;
    //     }
    //     if(complex.getImag()==0){
    //         cout<<complex.getReal()<<endl;
    //     }
    // }
    ~l(){
    
    }
};


