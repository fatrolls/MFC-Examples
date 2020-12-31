// BitmapButtonDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonDemoDlg dialog

#include "OXBitmapButton.h"
#include "OXSoundEffectManager.h"


class CBitmapButtonDemoDlg : public CDialog
{
// Construction
public:
	CBitmapButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBitmapButtonDemoDlg)
	enum { IDD = IDD_BITMAPBUTTONDEMO_DIALOG };
	COXBitmapButton	m_wndButtonAnimated;
	CStatic	m_wndNew;
	COXBitmapButton	m_wndButton12;
	COXBitmapButton	m_wndButton11;
	COXBitmapButton	m_wndButton10;
	COXBitmapButton	m_wndButton1;
	BOOL	m_bDisabled1;
	BOOL	m_bTrackLook1;
	BOOL	m_bTrackLook1x;
	BOOL	m_bAction1;
	int		m_nAlignment;
	BOOL	m_bAutoResize1;
	CString	m_sText1;
	BOOL	m_bText1x;
	CString	m_sToolTipText1;
	BOOL	m_bToolTip;
	BOOL	m_bDisabled1X;
	BOOL	m_bPseudoDisable;
	BOOL	m_bHyperLook;
	int		m_nStyle;
	CString	m_sHeader;
	BOOL	m_bMultiline;
	//}}AFX_DATA
	int nState;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSize m_originalSize1;
	CFont m_largeFont;

	void PositionButtonRow();

	// Generated message map functions
	//{{AFX_MSG(CBitmapButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDisabled1();
	afx_msg void OnTrackLook1x();
	afx_msg void OnTrackLook1();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnButton1();
	afx_msg void OnAlignment();
	afx_msg void OnAutoResize1();
	afx_msg void OnSetText();
	afx_msg void OnText1x();
	afx_msg void OnFont1();
	afx_msg void OnSetTooltip();
	afx_msg void OnTooltip();
	afx_msg void OnDisabled1x();
	afx_msg void OnHyper();
	afx_msg void OnPseudoDisable();
	afx_msg void OnHyperLook();
	afx_msg void OnRadioNormal();
	afx_msg void OnRadioDropdown();
	afx_msg void OnRadioRightdropdown();
	afx_msg void OnRadioToggle();
	afx_msg void OnRadioNoarrowdropdown();
	afx_msg void OnRadioTogglethreestate();
	afx_msg void OnAction1();
	afx_msg void OnMultiline();
	//}}AFX_MSG
	afx_msg void OnDropDownButton1(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnToggleButton1(NMHDR * pNotifyStruct, LRESULT * result);
	DECLARE_MESSAGE_MAP()

private:
};
