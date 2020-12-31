///////////////////////////////////////////////////////////////////
// Header  : PAGE2.H
//
// Purpose : Interface for class CPage2
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __PAGE2_H__
#define __PAGE2_H__

#include "stdafx.h"
#include "resource.h"
#include "wizdata.h"
#include "wizard.h"

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage2)

// Construction
public:
	CPage2();
	~CPage2();

   // Dialog Data
	enum { IDD = IDD_PAGE2 };
   
public:
   // Overrides
	virtual LRESULT OnWizardNext();

protected:                          
   // DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX); 

   CFont m_fntTitle;

   // Control access methods
   inline CButton& btn1() 
      { return *(CButton*) GetDlgItem(IDC_PAGE2_1); }

   inline CButton& btn2() 
      { return *(CButton*) GetDlgItem(IDC_PAGE2_2); }

   inline CButton& btn3()                       
      { return *(CButton*) GetDlgItem(IDC_PAGE2_3); }

   inline CButton& btn4() 
      { return *(CButton*) GetDlgItem(IDC_PAGE2_4); }

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

#endif  // __PAGE2_H__
