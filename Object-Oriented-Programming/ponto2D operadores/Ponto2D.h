#include<iostream> 

class Ponto2D{
    
    int x,y;
    
    public:
        Ponto2D(int xx=0, int yy=0): x(xx),y(yy){ };
        void setX (const int xx) { x = xx; };
        void setY (const int yy) { y = yy; };
        int getX (void) const { return x; }
        int getY (void) const { return y; }
        Ponto2D& operator-- ();
        Ponto2D operator+ (const Ponto2D& p2) const;
        ~Ponto2D(){}; 
}; 