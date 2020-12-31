// ParserViewDoc.cpp : implementation of the CParserViewDoc class
//

#include "stdafx.h"
#include "ParserView.h"

#include "ParserViewDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParserViewDoc

IMPLEMENT_DYNCREATE(CParserViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CParserViewDoc, CDocument)
	//{{AFX_MSG_MAP(CParserViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParserViewDoc construction/destruction

CParserViewDoc::CParserViewDoc()
{
    m_parser.SetErrorRptFunction(ReportError, (DWORD) this);
    m_HTMLparser.SetErrorRptFunction(ReportError, (DWORD) this);
    m_bHTML = FALSE;
}

CParserViewDoc::~CParserViewDoc()
{
}

COXParser* CParserViewDoc::GetParser()
{
    if (m_bHTML)
        return &m_HTMLparser;
    else 
        return &m_parser;
}

BOOL CParserViewDoc::OnNewDocument()
{
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CParserViewDoc serialization

void CParserViewDoc::Serialize(CArchive& /*ar*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CParserViewDoc diagnostics

#ifdef _DEBUG
void CParserViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CParserViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CParserViewDoc commands

BOOL CParserViewDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    //CWaitCursor wait;
    SetPathName(lpszPathName);

#ifdef _UNICODE
	USES_CONVERSION
    LPTSTR ptr = (LPTSTR)wcsrchr(A2W(lpszPathName), TCHAR('.'));
#else
    LPTSTR ptr = (LPTSTR)strrchr(lpszPathName, TCHAR('.'));
#endif
    if (ptr)
        m_bHTML = (_tcsstr(ptr, _T("htm")) != NULL);


#ifdef _DEBUG
    clock_t start = clock(); 
#endif

    GetParser()->ParseFile(lpszPathName);
    
#ifdef _DEBUG
    CString str;
    str.Format(_T("Parse time: %0.2f seconds"), (double) (clock() - start) / (double) CLOCKS_PER_SEC);
    //AfxMessageBox(str);
    TRACE1("%s\n", str);
#endif

    return TRUE;
}

BOOL CParserViewDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
    CWaitCursor wait;
    return GetParser()->WriteFile(lpszPathName);
}

BOOL CParserViewDoc::ReportError(int nError, LPCTSTR szError, int nLine, int nCol, DWORD dwData)
{
    CString str;
    CParserViewDoc* pDoc = (CParserViewDoc*) dwData;

    if (pDoc)
        str.Format(_T("Error parsing file %s.\n\nLine %d, Column %d. Error %d: %s\n\n%s"), 
                   pDoc->GetPathName(), nLine, nCol, 
                   nError, pDoc->GetParser()->TranslateErrorCode(nError),
                   szError);
    else
        str.Format(_T("Error parsing file.\n\nLine %d, Column %d. Error %d: %s\n\n%s"), 
                   nLine, nCol, nError, pDoc->GetParser()->TranslateErrorCode(nError), 
                   szError);

    AfxMessageBox(str, MB_ICONEXCLAMATION);
    return FALSE;
}