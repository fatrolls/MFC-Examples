#include <iostream.h>
class CShape
{
  public:
  virtual void display() { cout << "Shape \n"; }
};
//--------------------------------------------
class CEllipse : public CShape
{
  public:
  virtual void display() { cout << "Ellipse \n"; }
};
//--------------------------------------------
class CCircle : public CEllipse
{
  public:
  virtual void display() { cout << "Circle \n"; }
};
//--------------------------------------------
class CTriangle : public CShape
{
  public:
  virtual void display() { cout << "Triangle \n"; }
};
//--------------------------------------------
class CRect : public CShape
{
  public:
  virtual void display() { cout << "Rectangle \n"; }
};
//--------------------------------------------
class CSquare : public CRect
{
  public:
  virtual void display() { cout << "Square \n"; }
};
//--------------------------------------------
void main()
{
CShape     aShape;
CEllipse   aEllipse;
CCircle    aCircle;
CTriangle  aTriangle;
CRect      aRect;
CSquare    aSquare;
CShape* pShape[6] = { &aShape,
                      &aEllipse,
                      &aCircle,
                      &aTriangle,
                      &aRect,
                      &aSquare };

  for (int i=0; i< 6; i++)
       pShape[i]->display();
}
//--------------------------------------------
