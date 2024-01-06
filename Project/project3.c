#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<cblas.h>


typedef struct 
{
	int row,line;		//line为行,row为列
	float *data;
}Matrix;

Matrix* InitMatrix(Matrix *matrix,int row,int line);		//初始化矩阵
void ValueMatrix(Matrix *matrix,FILE* fpRead);				//给一个矩阵赋值
int SizeMatrix(Matrix *matrix);								//获得一个矩阵的大小
void FreeMatrix(Matrix *matrix);							//释放一个矩阵
void CopyMatrix(Matrix *matrix_A, Matrix *matrix_B);		//复制一个矩阵的值
void PrintMatrix(Matrix *matrix,FILE* fpWrite);							//打印一个矩阵
int GetNum(char* str);                                //获取矩阵的行和列

//矩阵的基本运算
Matrix* AddMatrix(Matrix *matrix_A,Matrix *matrix_B);		//矩阵的加法
Matrix* MulMatrix(Matrix *matrix_A,Matrix *matrix_B);		//矩阵的乘法
Matrix* MulMatrix1(Matrix *matrix_A,Matrix *matrix_B);      //矩阵的乘法（openBLAS）
void TransMatrix(Matrix *matrix);			//条件为方阵

int main(int argc,char* argv[])
{
	clock_t begin,end,begin1,end1;
	double cost,cost1;
    FILE* fpReadA=fopen(argv[1],"r");
    FILE* fpReadB=fopen(argv[2],"r");
    FILE* fpWrite=fopen(argv[3],"w");
    int a=GetNum(argv[1]);
	Matrix *matrix1 = InitMatrix(matrix1,a,a);
	Matrix *matrix2 = InitMatrix(matrix2,a,a);

	ValueMatrix(matrix1,fpReadA);
	// CopyMatrix(matrix1,matrix2);	//复制赋值
	ValueMatrix(matrix2,fpReadB);
	// begin=clock();
    // fprintf(fpWrite,"矩阵1 乘以 矩阵2: \n");
	// Matrix *matrix3 = MulMatrix(matrix1,matrix2);	//乘法
	// end=clock();
	// cost=(double)(end-begin)/CLOCKS_PER_SEC;
	// printf("%lf",cost);
	// PrintMatrix(matrix3,fpWrite);	
	begin1=clock();
    fprintf(fpWrite,"矩阵1 乘以 矩阵2（openBLAS）: \n");
	Matrix *matrix5 = MulMatrix1(matrix1,matrix2);	//乘法（openBLAS）
	end1=clock();
	cost1=(double)(end1-begin1)/CLOCKS_PER_SEC;
	printf("%lf",cost1);
	PrintMatrix(matrix5,fpWrite);	
    fprintf(fpWrite,"矩阵1 加上 矩阵2: \n");
	Matrix *matrix4 = AddMatrix(matrix1,matrix2);	//加法
	PrintMatrix(matrix4,fpWrite);
    fprintf(fpWrite,"矩阵1进行转置: \n");
	TransMatrix(matrix1);					//转置
	PrintMatrix(matrix1,fpWrite);
	FreeMatrix(matrix1);
	FreeMatrix(matrix2);
	FreeMatrix(matrix3);
	FreeMatrix(matrix4);
    fclose(fpWrite);
    fclose(fpReadA);
    fclose(fpReadB);
	

	return 0;
}

Matrix* InitMatrix(Matrix *matrix,int row,int line)				//初始化一个矩阵
{
		matrix = (Matrix*)malloc(sizeof(Matrix));
		matrix->row = row;
		matrix->line = line;
		matrix->data=(float*)malloc(sizeof(float)*(row*line));
		// memset(matrix->data,0,sizeof(float)*row*line);
		return matrix;
} 

void ValueMatrix(Matrix *matrix,FILE* fpRead) 		//给矩阵赋值
{
	// double* data=(double *) malloc(sizeof(double )*(matrix->row * matrix->line));
	for(int i=0;i<matrix->line * matrix->row;i++){
        fscanf(fpRead,"%f",&matrix->data[i]);
    }
	// memcpy(matrix->data, data, matrix->row*matrix->line*sizeof(double));
	// free(data);
	// data=NULL;
	// printf("temp释放成功\n");
	
}

int SizeMatrix(Matrix *matrix)
{
	return matrix->row*matrix->line;
}

void FreeMatrix(Matrix *matrix)
{
	free(matrix->data);		//释放掉矩阵的data存储区
	matrix->data = NULL;
	printf("释放成功\n");
}

void CopyMatrix(Matrix *matrix_A, Matrix *matrix_B)
{
	matrix_B->row = matrix_A->row;
	matrix_B->line = matrix_A->line;
	memcpy(matrix_B->data, matrix_A->data, SizeMatrix(matrix_A)*sizeof(float));
}

void PrintMatrix(Matrix *matrix,FILE* fpWrite)
{


	for (int i=0;i<SizeMatrix(matrix);i++)
	{
        fprintf(fpWrite,"%f ",matrix->data[i]);
        if ((i+1)%matrix->line == 0){
            fprintf(fpWrite,"\n");
        }

	}

			
}
//加法
Matrix* AddMatrix(Matrix *matrix_A,Matrix *matrix_B)
{

		Matrix *matrix_C = InitMatrix(matrix_C,matrix_A->row,matrix_A->line);
		for (int i=0;i<matrix_A->line;i++)
		{
			for (int j=0;j<matrix_A->row;j++)
			{
				matrix_C->data[i*matrix_C->row + j] = \
				matrix_A->data[i*matrix_A->row + j] + matrix_B->data[i*matrix_B->row + j];
			}
		}
		return matrix_C;
	

}

//乘法
Matrix* MulMatrix(Matrix *matrix_A,Matrix *matrix_B)
{
	Matrix *matrix_C = InitMatrix(matrix_C,matrix_B->row,matrix_A->line);
		for (int i=0;i<matrix_A->line;i++)
		{
			for (int k=0;k<matrix_B->line;k++)
			{
				for (int j=0;j<matrix_B->row;j++)
				{
					matrix_C->data[i*matrix_C->row + j] +=matrix_A->data[i*matrix_A->row + k] * matrix_B->data[k*matrix_B->row + j];
				}
			}
		}
		return matrix_C;
	
	
	
}
Matrix* MulMatrix1(Matrix *matrix_A,Matrix *matrix_B)
{
	Matrix *matrix_C = InitMatrix(matrix_C,matrix_B->row,matrix_A->line);
		const float alpha=1;
     const float beta=0;
     cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,matrix_A->line,matrix_B->row,matrix_A->row,alpha, matrix_A->data,matrix_A->row,matrix_B->data,matrix_B->row,beta,matrix_C,matrix_B->row);
     

		return matrix_C;
	
	
	
}


//矩阵转置
void TransMatrix(Matrix *matrix)			//条件为方阵
{

		Matrix *matrixTemp = InitMatrix(matrixTemp, matrix->row,matrix->line);       	//创建一个临时矩阵
		CopyMatrix(matrix,matrixTemp);	//将目标矩阵的data复制给临时矩阵

		for (int i=0;i<matrix->row;i++)
		{
			for (int j=0;j<matrix->line;j++)
			{
				matrix->data[i*matrix->row + j] = matrixTemp->data[j*matrix->row + i];
			}
		}
	
}
//获取矩阵的行和列数
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