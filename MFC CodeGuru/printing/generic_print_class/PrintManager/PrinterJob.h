// PrinterJob.h: interface for the CPrinterJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
#define AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPrinterJob  
{
public:
	void OnPrepareDC(CDC * pDC, CPrintInfo * pInfo);
	CWnd * pParent;
	CString strTitle;
	bool bAlreadyAskedPageOpt;

	bool DoPreparePrinting(CPrintInfo* pInfo);
	virtual void OnFilePrint();
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual bool OnPreparePrinting(CPrintInfo* pInfo, bool bPrintPreview = false);
	CPrinterJob();
	virtual ~CPrinterJob();

};

#endif // !defined(AFX_PRINTERJOB_H__7EADD893_6F4C_11D1_A6CD_0000B43382FE__INCLUDED_)
