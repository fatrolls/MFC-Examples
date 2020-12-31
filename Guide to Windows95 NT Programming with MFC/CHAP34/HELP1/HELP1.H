///////////////////////////////////////////////////////////////////
//  Header  : HELP1.H
//
//  Purpose : Header file for HELP1.CPP and the HELP1 program 
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-31-96
///////////////////////////////////////////////////////////////////

#include "resource.h"	// main symbols 

/////////////////////////////////////////////////////////////////////////////
// CHelp1App - Application class derived from CWinApp

class CHelp1App : public CWinApp
{
public:
   // Overrides
   virtual BOOL InitInstance();
   
   // Message handler
   afx_msg void OnHelp();

   // Help helper function
   DWORD GetHelpControl(DWORD nCtrlFirst, DWORD nCtrlLast);
   
   DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
