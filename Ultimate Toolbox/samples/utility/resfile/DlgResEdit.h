// DlgResEdit.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

class COXResourceFile;

/////////////////////////////////////////////////////////////////////////////
// CDlgResEdit dialog

class CDlgResEdit : public CDialog
{
// Construction
public:
	CDlgResEdit(COXResourceFile* pResFile, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDlgResEdit)
	enum { IDD = IDD_RES_EDIT };
	CEdit	m_ctlDump;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgResEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_fontCourier;
	COXResourceFile* m_pResFile;

	void DumpResContents();

	// Generated message map functions
	//{{AFX_MSG(CDlgResEdit)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
