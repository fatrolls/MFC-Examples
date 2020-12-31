// PukamSoft.h : main header file for the PUKAMSOFT application
//

#if !defined(AFX_PUKAMSOFT_H__44F256BE_ACCA_4F52_A958_1C33702527DE__INCLUDED_)
#define AFX_PUKAMSOFT_H__44F256BE_ACCA_4F52_A958_1C33702527DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif



#include "resource.h"		// main symbols
#include "BitmapIDs.h"
#include "ImageIDs.h"
#include "..\Common\Tools\CustomDB.h"
#include "..\Common\Tools\GlobalFunctions.h"
#include "MessageBoxDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CPukamSoftApp:
// See PukamSoft.cpp for the implementation of this class
//

class CPukamSoftApp : public CWinApp
{
public:
	CStringArray* GetCategories();
	CStringArray* GetStorageLocation();
	HMODULE GetDLLHandle();
	CCustomDB* GetConnectionObject();
	CPukamSoftApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPukamSoftApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPukamSoftApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CStringArray m_csCategoriesArray;
	CStringArray m_csStorageLocationArray;
	CCustomDB m_dbWrapper;
	HMODULE m_hDLL;
private:
	void LoadData();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUKAMSOFT_H__44F256BE_ACCA_4F52_A958_1C33702527DE__INCLUDED_)
