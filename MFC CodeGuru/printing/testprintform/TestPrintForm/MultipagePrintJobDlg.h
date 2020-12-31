// MultipagePrintJobDlg.h: interface for the CMultipagePrintJobDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIPAGEPRINTJOBDLG_H__B5ED7C14_1118_11D2_8434_0000B43382FE__INCLUDED_)
#define AFX_MULTIPAGEPRINTJOBDLG_H__B5ED7C14_1118_11D2_8434_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrinterJob.h"

class CTestPrintFormDlg;

class CMultiPagePrintJobDlg : public CFormPrinterJob  
{
public:
	CMultiPagePrintJobDlg();
	virtual ~CMultiPagePrintJobDlg();

	virtual void DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC);
	virtual void ParseScript(const char * cTag, CString &csValue);
	virtual void SelectPage(const long lPageId);
	virtual void SelectSubItem(const long lPageId, const long lSubItemIndex);

	CTestPrintFormDlg *		pDlg;
	long lSubItem;
};

#endif // !defined(AFX_MULTIPAGEPRINTJOBDLG_H__B5ED7C14_1118_11D2_8434_0000B43382FE__INCLUDED_)
