// ColorEditDoc.cpp : implementation of the CColorEditDoc class
//

//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

#include "stdafx.h"
#include "ColorEdit.h"

#include "ColorEditDoc.h"
#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEditDoc

IMPLEMENT_DYNCREATE(CColorEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorEditDoc, CDocument)
	//{{AFX_MSG_MAP(CColorEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CColorEditDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CColorEditDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IColorEdit to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F6898245-462B-11D1-B99D-00A0C9763A0A}
static const IID IID_IColorEdit =
{ 0xf6898245, 0x462b, 0x11d1, { 0xb9, 0x9d, 0x0, 0xa0, 0xc9, 0x76, 0x3a, 0xa } };

BEGIN_INTERFACE_MAP(CColorEditDoc, CDocument)
	INTERFACE_PART(CColorEditDoc, IID_IColorEdit, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEditDoc construction/destruction

CColorEditDoc::CColorEditDoc() : CUndo(25, 64*1024)
{
	m_text.AddComment(_T("/*"), _T("*/"));
	m_text.AddComment(_T("//"), _T("\n"));
	m_text.AddQuote(_T("\""), _T("\""), RGB(0, 200, 200));
	m_text.AddQuote(_T("\'"), _T("\'"), RGB(0, 200, 200));
	m_text.AddKeyword(_T("static"));
	m_text.AddKeyword(_T("const"));
	m_text.AddKeyword(_T("char"));
	m_text.AddKeyword(_T("short"));
	m_text.AddKeyword(_T("unsigned"));
	m_text.AddKeyword(_T("void"));
	m_text.AddKeyword(_T("long"));
	m_text.AddKeyword(_T("int"));
	m_text.AddKeyword(_T("float"));
	m_text.AddKeyword(_T("double"));
	m_text.AddKeyword(_T("struct"));
	m_text.AddKeyword(_T("typedef"));
	m_text.AddKeyword(_T("class"));
	m_text.AddKeyword(_T("public"));
	m_text.AddKeyword(_T("private"));
	m_text.AddKeyword(_T("protected"));
	m_text.AddKeyword(_T("for"));
	m_text.AddKeyword(_T("while"));
	m_text.AddKeyword(_T("do"));
	m_text.AddKeyword(_T("if"));
	m_text.AddKeyword(_T("else"));
	m_text.AddKeyword(_T("switch"));
	m_text.AddKeyword(_T("case"));
	m_text.AddKeyword(_T("break"));
	m_text.AddKeyword(_T("continue"));
	m_text.AddKeyword(_T("return"));
	m_text.AddKeyword(_T("this"));
	m_text.AddKeyword(_T("new"));
	m_text.AddKeyword(_T("delete"));
	m_text.AddKeyword(_T("sizeof"));
	m_text.AddKeyword(_T("#define"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#include"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#ifdef"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#ifndef"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#endif"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("define"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#else"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#elseif"), RGB(128, 128, 128));
	m_text.AddKeyword(_T("#undef"), RGB(128, 128, 128));
	m_text.AddUpdateTarget(this);

	EnableAutomation();

	AfxOleLockApp();
}

CColorEditDoc::~CColorEditDoc()
{
	AfxOleUnlockApp();
}

BOOL CColorEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CheckPoint();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CColorEditDoc serialization

void CColorEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_text;
	}
	else
	{
		ar >> m_text;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CColorEditDoc diagnostics

#ifdef _DEBUG
void CColorEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColorEditDoc commands

void CColorEditDoc::DeleteContents()
{
	m_text = _T("");
}

void CColorEditDoc::DoColorStringUpdate(BOOL bDataChangedFlag)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = GetNextView(pos);
		if (pView != NULL)
			pView->Invalidate();
	}
	if (bDataChangedFlag) SetModifiedFlag();
}

BOOL CColorEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	TCHAR	buffer[256];
	CProgressBar	bar(_T("Reading:"), 40);

	m_text.BeginUpdate();
	try {
		CStdioFile	file(lpszPathName, CFile::modeRead | CFile::typeText);
		long	count = 0;
		long	length = file.GetLength();
		long	pos = 0;
		bar.SetPos(0);
		do {
			memset(buffer, 0, sizeof(buffer));
			count = file.Read(buffer, sizeof(buffer)-1);
			m_text += buffer;
			pos += count;
			bar.SetPos((int) ((70.0)*((double) pos)/((double) length)));
		} while (count == sizeof(buffer)-1);

	} catch (...) {
		m_text.EndUpdate();
		return FALSE;
	}

	m_text.EndUpdate(0, m_text.GetLength());

	bar.SetPos(80);

	CheckPoint();

	bar.SetPos(100);

	return TRUE;
}

BOOL CColorEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	try {
		CStdioFile	file(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.WriteHuge(m_text, m_text.GetLength());
	} catch (...) {
		return FALSE;
	}

	return TRUE;
}

long CColorEditDoc::GetLineCount()
{
	return m_text.GetLineCount();
}

long CColorEditDoc::GetLineOffset(long index)
{
	return m_text.GetLineOffset(index);
}

TCHAR CColorEditDoc::GetAt(long pos)
{
	return m_text.GetAt(pos);
}

COLORREF CColorEditDoc::GetColor(long pos)
{
	return m_text.GetColor(pos);
}

long CColorEditDoc::GetLength()
{
	return m_text.GetLength();
}

CString CColorEditDoc::GetLine(long index)
{
	return m_text.GetLine(index);
}

long CColorEditDoc::Offset2Line(long offset)
{
	return m_text.Offset2Line(offset);
}

CString CColorEditDoc::Range(long start, long end)
{
	return m_text.Mid(start, end-start);
}
