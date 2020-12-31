// ClipDockDlg.h : header file
//

#if !defined(AFX_CLIPDOCKDLG_H__89C11C7E_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_)
#define AFX_CLIPDOCKDLG_H__89C11C7E_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXMulticlipboardDlg.h"
#include "OXAppBar.h"
/////////////////////////////////////////////////////////////////////////////
// CClipDockDlg dialog

class CClipDockDlg : public COXAppBar<COXMulticlipboardDlg>
{
// Construction
public:
	CButton* m_pButton;
	CClipDockDlg();	// standard constructor
 
	~CClipDockDlg();
// Dialog Data
	//{{AFX_DATA(CClipDockDlg)
//	enum { IDD = IDD_CLIPDOCK_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	virtual UINT GetButtonsHeight();
	virtual void OnSetEdge(UINT nEdge);
	virtual BOOL CanResize();
	virtual void OnClipInfoChanged(UINT nPocketNumber);
	virtual BOOL ClipObjectToPocket(COXClipPocket* pPocket, 
		COleDataObject* pObject);


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipDockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClipDockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPDOCKDLG_H__89C11C7E_DA60_11D3_AC98_0050BAAB46B1__INCLUDED_)
