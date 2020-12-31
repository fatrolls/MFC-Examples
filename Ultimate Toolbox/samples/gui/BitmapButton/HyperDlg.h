// HyperDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHyperDlg dialog

#include "OXBitmapButton.h"
#include "OXDIB.h"

class CHyperDlg : public CDialog
{
// Construction
public:
	CHyperDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHyperDlg)
	enum { IDD = IDD_HYPER_DLG };
	COXBitmapButton	m_wndButton3;
	COXBitmapButton	m_wndButton2;
	COXBitmapButton	m_wndButton1;
	CButton	m_wndSpace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect m_spaceRect;
	COXDIB m_space;

	// Generated message map functions
	//{{AFX_MSG(CHyperDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
