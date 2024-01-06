#include"Mat.hpp"
#include <iostream>
#include<memory>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

// construct
template<typename T>
Mat<T>::Mat(){
    cout << "default constructor" << endl;
    row=2;col=2;channel=1;
    T* array=new T[row*col]{};
    data=std::make_shared<T*>(array);
}
template<typename T>
Mat<T>::Mat(int i, int j,int k){
        row=i;
        col=j;
        channel=k;
        T* array=new T[row*col*channel]{};
        data=std::make_shared<T*>(array);
    }

// copy construct
template<typename T>
Mat<T>::Mat(const Mat<T>& m){
    cout << "copy constructor" << endl;
    row=m.row;
    col=m.col;
    channel=m.channel;
    data=m.data;
}

//destructor
template<typename T>
Mat<T>::~Mat(){
    cout<<"destructor"<<endl;
}

// showMat
template<typename T>
void Mat<T>::MatShow()
{
        for(int i=0;i<row;i++){
            for (size_t j = 0; j < col; j++)
            {
               for (size_t k = 0; k < channel; k++)
               {
                   cout<<data.get()[0][i*channel*col+j*channel+k]<<" ";
               }
               cout<<"  ";
                
            }
            cout<<endl;
            
        }
        cout<<endl;
        
    }


template<typename T>
void MatShowfile(const Mat<T>& m,char * filename){
    ofstream outfile;
    outfile.open(filename);
    for(int i=0;i<m.row;i++){
            for (size_t j = 0; j < m.col; j++)
            {
               for (size_t k = 0; k < m.channel; k++)
               {
                   outfile.precision(4);
                   outfile<<fixed<<m.data.get()[0][i*m.col*m.channel+j]<<" ";
               }
               outfile<<"  ";
                
            }
            outfile<<endl;
            
        }
        outfile.close();
}

// CinMat
template<typename T>
void Mat<T>::CinMat(){
    for (size_t i = 0; i < row*col*channel; i++)
    {
        cin>>data.get()[0][i];
    }
    
}


template<typename T>
void CinMatfile(const Mat<T>& m,char * filename){
       int count = 0;
    ifstream myfile;
    myfile.open(filename,ios::in);
    if (!myfile)
    {
        cout<<"无法打开文件"<<endl;
    }
    else
    {
        for (int i = 0; i < m.row*m.col*m.channel; i++)
        {
            myfile>>m.data.get()[0][i];
        }
        
    }
    myfile.close();
}

//ROI
template<typename T>
void Mat<T>:: ROI(int start_row,int start_col,int width,int height){
    int cur = (start_row-1)*col*channel+(start_col-1)*channel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            for (int k = 0; k < channel; k++)
            {
                cout<<data.get()[0][cur]<<" ";
                cur++;
            }
            cout<<"  ";
        }
        cout<<endl;
        cur += (col-width)*channel;
    }
    cout<<endl;
}

// mul
template<typename T>
const Mat<T> mul(const Mat<T>& m, const Mat<T>& m1){
    Mat<T> t(m.row,m1.col,1);
    if(m1.row==m.row&&m1.col==m.col&&m1.channel==m.channel){
        for (size_t i = 0; i < m.row; i++)
        {
                for (size_t j = 0; j < m.col; j++)
                {
                    for (size_t l = 0;l < m.channel; l++)
                    {
                        t.data.get()[0][i*t.col+j]+=m.data.get()[0][i*m.col*m.channel+j*m.channel+l]*m1.data.get()[0][i*m1.col*m1.channel+j*m.channel+l];
                    }
                }
                
            
            
        }
        

    }
    else{
        cout<<"row, col and channel must be same."<<endl;
    }
    return t;
} 

// dot
template<typename T>
T dot(const Mat<T>& m, const Mat<T>& m1){
    T t;
    if(m.channel==m1.channel&&m.row*m.col==m1.row*m1.col){
        for (size_t i = 0; i < m.row*m.col; i++)
        {
            for (size_t j = 0; j < m.channel; j++)
            {
                t+=m.data.get()[0][i*m.channel+j]*m1.data.get()[0][i*m.channel+j];
            }
            
        }
        

    }
    else{
        cout<<"channel and row*col must be same.";
    }
    return t;

}

