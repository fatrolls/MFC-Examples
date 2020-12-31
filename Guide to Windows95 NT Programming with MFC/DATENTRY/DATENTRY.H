// datentry.h : main header file for the DATENTRY application
//

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"   // main symbols

class CDatentryApp : public CWinApp
{
public:
  CDatentryApp();

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDatentryApp)
  public:
  virtual BOOL InitInstance(); 
  virtual int ExitInstance();
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CDatentryApp)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

