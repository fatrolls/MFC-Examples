///////////////////////////////////////////////////////////////////
// Header  : DV_VIEW.H
//
// Purpose : Implementation of the CDocView2View class.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"     // Standard include
#include "DocView2.h"   // Application
#include "DV_Doc.h"     // Document
#include "DV_View.h"    // View

#include <colors.h>     // Assorted COLORREF colors

IMPLEMENT_DYNCREATE(CDocView2View, CView)

// Message Map for CDocView2View
BEGIN_MESSAGE_MAP(CDocView2View, CView)

	// Required for printing
   ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)

   // Required for print preview
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

   ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CDocView2View::OnLButtonDown(UINT nFlags, CPoint point)
{
   CView::OnFilePrintPreview();
}

///////////////////////////////////////////////////////////////////
// CDocView2View construction/destruction

CDocView2View::CDocView2View()
{
}

CDocView2View::~CDocView2View()
{
}

///////////////////////////////////////////////////////////////////
// CDocView2View drawing

void CDocView2View::OnDraw(CDC* pDC)
{
	//
   // Typically, you get a pointer to the document and then use it
   // to render the document's data onto the DC. We have no document
   // data to render, so we'll won't get the doc pointer, but we
   // could do so like this: 
   //    CDocView2Doc* pDoc = GetDocument();
   //

   // Save the current state of the DC
   pDC->SaveDC();
   
   // Set mapping mode to TWIPS 
   pDC->SetMapMode(MM_TWIPS);

   //
   // Use the logical coordinates of the mapping mode to
   // draw an ellipse, 6 x 4 inches (1 inch = 1440 twips)
   //
   int nWidth  = 6 * 1440;
   int nHeight = 4 * 1440;

   // Create a gray brush and select it into the DC
   CBrush br(crGray);
   pDC->SelectObject(&br);

   // Draw the ellipse, y-axis reversed for MM_TWIPS
   pDC->Ellipse(0, 0, nWidth, -nHeight);

   //
   // Create a font and draw some text in the ellipse
   //
   CFont fnt;

   // Text is 1/3 inch high, bold italic, Arial
   fnt.CreateFont(1440 / 3, 0, 0, 0, FW_BOLD, TRUE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

   // Select it into the DC
   pDC->SelectObject(&fnt);
   
   // Get the bounds of the text
   CString sText = "Text output using the Arial font...";
   CSize   size;

   ::GetTextExtentPoint32( 
      pDC->m_hDC,          // handle of device context 
      sText,               // address of text string 
      sText.GetLength(),   // number of characters in string 
      &size);              // address of size structure  
   
   // Display text in blue using the new font
   pDC->SetBkMode(TRANSPARENT);   
   pDC->SetTextColor(crBlue);
   pDC->TextOut( 3 * 1440 - (size.cx / 2), // x
                -2 * 1440 + (size.cy / 2), // y
                sText);                    // text

   // Restore the saved DC state
   pDC->RestoreDC(-1);    
}
   
///////////////////////////////////////////////////////////////////
// CDocView2View::OnPreparePrinting - Required!!

BOOL CDocView2View::OnPreparePrinting(CPrintInfo* pInfo)
{
   // default preparation
	return DoPreparePrinting(pInfo);
}

