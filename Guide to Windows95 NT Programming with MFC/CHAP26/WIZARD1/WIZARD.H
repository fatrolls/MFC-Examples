///////////////////////////////////////////////////////////////////
// Header  : WIZARD.H
//
// Purpose : Interface for class CWizard
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __WIZARD_H__
#define __WIZARD_H__

#include "stdafx.h"
#include "wizdata.h"

/////////////////////////////////////////////////////////////////////////////
// CWizard

class CWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizard)

public:
   SAMPLEWIZDATA m_swd;  // custom data struct
   
   // Construction
	CWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, 
      UINT iSelectPage = 0);
	CWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, 
      UINT iSelectPage = 0);
	virtual ~CWizard();
 
   // Helper method
   void DisplayReport();
};

#endif  // __WIZARD_H__

/////////////////////////////////////////////////////////////////////////////
