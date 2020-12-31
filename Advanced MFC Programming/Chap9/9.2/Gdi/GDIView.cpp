#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CALLBACK EnumFontFamProc(LPLOGFONT, LPNEWTEXTMETRIC, DWORD, LPVOID);
int CALLBACK EnumFontProc(LPLOGFONT, LPNEWTEXTMETRIC, DWORD, LPVOID);

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_nFontCount[0]=m_nFontCount[1]=m_nFontCount[2]=0;
	m_lpLf[0]=m_lpLf[1]=m_lpLf[2]=NULL;
	m_ptrFont=NULL;
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);

	CString szStr;
	CFont *ptrFtOld;
	CFont *ptrFont;
	int nYPos;
	int i;

	nYPos=10;
	szStr.Format("Number of raster fonts: %d", m_nFontCount[0]);
	pDC->TextOut(10, nYPos, szStr); 
	nYPos+=20;
	
	ptrFont=m_ptrFont;
	for(i=0; i<m_nFontCount[0]; i++)
	{
		ASSERT(ptrFont != NULL);
		ASSERT(ptrFont->GetSafeHandle() != NULL);
		ptrFtOld=pDC->SelectObject(ptrFont);
		pDC->TextOut(10, nYPos, (m_lpLf[0]+i)->lfFaceName);
		nYPos+=(m_lpLf[0]+i)->lfHeight;
		pDC->SelectObject(ptrFtOld);
		ptrFont++;
	}
	nYPos+=20;

	szStr.Format("Number of vector fonts: %d", m_nFontCount[1]);
	pDC->TextOut(10, nYPos, szStr); 
	nYPos+=20;

	for(i=0; i<m_nFontCount[1]; i++)
	{
		ASSERT(ptrFont != NULL);
		ASSERT(ptrFont->GetSafeHandle() != NULL);
		ptrFtOld=pDC->SelectObject(ptrFont);
		pDC->TextOut(10, nYPos, (m_lpLf[1]+i)->lfFaceName);
		nYPos+=(m_lpLf[1]+i)->lfHeight;
		pDC->SelectObject(ptrFtOld);
		ptrFont++;
	}
	nYPos+=20;

	szStr.Format("Number of TrueType fonts: %d", m_nFontCount[2]);
	pDC->TextOut(10, nYPos, szStr); 
	nYPos+=20;

	for(i=0; i<m_nFontCount[2]; i++)
	{
		ASSERT(ptrFont != NULL);
		ASSERT(ptrFont->GetSafeHandle() != NULL);
		ptrFtOld=pDC->SelectObject(ptrFont);
		pDC->TextOut(10, nYPos, (m_lpLf[2]+i)->lfFaceName);
		nYPos+=(m_lpLf[2]+i)->lfHeight;
		pDC->SelectObject(ptrFtOld);
		ptrFont++;
	}
}

void CGDIView::OnInitialUpdate()
{
	CClientDC dc(this);
	CScrollView::OnInitialUpdate();
	CSize sizeTotal=CSize(100, 80);
	int i;
	CFont *ptrFont;

	ASSERT(dc.GetSafeHdc());
    ::EnumFontFamilies
	(
		dc.GetSafeHdc(),
		(LPCTSTR)NULL, 
        (FONTENUMPROC)EnumFontFamProc,
		(LPARAM)m_nFontCount
	); 

	if(m_nFontCount[0] != 0)
	{
		m_lpLf[0]=(LPLOGFONT) new BYTE[sizeof(LOGFONT)*m_nFontCount[0]];
	}
	if(m_nFontCount[1] != 0)
	{
		m_lpLf[1]=(LPLOGFONT) new BYTE[sizeof(LOGFONT)*m_nFontCount[1]];
	}
	if(m_nFontCount[2] != 0)
	{
		m_lpLf[2]=(LPLOGFONT) new BYTE[sizeof(LOGFONT)*m_nFontCount[2]];
	}

	::EnumFontFamilies
	(
		dc.GetSafeHdc(),
		(LPCTSTR)NULL, 
        (FONTENUMPROC)EnumFontProc,
		(LPARAM)m_lpLf
	);

	m_ptrFont=new CFont[m_nFontCount[0]+m_nFontCount[1]+m_nFontCount[2]];
	ptrFont=m_ptrFont;
	for(i=0; i<m_nFontCount[0]; i++)
	{
		if((m_lpLf[0]+i)->lfHeight < 10)(m_lpLf[0]+i)->lfHeight=10;
		ptrFont->CreateFontIndirect(m_lpLf[0]+i);
		ptrFont++;
		sizeTotal.cy+=(m_lpLf[0]+i)->lfHeight;
	}
	for(i=0; i<m_nFontCount[1]; i++)
	{
		if((m_lpLf[1]+i)->lfHeight < 10)(m_lpLf[1]+i)->lfHeight=10;
		ptrFont->CreateFontIndirect(m_lpLf[1]+i);
		ptrFont++;
		sizeTotal.cy+=(m_lpLf[1]+i)->lfHeight;
	}
	for(i=0; i<m_nFontCount[2]; i++)
	{
		if((m_lpLf[2]+i)->lfHeight < 10)(m_lpLf[2]+i)->lfHeight=10;
		ptrFont->CreateFontIndirect(m_lpLf[2]+i);
		ptrFont++;
		sizeTotal.cy+=(m_lpLf[2]+i)->lfHeight;
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
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
	CScrollView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

int CALLBACK EnumFontFamProc
(
	LPLOGFONT lplf,
	LPNEWTEXTMETRIC lpntm,
	DWORD FontType,
	LPVOID pFontCount
)
{ 
	int *nFontCount=(int *)pFontCount; 
	if(FontType & RASTER_FONTTYPE)nFontCount[0]++; 
	else if(FontType & TRUETYPE_FONTTYPE)nFontCount[2]++; 
	else nFontCount[1]++;
	if(nFontCount[0] || nFontCount[1] || nFontCount[2])return TRUE; 
	else return FALSE; 
}

int CALLBACK EnumFontProc
(
	LPLOGFONT lplf,
	LPNEWTEXTMETRIC lpntm,
	DWORD FontType,
	LPVOID pLfArray
)
{
	static int nRaster=0;
	static int nVector=0;
	static int nTrueType=0;

	LPLOGFONT *lpLogFont=(LPLOGFONT *)pLfArray;
	if(FontType & RASTER_FONTTYPE)
	{
		memcpy((*lpLogFont+nRaster), lplf, sizeof(LOGFONT));
		nRaster++; 
	}
	else if(FontType & TRUETYPE_FONTTYPE)
	{
		memcpy((*(lpLogFont+2)+nTrueType), lplf, sizeof(LOGFONT));
		nTrueType++;
	}
	else
	{
		memcpy((*(lpLogFont+1)+nVector), lplf, sizeof(LOGFONT));
		nVector++;
	}
	return TRUE;
}

void CGDIView::OnDestroy() 
{
	CScrollView::OnDestroy();
	if(m_lpLf[0] != NULL)delete [](BYTE *) m_lpLf[0];
	if(m_lpLf[1] != NULL)delete [](BYTE *) m_lpLf[1];
	if(m_lpLf[2] != NULL)delete [](BYTE *) m_lpLf[2];
	if(m_ptrFont != NULL)delete []m_ptrFont;
}	