// +
template<typename T>
const Mat<T> operator+(const Mat<T>& m1, const Mat<T>& m2){
    Mat<T> t(m1.row,m1.col,m1.channel);
    
    for (size_t i = 0; i < m1.row*m1.col*m1.channel; i++)
    {
        t.data.get()[0][i]=m1.data.get()[0][i];
    }
    
    t += m2;
    return t;
}

// -
template<typename T>
const Mat<T> operator-(const Mat<T>& m1, const Mat<T>& m2){
    Mat<T> t(m1.row,m1.col,m1.channel);
    
    for (size_t i = 0; i < m1.row*m1.col*m1.channel; i++)
    {
        t.data.get()[0][i]=m1.data.get()[0][i];
    }
    t-= m2;
    return t;
}

// *

// Mat<T>& Mat<T>:: operator*(const Mat<T>& m){
//     if(col*channel==m.row){
//         int count=128/sizeof(T);
//         int len=m.col*m.channel/count;
//         T temp[count];
//         for (int i = 0; i <row ; i++)
//         { 
//             for (int k = 0; k < col*m.channel; k++)
//             {
//                 __m128 vsum=_mm_set1_ps(data[i*col*channel+k]);                
//                 for (int j = 0; j < len; j++)
//                 {
//                     __m128 a=_mm_load_ps(&m.data[count*j]);
//                     __m128 b=_mm_mul_ps(vsum,a);
//                     _mm_store_ps(temp,b);
//                     for (int l = 0; l < count; l++)
//                     {
//                         data[i*m.col*m.channel+j*count+l]+=temp[l];
//                     }
//                 }
//                 if(m.col*m.channel%count!=0){
//                     for (int j = count*len; j <m.col*m.channel; j++)
//                     {
//                         data[i*m.col*m.channel+j]+=data[i*col*channel+k]*m.data[k*m.col*m.channel+j];
//                     }                    
//                 }                
//             }         
//         }
//     }
//     else{
//         cout<<"col and row must be same."<<endl;
//     }
//     return *this;
// }
template<typename T>
Mat<T> Mat<T>:: operator*(const Mat<T>& m){

    Mat<T> t(row,m.col,channel);
    if(col==m.row&&channel==m.channel){
       
        for (size_t i = 0; i < row; i++)
        {
            for (size_t k = 0; k < col; k++)
            {
                for (size_t j = 0; j < m.col; j++)
                {
                    for (size_t l = 0; l < channel; l++)
                    {
                        t.data.get()[0][i*m.col*channel+j*channel+l]+=data.get()[0][i*col*channel+k*channel+l]*m.data.get()[0][k*m.col*m.channel+j*channel+l];
                    
                    }
                    
                    
                }
                
            }
            
        }
        
    }
    else{
        cout<<"row!=m.col or channel!= m.channel"<<endl;
    }
    return t;
}
template<typename T>
Mat<T> Mat<T>:: operator*(const T & x){
    Mat<T> t(row,col,channel);
    for (size_t i = 0; i <row*col*channel ; i++)
    {
        t.data.get()[0][i]=data.get()[0][i]*x;
    }

    return t;
    
}

// +=
template<typename T>
Mat<T>& Mat<T>::operator+=(const Mat<T>& m){
        if(row==m.row&&col==m.col&&channel==m.channel){
        //     int count=128/sizeof(T);
        //     T temp[count];
        //     int len=m.col*m.channel*m.row/count;
        // for(int i=0;i<len;i++){
        //     __m128 m1=_mm_load_ps(&data.get()[0][count*i]);
        //     __m128 m2=_mm_load_ps(&m.data.get()[0][count*i]);
        //     __m128 sum=_mm_add_ps(m1,m2);
        //     _mm_store_ps(temp,sum);
        //     for (int k = 0; k < count; k++)
        //     {
        //         data.get()[0][count*i+k]=temp[k];
        //     }
        // }            
        // if(m.col*m.channel*m.row%count!=0){
        //     for(int i=len*count;i<m.row*m.col*m.channel;i++)
        //     {
        //          data.get()[0][i]=data.get()[0][i]+m.data.get()[0][i];
        //     }   
        // }
        for (size_t i = 0; i < row*col*channel; i++)
        {
            (*data.get())[i]+=m.data.get()[0][i];
            // data.get() == &array
            // p[0] == *p
        }       
        }
        else{
            cout<<"mat must be the same size."<<endl;
        }
        return *this;
    }

