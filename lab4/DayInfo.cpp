#include<iostream>
#include<string>
using namespace std;

enum Days{MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY};
enum Weather{Sunny,Rainy,Cloudy};
struct DayInfo{
    Days days;
    Weather weather;
}dayinfo;

int main(){
    dayinfo.days=MONDAY;
    dayinfo.weather=Sunny;

    bool flag=false;
    if((dayinfo.days==SUNDAY||dayinfo.days==SATURDAY)&&dayinfo.weather==Sunny){
       flag=true;
    }
    if(flag){
        cout<<"Yes"<<endl;
    }
    else {
        cout<<"No"<<endl;
    }


}