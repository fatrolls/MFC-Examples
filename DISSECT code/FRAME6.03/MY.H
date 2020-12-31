#include <iostream.h>
#include "mfc.h"

class CMyWinApp : public CWinApp
{
public:
  CMyWinApp::CMyWinApp()   {
                           }
  CMyWinApp::~CMyWinApp()  {
                           }

  virtual BOOL InitInstance();
};

class CMyFrameWnd : public CFrameWnd
{
        DECLARE_DYNCREATE(CMyFrameWnd)
public:
  CMyFrameWnd();
  ~CMyFrameWnd()  {
                  }
  void SayHello() { cout << "Hello CMyFrameWnd \n"; }
};

class CMyDoc : public CDocument
{
        DECLARE_DYNCREATE(CMyDoc)
public:
  CMyDoc::CMyDoc()  {
                      cout << "CMyDoc Constructor \n";
                    }
  CMyDoc::~CMyDoc() {
                    }
  void SayHello() { cout << "Hello CMyDoc \n"; }
};

class CMyView : public CView
{
        DECLARE_DYNCREATE(CMyView)
public:
  CMyView::CMyView()   {
                      cout << "CMyView Constructor \n";
                       }
  CMyView::~CMyView()  {
                       }
  void SayHello() { cout << "Hello CMyView \n"; }
};

// global function
void AfxPrintAllClasses();
