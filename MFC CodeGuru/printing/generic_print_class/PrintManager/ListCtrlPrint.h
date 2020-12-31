// ListCtrlPrint.h: interface for the CListCtrlPrint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTCTRLPRINT_H__E1B3DDE2_9D53_11D1_8BAC_0000B43382FE__INCLUDED_)
#define AFX_LISTCTRLPRINT_H__E1B3DDE2_9D53_11D1_8BAC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrinterJob.h"

class CListCtrlPrint : public CPrinterJob  
{
public:
	CListCtrlPrint();
	virtual ~CListCtrlPrint();

	
	CRect rcMarginMM;	// contain the margins in millimeters
	CFont	ftPrint, ftHead, ftFoot;	// fonts used for printing
	CSize	szFtPrint, szFtHead, szFtFoot;	// sizes of fonts (in device unit)
	int	*	pDx, * pFormat;	// datas about column size and format (center, right ..)
	char ** pColTitle;	// columns titles
	int		iItemXPage, iNumCol, iTotItem;	// number of item in page, of columns and of tot number of items in list control
	CListCtrl * pList;	// pointer of the list ctrl
	CString	csPageHead;	// text of header
	CString csPageFooter;	// text of footer
	CString csPage;	// format of page number / tot pages (ex. page %d of %d)

	CString	csFtHead, csFtFoot, csFtPrint;	// fonts type names
	int     iFtHead, iFtFoot, iFtPrint;	// fonts sizes

	CSize szFoot;	// internal use

	// this subtracts the margins from the page size
	void SubtractMargin(CDC * pDC, CRect &rc);

	// virtual overridden from base class; same meaning of CView's one
	void OnBeginPrinting(CDC * pDC, CPrintInfo * pInfo);
	void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	bool OnPreparePrinting(CPrintInfo* pInfo, bool bPrintPreview = false);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	// function self explicative; the items will be printed in the OnPrint function
	// if bCalc is true, the function is called to compute the space for items and so
	// no printing is needed, but only to return the size used and to subtract from the
	// rcpage the space used
	CSize PrintListFoot(CDC * pDC, CRect & rcPage, bool bCalc);
	CSize PrintListHead(CDC * pDC, CRect & rcPage, bool bCalc);
	CSize PrintPageFoot(CDC * pDC, CRect & rcPage, bool bCalc);
	CSize PrintPageHead(CDC * pDC, CRect & rcPage, const int nPage, const int iMaxPage, bool bCalc);

};

#endif // !defined(AFX_LISTCTRLPRINT_H__E1B3DDE2_9D53_11D1_8BAC_0000B43382FE__INCLUDED_)
