// ==========================================================================
// 							Class Implementation : COXPreviewDialog
// ==========================================================================

// Source file : OXPrvDlg.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "OXCommon.h"
#include <dlgs.h>
#include "OXPrvDlg.h"		// class specification
#include "path.h"

#define MORE_THAN_ONE 0xffff

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Definition of static members


// Data members -------------------------------------------------------------
// protected:

COXPreviewDialog::COXPreview::COXPreview()
{
}

void COXPreviewDialog::COXPreview::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC*	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect	rect(lpDrawItemStruct->rcItem);
	
	((COXPreviewDialog*)GetParent())->OnPaintPreview(pDC, rect);
}


// private:

// Member functions ---------------------------------------------------------
// public:


IMPLEMENT_DYNAMIC(COXPreviewDialog, CFileDialog)


COXPreviewDialog::COXPreviewDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, 
								   LPCTSTR lpszFileName, DWORD dwFlags, 
								   LPCTSTR lpszFilter, CWnd* pParentWnd)
   : CFileDialog(	bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, 
					lpszFilter, pParentWnd),
	 m_bPreview(FALSE),
	 m_bPrevPreview(FALSE)
{
	m_ofn.hInstance = AfxGetResourceHandle();
#ifdef WIN32
	SetTemplate(_T("PREVIEWFILEOPEN"), _T("PREVIEWFILEOPEN95"));    
#else
	m_ofn.lpTemplateName = _T("PREVIEWFILEOPEN");
	m_ofn.Flags |= OFN_ENABLETEMPLATE;
#endif
}

COXPreviewDialog::~COXPreviewDialog()
{
}

BEGIN_MESSAGE_MAP(COXPreviewDialog, CFileDialog)
	ON_BN_CLICKED(IDC_PREVIEW, OnPreview)
	ON_WM_PALETTECHANGED()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

void COXPreviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PREVIEW_FRAME, m_previewFrame);
	DDX_Control(pDX, IDC_PREVIEW_WND, m_preview);
	DDX_Check(pDX, IDC_PREVIEW, m_bPreview);
}

// protected:
void COXPreviewDialog::OnNewFileSelect(const CString& /* sFilename */)
{
}

void COXPreviewDialog::OnPaintPreview(CDC* /* pDC */, const CRect& /* paintRect */)
{
}

void COXPreviewDialog::OnDoRealizePalette(CWnd* /* pFocusWnd */)
{
}

void COXPreviewDialog::OnLBSelChangedNotify(UINT /* nIDBox */, UINT /* iCurSel */, UINT /* nCode */)
	// Notification for Windows 3.1 , Win32s, and Windows NT 3.51
{
#ifdef WIN32
	ASSERT(IsWin95() == FALSE);
	if (IsWin95())
		return;
#endif
	
    CListBox	fileLB;
	int			nFileCount = 0;
	COXPathSpec	pathPreview;
	CWnd* pPreview = NULL;
	CWnd* pFileList = NULL;
	CWnd* pDirStatic = NULL;
	
    pPreview = GetDlgItem(IDC_PREVIEW);
	pFileList = GetDlgItem(lst1); 
	if (pFileList != NULL)
	{
		fileLB.Attach(pFileList->m_hWnd);
		nFileCount = fileLB.GetSelCount();
	}
	
	if (nFileCount > 1 && pPreview != NULL)
	{
		m_bPreview = FALSE;
		pPreview->EnableWindow(FALSE);
	}
	else
		pPreview->EnableWindow(TRUE);
	
	if (nFileCount == 1)
	{
		CString		sDir;
		CString		sFileName;
		int			nIndex;
		int			nNum = 0;
		
		pDirStatic = GetDlgItem(stc1);
		if (pDirStatic != NULL)
#ifdef WIN32
			nNum = pDirStatic->GetWindowText(sDir.GetBuffer(MAX_PATH), MAX_PATH);
#else
			nNum = pDirStatic->GetWindowText(sDir.GetBuffer(_MAX_PATH), _MAX_PATH);
#endif
		sDir.ReleaseBuffer();
		fileLB.GetSelItems(1, &nIndex);
		fileLB.GetText(nIndex, sFileName);
		pathPreview.SetDirectory(sDir);
		pathPreview.SetFileName(sFileName);
		m_sSelectedFile = pathPreview.GetPath();
	}
	else
		m_sSelectedFile.Empty();
	
	fileLB.Detach();   
	
    UpdateData(FALSE);
	
	CheckFileSelection();
}


