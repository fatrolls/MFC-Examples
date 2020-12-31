// SinglePagePrintJob.cpp: implementation of the CSinglePagePrintJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrintForm.h"
#include "SinglePagePrintJob.h"

#include "TestPrintFormView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSinglePagePrintJob::CSinglePagePrintJob()
{
	pView = NULL;
}

CSinglePagePrintJob::~CSinglePagePrintJob()
{

}

void CSinglePagePrintJob::DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC)
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CDC memDc;
	memDc.CreateCompatibleDC(pDC);
	CBitmap * obmp = memDc.SelectObject(&bmp);
	BITMAP bm;
	bmp.GetBitmap(&bm);

	pDC->StretchBlt(rcBitmap.left, rcBitmap.top, rcBitmap.Width(), rcBitmap.Height(), &memDc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	memDc.SelectObject(obmp);
}

void CSinglePagePrintJob::ParseScript(const char * cTag, CString &csValue)
{
	ASSERT(pView);

	if (!(lstrcmpi(cTag, "m_Field1"))) csValue = pView->csVal1;
	else if (!(lstrcmpi(cTag, "m_Field2"))) csValue = pView->csVal2;
	else if (!(lstrcmpi(cTag, "m_Field3"))) csValue = pView->csVal3;
	else if (!(lstrcmpi(cTag, "m_Field4"))) csValue = pView->csVal4;
}

void CSinglePagePrintJob::SelectPage(const long lPageId)
{
}
