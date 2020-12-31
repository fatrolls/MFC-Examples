///////////////////////////////////////////////////////////////////
// Header  : DOCVIEW1.H
//
// Purpose : Interface for the CDocView1App class.
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
// The CDocView1App application class

class CDocView1App : public CWinApp
{
public:
   CDocView1App();
   virtual ~CDocView1App();

   // Overrides
	virtual BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////
