// ScrollDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog

#include "OXScrollTipOwner.h"

class CScrollDlg : public CDialog
{
// Construction
public:
	CScrollDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollDlg)
	enum { IDD = IDD_SCROLL_DLG };
	CListBox	m_wndList;
	CScrollBar	m_wndHorzScroll1;
	CScrollBar	m_wndHorzScroll2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXScrollTipOwner m_wndHScrollTipOwner1;
	COXScrollTipOwner m_wndHScrollTipOwner2;
	COXScrollTipOwner m_wndVScrollTipOwner1;
	COXScrollTipOwner m_wndListScrollTipOwner;

	// Generated message map functions
	//{{AFX_MSG(CScrollDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
