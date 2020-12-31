// MultiPagePrintJob.h: interface for the CMultiPagePrintJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIPAGEPRINTJOB_H__F206743C_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_MULTIPAGEPRINTJOB_H__F206743C_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PrinterJob.h"

class CTestPrintFormView;

class CMultiPagePrintJob : public CFormPrinterJob  
{
public:
	CMultiPagePrintJob();
	virtual ~CMultiPagePrintJob();

	virtual void DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC);
	virtual void ParseScript(const char * cTag, CString &csValue);
	virtual void SelectPage(const long lPageId);
	virtual void SelectSubItem(const long lPageId, const long lSubItemIndex);

	CTestPrintFormView * pView;

	long lSubItem;

};

#endif // !defined(AFX_MULTIPAGEPRINTJOB_H__F206743C_101A_11D2_8432_0000B43382FE__INCLUDED_)
