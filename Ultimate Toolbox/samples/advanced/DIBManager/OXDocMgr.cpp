#include "stdafx.h"

#include "OXDocMgr.h"
#include "OXWinApp.h"

#include "MainFrm.h"

#include "OXPrvDlg.h"

IMPLEMENT_DYNAMIC(COXDocManager, CDocManager)

// standard function
// emulate the same function for CDocManager
static void AppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
	ASSERT_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	 !strFilterExt.IsEmpty() &&
	 pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
	 !strFilterName.IsEmpty())
	{
		// a file based document template - add to filter list
#ifndef _MAC
		ASSERT(strFilterExt[0] == '.');
#endif
		if (pstrDefaultExt != NULL)
		{
			// set the default extension
#ifndef _MAC
			*pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
#else
			*pstrDefaultExt = strFilterExt;
#endif
			ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
			ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
		}

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please
#ifndef _MAC
		filter += (TCHAR)'*';
#endif
		filter += strFilterExt;
		filter += (TCHAR)'\0';  // next string please
		ofn.nMaxCustFilter++;
	}
}

COXDocManager::COXDocManager()
{
}

// use to provide multiselection and BitmapPreview
BOOL COXDocManager::DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
	ASSERT(AfxGetApp()->IsKindOf(RUNTIME_CLASS(COXWinApp)));

	// get the dialog from COXWinApp
	CFileDialog* pDlgFile=((COXWinApp*) AfxGetApp())->
		NewFileDialog(bOpenFileDialog,lFlags);

	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	CString strFilter;
	CString strDefault;
	if (pTemplate != NULL)
	{
		ASSERT_VALID(pTemplate);
		AppendFilterSuffix(strFilter, pDlgFile->m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_templateList.GetHeadPosition();
		BOOL bFirst = TRUE;
		while (pos != NULL)
		{
			CDocTemplate* pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
			AppendFilterSuffix(strFilter, pDlgFile->m_ofn, pTemplate,
				bFirst ? &strDefault : NULL);
			bFirst = FALSE;
		}
	}

	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
#ifndef _MAC
	strFilter += _T("*.*");
#else
	strFilter += _T("****");
#endif
	strFilter += (TCHAR)'\0';   // last string
	pDlgFile->m_ofn.nMaxCustFilter++;

	pDlgFile->m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
	pDlgFile->m_ofn.lpstrTitle = title;
#else
	pDlgFile->m_ofn.lpstrPrompt = title;
#endif
	if(bOpenFileDialog)
	{
		// set sound space to get multiselection
		pDlgFile->m_ofn.nMaxFile=128*_MAX_PATH;
	}
	else
	{
		pDlgFile->m_ofn.Flags&=~OFN_ALLOWMULTISELECT;
		pDlgFile->m_ofn.nMaxFile=_MAX_PATH;
	}
	pDlgFile->m_ofn.lpstrFile = fileName.GetBuffer(pDlgFile->m_ofn.nMaxFile);

	BOOL bResult = pDlgFile->DoModal() == IDOK ? TRUE : FALSE;
	fileName.ReleaseBuffer();

	if(bOpenFileDialog && bResult)
	{
		CMainFrame* pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;

		// go through all names of multiselected files
		// and try to create document
		POSITION pos=pDlgFile->GetStartPosition();
		while(pos!=NULL)
		{
			CString sFileName=pDlgFile->GetNextPathName(pos);
			pMainFrame->CreateDocumentFromOpenedFile(sFileName);
		}
	}

	delete pDlgFile;

	if(bOpenFileDialog)
	{
		// we don't want to call standard OnOpenDocument
		return FALSE;
	}
	else
	{
		return bResult;
	}
}
