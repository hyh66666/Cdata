#include<iostream>
using namespace std;
#include"function1.h"
int main(){
  point a, b;
 Setvalues(a,b);
  point c=middle(a,b);
  cout<<c.x<<endl;
  cout<<c.y<<endl;
  return 0;

}