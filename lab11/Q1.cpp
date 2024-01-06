#include<iostream>
using namespace std;



class CStereoShape{
    private:
    static int numberOfObject;
    public:
        virtual float GetArea(){
            cout<<"CStereoShape::GetArea()"<<endl;
            return 0.0;
        }
        virtual float GetVolume(){
            cout<<"CStereoShape::GetVolume()"<<endl;
            return 0.0;
        }
        virtual void Show(){
            cout<<"CStereoShape::Show()"<<endl;
        }
        int GetNumOfObject(){
            return numberOfObject;
        }
        void add(){
            numberOfObject++;
        }

        CStereoShape(){}

};
int CStereoShape::numberOfObject=0;

    class CCube:public CStereoShape
    {
        private:
        float length,width,height;
        public:
        CCube():length(2),width(2),height(2){
            add();

        }
        CCube(float a,float b,float c):length(a),width(b),height(c){
            add();
        }
        

        float GetArea(){
            return 2*(length*width+length*height+width*height);
        }
        float GetVolume(){
            return length*width*height;
        }
        void Show(){
            cout<<"Cube length:"<<length<<" width:"<<width<<" height:"<<height<<endl;
            cout<<"Cube area:"<<GetArea()<<" volume:"<<GetVolume()<<endl;
        }
    };
    class CSphere:public CStereoShape{
        private:
        float r;
        public:
        CSphere():r(2){
            add();
        }
        CSphere(float a){
            r=a;
            add();
            
        }
        float GetArea(){
            return 4*3.14*r*r;
        }
        float GetVolume(){
            return 3.14*r*r*r*4/3;
        }
        void Show(){
            cout<<"Sphere radius:"<<r<<endl;
            cout<<"Sphere area:"<<GetArea()<<" volume:"<<GetVolume()<<endl;
        }


    };
    int main(){
        CCube a_cube(4.0,5.0,6.0);
        CSphere c_sphere(7.9);
        CStereoShape* p;
        p=&a_cube;
        
        p->Show();
        p=&c_sphere;
        p->Show();
        cout<<p->GetNumOfObject()<<endl;


    }
