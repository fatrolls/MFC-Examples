// MyFontDlg.h : header file
//

#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CFontDlg dialog

class CFontDlg : public CFontDialog
{
	DECLARE_DYNAMIC(CFontDlg)

public:
	CFontDlg(double,LPLOGFONT);

	double GetHeight(void);

	CString m_szSpecFont;
	BOOL	m_bFontAdded;

	CString	m_szHeight;

protected:
	// member variables
	BOOL	m_bHeightUndefined;
	double  m_Height;
	BOOL    m_bActive;

	LOGFONT m_MyLogfont;
	BOOL    m_bLogfontInitialized;
	BOOL    m_bFontChanged;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	void UpdateCombos(void);
	// disable default constructor
	CFontDlg ();

public:
	void GetCurrentFont(LPLOGFONT);

protected:
	//{{AFX_MSG(CFontDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckHeightundefined();
	afx_msg void OnKillfocusEditheight();
	afx_msg void OnHelpBut();
	//}}AFX_MSG
	afx_msg void OnSelchangeFontCombo();
	afx_msg void OnSelchangeFontstyleCombo();
	afx_msg void OnSelchangeScriptCombo();
	afx_msg void OnActivateApp(BOOL,HTASK);
	afx_msg BOOL OnQueryEndSession();
	afx_msg LONG OnErrMessage(UINT,LONG);
	DECLARE_MESSAGE_MAP()
};
