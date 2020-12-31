#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ANIMATE	500

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	//{{AFX_MSG_MAP(CGDIView)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	int i;
	LPLOGPALETTE lpLogPal;

	for(i=0; i<79; i++)
	{
		m_palEntry[i].peRed=255*(78-i)/78;
		m_palEntry[i].peGreen=255*i/78;
		m_palEntry[i].peBlue=0;
		m_palEntry[i].peFlags=PC_RESERVED;
	}
	for(i=79; i<157; i++)
	{
		m_palEntry[i].peRed=0;
		m_palEntry[i].peGreen=255*(156-i)/77;
		m_palEntry[i].peBlue=255*(i-79)/77;
		m_palEntry[i].peFlags=PC_RESERVED;
	}
	for(i=157; i<236; i++)
	{
		m_palEntry[i].peRed=255*(i-157)/78;
		m_palEntry[i].peGreen=0;
		m_palEntry[i].peBlue=255*(235-i)/78;
		m_palEntry[i].peFlags=PC_RESERVED;
	}
	memcpy
	(
		(BYTE *)&m_palEntry[236],
		(BYTE *)&m_palEntry[0],
		235*sizeof(PALETTEENTRY)
	);

	lpLogPal=(LPLOGPALETTE) new BYTE[sizeof(LOGPALETTE)+235*sizeof(PALETTEENTRY)];
	lpLogPal->palVersion=0x300;
	lpLogPal->palNumEntries=236;

	for(i=0; i<236; i++)
	{
		lpLogPal->palPalEntry[i].peRed=m_palEntry[i].peRed;
		lpLogPal->palPalEntry[i].peGreen=m_palEntry[i].peGreen;
		lpLogPal->palPalEntry[i].peBlue=m_palEntry[i].peBlue;
		lpLogPal->palPalEntry[i].peFlags=m_palEntry[i].peFlags;
	}
	VERIFY(m_palAni.CreatePalette(lpLogPal));
	delete [](BYTE *)lpLogPal;

	m_nEntryID=0;
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CRect rect;
	CPalette *ptrPalOld;
	int i;

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	ptrPalOld=pDC->SelectPalette(&m_palAni, FALSE);
	pDC->RealizePalette();
	GetClientRect(rect);
	rect.right+=rect.right/2;
	rect.right/=236;
	for(i=0; i<236; i++)
	{
		pDC->FillSolidRect(rect, PALETTEINDEX(i));
		rect.OffsetRect(rect.Width(), 0);
	}
	pDC->SelectPalette(ptrPalOld, FALSE);
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

void CGDIView::OnInitialUpdate() 
{
	SetTimer(TIMER_ANIMATE, 100, NULL);
	
	CView::OnInitialUpdate();
}

void CGDIView::OnTimer(UINT nIDEvent) 
{
	CClientDC dc(this);
	CPalette *ptrPalOld;

	ptrPalOld=dc.SelectPalette(&m_palAni, FALSE);
	dc.RealizePalette();
	m_nEntryID++;
	if(m_nEntryID >= 236)m_nEntryID=0;
	m_palAni.AnimatePalette(0, 236, (LPPALETTEENTRY)&m_palEntry[m_nEntryID]);
	dc.SelectObject(ptrPalOld);
	CView::OnTimer(nIDEvent);
}

void CGDIView::OnDestroy() 
{
	KillTimer(TIMER_ANIMATE);

	CView::OnDestroy();
}
