#include "stdafx.h"
#include "OXWinApp.h"
#include "OXDocMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COXWinApp


IMPLEMENT_DYNAMIC(COXWinApp, CWinApp)

/////////////////////////////////////////////////////////////////////////////
// COXWinApp construction

COXWinApp::COXWinApp()
{
}

void COXWinApp::AddDocTemplate(CDocTemplate* pTemplate)
{
	if (m_pDocManager == NULL)
		m_pDocManager = new COXDocManager;
	m_pDocManager->AddDocTemplate(pTemplate);
}

CFileDialog* COXWinApp::NewFileDialog(BOOL bOpenFileDialog)
{
	return new CFileDialog(bOpenFileDialog);
}


