// TriangleButtonDemoDlg.h : header file
//

#include "trianglebutton.h"

#if !defined(AFX_TRIANGLEBUTTONDEMODLG_H__11402BAB_8D8B_11D1_8F03_0060975DBA64__INCLUDED_)
#define AFX_TRIANGLEBUTTONDEMODLG_H__11402BAB_8D8B_11D1_8F03_0060975DBA64__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoDlg dialog

class CTriangleButtonDemoDlg : public CDialog
{
// Construction
public:
	CTriangleButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor
	
	void ChangeTriButtonDirection(CTriangleButton::POINTDIRECTION d);



// Dialog Data
	//{{AFX_DATA(CTriangleButtonDemoDlg)
	enum { IDD = IDD_TRIANGLEBUTTONDEMO_DIALOG };
	CEdit	buttontext;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CTriangleButton	trif7;
	CTriangleButton	trif6;
	CTriangleButton	tri3d7;
	CTriangleButton	tri3d6;
	CTriangleButton	trif5;
	CTriangleButton	trif4;
	CTriangleButton	trif3;
	CTriangleButton	trif2;
	CTriangleButton trif1;
	CTriangleButton	tri3d5;
	CTriangleButton	tri3d4;
	CTriangleButton	tri3d3;
	CTriangleButton	tri3d2;
	CTriangleButton	tri3d1;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriangleButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTriangleButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeButtontext();
	afx_msg void OnChDisable();
	afx_msg void OnRaDown();
	afx_msg void OnRaLeft();
	afx_msg void OnRaRight();
	afx_msg void OnRaUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIANGLEBUTTONDEMODLG_H__11402BAB_8D8B_11D1_8F03_0060975DBA64__INCLUDED_)
