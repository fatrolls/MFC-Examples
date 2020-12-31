// PrinterJob.cpp: implementation of the CFormPrinterJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestPrintForm.h"
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

CFormPrinterJob::CFormPrinterJob()
{
	pParent = NULL;
	strTitle = "senza nome";
	bAlreadyAskedPageOpt = false;
	pPages = NULL;
	lPages = 0;
}

CFormPrinterJob::~CFormPrinterJob()
{
	Clear();
}

bool CFormPrinterJob::OnPreparePrinting(CPrintInfo * pInfo)
{
	if (pInfo->m_bPreview) return true;
	return DoPreparePrinting(pInfo);
}

void CFormPrinterJob::OnBeginPrinting(CDC * pDC, CPrintInfo * pInfo)
{
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(lPages);

	cForm.Clear();
}

void CFormPrinterJob::OnEndPrinting(CDC * pDC, CPrintInfo * pInfo)
{

	cForm.Clear();
}

void CFormPrinterJob::OnPrint(CDC * pDC, CPrintInfo * pInfo)
{
	int iPI = pInfo->m_nCurPage - 1, t, max, omp, i, maxi;
	ASSERT(iPI >= 0 && iPI < lPages);

	SelectPage(pPages[iPI].lObjId);
	if (cForm.csScriptFile.CompareNoCase(pPages[iPI].cScriptFile) != 0 || cForm.csPageName.CompareNoCase(pPages[iPI].cPageName) != 0)
		VERIFY(cForm.LoadPage(pPages[iPI].cScriptFile, pPages[iPI].cPageName));

	omp = pDC->SetMapMode(MM_LOMETRIC);

	max = cForm.GetPrintObjectCount();
	for (t = 0; t < max; t++)
	{
		VERIFY(cForm.SelectPrintObject(t));

		if (*(cForm.cPrintObject.cCond))
		{
			if (ParseCondition(cForm.cPrintObject.cCond))
			{
				lstrcpy(cForm.cPrintObject.cId, cForm.cPrintObject.cId2);
			}
		}
		if (cForm.cPrintObject.iType == CFormJob::pfoEdit && *(cForm.cPrintObject.cId))
		{
			CString cs;
			ParseScript(cForm.cPrintObject.cId, cs);
			lstrcpy(cForm.cPrintObject.cId, cs);
		}
		
		if (cForm.cPrintObject.iType == CFormJob::pfoImage)
		{
			CRect rc1(cForm.cPrintObject.rc);
			rc1.OffsetRect(cForm.rcPage.TopLeft());
			rc1.top *= -1;
			rc1.bottom *= -1;
			DrawBitmap(cForm.cPrintObject.cId, rc1, pDC);
		}
		else if (cForm.cPrintObject.iType == CFormJob::pfoSubForm)
		{
			if (pPages[iPI].lSubItemCount > 0)
			{
				CFormJob cSubForm;
				VERIFY(cSubForm.LoadPage(pPages[iPI].cScriptFile, cForm.cPrintObject.cId));
				
				int subHeight = cSubForm.rcPage.Height();

				cSubForm.rcPage.left  = cForm.rcPage.left + cForm.cPrintObject.rc.left;
				cSubForm.rcPage.top	  = cForm.rcPage.top + cForm.cPrintObject.rc.top;
				cSubForm.rcPage.right = cForm.rcPage.left + cForm.cPrintObject.rc.right;
				cSubForm.rcPage.bottom = cSubForm.rcPage.top + subHeight;

				for (int ls = pPages[iPI].lFromSubItem; ls < pPages[iPI].lToSubItem; ls ++)
				{
					SelectSubItem(pPages[iPI].lObjId, ls);

					maxi = cSubForm.GetPrintObjectCount();
					for (i = 0; i < maxi; i++)
					{
						VERIFY(cSubForm.SelectPrintObject(i));

						if (*(cSubForm.cPrintObject.cCond))
						{
							if (ParseCondition(cSubForm.cPrintObject.cCond))
							{
								lstrcpy(cSubForm.cPrintObject.cId, cSubForm.cPrintObject.cId2);
							}
						}
						if (cSubForm.cPrintObject.iType == CFormJob::pfoEdit && *(cSubForm.cPrintObject.cId))
						{
							CString cs;
							ParseScript(cSubForm.cPrintObject.cId, cs);
							lstrcpy(cSubForm.cPrintObject.cId, cs);
						}
						cSubForm.Print(pDC);
					}
					cSubForm.rcPage.OffsetRect(0, subHeight);
				}
			}
		}			
		else cForm.Print(pDC);
	}

	pDC->SetMapMode(omp);
}