void COXPreviewDialog::OnPreview() 
{
	UpdateData(TRUE);
    CheckFileSelection();
}

void COXPreviewDialog::CheckFileSelection()
{
	CString sFile;
	
	if ((m_sPrevSelectedFile.CompareNoCase(m_sSelectedFile) != 0) ||
		(m_bPrevPreview != m_bPreview))
	{
		if (m_bPreview)
			sFile = m_sSelectedFile;

		OnNewFileSelect(sFile);
		UpdateData(FALSE);
		
		if (!m_sSelectedFile.IsEmpty() && m_bPreview)
		{
			m_preview.ShowWindow(SW_SHOW);
			m_preview.Invalidate(FALSE);
		}
		else if (m_preview.m_hWnd)
			m_preview.ShowWindow(SW_HIDE);
		
		m_sPrevSelectedFile = m_sSelectedFile;
		m_bPrevPreview = m_bPreview;
	}
}	

#ifdef WIN32

void COXPreviewDialog::OnFileNameChange()
	// Notification for Windows 95 and Windows NT 4.0
{
	ASSERT(IsWin95());
	if (!IsWin95())
		return;
	
   	HWND        hPreview;
	int			nFileCount;
	CString		sPreviewFile;
	COXPathSpec	pathPreview;
	
    GetDlgItem(IDC_PREVIEW, &hPreview);
	
	sPreviewFile = GetFilePath();
	pathPreview.SetPath(sPreviewFile);	
	if (sPreviewFile.IsEmpty())
		nFileCount = 0;
	else if (pathPreview.Exists())
		nFileCount = 1;
	else
		nFileCount = MORE_THAN_ONE;
	
	if (nFileCount>1)
	{
		m_bPreview = FALSE;
		::EnableWindow(hPreview, FALSE);
	}
	else
		::EnableWindow(hPreview, TRUE);
	
	if (nFileCount==1)
		m_sSelectedFile = pathPreview.GetPath();
	else
		m_sSelectedFile.Empty();
	
	UpdateData(FALSE);
	
	CheckFileSelection();
}

BOOL COXPreviewDialog::IsWin95()
{
	static BOOL bFound = FALSE;
	static BOOL bWin95 = FALSE;
	
	if (!bFound)
	{
		OSVERSIONINFO info;
		info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
		GetVersionEx(&info);
		bFound = TRUE;
		if (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
			(info.dwPlatformId == VER_PLATFORM_WIN32_NT && info.dwMajorVersion >= 4))
			bWin95 = TRUE;
	}

	return bWin95;
}

CString COXPreviewDialog::GetFilePath() const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(m_ofn.Flags & OFN_EXPLORER);
	
	CString strResult;
	if (GetParent()->SendMessage(CDM_GETFILEPATH, (WPARAM)MAX_PATH, (LPARAM)strResult.GetBuffer(MAX_PATH)) < 0)
		strResult.Empty();
	else
		strResult.ReleaseBuffer();
	
	return strResult;
}

#endif

// private:



BOOL COXPreviewDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	m_preview.ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void COXPreviewDialog::OnPaletteChanged(CWnd* pFocusWnd)
{
	OnDoRealizePalette(pFocusWnd);
}

void COXPreviewDialog::OnActivate(UINT nState, CWnd* /* pWndOther */, 
								  BOOL /* bMinimized */)
{
	if (nState == WA_CLICKACTIVE || nState == WA_ACTIVE)
		OnDoRealizePalette(this);
}
  

