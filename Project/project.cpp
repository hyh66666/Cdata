#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;
int GetNum(string str);
   float E[2048][2048];
   float F[2048][2048];
   float G[2048][2048];
//    double E[2048][2048];
//    double F[2048][2048];
//    double G[2048][2048];

double matmul(string txt1,string txt2,string txt3){
    time_t begin,end;
    double cost;
    ifstream myfileA(txt1);
    ifstream myfileB(txt2);
    ofstream outfile(txt3);
    int a=GetNum(txt1);
    if(a<2048){
    begin=clock();
    float A[a][a];
    float B[a][a];
    float C[a][a];
    // double A[a][a];
    // double B[a][a];
    // double C[a][a];
    for (int i = 0; i<a; i++)
    {
        for(int j=0;j<a;j++){
            myfileA>>A[i][j];
        
            myfileB>>B[i][j];
        }
    }
    for(int i=0;i<a;++i){
        for(int k=0;k<a;++k){
            for(int j=0;j<a;++j){
            C[i][j]+=A[i][k]*B[k][j];
        }
    }
    }
    for (int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            outfile.precision(4);
            outfile<<fixed<<C[i][j]<<" ";
        }
        outfile<<endl;
    }
    end=clock();
    cost=(double)(end-begin)/CLOCKS_PER_SEC;
    outfile<<endl;
    // myfileA.clear();
    // myfileA.seekg(0);
    // myfileB.clear();
    // myfileB.seekg(0);
    
    myfileA.close();
    myfileB.close();
    outfile.close();
    }
    else{
        begin=clock();
        for (int i = 0; i<a; i++)
    {
        for(int j=0;j<a;j++){
            myfileA>>E[i][j];
            myfileB>>F[i][j];
        }
    }
    for(int i=0;i<a;++i){
        for(int k=0;k<a;++k){
            for(int j=0;j<a;++j){
            G[i][j]+=E[i][k]*F[k][j];
        }
    }
    }
    for (int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            outfile.precision(4);
            outfile<<fixed<<G[i][j]<<" ";
        }
        outfile<<endl;
    }
    end=clock();
    cost=(double)(end-begin)/CLOCKS_PER_SEC;

    }
    return cost;
    

}

 int GetNum(string str){
    int num=0,t;
    for(int i=0;i<str.length();i++){
        while(str.c_str()[i]>='0'&&str.c_str()[i]<= '9'){
            t=str.c_str()[i]-'0';
            num=num*10+t;
            i++;
        }
    }
    return num;

}
int main(int argc,char*argv[]){ 
    if(argc==4){
        string txt1=argv[1];
        string txt2=argv[2];
        string txt3=argv[3];
        double cost;
        cost=matmul(txt1,txt2,txt3);
        cout<<"time:"<<cost<<"s"<<endl;
    return 0;
    }
    
}