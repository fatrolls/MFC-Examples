// scribdoc.cpp : implementation of the CScribDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "scribble.h"
#include "scribdoc.h"
#include "pendlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribDoc

IMPLEMENT_DYNCREATE(CScribDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribDoc, CDocument)
	//{{AFX_MSG_MAP(CScribDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_COMMAND(ID_PEN_THICK_OR_THIN, OnPenThickOrThin)
	ON_UPDATE_COMMAND_UI(ID_PEN_THICK_OR_THIN, OnUpdatePenThickOrThin)
	ON_COMMAND(ID_PEN_WIDTHS, OnPenWidths)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribDoc construction/destruction

CScribDoc::CScribDoc()
{
	// TODO: add one-time construction code here
}

CScribDoc::~CScribDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
void CScribDoc::DeleteContents()
{
	while (!m_strokeList.IsEmpty())
	{
		delete m_strokeList.RemoveHead();
	}
}

void CScribDoc::InitDocument()
{
	m_bThickPen = FALSE;
	m_nThinWidth = 2;   // default thin pen is 2 pixels wide
	m_nThickWidth = 5;  // default thick pen is 5 pixels wide
	ReplacePen();       // initialze pen according to current width

	// default document size is 6 x 4 inches, measures in MM_LOENGLISH
	// (0.01 inches). Origin is bottom left.
	m_rectDoc = CRect(0,400,600,0);

}

BOOL CScribDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	InitDocument();
	return TRUE;
}

BOOL CScribDoc::OnOpenDocument(LPCTSTR pszPathName)
{
	if (!CDocument::OnOpenDocument(pszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CScribDoc serialization

void CScribDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectDoc;
	}
	else
	{
		ar >> m_rectDoc;
	}
	m_strokeList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScribDoc diagnostics

#ifdef _DEBUG
void CScribDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribDoc commands

void CScribDoc::OnEditClearAll()
{
	DeleteContents();
	SetModifiedFlag();  // Mark the document as having been modified, for
						// purposes of confirming File Close.
	UpdateAllViews(NULL);
}

void CScribDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
	// Enable the command user interface object (menu item or tool bar
	// button) if the document is non-empty, i.e., has at least one stroke.
	pCmdUI->Enable(!m_strokeList.IsEmpty());
}


/////////////////////////////////////////////////////////////////////////////
void CScribDoc::OnPenThickOrThin()
{
	// Toggle the state of the pen between thin or thick.
	m_bThickPen = !m_bThickPen;

	// Change the current pen to reflect the new user-specified width.
	ReplacePen();
}


/////////////////////////////////////////////////////////////////////////////
void CScribDoc::OnUpdatePenThickOrThin(CCmdUI* pCmdUI)
{
	// Add check mark to Draw Thick Line menu item, if the current
	// pen width is "thick".
	pCmdUI->SetCheck(m_bThickPen);
}


/////////////////////////////////////////////////////////////////////////////
void CScribDoc::OnPenWidths()
{
	CPenWidthsDlg dlg;
	// Initialize dialog data
	dlg.m_nThinWidth = m_nThinWidth;
	dlg.m_nThickWidth = m_nThickWidth;

	// Invoke the dialog box
	if (dlg.DoModal() == IDOK)
	{
		// retrieve the dialog data
		m_nThinWidth = dlg.m_nThinWidth;
		m_nThickWidth = dlg.m_nThickWidth;

		// Update the pen that is used by views when drawing new strokes,
		// to reflect the new pen width definitions for "thick" and "thin".
		ReplacePen();
	}
}

/////////////////////////////////////////////////////////////////////////////
void CScribDoc::ReplacePen()
{
	m_nPenWidth = m_bThickPen? m_nThickWidth : m_nThinWidth;

	// Change the current pen to reflect the new user-specified width.
	m_penCur.DeleteObject();
	m_penCur.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)); // solid black
}

/////////////////////////////////////////////////////////////////////////////
CStroke* CScribDoc::NewStroke()
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail(pStrokeItem);
	SetModifiedFlag();  // Mark the document as having been modified, for
						// purposes of confirming File Close.
	return pStrokeItem;
}

/////////////////////////////////////////////////////////////////////////////
POSITION CScribDoc::GetFirstStrokePos()
{
	return m_strokeList.GetHeadPosition();
}


/////////////////////////////////////////////////////////////////////////////
CStroke* CScribDoc::GetNextStroke(POSITION& pos)
{
	return (CStroke*)m_strokeList.GetNext(pos);
}


/////////////////////////////////////////////////////////////////////////////
// CStroke

// Each time we change what gets serialized, we change the
// schema number.
IMPLEMENT_SERIAL(CStroke, CObject, 2)

/////////////////////////////////////////////////////////////////////////////
CStroke::CStroke()
{
	// this empty constructor should be used by serialization only
}

/////////////////////////////////////////////////////////////////////////////
CStroke::CStroke(UINT nPenWidth)
{
	m_nPenWidth = nPenWidth;
	m_rectBounding.SetRectEmpty();
}

/////////////////////////////////////////////////////////////////////////////
void CStroke::AddPoint(CPoint pt)
{
	m_pointArray.Add(MAKELONG(pt.x, pt.y));
}

/////////////////////////////////////////////////////////////////////////////
BOOL CStroke::DrawStroke(CDC* pDC)
{
	CPen penStroke;
	if (!penStroke.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0)))
		return FALSE;
	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(GetPoint(0));
	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		pDC->LineTo(GetPoint(i));
	}

	pDC->SelectObject(pOldPen);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void CStroke::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_rectBounding;
		ar << (WORD)m_nPenWidth;
		m_pointArray.Serialize(ar);
	}
	else
	{
		ar >> m_rectBounding;
		WORD w;
		ar >> w;
		m_nPenWidth = w;
		m_pointArray.Serialize(ar);
	}
}

/////////////////////////////////////////////////////////////////////////////
void CStroke::FinishStroke()
{
	// Calculate the bounding rectangle.  It's needed for smart
	// repainting.

	if (m_pointArray.GetSize()==0)
	{
		m_rectBounding.SetRectEmpty();
		return;
	}
	CPoint pt = GetPoint(0);
	m_rectBounding = CRect(pt.x, pt.y, pt.x, pt.y);

	for (int i=1; i < m_pointArray.GetSize(); i++)
	{
		// If the point lies outside of the accumulated bounding
		// rectangle, then inflate the bounding rect to include it.
		pt = GetPoint(i);
		m_rectBounding.left     = __min(m_rectBounding.left, pt.x);
		m_rectBounding.right    = __max(m_rectBounding.right, pt.x);
		m_rectBounding.top      = __max(m_rectBounding.top, pt.y);
		m_rectBounding.bottom   = __min(m_rectBounding.bottom, pt.y);
	}

	// Add the pen width to the bounding rectangle.  This is necessary
	// to account for the width of the stroke when invalidating
	// the screen.
	m_rectBounding.InflateRect(CSize(m_nPenWidth, -(int)m_nPenWidth));
	return;
}
