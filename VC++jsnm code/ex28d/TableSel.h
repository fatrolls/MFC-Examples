// tablesel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableSelect dialog

class CTableSelect : public CDialog
{
// Construction
public:
	CTableSelect(CDatabase* pDatabase, CWnd* pParent = NULL);

// Dialog Data
	CDatabase* m_pDatabase;  // listbox init needs this
	//{{AFX_DATA(CTableSelect)
	enum { IDD = IDD_TABLE_SELECT };
	CString	m_strSelection;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTableSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
