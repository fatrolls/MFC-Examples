// PrinterJob.cpp: implementation of the CPrinterJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PrintManager.h"
#include "PrinterJob.h"
#include "PrintStatus.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool bGfxUserAbort;

BOOL CALLBACK EXPORT _GfxAbortProc( HDC, int )
{
	MSG msg;
	while (!bGfxUserAbort && ::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage()) return FALSE;
	}
	return !bGfxUserAbort;
}

CPrinterJob::CPrinterJob()
{
	pParent = NULL;
	strTitle = "senza nome";
	bAlreadyAskedPageOpt = false;
}

CPrinterJob::~CPrinterJob()
{

}

bool CPrinterJob::OnPreparePrinting(CPrintInfo * pInfo, bool bPrintPreview)
{
	if (bPrintPreview) return true;
	return DoPreparePrinting(pInfo);
}

void CPrinterJob::OnBeginPrinting(CDC * pDC, CPrintInfo * pInfo)
{

}

void CPrinterJob::OnEndPrinting(CDC * pDC, CPrintInfo * pInfo)
{

}

void CPrinterJob::OnPrint(CDC * pDC, CPrintInfo * pInfo)
{

}

bool CPrinterJob::DoPreparePrinting(CPrintInfo * pInfo)
{
	ASSERT(pInfo != NULL);
	ASSERT(pInfo->m_pPD != NULL);
	if (pInfo->m_pPD->m_pd.nMinPage > pInfo->m_pPD->m_pd.nMaxPage)
		pInfo->m_pPD->m_pd.nMaxPage = pInfo->m_pPD->m_pd.nMinPage;
	pInfo->m_pPD->m_pd.nFromPage = (WORD)pInfo->GetMinPage();
	pInfo->m_pPD->m_pd.nToPage = (WORD)pInfo->GetMaxPage();
	if (AfxGetApp()->DoPrintDialog(pInfo->m_pPD) != IDOK) return FALSE;
	ASSERT(pInfo->m_pPD != NULL);
	ASSERT(pInfo->m_pPD->m_pd.hDC != NULL);
	if (pInfo->m_pPD->m_pd.hDC == NULL) return FALSE;
	pInfo->m_nNumPreviewPages = AfxGetApp()->m_nNumPreviewPages;
	VERIFY(pInfo->m_strPageDesc.LoadString(AFX_IDS_PREVIEWPAGEDESC));
	return TRUE;
}

