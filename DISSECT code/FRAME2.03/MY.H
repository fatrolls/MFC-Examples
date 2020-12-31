
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


