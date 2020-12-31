#include "ocp.hpp"

#include <iostream>
void DrawSquare(Square*)
{
    std::cout<<"Draw Square";
}
void DrawCircle(Circle*)
{
    std::cout<<"Draw Circle";
}
void DrawAllShapes(std::set<Shape*>& ss) 
{ 
    for (std::set<Shape*>::iterator i=ss.begin(); i!=ss.end(); i++) 
    { 
        Circle* c = dynamic_cast<Circle*>(*i); 
        Square* s = dynamic_cast<Square*>(*i); 
        if (c) 
            DrawCircle(c); 
        else if (s) 
            DrawSquare(s); 
    } 
} 
///////////////////////////////////////
void DrawSquaresOnly(std::set<Shape2*>& ss) 
{ 
    for (std::set<Shape2*>::iterator i=ss.begin(); i!=ss.end(); i++) 
    { 
        Square2* s = dynamic_cast<Square2*>(*i); 
        if (s) 
        s->Draw(); 
    } 
} 