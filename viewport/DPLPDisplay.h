#if !defined(AFX_DPLPDISPLAY_H__13ECFB11_F04F_4220_AA0E_EAFBEAB00442__INCLUDED_)
#define AFX_DPLPDISPLAY_H__13ECFB11_F04F_4220_AA0E_EAFBEAB00442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DPLPDisplay.h : header file
//
#include "msg.h"

/////////////////////////////////////////////////////////////////////////////
// CDPLPDisplay window

class CDPLPDisplay : public CStatic
{
// Construction
public:
        CDPLPDisplay();

// Attributes
public:

// Operations
public:
   void SetViewportOrg(int x, int y);
   void SetViewportExt(int x, int y);
   void SetWindowOrg(int x, int y);
   void SetWindowExt(int x, int y);
   void SetMapMode(UINT mode);
   void SetDeviceGrid(int delta);
   void SetLogicalGrid(int delta);
   void PrepareDC(CDC & dc);
   void SetPositive(int n);
   void SetCircles(BOOL mode);
   void SetGridLines(BOOL mode);
   void SetLineStyle(UINT style);
   void DPtoLP(CPoint & pt);
   void DPtoLP(CSize & pt);
   void DPtoLP(CRect & r);
   void LPtoDP(CPoint & pt);
   void LPtoDP(CRect & r);
   CSize GetSign();
   
// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CDPLPDisplay)
        protected:
        virtual void PreSubclassWindow();
        //}}AFX_VIRTUAL

// Implementation
public:
        virtual ~CDPLPDisplay();

        // Generated message map functions
protected:
   CSize ViewportExt;
   CSize WindowExt;
   CPoint ViewportOrg;
   CPoint WindowOrg;
   CPoint anchor;
   BOOL circles;
   BOOL gridlines;
   UINT GridLineStyle;
   int dx;
   int dy;
   int Ldx;
   int Ldy;
   int positive;
   
   UINT MapMode;
   
        //{{AFX_MSG(CDPLPDisplay)
        afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnPaint();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
        afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};

/****************************************************************************
*                                UWM_MOUSEMOVE
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) the mouse coordinates in client coordinates
*       LPARAM: (WPARAM)(CPoint *) the mouse coordinates in logical coordinates
* Result: LRESULT
*       ignored
* Effect: 
*       Notifies the parent of the mouse coordinates
****************************************************************************/

#define UWM_MOUSEMOVE_MSG _T("UWM_MOUSEMOVE-13ECFB11_F04F_4220_AA0E_EAFBEAB00442")

/****************************************************************************
*                                UWM_MOUSEDRAG
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) current position (client coordinates)
*       LPARAM: (LPARAM)(CPoint *) current position (logical coordinates)
* Result: LRESULT
*       ignored
* Effect: 
*       Notifies the parent of the mouse motion from the anchor point
****************************************************************************/

#define UWM_MOUSEDRAG_MSG _T("UWM_MOUSEDRAG-13ECFB11_F04F_4220_AA0E_EAFBEAB00442")

/****************************************************************************
*                                UWM_MOUSEDRAGSTART
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) initial anchor point (client coordinates)
*       LPARAM: (WPARAM)(CPoint *) initial anchor point (logical coordinates)
* Result: LRESULT
*       ignored
* Effect: 
*       Notifies the parent of the mouse motion from the anchor point
****************************************************************************/

#define UWM_MOUSEDRAGSTART_MSG _T("UWM_MOUSEDRAGSTART-13ECFB11_F04F_4220_AA0E_EAFBEAB00442")


/****************************************************************************
*                                UWM_MOUSEDRAGEND
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) final point (client coordinates)
*       LPARAM: (WPARAM)(CPoint *) final point (logical coordinates)
* Result: LRESULT
*       ignored
* Effect: 
*       Notifies the parent of the mouse motion from the anchor point
****************************************************************************/

#define UWM_MOUSEDRAGEND_MSG _T("UWM_MOUSEDRAGEND-13ECFB11_F04F_4220_AA0E_EAFBEAB00442")

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DPLPDISPLAY_H__13ECFB11_F04F_4220_AA0E_EAFBEAB00442__INCLUDED_)
