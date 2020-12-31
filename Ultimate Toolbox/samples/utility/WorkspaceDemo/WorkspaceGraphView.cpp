// WorkspaceGraphView.cpp : implementation file
//

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceGraphDoc.h"
#include "WorkspaceGraphView.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.1415926

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphView

IMPLEMENT_DYNCREATE(CWorkspaceGraphView, CFormView)

CWorkspaceGraphView::CWorkspaceGraphView()
	: 
	CFormView(CWorkspaceGraphView::IDD),
	m_nPolyRadius(50),			// Use some valid initial values (will be changed)
	m_nPolyOffsetX(520),
	m_nPolyOffsetY(90),
	m_nSides(3),
	m_color(0)
	{
	//{{AFX_DATA_INIT(CWorkspaceGraphView)
	//}}AFX_DATA_INIT
	}

CWorkspaceGraphView::~CWorkspaceGraphView()
	{
	}

void CWorkspaceGraphView::DoDataExchange(CDataExchange* pDX)
	{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaceGraphView)
	//}}AFX_DATA_MAP
	}


BEGIN_MESSAGE_MAP(CWorkspaceGraphView, CFormView)
	//{{AFX_MSG_MAP(CWorkspaceGraphView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphView diagnostics

#ifdef _DEBUG
void CWorkspaceGraphView::AssertValid() const
	{
	CFormView::AssertValid();
	}

void CWorkspaceGraphView::Dump(CDumpContext& dc) const
	{
	CFormView::Dump(dc);
	}

CWorkspaceGraphDoc* CWorkspaceGraphView::GetDocument() // non-debug version is inline
	{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkspaceGraphDoc)));
	return (CWorkspaceGraphDoc*)m_pDocument;
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphView message handlers

void CWorkspaceGraphView::OnInitialUpdate() 
	{
	CFormView::OnInitialUpdate();
	
	// Calculate figure position relative to the group control
	CWnd* pGroupCtrl;
	CRect r;
	pGroupCtrl = GetDlgItem(IDC_GROUP);
	// ... Group control must exist
	ASSERT(pGroupCtrl != NULL);
	// Calculate the window rect of the group control relative to its parent (this dialog)
	pGroupCtrl->GetWindowRect(r);
	ScreenToClient(r);

	// Position the polygon at the right part of the group control
	if (r.Height() < r.Width())
		m_nPolyRadius = UINT(r.Height() / 3);
	else
		m_nPolyRadius = UINT(r.Width() / 3);
	m_nPolyOffsetX = r.left + r.Width() / 2;
	m_nPolyOffsetY = r.top + r.Height() / 2;

	// Fit frame around view
	ResizeParentToFit(FALSE);
	}

void CWorkspaceGraphView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pHint);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pSender);
	m_color = GetDocument()->GetColor();
	m_nSides = GetDocument()->GetSides();
	Invalidate();
	}


void CWorkspaceGraphView::OnPaint() 
	{
	if (IsIconic())
		{
		CFormView::OnPaint();
		}
	else
		{
		// Draw the polygon using the current value of the data members
		if (3 <= m_nSides && m_nSides <= 20)
			{
			CPaintDC dc(this);
			// Calculate the corner positions
			POINT* pPoint = new POINT[m_nSides];
			for (UINT nSide = 0; nSide < m_nSides; nSide++)
				{
				pPoint[nSide].x = long(cos(2 * PI * nSide / m_nSides) * m_nPolyRadius) + m_nPolyOffsetX;
				pPoint[nSide].y = long(sin(2 * PI * nSide / m_nSides) * m_nPolyRadius) + m_nPolyOffsetY;
				}

			// Use the correct color
			CBrush brush(m_color);
			CBrush* pOldBrush;
			pOldBrush = dc.SelectObject(&brush);
			dc.Polygon(pPoint, m_nSides);
			dc.SelectObject(pOldBrush);

			// Clean up
			delete[] pPoint;
			}
		}
	}
