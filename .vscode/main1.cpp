#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
using namespace std;
bool is_number(string str);
int main(int argc,char*argv[] )
{
    if(argc==3){
        if(is_number(argv[1])&&is_number(argv[2])){
        int x=atoi(argv[1]);
       int y=atoi(argv[2]);
        printf("%d*%d=%lld\n",x,y,(long long) x*y);
        return 0;
            }
         else {
              cout<<"The input is wrong."<<endl;
             return 0;  
         }
}
if(argc!=1&&argc!=3){
    cout<<"The input is wrong."<<endl;
             return 0;  
}

    string a,b;
    int e,f;
    cout << "Pick two integers:\n";
    cin >> a;
    cin >> b;
    if(is_number(a)&&is_number(b)){
        e=atoi(a.c_str());
        f=atoi(b.c_str());
          printf("%d*%d=%lld\n",e,f, (long long)e*f);
    return 0;
}
else{
    cout<<"The input is wrong."<<endl;
    return 0;
}
}
 bool is_number(string str){
    for(int i=0;i<str.length();i++){
        if(str.c_str()[0]=='-'&&str.length()>1){
            continue;
        }
        if(str.c_str()[i]>'9'||str.c_str()[i]< '0'){
            return false;
        }
    }
    return true;
}
    
    
    

