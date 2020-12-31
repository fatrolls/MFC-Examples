#include <iostream.h>

class CObject
{
public:
  virtual void Serialize() { cout << "CObject::Serialize() \n\n"; }
};

class CDocument : public CObject
{
public:
  int m_data1;
  void func() { cout << "CDocument::func()" << endl;
                Serialize();
              }

  virtual void Serialize() { cout << "CDocument::Serialize() \n\n"; }
};

class CMyDoc : public CDocument
{
public:
  int m_data2;
  virtual void Serialize() { cout << "CMyDoc::Serialize() \n\n"; }
};
//------------------------------------------------------------------
void main()
{
CMyDoc  mydoc;
CMyDoc* pmydoc = new CMyDoc;

  cout << "#1 testing" << endl;
  mydoc.func();

  cout << "#2 testing" << endl;
  ((CDocument*)(&mydoc))->func();

  cout << "#3 testing" << endl;
  pmydoc->func();

  cout << "#4 testing" << endl;
  ((CDocument)mydoc).func();
}

