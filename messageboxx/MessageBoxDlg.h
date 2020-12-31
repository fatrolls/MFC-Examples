#pragma once

class CMessageBoxDlg : public CDialog
{
public:
//Constructors / Destructors
	CMessageBoxDlg(CWnd* pParent = NULL);	// standard constructor

//Member variables
	enum { IDD = IDD_MESSAGEBOX_DIALOG };
	CString	m_sCaption;
	BOOL	m_bCheckBox;
	BOOL	m_bCheckBoxInitialState;
	CString	m_sCheckBoxText;
	BOOL	m_bDisable;
	BOOL	m_bRightAlign;
	CString	m_sText;
	BOOL	m_bTimeout;
	BOOL	m_bModifyCaptionForDisabled;
	BOOL	m_bModifyCaptionForTimer;
	BOOL	m_bResetTimerOnUserActivity;
	BOOL	m_bHTML;
	CString	m_sHTMLText;
	BOOL	m_bSelectableText;
	CString	m_sCaption1;
	CString	m_sCaption2;
	BOOL	m_bAnimatedCaption;
	BOOL	m_bAnimatedText;
  BOOL m_bUserIcon;

protected:
//Member variables
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnHtml();

	DECLARE_MESSAGE_MAP()
};
