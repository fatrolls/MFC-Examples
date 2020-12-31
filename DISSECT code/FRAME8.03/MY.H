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
  DECLARE_MESSAGE_MAP()
};

class CMyFrameWnd : public CFrameWnd
{
public:
  CMyFrameWnd();
  ~CMyFrameWnd()  {
                  }
  DECLARE_MESSAGE_MAP()
};

class CMyDoc : public CDocument
{
public:
  CMyDoc::CMyDoc()  {
                    }
  CMyDoc::~CMyDoc() {
                    }
  DECLARE_MESSAGE_MAP()
};

class CMyView : public CView
{
public:
  CMyView::CMyView()   {
                       }
  CMyView::~CMyView()  {
                       }
  DECLARE_MESSAGE_MAP()
};
