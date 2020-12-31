// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Phones.h"
#include "PhonesListBox.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

const TCHAR CChildView::m_szFilters[] =
    _T ("Phone Files (*.phn)|*.phn|All Files (*.*)|*.*||");

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CPhonesListBox)
	//{{AFX_MSG_MAP(CChildView)
	ON_COMMAND(ID_FILE_NEW, OnNewEntry)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CPhonesListBox::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	return TRUE;
}

void CChildView::OnNewEntry() 
{
	NewEntry ();	
}

void CChildView::OnFileOpen() 
{
    CFileDialog dlg (TRUE, _T ("phn"), _T ("*.phn"),
        OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, m_szFilters);

    if (dlg.DoModal () == IDOK) {
        if (LoadFile (dlg.GetPathName ())) {
            m_strPathName = dlg.GetPathName ();
			SetCurSel (0);
		}
	}
}

void CChildView::OnFileSave() 
{
    if (!m_strPathName.IsEmpty ())
        SaveFile (m_strPathName);
    else // Need a file name first
        OnFileSaveAs ();
}

void CChildView::OnFileSaveAs() 
{
    CFileDialog dlg (FALSE, _T ("phn"), m_strPathName,
        OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
        m_szFilters);

    if (dlg.DoModal () == IDOK)
        if (SaveFile (dlg.GetPathName ()))
            m_strPathName = dlg.GetPathName ();
}

BOOL CChildView::LoadFile(LPCTSTR pszFile)
{
    BOOL bResult = FALSE;

	try {
		CStdioFile file (pszFile, CFile::modeRead);
		ResetContent ();
		DWORD dwCount;
		file.Read (&dwCount, sizeof (dwCount));
		if (dwCount) {
			for (int i=0; i<(int) dwCount; i++) {
				CString string;
				file.ReadString (string);
				AddString (string);
			}
		}
		bResult = TRUE;
	}
	catch (CFileException* e) {
		e->ReportError ();
		e->Delete ();
	}
    return bResult;
}

BOOL CChildView::SaveFile(LPCTSTR pszFile)
{
    BOOL bResult = FALSE;

	try {
		CStdioFile file (pszFile, CFile::modeWrite | CFile::modeCreate);
		DWORD dwCount = GetCount ();
		file.Write (&dwCount, sizeof (dwCount));
		if (dwCount) {
			for (int i=0; i<(int) dwCount; i++) {
				CString string;
				GetText (i, string);
				string += _T ("\n");
				file.WriteString (string);
			}
		}
		bResult = TRUE;
	}
	catch (CFileException* e) {
		e->ReportError ();
		e->Delete ();
	}
    return bResult;
}
