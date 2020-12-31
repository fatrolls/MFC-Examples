// ListCtrlPrint.cpp: implementation of the CListCtrlPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrintManager.h"
#include "ListCtrlPrint.h"
#include "ListPrintSetup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListCtrlPrint::CListCtrlPrint()
{
	rcMarginMM = CRect(10,10,10,10);
	szFtPrint = szFtHead = szFtFoot = CSize(0,0);
	pDx = NULL;
	iItemXPage = 1;
	iNumCol = 0;
	pList = NULL;
	szFoot = CSize(0,0);
	pFormat = NULL;
	pColTitle = NULL;
	iTotItem = 0;

	csFtHead = "Arial";
	csFtFoot = "Times New Roman";
	csFtPrint = "Arial";
	iFtHead = 12;
	iFtFoot = 6;
	iFtPrint = 8;
}

CListCtrlPrint::~CListCtrlPrint()
{
	if (iNumCol) 
	{
		if (pDx) delete [] pDx;
		if (pFormat) delete [] pFormat;
		if (pColTitle)
		{
			for (int t = 0; t < iNumCol; t++)
				if (pColTitle[t]) delete [] pColTitle[t];
			delete [] pColTitle;
		}
	}
}

bool 
CListCtrlPrint::OnPreparePrinting(CPrintInfo* pInfo, bool bPrintPreview)
{
	pInfo->SetMinPage(1);
	if (!pList) return false;
	iTotItem = pList->GetItemCount();

	if (iTotItem <= 0) return false;

	ASSERT(pDx == NULL);
	

	CHeaderCtrl* pHeader = (CHeaderCtrl*)(pList->GetDlgItem(0));
	ASSERT(pHeader);
	iNumCol = pHeader->GetItemCount();
	if (iNumCol <= 0) return false;
	pDx = new int[iNumCol+1];
	pFormat = new int[iNumCol];
	pColTitle = new char *[iNumCol];
	ZeroMemory(pColTitle, sizeof(char *) * iNumCol);
	ZeroMemory(pDx, sizeof(int) * (iNumCol + 1));
	ZeroMemory(pFormat, sizeof(int) * iNumCol);
	char txt[128];
	for (int t = 0; t < iNumCol; t++)
	{
		HDITEM hi;
		hi.cchTextMax = 128;
		hi.pszText    = txt;

		hi.mask = HDI_TEXT|HDI_WIDTH|HDI_FORMAT;
		if (pHeader->GetItem(t, &hi))
		{
			pDx[t+1] = hi.cxy;
			pFormat[t] = hi.fmt;
			if (hi.cchTextMax > 0 && hi.pszText)
			{
				pColTitle[t] = new char[hi.cchTextMax];
				ASSERT(pColTitle[t]);
				lstrcpy(pColTitle[t], hi.pszText);
			}
		}
	}

	CListPrintSetup dlg;

	dlg.dlgSheet2.iSx = rcMarginMM.left;
	dlg.dlgSheet2.iUp = rcMarginMM.top;
	dlg.dlgSheet2.iDx = rcMarginMM.right;
	dlg.dlgSheet2.iDown = rcMarginMM.bottom;
	dlg.dlgSheet1.csFtHead = csFtHead;
	dlg.dlgSheet1.csFtFoot = csFtFoot;
	dlg.dlgSheet1.csFtPrint = csFtPrint;
	dlg.dlgSheet1.iFtHead = iFtHead;
	dlg.dlgSheet1.iFtFoot = iFtFoot;
	dlg.dlgSheet1.iFtPrint = iFtPrint;
	dlg.dlgSheet1.csHead = csPageHead;
	dlg.dlgSheet1.csFooter = csPageFooter;
	dlg.dlgSheet1.csPage = csPage;

	if (dlg.DoModal() == IDCANCEL) return false;
	rcMarginMM = CRect(dlg.dlgSheet2.iSx, dlg.dlgSheet2.iUp, dlg.dlgSheet2.iDx, dlg.dlgSheet2.iDown);

	csFtHead = dlg.dlgSheet1.csFtHead;
	csFtFoot = dlg.dlgSheet1.csFtFoot;
	csFtPrint = dlg.dlgSheet1.csFtPrint;
	iFtHead = dlg.dlgSheet1.iFtHead;
	iFtFoot = dlg.dlgSheet1.iFtFoot;
	iFtPrint = dlg.dlgSheet1.iFtPrint;

	csPageHead = dlg.dlgSheet1.csHead;
	csPageFooter = dlg.dlgSheet1.csFooter;
	csPage = dlg.dlgSheet1.csPage;

	return CPrinterJob::OnPreparePrinting(pInfo, bPrintPreview);
}

