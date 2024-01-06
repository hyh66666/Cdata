#include <iostream>
#include <string>
#include <cstring>
using namespace std;
void displaySquare(int side=4,char filledCharacter);

int main(){
    int side;
    char c;
    printf("input:\n");
    // cin>>side;
    cin>>c;
    displaySquare(c);
    return 0;
}
void displaySquare(int side,char filledCharacter){
    for(int i=0;i<side;i++){
        for(int j=0;j<side;j++){
            cout<<filledCharacter;
        }
        cout<<endl;
    }
    
}
