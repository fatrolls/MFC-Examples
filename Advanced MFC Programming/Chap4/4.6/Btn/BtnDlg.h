// BtnDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBtnDlg dialog

#include "MButton.h"

class CBtnDlg : public CDialog
{
// Construction
public:
	CBtnDlg(CWnd* pParent = NULL);	// standard constructor
	void SetCheckBitmap(UINT);
	void SetRadioBitmap();

// Dialog Data
	//{{AFX_DATA(CBtnDlg)
	enum { IDD = IDD_BTN_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBtnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	MCBitmapButton m_btnPlay;
	MCBitmapButton m_btnPlayPos;
	CBitmapButton m_btnCheck;
	CBitmapButton m_btnRadioA;
	CBitmapButton m_btnRadioB;
	CBitmap m_bmpCheck;
	CBitmap m_bmpUnCheck;
	BOOL m_bBmpCheck;
	UINT m_uBmpRadio;
	CRect m_rectBtnPos[4];

	// Generated message map functions
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
	afx_msg LONG OnBtnPos(UINT, LONG);
	DECLARE_MESSAGE_MAP()
};
