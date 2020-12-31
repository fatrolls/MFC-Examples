#if !defined(AFX_IMAGEINFODLG_H__3581B502_8ABD_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_IMAGEINFODLG_H__3581B502_8ABD_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImageInfoDlg.h : header file
//

#include "DIBManagerDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg dialog

class CImageInfoDlg : public CDialog
{
// Construction
public:
	CImageInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageInfoDlg)
	enum { IDD = IDD_IMAGE_INFO_DIALOG };
	CStatic	m_ctlStaticFileStatus;
	CString	m_sFileName;
	CString	m_sFileSize;
	CString	m_sFileStatus;
	CString	m_sFormat;
	CString	m_sHeight;
	CString	m_sSizeInMemory;
	CString	m_sType;
	CString	m_sWidth;
	//}}AFX_DATA
	CDIBManagerDoc* pDoc;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEINFODLG_H__3581B502_8ABD_11D1_A3D5_0080C83F712F__INCLUDED_)
