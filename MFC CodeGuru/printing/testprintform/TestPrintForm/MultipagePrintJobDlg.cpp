// MultipagePrintJobDlg.cpp: implementation of the CMultipagePrintJobDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrintForm.h"
#include "MultipagePrintJobDlg.h"

#include "TestPrintFormDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiPagePrintJobDlg::CMultiPagePrintJobDlg()
{
	pDlg = NULL;
	lSubItem = 0;
}

CMultiPagePrintJobDlg::~CMultiPagePrintJobDlg()
{

}

void CMultiPagePrintJobDlg::DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC)
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

void CMultiPagePrintJobDlg::ParseScript(const char * cTag, CString &csValue)
{
	ASSERT(pDlg);

	if (!(lstrcmpi(cTag, "m_Field1"))) csValue = pDlg->csVal1;
	else if (!(lstrcmpi(cTag, "m_Field2"))) csValue = pDlg->csVal2;
	else if (!(lstrcmpi(cTag, "m_Field3"))) csValue = pDlg->csVal3;
	else if (!(lstrcmpi(cTag, "m_Field4"))) csValue = pDlg->csVal4;
	else if (!(lstrcmpi(cTag, "m_subfield1"))) csValue = pDlg->wndList.GetItemText(lSubItem, 0);
	else if (!(lstrcmpi(cTag, "m_subfield2"))) csValue = pDlg->wndList.GetItemText(lSubItem, 1);
}

void CMultiPagePrintJobDlg::SelectPage(const long lPageId)
{
}

void CMultiPagePrintJobDlg::SelectSubItem(const long lPageId, const long lSubItemIndex)
{
	lSubItem = lSubItemIndex;
}

