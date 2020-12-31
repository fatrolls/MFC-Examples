// SinglePagePrintJobDlg.h: interface for the CSinglePagePrintJobDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLEPAGEPRINTJOBDLG_H__B5ED7C13_1118_11D2_8434_0000B43382FE__INCLUDED_)
#define AFX_SINGLEPAGEPRINTJOBDLG_H__B5ED7C13_1118_11D2_8434_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrinterJob.h"

class CTestPrintFormDlg;

class CSinglePagePrintJobDlg : public CFormPrinterJob  
{
public:
	CSinglePagePrintJobDlg();
	virtual ~CSinglePagePrintJobDlg();

	virtual void DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC);
	virtual void ParseScript(const char * cTag, CString &csValue);
	virtual void SelectPage(const long lPageId);

	CTestPrintFormDlg *		pDlg;
};

#endif // !defined(AFX_SINGLEPAGEPRINTJOBDLG_H__B5ED7C13_1118_11D2_8434_0000B43382FE__INCLUDED_)
