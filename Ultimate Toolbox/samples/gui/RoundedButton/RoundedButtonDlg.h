// RoundedButtonDlg.h : header file
//

#if !defined(AFX_ROUNDEDBUTTONDLG_H__9B0A917C_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
#define AFX_ROUNDEDBUTTONDLG_H__9B0A917C_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXRoundedButton.h"
#include "OXColorPickerButton.h"
#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonDlg dialog

class CRoundedButtonDlg : public CPropertyPage
{
// Construction
public:
	CRoundedButtonDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRoundedButtonDlg)
	enum { IDD = IDD_ROUNDEDBUTTON_CUSTOMIZE_DIALOG };
	CSpinButtonCtrl	m_spinThetta;
	CSpinButtonCtrl	m_spinIntRadius;
	CSpinButtonCtrl	m_spinExtRadius;
	CSpinButtonCtrl	m_spinPhong;
	CSpinButtonCtrl	m_spinPhi;
	CSpinButtonCtrl	m_spinMirror;
	CSpinButtonCtrl	m_spinLightIntensity;
	CSpinButtonCtrl	m_spinDiffuse;
	CSpinButtonCtrl	m_spinAmbient;
	COXSeparator	m_separator;
	COXSeparator	m_sepSurfaceSettings;
	COXSeparator	m_sepLightSourceSettings;
	COXSeparator	m_sepButtonSettings;
	COXColorPickerButton	m_btnLightColor;
	COXColorPickerButton	m_btnButtonColor;
	COXRoundedButton	m_btnRound;
	float	m_fAmbient;
	float	m_fDiffuse;
	float	m_fLightIntensityCoef;
	float	m_fMirror;
	float	m_fPhi;
	int		m_nPhong;
	int		m_nSphereExtRadius;
	int		m_nSphereIntRadius;
	float	m_fThetta;
	//}}AFX_DATA
	COLORREF m_clrButton;
	COLORREF m_clrLight;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundedButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void GetVars();
	void SetVars();

	// Generated message map functions
	//{{AFX_MSG(CRoundedButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDEDBUTTONDLG_H__9B0A917C_D23B_11D2_A7D8_525400DAF3CE__INCLUDED_)
