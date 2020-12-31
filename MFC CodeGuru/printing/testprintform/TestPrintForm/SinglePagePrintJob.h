// SinglePagePrintJob.h: interface for the CSinglePagePrintJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLEPAGEPRINTJOB_H__F206743B_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_SINGLEPAGEPRINTJOB_H__F206743B_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrinterJob.h"

class CTestPrintFormView;

class CSinglePagePrintJob : public CFormPrinterJob  
{
public:
	CSinglePagePrintJob();
	virtual ~CSinglePagePrintJob();

	virtual void DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC);
	virtual void ParseScript(const char * cTag, CString &csValue);
	virtual void SelectPage(const long lPageId);

	CTestPrintFormView * pView;

};

#endif // !defined(AFX_SINGLEPAGEPRINTJOB_H__F206743B_101A_11D2_8432_0000B43382FE__INCLUDED_)
