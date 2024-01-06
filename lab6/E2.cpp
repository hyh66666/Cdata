#include <iostream>
#include <string>
#include <cstring>
using namespace std;

char* match(char* s,char ch);
int main(){
    cout<<"Please input a string:"<<endl;
    char* s = new char[50];
    cin.get(s,50);
    cout<<"Please input a character:"<<endl;
    char ch;
    cin>>ch;
    char* str = match(s,ch);
    if (str==NULL){
        cout<<"Not Found"<<endl;
    }
    else{
        for (size_t i = 0; i < strlen(str); i++)
        {
            cout<<str[i];
        }
        cout<<endl;
    }
    
}
char* match(char* s,char ch){
    int i = 0;
    for (; i < 50; i++){
        if (s[i]==ch)
        {
            break;
        }
        else if(i == 49 ){
            return NULL;
        }
    }
    char* str = new char[50]; 
    for (size_t j = 0; j < 50-i; j++)
    {
        str[j] = s[i++];
    }
    return str;
}