void 
CListCtrlPrint::OnBeginPrinting(CDC * pDC, CPrintInfo * pInfo)
{
	ftPrint.CreatePointFont(iFtPrint*10, csFtPrint, pDC);
	ftHead.CreatePointFont(iFtHead*10, csFtHead, pDC);
	ftFoot.CreatePointFont(iFtFoot*10, csFtFoot, pDC);;
	CString cs = "X";
	CFont * of = pDC->SelectObject(&ftPrint);
	szFtPrint = pDC->GetTextExtent(cs);
	pDC->SelectObject(&ftHead);
	szFtHead  = pDC->GetTextExtent(cs);
	pDC->SelectObject(&ftFoot);
	szFtFoot  = pDC->GetTextExtent(cs);
	pDC->SelectObject(of);

	szFtPrint.cy += 4;
	szFtHead.cy += 4;

	for (int t = 1; t <= iNumCol; t++) pDx[t] += pDx[t-1];

	CRect rcPrint(pInfo->m_rectDraw);
	SubtractMargin(pDC, rcPrint);
	double db = rcPrint.Width();
	db /= (double) pDx[iNumCol];
	for (t = 0; t <= iNumCol; t++) pDx[t] = (int)double(pDx[t] * db);
	ASSERT(pList);

	PrintListHead(pDC, rcPrint, true);
	PrintPageHead(pDC, rcPrint, 0, 0, true);

	CSize sz1 = PrintListFoot(pDC, rcPrint, true);
	CSize sz2 = PrintPageFoot(pDC, rcPrint, true);
	szFoot.cy = sz1.cy+sz2.cy + 2;

	iItemXPage = rcPrint.Height() / (szFtPrint.cy + 1) -1;
	int nPages = iTotItem / iItemXPage + 1;
	pInfo->SetMaxPage(nPages);
}

void 
CListCtrlPrint::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{

}

void 
CListCtrlPrint::SubtractMargin(CDC * pDC, CRect &rc)
{
	CSize upsz(rcMarginMM.left*100, rcMarginMM.top*100);
	CSize dwsz(rcMarginMM.right*100, rcMarginMM.bottom*100);
	pDC->HIMETRICtoDP(&upsz);
	pDC->HIMETRICtoDP(&dwsz);
	rc.top    += upsz.cy;
	rc.left   += upsz.cx;
	rc.right  -= dwsz.cx;
	rc.bottom -= dwsz.cy;
}

void 
CListCtrlPrint::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CRect rcPrint(pInfo->m_rectDraw);

	SubtractMargin(pDC, rcPrint);
	int obkm = pDC->SetBkMode(TRANSPARENT);

	PrintPageHead(pDC, rcPrint, pInfo->m_nCurPage, (int) pInfo->GetMaxPage(), false);
	PrintListHead(pDC, rcPrint, false);

	int iFirst = (pInfo->m_nCurPage - 1) * iItemXPage;
	int iLast = (pInfo->m_nCurPage) * iItemXPage;

	int y = rcPrint.top;
	int x = rcPrint.left;

	CFont * oft = pDC->SelectObject(&ftPrint);
	CRect rc1;
	CString cs;
	int iMax = iTotItem;

	for (int i = iFirst; i < iLast; i++)
	{
		bool bIs = i < iMax;

		int box = 0;
		for (int t = 0; t < iNumCol; t++)
		{
			rc1.SetRect(rcPrint.left+pDx[t], y, rcPrint.left+pDx[t+1], y+szFtPrint.cy);
			if (bIs)
			{
				cs = pList->GetItemText(i, t);
				UINT ftm = DT_LEFT;
				if (pFormat[t]&HDF_CENTER) ftm = DT_CENTER;
				else if (pFormat[t]&HDF_RIGHT) ftm = DT_RIGHT;

				pDC->DrawText(cs, rc1, ftm|DT_VCENTER);
			}
			pDC->MoveTo(rc1.left,rc1.bottom);
			pDC->LineTo(rc1.left,rc1.top);
			pDC->LineTo(rc1.right,rc1.top);
		}
		pDC->LineTo(rc1.right,rc1.bottom);
		y += szFtPrint.cy + 1;
	}

	pDC->MoveTo(rcPrint.left,y);
	pDC->LineTo(rcPrint.right,y);
	pDC->SelectObject(oft);

	
	rcPrint = pInfo->m_rectDraw;
	SubtractMargin(pDC, rcPrint);
	rcPrint.top = rcPrint.bottom - szFoot.cy;

	PrintListFoot(pDC, rcPrint, false);
	PrintPageFoot(pDC, rcPrint, false);
	
	pDC->SetBkMode(obkm);
}

