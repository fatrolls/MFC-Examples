// winpeDoc.cpp : implementation of the CWinpeDoc class
//

#include "stdafx.h"
#include "winpe.h"

#include "winpeDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinpeDoc

IMPLEMENT_DYNCREATE(CWinpeDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinpeDoc, CDocument)
	//{{AFX_MSG_MAP(CWinpeDoc)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_DEBUGDIR, OnUpdateViewsDebugdir)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_DUMP, OnUpdateViewsDump)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_EXPORTS, OnUpdateViewsExports)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_HEADERS, OnUpdateViewsHeaders)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_IMPORTS, OnUpdateViewsImports)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_RESOURCES, OnUpdateViewsResources)
	ON_UPDATE_COMMAND_UI(ID_VIEWS_SECTNTBL, OnUpdateViewsSectntbl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinpeDoc construction/destruction

CWinpeDoc::CWinpeDoc()
{
	// TODO: add one-time construction code here
	m_nDocLength = 0;
	m_pFileData = 0;
	m_hFileMapping = 0;
	m_nFileType = 0;
	m_hFile = 0;

	m_printerFont = new CFont;
	m_screenFont = new CFont;

	CClientDC dc (AfxGetMainWnd());
	int nHeight = -((dc.GetDeviceCaps (LOGPIXELSY) * 10 ) / 72);

	m_screenFont->CreateFont(nHeight,
							0,0,0,
							FW_NORMAL,
							0,0,0,
							DEFAULT_CHARSET,
							OUT_CHARACTER_PRECIS,
							CLIP_CHARACTER_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH | FF_DONTCARE,
							"Courier New");
	nHeight = -((dc.GetDeviceCaps (LOGPIXELSY) * 12 ) / 72);
	
	m_printerFont->CreateFont (nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0,
        DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier New");

	TEXTMETRIC tm;
	CFont *pOldFont;

	pOldFont = dc.SelectObject(m_screenFont);
	dc.GetTextMetrics (&tm);
	m_cyScreen = tm.tmHeight + tm.tmExternalLeading;
	dc.SelectObject(pOldFont);

	
	//pOldFont = dc.SelectObject(&m_printerFont);
	//dc.GetTextMetrics (&tm);
	//m_cyPrinter = tm.tmHeight + tm.tmExternalLeading;
	//dc.SelectObject(pOldFont);

	
	
}

CWinpeDoc::~CWinpeDoc()
{
	delete m_printerFont;
	delete m_screenFont;
}

BOOL CWinpeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWinpeDoc serialization

void CWinpeDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
	{
	//	//CFile* pFile = ar.GetFile();
	//	m_nDocLength = (UINT) pFile->GetLength();
	//	try
	//	{
	//		m_pFileData = new BYTE[m_nDocLength];
	//	}
	//	catch (CMemoryException* e)
	//	{
	//		m_nDocLength = 0;
	//		throw e;
	//	}
//
//		try
//		{
//			pFile->Read (m_pFileData,m_nDocLength);
//		}
//		catch (CFileException* e)
//		{
//			delete[] m_pFileData;
//			m_pFileData = NULL;
//			m_nDocLength = 0;
//			throw e;
//		}

	
	}
	else
	{
		// TODO: add storing code here
	}


}

/////////////////////////////////////////////////////////////////////////////
// CWinpeDoc diagnostics

#ifdef _DEBUG
void CWinpeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinpeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinpeDoc commands

UINT CWinpeDoc::GetBytes(UINT nIndex,UINT nCount,PVOID pBuffer)
{

	if (nIndex >= m_nDocLength)
		return 0;

	UINT nLength = nCount;
	if((nIndex + nCount) > m_nDocLength)
		nLength = m_nDocLength - nIndex;

	::CopyMemory(pBuffer,m_pFileData + nIndex,nLength);
	return nLength;

}

UINT CWinpeDoc::GetDocumentLength()
{

	return m_nDocLength;
}

void CWinpeDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	//if (m_pFileData != NULL)
	//{
	//	delete[] m_pFileData;
	//	m_pFileData = NULL;
	//	m_nDocLength = 0;
	//}

	if (m_pFileData)
	{
		UnmapViewOfFile(m_pFileData);
		m_pFileData = NULL;
	}

	if (m_hFileMapping)
	{
		CloseHandle(m_hFileMapping);
		m_hFileMapping = NULL;
	}
	
	if (m_hFile)
	{
		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hFile);
			m_nDocLength = 0;
			m_hFile = NULL;
		}
	}

	CWnd* mywnd = AfxGetMainWnd();
	if (mywnd) // after first time thru
		// dumpview always default view
		mywnd->SendMessage(WM_RESET_FRAMEVIEW,ID_VIEWS_DUMP,0);

	// must call base class
	CDocument::DeleteContents();
}

