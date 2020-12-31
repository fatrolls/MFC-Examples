// GridCtrlDemoDlg.h : header file
//

#if !defined(AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_)
#define AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

#include "GridCtrl.h"

class CGridCtrlDemoDlg : public CDialog
{

	class CGridEx : public CGridCtrl
	{
		// Override this function to fill InPlaceListBoxes
		void FillListItems(int nCol, LPARAM cltList);
	};


// Construction
public:
	CGridCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGridCtrlDemoDlg)
	enum { IDD = IDD_GRIDCTRLDEMO_DIALOG };
	CStatic	m_GridRect;
	//}}AFX_DATA
	CGridEx m_Grid;
	CSize m_OldSize;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CGridCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRowResize();
	afx_msg void OnColResize();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_)