CSize 
CListCtrlPrint::PrintPageHead(CDC * pDC, CRect & rcPage, const int nPage, const int iMaxPage, bool bCalc)
{
	CFont * oft = pDC->SelectObject(&ftHead);
	int y = rcPage.top;
	int x = rcPage.left;
	CSize szPg(0,0);
	if (csPage != "")
	{
		CString cs;
		cs.Format(csPage, nPage, iMaxPage);
		CRect rc1(x,y,rcPage.right,y);
		pDC->DrawText(cs, rc1, DT_WORDBREAK|DT_CALCRECT|DT_RIGHT);
		rc1.left = rcPage.right - rc1.Width();
		rc1.right = rcPage.right;
		if (!bCalc) pDC->DrawText(cs, rc1, DT_WORDBREAK|DT_RIGHT);
		szPg = rc1.Size();
	}

	if (csPageHead != "")
	{
		CRect rc1(x,y,rcPage.right - szPg.cy,y);
		pDC->DrawText(csPageHead, rc1, DT_WORDBREAK|DT_CALCRECT|DT_LEFT);
		if (!bCalc) pDC->DrawText(csPageHead, rc1, DT_WORDBREAK|DT_LEFT);
		if (rc1.Height() > szPg.cy) szPg.cy = rc1.Height();
	}

	rcPage.top += szPg.cy;
	pDC->SelectObject(oft);
	return szPg;
}

CSize
CListCtrlPrint::PrintPageFoot(CDC * pDC, CRect & rcPage, bool bCalc)
{
	CFont * oft = pDC->SelectObject(&ftFoot);
	int y = rcPage.top;
	int x = rcPage.left;
	CSize szPg(0,0);

	if (csPageFooter != "")
	{
		CRect rc1(x,y,rcPage.right - szPg.cy,y);
		pDC->DrawText(csPageFooter, rc1, DT_WORDBREAK|DT_CALCRECT|DT_LEFT);
		if (!bCalc) pDC->DrawText(csPageFooter, rc1, DT_WORDBREAK|DT_LEFT);
		szPg.cy = rc1.Height();
	}

	rcPage.bottom -= szPg.cy;
	pDC->SelectObject(oft);
	return szPg;
}

CSize
CListCtrlPrint::PrintListHead(CDC * pDC, CRect & rcPage, bool bCalc)
{
	if (!bCalc)
	{
		CFont * oft = pDC->SelectObject(&ftPrint);
		CRect rcc(rcPage.left, rcPage.top, rcPage.right, rcPage.top + szFtPrint.cy);
		pDC->MoveTo(rcc.left, rcc.top);
		pDC->LineTo(rcc.right, rcc.top);
		pDC->LineTo(rcc.right, rcc.bottom);
		pDC->LineTo(rcc.left, rcc.bottom);
		pDC->LineTo(rcc.left, rcc.top);

		int box = 0;
		CRect rc1;
		int y = rcPage.top;
		for (int t = 0; t < iNumCol; t++)
		{
			rc1.SetRect(rcPage.left+pDx[t], y, rcPage.left+pDx[t+1], y+szFtPrint.cy);
			CString cs = pColTitle[t] ? pColTitle[t] : "";
			pDC->Rectangle(rc1);

			UINT ftm = DT_LEFT;
			if (pFormat[t]&HDF_CENTER) ftm = DT_CENTER;
			else if (pFormat[t]&HDF_RIGHT) ftm = DT_RIGHT;

			pDC->DrawText(cs, rc1, ftm|DT_VCENTER);

			pDC->MoveTo(rc1.left,rc1.bottom);
			pDC->LineTo(rc1.left,rc1.top);
			pDC->LineTo(rc1.right,rc1.top);
		}
		pDC->SelectObject(oft);
	}
	rcPage.top += szFtPrint.cy;
	return CSize(0,szFtPrint.cy);
}

CSize
CListCtrlPrint::PrintListFoot(CDC * pDC, CRect & rcPage, bool bCalc)
{
	return CSize(0,0);
}
