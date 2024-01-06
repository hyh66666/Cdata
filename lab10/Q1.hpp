#pragma once
#include<iostream>
#include <cstring>
#include<memory>
using namespace std;
class Matrix
{
private:
    int row;
    int col;
    float* data;
public:
    Matrix(int n,int m ,float*& data):row(n),col(m),data(data){

    }
    Matrix(){
        row=1;
        col=1;
        data=new float[1]{};

    }
    void show(){
    for (int i=0;i<row*col;i++)
	{
    
        cout<<data[i]<<" ";
        if ((i+1)%row == 0){
            cout<<endl;
        }

	}
    }
    Matrix operator=(const Matrix* matrix){
        // if(this==& matrix){
        //     return *this;
        // }
        // delete[] data;
        // data=new float[matrix.row*matrix.col];
        // row=matrix.row;
        // col=matrix.col;
        // memcpy(data, matrix.data, matrix.row*matrix.col*sizeof(float));
        // return *this;
        shared_ptr<Matrix> sptr=make::shared<Matrix>();
        sptr=matrix;
        return sptr;
        

        
    

    }
    Matrix operator+(const Matrix& matrix){
        for (int i=0;i<matrix.row;i++)
		{
			for (int j=0;j<matrix.col;j++)
			{
				data[i*row + j] = \
				data[i*row + j] + matrix.data[i*matrix.row + j];
			}
		}
		return *this;

    }
    Matrix operator*(const float & x){
        // for (int i=0;i<matrix.row;i++)
		// {
		// 	for (int k=0;k<row;k++)
		// 	{
		// 		for (int j=0;j<col;j++)
		// 		{
		// 			data[i*row + j] +=data[i*row + k] * matrix.data[k*matrix.row + j];
		// 		}
		// 	}
		// }
        for (size_t i = 0; i < row*col; i++)
        {
            data[i]=data[i]*x;
        }
        
        
        return *this;
    }
    ~Matrix(){

    }
};

