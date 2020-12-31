// MeasurePage.h : header file
//

#ifndef __MEASPAGE_H_
#define __MEASPAGE_H_

#include "OXDckPPg.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// SMeasureParms struct

struct SMeasureParms 
{
	BOOL	bShowSection;
	BOOL	bSnapSection;
	enum EMeasureType
	{
		mtNothing = 0,
		mtP2P,
		mtLine,
		mtArc,
		mtAngle
	} eMeasureType;

	enum EHint
	{
		hAll
	};

	SMeasureParms() :
		bShowSection(FALSE),
		bSnapSection(FALSE),
		eMeasureType(mtNothing)
		{}
};

/////////////////////////////////////////////////////////////////////////////
// CMeasurePage dialog

class CMeasurePage : public COXDockPropertyPage
{
// Data Members
public:

protected:
//	CMeasureBar  m_toolBar;
	//{{AFX_DATA(CMeasurePage)
	enum { IDD = IDD_MEASURE };
	CButton			m_snapSection;
	CButton			m_showSection;
	CSpinButtonCtrl	m_spinP2P;
	BOOL			m_bShowSection;
	BOOL			m_bSnapSection;
	//}}AFX_DATA

private:

//Member Functions
public:
	CMeasurePage(BOOL bDynamic = FALSE);
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasurePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeasurePage)
	afx_msg void OnP2P();
	afx_msg void OnAngle();
	afx_msg void OnArc();
	afx_msg void OnLine();
	afx_msg void OnShowSection();
	afx_msg void OnSnapSection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

#endif // __MEASPAGE_H_
