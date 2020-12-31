// DialogPalette.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogPalette dialog

class CDialogPalette : public CDialog
{
// Construction
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_IsNode[256];
	int m_Space;
	int m_Height;
	int m_Width;
  int m_Oldi;
  int m_Oldj;

  BYTE m_Red[256];
  BYTE m_Green[256];
  BYTE m_Blue[256];
	CUIntArray m_ArrayNode;
  int m_Selected;
  
	CDialogPalette(CWnd* pParent = NULL);   // standard constructor
	CBitmap m_Bitmap;
	CDC m_MemDC;

	void DrawPalette();
  void MakePalette();
  void DrawItem(CDC *pDC,COLORREF LineColor,COLORREF FillColor,CRect &rect);
  void DrawPaletteItem(int i,int j);
  void DrawLine(CDC *pDC,int x1,int y1,int x2,int y2,COLORREF color = RGB(0,0,0),int PenStyle = PS_SOLID);
	void Init();





// Dialog Data
	//{{AFX_DATA(CDialogPalette)
	enum { IDD = IDD_DIALOG_PALETTE };
	CString	m_StringBlue;
	CString	m_StringGreen;
	CString	m_StringRed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPalette)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;

	// Generated message map functions
	//{{AFX_MSG(CDialogPalette)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonChange();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonDeleteAll();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
