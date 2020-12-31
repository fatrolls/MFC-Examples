#if !defined(AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HeaderCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx window

class CHeaderCtrlEx : public CHeaderCtrl
{
// Construction
public:
	CHeaderCtrlEx();

// Attributes
public:
	CFont	m_NewHeaderFont;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHeaderCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEX_H__30509657_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