bool CFormPrinterJob::DoPreparePrinting(CPrintInfo * pInfo)
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

void CFormPrinterJob::OnFilePrint()
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

void CFormPrinterJob::OnPrepareDC(CDC * pDC, CPrintInfo * pInfo)
{
	ASSERT_VALID(pDC);
	UNUSED(pDC); // unused in release builds

	// Default to one page printing if doc length not known
	if (pInfo != NULL)
		pInfo->m_bContinuePrinting =
			(pInfo->GetMaxPage() != 0xffff || (pInfo->m_nCurPage == 1));
}

bool CFormPrinterJob::AddPage(const char * cScriptFile, const char * cPageName, const long lPageId, const long lSubItemCount)
{
	lPages ++;

	if (lPages > 1) pPages = (CPageData *) GlobalReAlloc((HGLOBAL) pPages, sizeof(CPageData) * lPages, GMEM_MOVEABLE|GMEM_ZEROINIT);
	else pPages = (CPageData *) GlobalAlloc(GPTR, sizeof(CPageData));

	if (pPages)
	{
		lstrcpy(pPages[lPages - 1].cPageName, cPageName);
		lstrcpy(pPages[lPages - 1].cScriptFile, cScriptFile);
		pPages[lPages - 1].lObjId = lPageId;
		pPages[lPages - 1].lSubItemCount = lSubItemCount;
		pPages[lPages - 1].lFromSubItem = 0;
		pPages[lPages - 1].lToSubItem = 0;
	}

	if (lSubItemCount > 0)
	{
		VERIFY(cForm.LoadPage(cScriptFile, cPageName));
		CSize sz;
		CString csSubForm;
		if (cForm.HasSubForm(csSubForm, sz))
		{
			int iSubRectH = cForm.cPrintObject.rc.Height();
			int iItemxPage = iSubRectH / sz.cy;
			ASSERT(iItemxPage > 1);

			if (lSubItemCount < iItemxPage)
			{
				pPages[lPages - 1].lFromSubItem = 0;
				pPages[lPages - 1].lToSubItem = lSubItemCount;
			}
			else
			{
				for (int t = 0; t < lSubItemCount; t += iItemxPage)
				{
					if (t != 0)
					{
						lPages ++;
						pPages = (CPageData *) GlobalReAlloc((HGLOBAL) pPages, sizeof(CPageData) * lPages, GMEM_MOVEABLE|GMEM_ZEROINIT);
						ASSERT(pPages);
						lstrcpy(pPages[lPages - 1].cPageName, cPageName);
						lstrcpy(pPages[lPages - 1].cScriptFile, cScriptFile);
						pPages[lPages - 1].lObjId = lPageId;
						pPages[lPages - 1].lSubItemCount = lSubItemCount;
						pPages[lPages - 1].lFromSubItem = t;
						pPages[lPages - 1].lToSubItem = t + iItemxPage;
					}
					else
					{
						pPages[lPages - 1].lFromSubItem = t;
						pPages[lPages - 1].lToSubItem = t + iItemxPage;
					}
					if (pPages[lPages - 1].lToSubItem >= lSubItemCount) 
						pPages[lPages - 1].lToSubItem = lSubItemCount;
				}
			}
		}
	}

	return pPages ? true : false;
}

void CFormPrinterJob::SelectPage(const long lPageId)
{
}

void CFormPrinterJob::ParseScript(const char * cTag, CString & csValue)
{
	csValue = cTag;
}

void CFormPrinterJob::DrawBitmap(const char * cTag, CRect rcBitmap, CDC * pDC)
{
	pDC->FillSolidRect(rcBitmap, RGB(223, 192, 192));
}

bool CFormPrinterJob::ParseCondition(const char * pTag)
{
	return false;
}

void CFormPrinterJob::Clear()
{
	if (lPages > 0 && pPages) GlobalFree((HGLOBAL) pPages);
	pPages = NULL;
	lPages = 0;
	cForm.Clear();
}


void CFormPrinterJob::SelectSubItem(const long lPageId, const long lSubItemIndex)
{

}