// -=
template<typename T>
Mat<T>& Mat<T>::operator-=(const Mat<T>& m){
        if(row==m.row&&col==m.col&&channel==m.channel){
        //     int count=128/sizeof(T);
        //     T temp[count];
        //     int len=m.col*m.channel*m.row/count;
        // for(int i=0;i<len;i++){
        //     __m128 m1=_mm_load_ps(&data.get()[0][count*i]);
        //     __m128 m2=_mm_load_ps(&m.data.get()[0][count*i]);
        //     __m128 sum=_mm_sub_ps(m1,m2);
        //     _mm_store_ps(temp,sum);
        //     for (int k = 0; k < count; k++)
        //     {
        //         data.get()[0][count*i+k]=temp[k];
        //     }
        // }
        // if(m.col*m.channel*m.row%count!=0){
        //     for(int i=len*count;i<m.row*m.col*m.channel;i++)
        //     {
        //          data.get()[0][i]=data.get()[0][i]-m.data.get()[0][i];
        //     }   
        // }
        for (size_t i = 0; i < row*col*channel; i++)
        {
            data.get()[0][i]-=m.data.get()[0][i];
        }       
        }
        else{
            cout<<"mat must be the same size."<<endl;
        }
        return *this;
    }

// ==
template<typename T>
bool Mat<T>::operator==(const Mat<T> & m){
    if(row!=m.row||col!=m.col||channel!=m.channel){
        return false;
    }
    for (size_t i = 0; i < row*col*channel; i++)
    {
        if(data.get()[0][i]!=m.data.get()[0][i]){
            return false;
        }
    }
    return true;
}

// =
template<typename T>
Mat<T>& Mat<T>::operator=(const Mat<T>& m){
    row=m.row;
    col=m.col;
    channel=m.channel;
    this->data=m.data;
    return *this;
}

// 文件读入获取矩阵的行列
int GetNum(char * str) {
        int row = 0;
		int f=0;
        FILE* fpRead=fopen(str,"r");
        while (!feof(fpRead)) {
            f = fgetc(fpRead);
            if (f == '\n') {
                row++;
            }
        }
        return row;
    }

//lab13 codes
template<typename T>
T& Mat<T>::operator()(int i, int j){
        cout<<"float&"<<endl;
    return data.get()[0][(i-1)*col+j-1];
}

template<typename T>
T Mat<T>::operator()(int i, int j) const{
    cout<<"float"<<endl;
    return data.get()[0][(i-1)*col+j-1];
}



typedef int Type;
int main(int argc,char* argv[]){
    double cost;
    // int a=GetNum(argv[1]);
    Mat<Type> A(4,4,1);
    Mat<Type> B;
    Mat<Type> C;
    A.CinMat();
    A.MatShow();
    B=A;
    B.MatShow();
    A+=B;
    int a=A(2,2)-1;
    cout<<a<<endl;
    A.MatShow();
    // time_t begin,end;
    // Mat<Type> C;
    // CinMatfile(A,argv[1]);
    // CinMatfile(B,argv[2]);

    // C=A+B;
    // cout<<"66"<<endl;
    // MatShowfile(A,argv[3]);

    // CinMatfile(A,argv[1]);
    // CinMatfile(B,argv[2]);
    // begin=clock();
    // C=A*B;
    // end=clock();
    // cost=(double)(end-begin)/CLOCKS_PER_SEC;
    // cout<<cost<<endl;

    // MatShowfile(C,argv[3]);
   

    
    // Mat<Type> A(2,2,2);
    // Mat<Type> B(2,2,2);
    // A.CinMat();
    // B.CinMat();
    // Mat<Type> C;
    // C=A+B;
    // cout<<"matrix A:"<<endl;
    // A.MatShow();
    // cout<<"matrix B:"<<endl;
    // B.MatShow();
    // cout<<"matrix C:"<<endl;
    // C.MatShow();
    


    
    return 0;
}


