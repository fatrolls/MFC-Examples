// UNCListDlg.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////
// CRegistryListDlg dialog

#include "OXIteratorRegistryItem.h"

class CRegistryListDlg : public CDialog
{
// Construction
public:
	void SetSearchItem(COXIteratorRegistryItem iterItem, BOOL bIncludeValues,
	BOOL bIncludeSubkeys, BOOL bReversedOrder, BOOL bRecursive,
	BOOL bDepthFirst);

	CRegistryListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegistryListDlg)
	enum { IDD = IDD_REGISTRY_LIST };
	CButton	m_wndClose;
	CListBox	m_wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistryListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bIncludeValues;
	BOOL m_bIncludeSubkeys;
	BOOL m_bReversedOrder;
	BOOL m_bRecursive;
	BOOL m_bDepthFirst;
	COXIteratorRegistryItem m_iterItem;

	// Generated message map functions
	//{{AFX_MSG(CRegistryListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
