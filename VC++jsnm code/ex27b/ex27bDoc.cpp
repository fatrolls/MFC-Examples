// ex27bDoc.cpp : implementation of the CEx27bDoc class
//

#include "stdafx.h"
#include "ex27b.h"

#include "ex27bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const OLECHAR* CEx27bDoc::s_szSub = L"sub";   // static                                       ";

/////////////////////////////////////////////////////////////////////////////
// CEx27bDoc

IMPLEMENT_DYNCREATE(CEx27bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx27bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx27bDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CEx27bDoc, CDocument)
	INTERFACE_PART(CEx27bDoc, IID_IOleClientSite, OleClientSite)
	INTERFACE_PART(CEx27bDoc, IID_IAdviseSink, AdviseSink)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Implementation of IOleClientSite

STDMETHODIMP_(ULONG) CEx27bDoc::XOleClientSite::AddRef()
{
	TRACE("CEx27bDoc::XOleClientSite::AddRef\n");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx27bDoc::XOleClientSite::Release()
{
	TRACE("CEx27bDoc::XOleClientSite::Release\n");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx27bDoc::XOleClientSite::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx27bDoc::XOleClientSite::QueryInterface");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CEx27bDoc::XOleClientSite::SaveObject()
{
	TRACE("CEx27bDoc::XOleClientSite::SaveObject\n");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	ASSERT_VALID(pThis);

	LPPERSISTSTORAGE lpPersistStorage;
	pThis->m_lpOleObj->QueryInterface(IID_IPersistStorage, 
		(void**) &lpPersistStorage);
	ASSERT(lpPersistStorage != NULL);
	HRESULT hr = NOERROR;
	if (lpPersistStorage->IsDirty() == NOERROR)
	{
		// NOERROR == S_OK != S_FALSE, therefore object is dirty!
		hr = ::OleSave(lpPersistStorage, pThis->m_pTempStgSub, TRUE);
		if (hr != NOERROR)
			hr = lpPersistStorage->SaveCompleted(NULL);

		// Mark the document as dirty, if save successful
		pThis->SetModifiedFlag();
	}
	lpPersistStorage->Release();
	pThis->UpdateAllViews(NULL);
	return hr;
}

STDMETHODIMP CEx27bDoc::XOleClientSite::GetMoniker(
	DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMoniker)
{
	TRACE("CEx27bDoc::XOleClientSite::GetMoniker\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx27bDoc::XOleClientSite::GetContainer(
	LPOLECONTAINER* ppContainer)
{
	TRACE("CEx27bDoc::XOleClientSite::GetContainer\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx27bDoc::XOleClientSite::ShowObject()
{
	TRACE("CEx27bDoc::XOleClientSite::ShowObject\n");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	ASSERT_VALID(pThis);
	pThis->UpdateAllViews(NULL);
	return NOERROR;
}

STDMETHODIMP CEx27bDoc::XOleClientSite::OnShowWindow(BOOL fShow)
{
	TRACE("CEx27bDoc::XOleClientSite::OnShowWindow\n");
	METHOD_PROLOGUE(CEx27bDoc, OleClientSite)
	ASSERT_VALID(pThis);
	pThis->m_bHatch = fShow;
	pThis->UpdateAllViews(NULL);
	return NOERROR;
}

STDMETHODIMP CEx27bDoc::XOleClientSite::RequestNewObjectLayout()
{
	TRACE("CEx27bDoc::XOleClientSite::RequestNewObjectLayout\n");
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation of IAdviseSink

STDMETHODIMP_(ULONG) CEx27bDoc::XAdviseSink::AddRef()
{
	TRACE("CEx27bDoc::XAdviseSink::AddRef\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx27bDoc::XAdviseSink::Release()
{
	TRACE("CEx27bDoc::XAdviseSink::Release\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx27bDoc::XAdviseSink::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx27bDoc::XAdviseSink::QueryInterface");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(void) CEx27bDoc::XAdviseSink::OnDataChange(
	LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	TRACE("CEx27bDoc::XAdviseSink::OnDataChange\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	// Interesting only for advanced containers.  Forward it such that
	//  containers do not have to implement the entire interface.
}

STDMETHODIMP_(void) CEx27bDoc::XAdviseSink::OnViewChange(
	DWORD aspects, LONG /*lindex*/)
{
	TRACE("CEx27bDoc::XAdviseSink::OnViewChange\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);	// the really important one
}

STDMETHODIMP_(void) CEx27bDoc::XAdviseSink::OnRename(
	LPMONIKER /*lpMoniker*/)
{
	TRACE("CEx27bDoc::XAdviseSink::OnRename\n");
	// Interesting only to the OLE link object. Containers ignore this.
}

STDMETHODIMP_(void) CEx27bDoc::XAdviseSink::OnSave()
{
	TRACE("CEx27bDoc::XAdviseSink::OnSave\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);
}

STDMETHODIMP_(void) CEx27bDoc::XAdviseSink::OnClose()
{
	TRACE("CEx27bDoc::XAdviseSink::OnClose\n");
	METHOD_PROLOGUE(CEx27bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bDoc construction/destruction

CEx27bDoc::CEx27bDoc()
{
	m_lpOleObj = NULL;
	m_pTempStgRoot = NULL;
	m_pTempStgSub = NULL;
	m_bHatch = FALSE;
}

CEx27bDoc::~CEx27bDoc()
{
}

BOOL CEx27bDoc::OnNewDocument()
{
	TRACE("Entering CEx27bDoc::OnNewDocument\n");
	// Create a structured storage home for the object (m_pTempStgSub).
	//  This is a temporary file -- random name supplied by OLE.
	VERIFY(::StgCreateDocfile(NULL,
		STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE|
		STGM_DELETEONRELEASE,
		0, &m_pTempStgRoot) == S_OK);
	ASSERT(m_pTempStgRoot!= NULL);
	
    VERIFY(m_pTempStgRoot->CreateStorage(OLESTR("sub"),
    	   STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
    	   0, 0, &m_pTempStgSub) == S_OK);
	ASSERT(m_pTempStgSub != NULL);
	return CDocument::OnNewDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bDoc serialization

void CEx27bDoc::Serialize(CArchive& ar)
{
	// no hookup to MFC serialization
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx27bDoc diagnostics

#ifdef _DEBUG
void CEx27bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx27bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27bDoc commands

void CEx27bDoc::OnCloseDocument() 
{
	m_pTempStgSub->Release(); // must release BEFORE calling base class
	m_pTempStgRoot->Release();
	CDocument::OnCloseDocument();
}

void CEx27bDoc::DeleteContents() 
{
	if(m_lpOleObj != NULL) {
	   // If object is running, close it, which releases our IOleClientSite
		m_lpOleObj->Close(OLECLOSE_NOSAVE);
		m_lpOleObj->Release(); // should be final release (or else..)
		m_lpOleObj = NULL;
	}
}

void CEx27bDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
	m_bHatch = FALSE;
}

BOOL CEx27bDoc::SaveModified() 
{
	// Eliminate "save to file" message
	return TRUE;
}

void ITrace(REFIID iid, const char* str)
{
	OLECHAR* lpszIID;
	::StringFromIID(iid, &lpszIID);
	CString strIID = lpszIID;
	TRACE("%s - %s\n", (const char*) strIID, (const char*) str);
	AfxFreeTaskMem(lpszIID);
}
