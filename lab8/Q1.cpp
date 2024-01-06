#include<iostream>
#include<ctime>
#include <cstring>
#include<immintrin.h>
using namespace std;

struct MyMatrix
{
    float* mat;
    size_t row;
    size_t col;
};
MyMatrix allocMatrix(int row,int col){
    struct MyMatrix result;
    result.row=row;
    result.col=col;
    result.mat=(float*)malloc(sizeof(float)*row*col);
    return result;
    
}
void freeMatrix(struct MyMatrix& matrix){
    free(matrix.mat);
}
MyMatrix add(MyMatrix& a,MyMatrix& b){
    MyMatrix result=allocMatrix(a.row,a.col);
    memset(result.mat,0,sizeof(float)*result.row*result.col);
    float temp[4];
    //     int len=a.col/4;
    // for(int i=0;i<a.row;i++){
    //     for(int j=0;j<len;j++){
    //         __m128 m1=_mm_set_ps(a.mat[i*a.col+4*j+3],a.mat[i*a.col+4*j+2],a.mat[i*a.col+4*j+1],a.mat[i*a.col+4*j]);
    //         __m128 m2=_mm_set_ps(b.mat[i*b.col+4*j+3],b.mat[i*b.col+4*j+2],b.mat[i*b.col+4*j+1],b.mat[i*b.col+4*j]);
    //         __m128 sum=_mm_add_ps(m1,m2);
    //         _mm_store_ps(temp,sum);
    //         for (int k = 0; k < 4; k++)
    //         {
    //             result.mat[i*a.col+4*j+k]=temp[k];
    //         }
            
            // result.mat[i*a.col+j]=a.mat[i*a.col+j]+b.mat[i*a.col+j];
    //     }
    // }
    int len1=a.row/4;
        for(int j=0;j<a.col;j++){
        for(int i=0;i<len1;i++){
            // __m128 m1=_mm_set_ps(a.mat[(i*4+3)*a.col+j],a.mat[(i*4+2)*a.col+j],a.mat[(i*4+1)*a.col+j],a.mat[i*4*a.col+j]);
            // __m128 m2=_mm_set_ps(b.mat[(i*4+3)*b.col+j],b.mat[(i*4+2)*b.col+j],b.mat[(i*4+1)*b.col+j],b.mat[i*4*b.col+j]);
            // __m128 sum=_mm_add_ps(m1,m2);
            // _mm_store_ps(temp,sum);
            // for(int k=0;k<4;k++){
            //     result.mat[(4*i+k)*a.col+j]=temp[k];
            // }

            result.mat[i*a.col+j]=a.mat[i*a.col+j]+b.mat[i*a.col+j];
        }
    }

    return result;
}
int main(){
    MyMatrix a=allocMatrix(10000,1000);
    MyMatrix b=allocMatrix(10000,1000);
    memset(a.mat,1,sizeof(float)*10000*1000);
    memset(b.mat,2,sizeof(float)*10000*1000);
    time_t begin,end;
    double cost;
    begin=clock();
        cout<<1<<endl;

    MyMatrix result=add(a,b);
    end=clock();
    cost=(double)(end-begin)/CLOCKS_PER_SEC;
    cout<<cost<<endl;
    freeMatrix(a);
    freeMatrix(b);
    freeMatrix(result);


}
