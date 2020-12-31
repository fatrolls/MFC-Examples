// HexDoc.cpp : implementation of the CHexDoc class
//

#include "stdafx.h"
#include "HexDump.h"

#include "HexDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexDoc

IMPLEMENT_DYNCREATE(CHexDoc, CDocument)

BEGIN_MESSAGE_MAP(CHexDoc, CDocument)
	//{{AFX_MSG_MAP(CHexDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexDoc construction/destruction

CHexDoc::CHexDoc()
{
    m_nDocLength = 0;
    m_pFileData = NULL;
}

CHexDoc::~CHexDoc()
{
}

BOOL CHexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CHexDoc serialization

void CHexDoc::Serialize(CArchive& ar)
{
    if (ar.IsLoading ()) {
        CFile* pFile = ar.GetFile ();
        m_nDocLength = (UINT) pFile->GetLength ();

		//
        // Allocate a buffer for the file data.
		//
        try {
            m_pFileData = new BYTE[m_nDocLength];
        }
        catch (CMemoryException* e) {
            m_nDocLength = 0;
            throw e;
        }

		//
        // Read the file data into the buffer.
		//
        try {
            pFile->Read (m_pFileData, m_nDocLength);
        }
        catch (CFileException* e) {
            delete[] m_pFileData;
            m_pFileData = NULL;
            m_nDocLength = 0;
            throw e;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CHexDoc diagnostics

#ifdef _DEBUG
void CHexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexDoc commands

void CHexDoc::DeleteContents() 
{
	CDocument::DeleteContents();

    if (m_pFileData != NULL) {
        delete[] m_pFileData;
        m_pFileData = NULL;
        m_nDocLength = 0;
    }
}

UINT CHexDoc::GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer)
{
    if (nIndex >= m_nDocLength)
        return 0;

    UINT nLength = nCount;
    if ((nIndex + nCount) > m_nDocLength)
        nLength = m_nDocLength - nIndex;

    ::CopyMemory (pBuffer, m_pFileData + nIndex, nLength);
    return nLength;
}

UINT CHexDoc::GetDocumentLength()
{
    return m_nDocLength;
}
