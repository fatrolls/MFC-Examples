// MsgMapperDoc.cpp : implementation of the CMsgMapperDoc class
//

#include "stdafx.h"
#include "MsgMapper.h"
#include "mainfrm.h"
#include "MsgMapperDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMsgMapperDoc

IMPLEMENT_DYNCREATE(CMsgMapperDoc, CDocument)

BEGIN_MESSAGE_MAP(CMsgMapperDoc, CDocument)
END_MESSAGE_MAP()


// CMsgMapperDoc construction/destruction

CMsgMapperDoc::CMsgMapperDoc()
{
	// TODO: add one-time construction code here

}

CMsgMapperDoc::~CMsgMapperDoc()
{
}

BOOL CMsgMapperDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMsgMapperDoc serialization

void CMsgMapperDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// Load 'raw' message data into a member CString
		char buf[2048];
		UINT count = 0;
		do{
			count= ar.Read(buf, 2046);
			if(count > 0) {
				buf[count] = 0;
				m_strRawMessage += buf;
			}
		} while (count > 0);	
	}
}


// CMsgMapperDoc diagnostics

#ifdef _DEBUG
void CMsgMapperDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMsgMapperDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMsgMapperDoc commands

BOOL CMsgMapperDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	BOOL retval = TRUE;
	if (!CDocument::OnOpenDocument(lpszPathName)) {
		retval = FALSE;
	}
	else {
		int result = m_message.LoadMessage(lpszPathName);
		if(result != UTE_SUCCESS) {
			((CMainFrame*)((CMsgMapperApp*)AfxGetApp())->m_pMainWnd)->
				SetStatusText(CUT_ERR::GetErrorString(result));
				
				retval = FALSE;
		}
	}
	return retval;
}
