#include <iostream>
#include<assert.h>
using namespace std;
float av(float a,float b,float c,float d);
float av(float a,float b,float c,float d){
    assert(a>=0&&a<=100&&b>=0&&b<=100&&c>=0&&c<=100&&d>=0&&d<=100);
    
    return a;
}

// float& average(float &out, float a, float b) {
//     out = (a + b) / 2;
//     return out;
// }
int main(){
    float a,b,c,d,e;
    e=av(a,b,c,d);
    char C;
    bool flag=true;
    while(flag){
    cout<<"Please enter marks for 4 courses:"<<endl;
    cin>>a>>b>>c>>d;
    cout<<"The average of the four courses is:"<<av(a,b,c,d)<<endl;
    cout<<"Would you want to enter another marks for 4 courses(y/n)?"<<endl;
    cin>>C;
    if(C=='n'){
        flag=false;
    }
    }

}