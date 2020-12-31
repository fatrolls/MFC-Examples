// PhysicalEditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhysicalEditDlg dialog

#include "OXPhysicalEditEx.h"
#include "OXColorPickerButton.h"
#include "OXFontPickerButton.h"
#include "OXSeparator.h"

class CPhysicalEditDlg : public CPropertyPage
{
// Construction
public:
	CPhysicalEditDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPhysicalEditDlg)
	enum { IDD = IDD_PHYSICALEDIT_DIALOG };
	COXSeparator	m_sepValue;
	COXSeparator	m_sepBottom;
	COXSeparator	m_sepControlAppearance;
	COXColorPickerButton	m_btnTextColorNegative;
	COXFontPickerButton	m_btnFont;
	COXColorPickerButton	m_btnTextColor;
	COXColorPickerButton	m_btnBackColor;
	COXTempEdit	m_wndTemp;
	COXTimeEdit	m_wndTime;
	COXLengthEdit	m_wndLength;
	COXAngleEdit	m_wndAngle;
	BOOL	m_bShowUnit;
	BOOL	m_bShowDropdownButton;
	BOOL	m_bDropdownLeftAligned;
	//}}AFX_DATA
	double	m_dConvAngle;
	double	m_dConvLength;
	double	m_dConvTemp;
	double	m_dConvTime;
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrTextNegative;
	CFont m_font;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhysicalEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhysicalEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBackcolor();
	afx_msg void OnButtonTextcolor();
	afx_msg void OnButtonFont();
	afx_msg void OnButtonTextcolorNegative();
	afx_msg void OnCheckShowUnit();
	afx_msg void OnCheckShowDropdown();
	afx_msg void OnCheckLeftaligned();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
