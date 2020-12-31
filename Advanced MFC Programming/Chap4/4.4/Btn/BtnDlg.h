class CBtnDlg : public CDialog
{
public:
	CBtnDlg(CWnd* pParent = NULL);
	void SetCheckBitmap(UINT);
	void SetRadioBitmap();
	//{{AFX_DATA(CBtnDlg)
	enum { IDD = IDD_BTN_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CBtnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	CBitmapButton m_btnPlay;
	CBitmapButton m_btnCheck;
	CBitmapButton m_btnRadioA;
	CBitmapButton m_btnRadioB;
	CBitmap m_bmpCheck;
	CBitmap m_bmpUnCheck;
	BOOL m_bBmpCheck;
	UINT m_uBmpRadio;
	//{{AFX_MSG(CBtnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck();
	afx_msg void OnRadioA();
	afx_msg void OnRadioB();
	afx_msg void OnBmpCheck();
	afx_msg void OnBmpRadioA();
	afx_msg void OnBmpRadioB();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
