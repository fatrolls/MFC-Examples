///////////////////////////////////////////////////////////////////
// Header  : INTROPG.H
//
// Purpose : Interface for class CIntroPage
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __INTROPG_H__
#define __INTROPG_H__

#include "stdafx.h"
#include "resource.h"
#include "colors.h"
#include "wizard.h"

///////////////////////////////////////////////////////////////////
// CIntroPage dialog

class CIntroPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CIntroPage)

// Construction
public:
	CIntroPage();
   ~CIntroPage();

   // Dialog Data
	enum { IDD = IDD_INTRO };

protected:    
   CFont m_fntTitle;  // font for the title of this page
   
   // DDX/DDV support
   virtual void DoDataExchange(CDataExchange* pDX);  

	// Message map entries
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

   DECLARE_MESSAGE_MAP()   
};

#endif  // __INTROPG_H__
