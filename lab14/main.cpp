#include<iostream>
#include<string>
using namespace std;

class Driver;
class Car
{
    
private:
    enum Mode{Off, On};
    enum vel{Minvel = 0, Maxvel = 200};
    int mode;
    int velocity;
    
public:

    friend class Driver;
    Car(int m = On, int v = 50):mode(m),velocity(v){ }
    bool velup(int v)
    {
        if (velocity+v > Maxvel)
        {
            return false;
        } 
        else
        {
            velocity += v;
            string s;
            if (mode == 0)
                s = "Off";
            else
                s = "On";
            cout<<"Increase velocity by car, its mode is "<<s<<", velovity is "<<velocity<<endl;
            return true;
        }
    }
    bool veldowm(int v)
    {
        if (velocity-v < Minvel)
        {
            return false;
        }
        else
        {
            velocity -= v;
            return true;
        }
    }
    bool ison() const
    {
        if (mode == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
    int getvel() const
    {
        return velocity;
    }
    void showinfo() const
    {      
        string s;
            if (mode == 0)
                s = "Off";
            else
                s = "On";
        cout<<"The imfomation of car: mode is "<<s<<", velocity is "<<velocity<<endl;
    }
};

class Driver
{
public:

    bool velup(Car& car,int v)
    {
        string s;
            if (car.mode == 0)
                s = "Off";
            else
                s = "On";
        cout<<"Increase velocity by driver: mode is "<<s<<", velocity is "<<car.velocity + v<<".";
        if (car.velocity+v > car.Maxvel)
        {
            cout<<" It is out of Maxvel"<<endl;
            return false;
        } 
        else
        {
            car.velocity += v;
            cout<<endl;
            return true;
        }
    }
    bool veldown(Car& car, int v)
    {
        string s;
            if (car.mode == 0)
                s = "Off";
            else
                s = "On";
        cout<<"Decrease velocity by driver: mode is "<<s<<", velocity is "<<car.velocity - v<<".";
        if (car.velocity-v < car.Minvel)
        {
            cout<<" It is out of Minvel"<<endl;
            return false;
        }
        else
        {
            car.velocity -= v;
            cout<<endl;
            return true;
        }
    }
    void setmode(Car& car)
    {
        cout<<"Set the mode of car by driver:"<<endl;
        string s;
            if (car.mode == 0)
                s = "Off";
            else
                s = "On";
        cout<<"The mode of car is: "<<s<<endl;
        if (car.mode == 0)
        {
            car.mode = 1;
        }
        else
        {
            car.mode = 0;
        }
    }
    bool ison(Car& car) const
    {
        if (car.mode == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    Car car;
    car.showinfo();
    Driver driver;
    car.velup(120);
    driver.setmode(car);
    car.showinfo();
    driver.veldown(car,100);
    driver.velup(car,150);
}
