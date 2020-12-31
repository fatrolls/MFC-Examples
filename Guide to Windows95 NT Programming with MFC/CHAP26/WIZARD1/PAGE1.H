///////////////////////////////////////////////////////////////////
// Header  : PAGE1.H
//
// Purpose : Interface for class CPage1
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __PAGE1_H__
#define __PAGE1_H__

#include "stdafx.h"
#include "resource.h"
#include "wizdata.h"
#include "wizard.h"

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage1)

public:
   // Construction
	CPage1();
	~CPage1();

   // Dialog Data
	enum { IDD = IDD_PAGE1 };
	
   CString	m_sCompany;
	CString	m_sEmail;
	CString	m_sFirstName;
	CString	m_sLastName;

public:
   // Overrides
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
   CFont m_fntTitle;
   
   // Control access methods
   inline CEdit& editFirst() 
      { return *(CEdit*) GetDlgItem(IDC_FIRSTNAME); }

   inline CEdit& editLast() 
      { return *(CEdit*) GetDlgItem(IDC_LASTNAME); }

protected:
	// Message map members
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();

   DECLARE_MESSAGE_MAP()
};

#endif  // __PAGE1_H__
