// SinglePagePrintJobDlg.cpp: implementation of the CSinglePagePrintJobDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrintForm.h"
#include "SinglePagePrintJobDlg.h"

#include "TestPrintFormDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSinglePagePrintJobDlg::CSinglePagePrintJobDlg()
{
	pDlg = NULL;
}

CSinglePagePrintJobDlg::~CSinglePagePrintJobDlg()
{

}

void CSinglePagePrintJobDlg::DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC)
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

void CSinglePagePrintJobDlg::ParseScript(const char * cTag, CString &csValue)
{
	ASSERT(pDlg);

	if (!(lstrcmpi(cTag, "m_Field1"))) csValue = pDlg->csVal1;
	else if (!(lstrcmpi(cTag, "m_Field2"))) csValue = pDlg->csVal2;
	else if (!(lstrcmpi(cTag, "m_Field3"))) csValue = pDlg->csVal3;
	else if (!(lstrcmpi(cTag, "m_Field4"))) csValue = pDlg->csVal4;
}

void CSinglePagePrintJobDlg::SelectPage(const long lPageId)
{
}
