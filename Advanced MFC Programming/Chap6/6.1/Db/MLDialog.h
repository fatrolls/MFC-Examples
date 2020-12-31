class CMLDialog : public CDialog
{
public:
	CMLDialog(CWnd* pParent = NULL);
	void DoModeless();
	//{{AFX_DATA(CMLDialog)
	enum { IDD = IDD_DIALOG_MODELESS };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CMLDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	CWnd *m_pParent;
	//{{AFX_MSG(CMLDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