BOOL CWinpeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	m_pFileData = 0;
	m_hFileMapping = 0;
	m_nFileType = 0;
	m_nDocLength = 0;
	m_hFile = CreateFile(lpszPathName,GENERIC_READ,
							FILE_SHARE_READ,NULL,
							OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							(HANDLE)0);
	if (m_hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	m_hFileMapping = CreateFileMapping(m_hFile,
										NULL,
										PAGE_READONLY,
										0,0,NULL);
	if (m_hFileMapping == 0)
		return FALSE;
	m_pFileData = (LPBYTE)MapViewOfFile(m_hFileMapping,
										FILE_MAP_READ,
										0,0,0);
	if (m_pFileData == 0)
		return FALSE;

	m_nDocLength = GetFileSize (m_hFile, NULL);

	m_nFileType = 0;
	CHAR *hit;
	hit = strstr(lpszPathName,".exe");
	if (hit != NULL)
		m_nFileType = FILETYPE_EXE;
	hit = strstr(lpszPathName,".EXE");
	if (hit != NULL)
		m_nFileType = FILETYPE_EXE;

	hit = strstr(lpszPathName,".dll");
	if (hit != NULL)
		m_nFileType = FILETYPE_DLL;
	hit = strstr(lpszPathName,".DLL");
	if (hit != NULL)
		m_nFileType = FILETYPE_DLL;

	m_Dump_Enabled = TRUE; // dump anything

	if (m_nFileType == 0)
	{
		m_DebugDir_Enabled = FALSE;
		m_Exports_Enabled = FALSE;
		m_Headers_Enabled = FALSE;
		m_Imports_Enabled = FALSE;
		m_Resources_Enabled = FALSE;
		m_Sections_Enabled = FALSE;
		
		
	}
	else
	{
		m_DebugDir_Enabled = TRUE;
		m_Exports_Enabled = TRUE;
		m_Headers_Enabled = TRUE;
		m_Imports_Enabled = TRUE;
		m_Resources_Enabled = TRUE;
		m_Sections_Enabled = TRUE;
	}

	return TRUE;
}

BYTE* CWinpeDoc::GetDocumentDataP()
{
	return m_pFileData;

}

INT CWinpeDoc::GetOpenFileType()
{
	return m_nFileType;
	
}	



void CWinpeDoc::OnUpdateViewsDebugdir(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_DebugDir_Enabled);
	pCmdUI->SetCheck(m_DebugDir_Checked);
	
}

void CWinpeDoc::OnUpdateViewsDump(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Dump_Enabled);
	pCmdUI->SetCheck(m_Dump_Checked);
	
}

void CWinpeDoc::OnUpdateViewsExports(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Exports_Enabled);
	pCmdUI->SetCheck(m_Exports_Checked);
	
}

void CWinpeDoc::OnUpdateViewsHeaders(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Headers_Enabled);
	pCmdUI->SetCheck(m_Headers_Checked);
	
}

void CWinpeDoc::OnUpdateViewsImports(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Imports_Enabled);
	pCmdUI->SetCheck(m_Imports_Checked);
	
}

void CWinpeDoc::OnUpdateViewsResources(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Resources_Enabled);
	pCmdUI->SetCheck(m_Resources_Checked);
	
}

void CWinpeDoc::OnUpdateViewsSectntbl(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_Sections_Enabled);
	pCmdUI->SetCheck(m_Sections_Checked);
	
}

void CWinpeDoc::TurnChecksOff()
{
	m_Dump_Checked = FALSE;
	m_DebugDir_Checked = FALSE;
	m_Imports_Checked = FALSE;
	m_Exports_Checked = FALSE;
	m_Resources_Checked = FALSE;
	m_Headers_Checked = FALSE;
	m_Sections_Checked = FALSE;

}


PIMAGE_SECTION_HEADER CWinpeDoc::GetEnclosingSectionHeader(DWORD rva,
															 PIMAGE_NT_HEADERS pNTHeader)
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);
    unsigned i;
    
    for ( i=0; i < pNTHeader->FileHeader.NumberOfSections; i++, section++ )
    {
        // Is the RVA within this section?
        if ( (rva >= section->VirtualAddress) && 
             (rva < (section->VirtualAddress + section->Misc.VirtualSize)))
            return section;
    }
    
    return 0;

}

void CWinpeDoc::SetDocPrtFont(LPLOGFONT lp)
{
	delete m_printerFont;
	m_printerFont = new CFont;
	//m_printerFont.DeleteObject();
	m_printerFont->CreateFontIndirect(lp);

}

void CWinpeDoc::SetDocScrnFont(LPLOGFONT lp)
{
	delete m_screenFont;
	m_screenFont = new CFont;
	//m_screenFont.DeleteObject();
	m_screenFont->CreateFontIndirect(lp);

}