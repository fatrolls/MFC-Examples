///////////////////////////////////////////////////////////////////
// Header  : DOCVIEW2.H
//
// Purpose : Interface for the CDocView2App class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////
// The CDocView2App application class

class CDocView2App : public CWinApp
{
public:
   CDocView2App();
   virtual ~CDocView2App();

   // Overrides
	virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////