void CPrinterJob::OnFilePrint()
{
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL);    // must be set

	if (OnPreparePrinting(&printInfo))
	{
		// hDC must be set (did you remember to call DoPreparePrinting?)
		ASSERT(printInfo.m_pPD->m_pd.hDC != NULL);

		// gather file to print to if print-to-file selected
		CString strOutput;
		if (printInfo.m_pPD->m_pd.Flags & PD_PRINTTOFILE)
		{
			// construct CFileDialog for browsing
			CString strDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULTEXT));
			CString strPrintDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULT));
			CString strFilter(MAKEINTRESOURCE(AFX_IDS_PRINTFILTER));
			CString strCaption(MAKEINTRESOURCE(AFX_IDS_PRINTCAPTION));
			CFileDialog dlg(FALSE, strDef, strPrintDef,	OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
			dlg.m_ofn.lpstrTitle = strCaption;
			if (dlg.DoModal() != IDOK) return;
			// set output device to resulting path name
			strOutput = dlg.GetPathName();
		}
		DOCINFO docInfo;
		memset(&docInfo, 0, sizeof(DOCINFO));
		docInfo.cbSize = sizeof(DOCINFO);
		docInfo.lpszDocName = strTitle;
		CString strPortName;
		int nFormatID;
		if (strOutput.IsEmpty())
		{
			docInfo.lpszOutput = NULL;
			strPortName = printInfo.m_pPD->GetPortName();
			nFormatID = AFX_IDS_PRINTONPORT;
		}
		else
		{
			docInfo.lpszOutput = strOutput;
			nFormatID = AFX_IDS_PRINTTOFILE;
		}

		// setup the printing DC
		CDC dcPrint;
		dcPrint.Attach(printInfo.m_pPD->m_pd.hDC);  // attach printer dc
		dcPrint.m_bPrinting = TRUE;
		printInfo.m_rectDraw.SetRect(0, 0, dcPrint.GetDeviceCaps(HORZRES), dcPrint.GetDeviceCaps(VERTRES));
		dcPrint.DPtoLP(&printInfo.m_rectDraw);
		
		OnBeginPrinting(&dcPrint, &printInfo);
		dcPrint.SetAbortProc(_GfxAbortProc);

		// disable main window while printing & init printing status dialog
		CString csFormat, cs, strTemp;
		AfxGetMainWnd()->EnableWindow(FALSE);
		CPrintStatus dlgPrintStatus(pParent);
		cs.Format("Stampa di %s in corso ..", strTitle);
		dlgPrintStatus.SetWindowText(cs);
		
		dlgPrintStatus.GetDlgItemText(IDC_TEXT1, csFormat);
		AfxFormatString1(strTemp, nFormatID, strPortName);
		cs.Format(csFormat, strTitle, printInfo.m_pPD->GetDeviceName(), strTemp);
		dlgPrintStatus.SetDlgItemText(IDC_TEXT1, cs);



		dlgPrintStatus.ShowWindow(SW_SHOW);
		dlgPrintStatus.UpdateWindow();

		// start document printing process
		if (dcPrint.StartDoc(&docInfo) == SP_ERROR)
		{
			// enable main window before proceeding
			AfxGetMainWnd()->EnableWindow(TRUE);

			// cleanup and show error message
			OnEndPrinting(&dcPrint, &printInfo);
			dlgPrintStatus.DestroyWindow();
			dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
			AfxMessageBox(AFX_IDP_FAILED_TO_START_PRINT);
			return;
		}

		// Guarantee values are in the valid range
		UINT nEndPage = printInfo.GetToPage();
		UINT nStartPage = printInfo.GetFromPage();

		if (nEndPage < printInfo.GetMinPage()) nEndPage = printInfo.GetMinPage();
		if (nEndPage > printInfo.GetMaxPage()) nEndPage = printInfo.GetMaxPage();
		if (nStartPage < printInfo.GetMinPage()) nStartPage = printInfo.GetMinPage();
		if (nStartPage > printInfo.GetMaxPage()) nStartPage = printInfo.GetMaxPage();
		int nStep = (nEndPage >= nStartPage) ? 1 : -1;
		nEndPage = (nEndPage == 0xffff) ? 0xffff : nEndPage + nStep;
		int iPageTot = abs(abs(nEndPage) - abs(nStartPage)), iPrintedPages = 0;
		CString csPageFormat;
		dlgPrintStatus.GetDlgItemText(IDC_PAGES, csPageFormat);

		// begin page printing loop
		DWORD dwStart = GetTickCount(), dTickPerPage = 0;

		dlgPrintStatus.wndProg.SetRange(0, iPageTot);
		dlgPrintStatus.wndProg.SetPos(0);

		bool bRectSet = false;
		BOOL bError = FALSE;
		for (printInfo.m_nCurPage = nStartPage; printInfo.m_nCurPage != nEndPage; printInfo.m_nCurPage += nStep)
		{
			TCHAR szBuf[80];

			iPrintedPages ++;
			dlgPrintStatus.wndProg.SetPos(iPrintedPages);
			dlgPrintStatus.wndProg.UpdateWindow();

			wsprintf(szBuf, "%d %%", iPrintedPages*100/iPageTot);
			dlgPrintStatus.SetDlgItemText(IDC_PC, szBuf);

			OnPrepareDC(&dcPrint, &printInfo);
			
			// check for end of print
			if (!printInfo.m_bContinuePrinting) break;
			// write current page

			DWORD tck = dTickPerPage * (iPageTot - iPrintedPages + 1) / 1000;
			if (tck > 60)
			{
				tck != 60;
				DWORD tckS = tck%60;
				tck /= 60;
				strTemp.Format("%d minuti, %d secondi", tck, tckS);
			}
			else
			{
				if (iPageTot > 1)
				{
					if (tck > 0) strTemp.Format("%d secondi", tck);
					else strTemp = "??";
				}
			}

			wsprintf(szBuf, csPageFormat, iPrintedPages, iPageTot, strTemp);
			dlgPrintStatus.SetDlgItemText(IDC_PAGES, szBuf);

			printInfo.m_rectDraw.SetRect(0, 0, dcPrint.GetDeviceCaps(HORZRES), dcPrint.GetDeviceCaps(VERTRES));
			dcPrint.DPtoLP(&printInfo.m_rectDraw);

			// attempt to start the current page
			if (dcPrint.StartPage() < 0)
			{
				bError = TRUE;
				break;
			}
			OnPrepareDC(&dcPrint, &printInfo);
			ASSERT(printInfo.m_bContinuePrinting);
			// page successfully started, so now render the page
			int is = dcPrint.SaveDC();
			OnPrint(&dcPrint, &printInfo);
			if (dcPrint.EndPage() < 0 || !_GfxAbortProc(dcPrint.m_hDC, 0))
			{
				bError = TRUE;
				break;
			}
			dcPrint.RestoreDC(is);

			dTickPerPage = (GetTickCount() - dwStart) / iPrintedPages;
		}

		// cleanup document printing process
		if (!bError) dcPrint.EndDoc();
		else dcPrint.AbortDoc();
		AfxGetMainWnd()->EnableWindow();    // enable main window
		OnEndPrinting(&dcPrint, &printInfo);    // clean up after printing
		dlgPrintStatus.DestroyWindow();
		dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
	}
}

void CPrinterJob::OnPrepareDC(CDC * pDC, CPrintInfo * pInfo)
{
	ASSERT_VALID(pDC);
	UNUSED(pDC); // unused in release builds

	// Default to one page printing if doc length not known
	if (pInfo != NULL)
		pInfo->m_bContinuePrinting =
			(pInfo->GetMaxPage() != 0xffff || (pInfo->m_nCurPage == 1));
}
