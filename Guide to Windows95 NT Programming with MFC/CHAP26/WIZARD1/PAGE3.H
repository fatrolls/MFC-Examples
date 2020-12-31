///////////////////////////////////////////////////////////////////
// Header  : PAGE3.H
//
// Purpose : Interface for class CPage3
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __PAGE3_H__
#define __PAGE3_H__

#include "stdafx.h"
#include "resource.h"
#include "wizdata.h"
#include "wizard.h"

///////////////////////////////////////////////////////////////////
// CPage3 dialog

class CPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage3)

// Construction
public:
	CPage3();
	~CPage3();

   // Dialog Data
	enum { IDD = IDD_PAGE3 };
   
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   CFont m_fntTitle;

   // Control access methods
   inline CButton& btn1() 
      { return *(CButton*) GetDlgItem(IDC_PAGE3_1); }

   inline CButton& btn2() 
      { return *(CButton*) GetDlgItem(IDC_PAGE3_2); }

   inline CButton& btn3()                       
      { return *(CButton*) GetDlgItem(IDC_PAGE3_3); }

   inline CButton& btn4() 
      { return *(CButton*) GetDlgItem(IDC_PAGE3_4); }

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

   DECLARE_MESSAGE_MAP()
};

#endif // __PAGE3_H__

