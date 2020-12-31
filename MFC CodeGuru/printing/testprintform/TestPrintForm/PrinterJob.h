// PrinterJob.h: interface for the CPrinterJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
#define AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FormJob.h"
#include <afxcoll.h>

class CFormPrinterJob  
{
public:
	class CPageData
	{
	public:
		char cPageName[64];
		char cScriptFile[64];
		long lObjId;
		long lSubItemCount;
		long lFromSubItem, lToSubItem;
	};

	CPageData	* pPages;
	long		  lPages;

	CFormJob cForm;

	void Clear();
	virtual bool ParseCondition(const char * pTag);
	virtual void SelectSubItem(const long lPageId, const long lSubItemIndex);
	virtual void DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC);
	virtual void ParseScript(const char * cTag, CString &csValue);
	virtual void SelectPage(const long lPageId);
	bool AddPage(const char * cScriptFile, const char * cPageName, const long lPageId, const long lSubItemCount = 0);
	void OnPrepareDC(CDC * pDC, CPrintInfo * pInfo);
	CWnd * pParent;
	CString strTitle;
	bool bAlreadyAskedPageOpt;

	bool DoPreparePrinting(CPrintInfo* pInfo);
	virtual void OnFilePrint();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual bool OnPreparePrinting(CPrintInfo* pInfo);
	CFormPrinterJob();
	virtual ~CFormPrinterJob();

};

#endif // !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
