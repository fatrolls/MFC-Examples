///////////////////////////////////////////////////////////////////
// Module  : DV_VIEW.CPP
//
// Purpose : Implementation of the CDocView1View class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"     // Standard include
#include "DocView1.h"   // Application
#include "DV_Doc.h"     // Document
#include "DV_View.h"    // View

#include <colors.h>     // Assorted COLORREF colors

IMPLEMENT_DYNCREATE(CDocView1View, CView)

// Message Map for CDocView1View
BEGIN_MESSAGE_MAP(CDocView1View, CView)
   ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CDocView1View::OnLButtonDown(UINT nFlags, CPoint point)
{
   MessageBeep(MB_ICONASTERISK);
   MessageBox("A minimal document/view MFC application", "About",
              MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
// CDocView1View construction/destruction

CDocView1View::CDocView1View()
{
}

CDocView1View::~CDocView1View()
{
}

///////////////////////////////////////////////////////////////////
// CDocView1View drawing

void CDocView1View::OnDraw(CDC* pDC)
{
	//
   // Typically, you get a pointer to the document and then use it
   // to render the document's data onto the DC. We have no document
   // data to render, so we'll won't get the doc pointer, but we
   // could do so like this: 
   //
   //    CDocView2Doc* pDoc = GetDocument();
   //

   // Save the current state of the DC
   pDC->SaveDC();
   
   //
   // Draw an ellipse to fill the client area
   //
   CRect rc;
   GetClientRect(&rc);

   int nWidth  = rc.Width();
   int nHeight = rc.Height();

   // Create a gray brush and select it into the DC
   CBrush br(crGray);
   pDC->SelectObject(&br);

   // Draw the ellipse
   pDC->Ellipse(0, 0, nWidth, nHeight);

   // Restore the saved DC state
   pDC->RestoreDC(-1);
}
   
