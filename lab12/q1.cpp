#include <iostream>
using namespace std;
float av(float a,float b,float c,float d);
float av(float a,float b,float c,float d){
    if(a<0||a>100){
          throw 1;  
    }
    if(b<0||b>100){
          throw 2;  
    }
    if(c<0||c>100){
          throw 3;  
    }
    if(d<0||d>100){
          throw 4;  
    }
    
    return (a+b+c+d)/4;
}
int main(){
    float a,b,c,d;
    char C;
    bool flag=true;
    
    while(flag){
        cout<<"Please enter marks for 4 courses:"<<endl;
        cin>>a>>b>>c>>d;
    try
    {
        cout<<"The average of the four courses is:"<<av(a,b,c,d)<<endl;
    
    }
    catch(int code)
    {
        if(code==1){
        cout<<"The parameter "<<code<<" is "<<a<<" which out of range(0-100)."<<endl;
        }
        if(code==2){
        cout<<"The parameter "<<code<<" is "<<b<<" which out of range(0-100)."<<endl;
        }
        if(code==3){
        cout<<"The parameter "<<code<<" is "<<c<<" which out of range(0-100)."<<endl;
        }
        if(code==4){
        cout<<"The parameter "<<code<<" is "<<d<<" which out of range(0-100)."<<endl;
        }
    }
    cout<<"Would you want to enter another marks for 4 courses(y/n)?"<<endl;
    cin>>C;
    if(C=='n'){
        flag=false;
    }
    }
    
    return 0;
}