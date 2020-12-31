//********************************************
// FormCommandView.h
// The command panel view
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created :
// Modified
//********************************************


#if !defined(AFX_FORMCOMMANDVIEW_H__A4283CC1_72E6_11D1_A6C2_00A0242C0A32__INCLUDED_)
#define AFX_FORMCOMMANDVIEW_H__A4283CC1_72E6_11D1_A6C2_00A0242C0A32__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CToolDoc;

class CFormCommandView : public CFormView
{
protected:
	CFormCommandView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormCommandView)

// Form Data
public:
	//{{AFX_DATA(CFormCommandView)
	enum { IDD = IDD_FORM_COMMAND };
	CSliderCtrl	m_SliderScaleZ;
	CSliderCtrl	m_SliderScaleY;
	CSliderCtrl	m_SliderScaleX;
	CStatic	m_ControlColorLightAmbient;
	CStatic	m_ControlBackColor;
	BOOL	m_Lighting;
	BOOL	m_Smooth;
	BOOL	m_Antialias;
	int		m_Model;
	BOOL	m_VRotate;
	BOOL	m_LinkScale;
	//}}AFX_DATA

// Attributes
public:
	CToolDoc* GetDocument();
	CView *GetRenderView(); 
	BOOL UpdateScale(); 


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormCommandView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormCommandView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormCommandView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRadioModel0();
	afx_msg void OnRadioModel1();
	afx_msg void OnRadioModel2();
	afx_msg void OnCheckLighting();
	afx_msg void OnCheckSmooth();
	afx_msg void OnCheckVrotation();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckLinkScale();
	afx_msg void OnCheckAntialias();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RenderView.cpp
inline CToolDoc* CFormCommandView::GetDocument()
   { return (CToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMCOMMANDVIEW_H__A4283CC1_72E6_11D1_A6C2_00A0242C0A32__INCLUDED_)


