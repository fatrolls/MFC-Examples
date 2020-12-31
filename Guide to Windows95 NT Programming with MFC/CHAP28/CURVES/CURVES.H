///////////////////////////////////////////////////////////////////
//  Header  : CURVES.H
//
//  Purpose : Header for the CURVES program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-20-96
///////////////////////////////////////////////////////////////////

#include "mainfram.h"   // Custom frame window base class

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class 

class CMainWnd : public CMainFrame
{ 
protected:
   CCurveThread*  m_pThread1;
   CCurveThread*  m_pThread2;
   CCurveThread*  m_pThread3;

public: 
   virtual ~CMainWnd();
   void StartThreads();
};
