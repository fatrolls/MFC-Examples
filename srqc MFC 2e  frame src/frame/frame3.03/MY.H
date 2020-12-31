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
public:
  CMyFrameWnd();
  ~CMyFrameWnd()  {
                  }
};


class CMyDoc : public CDocument
{
public:
  CMyDoc::CMyDoc()  {
                    }
  CMyDoc::~CMyDoc() {
                    }
};

class CMyView : public CView
{
public:
  CMyView::CMyView()   {
                       }
  CMyView::~CMyView()  {
                       }
};

// global function
void PrintAllClasses();
