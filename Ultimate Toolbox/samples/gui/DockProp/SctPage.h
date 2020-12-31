// SctPage.h : header file
//

#ifndef __SCTPAGE_H_
#define __SCTPAGE_H_

#include "OXDckPPg.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// SSectionParms struct

struct SSectionParms 
{
	long	lXMin;
	long	lYMin;
	long	lZMin;

	long	lXMax;
	long	lYMax;
	long	lZMax;

	long	lXPosValue;
	long	lYPosValue;
	long	lZPosValue;

	enum EHint
	{
		hAll,
		hPosition,
		hSection
	};

	enum ESection
	{
		sX,
		sY,
		sZ
	} eSection;

	SSectionParms() :
		eSection(sX),
		lXMin(0),
		lYMin(0),
		lZMin(0),
		lXMax(0),
		lYMax(0),
		lZMax(0),
		lXPosValue(0),
		lYPosValue(0),
		lZPosValue(0)
		{}
	void operator=(const SSectionParms& parms) {
		eSection = parms.eSection;
		lXMin = parms.lXMin;
		lYMin = parms.lYMin;
		lZMin = parms.lZMin;
		lXMax = parms.lXMax;
		lYMax = parms.lYMax;
		lZMax = parms.lZMax;
		lXPosValue = parms.lXPosValue;
		lYPosValue = parms.lYPosValue;
		lZPosValue = parms.lZPosValue;}
};

/////////////////////////////////////////////////////////////////////////////
// CSlicePage dialog

class CSectionPage : public COXDockPropertyPage
{
// Data Members
public:

protected:
	SSectionParms	m_parms;

	//{{AFX_DATA(CSectionPage)
	enum { IDD = IDD_SECTION };
	CSliderCtrl	m_slider;
	float	m_fPosValue;
	int		m_nSection;
	//}}AFX_DATA


private:

// Member Functions
public:
	CSectionPage();
	virtual BOOL OnSetActive( );
	virtual BOOL OnKillActive( );

	void SetParms(const SSectionParms& parms, SSectionParms::EHint eHint = SSectionParms::hAll);
	void GetParms(SSectionParms& parms, SSectionParms::EHint eHint = SSectionParms::hAll);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSectionPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CSectionPage)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChangeCutvalue();
	virtual BOOL OnInitDialog();
	afx_msg void OnSliceApply();
	afx_msg void OnSectionSelect();
	afx_msg void OnTimer( UINT );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

};

#endif // __SLCPAGE_H_
