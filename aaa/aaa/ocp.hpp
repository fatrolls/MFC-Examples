#pragma  once
/*RTTI violating the open-closed principle.*/ 
#include <set>
class Point 
{
private: 
    int x;
    int y;
};
class Shape 
{
    virtual void whooww();
}; 
class Square : public Shape 
{ 
private: 
    Point itsTopLeft; 
    double itsSide; 
    friend void DrawSquare(Square*); 
}; 
class Circle : public Shape 
{ 
private: 
    Point itsCenter; 
    double itsRadius; 
    friend void DrawCircle(Circle*); 
}; 
void DrawAllShapes(std::set<Shape*>& ss);
void DrawSquare(Square*);
void DrawCircle(Circle*); 

/////////////////////////////

/*RTTI that does not violate the open-closed Principle.*/ 
class Shape2 
{ 
public: 
   virtual void Draw() const = 0; 
}; 
class Square2 : public Shape2 
{ 
   // as expected. 
}; 
void DrawSquaresOnly(std::set<Shape2*>& ss);