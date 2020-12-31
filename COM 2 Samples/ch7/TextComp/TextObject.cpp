// TextObject.cpp : implementation file
//

#include "stdafx.h"
#include "TextComp.h"
#include "TextObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextObject

IMPLEMENT_DYNCREATE(CTextObject, CCmdTarget)

CTextObject::CTextObject()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
	m_pText = NULL;
}

CTextObject::~CTextObject()
{
	if(m_pText != NULL) {
		delete [] m_pText;
	}
	
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	AfxOleUnlockApp();
}


void CTextObject::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CTextObject, CCmdTarget)
	//{{AFX_MSG_MAP(CTextObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTextObject, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTextObject)
	DISP_PROPERTY_EX(CTextObject, "Text", GetText, SetText, VT_VARIANT)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ITextObject to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {4F168D56-C210-11D2-9E60-00104B08CC22}
static const IID IID_ITextObject =
{ 0x4f168d56, 0xc210, 0x11d2, { 0x9e, 0x60, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

BEGIN_INTERFACE_MAP(CTextObject, CCmdTarget)
	INTERFACE_PART(CTextObject, IID_IPersistStream, PersistStream)
	INTERFACE_PART(CTextObject, IID_ITextObject, Dispatch)
END_INTERFACE_MAP()

// {4F168D57-C210-11D2-9E60-00104B08CC22}
IMPLEMENT_OLECREATE(CTextObject, "Text.Object", 0x4f168d57, 0xc210, 0x11d2, 0x9e, 0x60, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22)

/////////////////////////////////////////////////////////////////////////////
// CTextObject message handlers

VARIANT CTextObject::GetText() 
{
	return COleVariant(m_pText).Detach();
}

void CTextObject::SetText(const VARIANT FAR& newValue) 
{
	CString strTemp;
	ASSERT(newValue.vt == VT_BSTR);
	if(m_pText != NULL) {
		delete [] m_pText;
	}
	strTemp = newValue.bstrVal; // converts to narrow chars
	m_pText = new char[strTemp.GetLength() + 1];
	strcpy(m_pText, strTemp);
}

/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP_(ULONG) CTextObject::XPersistStream::AddRef()
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	return (ULONG) pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CTextObject::XPersistStream::Release()
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	return (ULONG) pThis->ExternalRelease();
}

STDMETHODIMP CTextObject::XPersistStream::QueryInterface(REFIID iid,
			void FAR* FAR* ppvObj)
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	// ExternalQueryInterface looks up iid in the macro-generated tables
	return (HRESULT) pThis->ExternalQueryInterface(&iid, ppvObj);
}
/////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTextObject::XPersistStream::GetClassID(LPCLSID lpClassID)
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	ASSERT_VALID(pThis);

	*lpClassID = CTextObject::guid;
	return NOERROR;
}

STDMETHODIMP CTextObject::XPersistStream::IsDirty()
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	ASSERT_VALID(pThis);

	return NOERROR;
}

STDMETHODIMP CTextObject::XPersistStream::Load(LPSTREAM pStm)
{
	ULONG nLength;
    STATSTG statstg;
	
	METHOD_PROLOGUE(CTextObject, PersistStream)
	ASSERT_VALID(pThis);
	if(pThis->m_pText != NULL) {
		delete [] pThis->m_pText;
	}

	// don't need to free statstg.pwcsName because of NONAME flag
	VERIFY(pStm->Stat(&statstg, STATFLAG_NONAME) == NOERROR);
	int nSize = statstg.cbSize.LowPart; // assume < 4 GB
	if(nSize > 0) {
		pThis->m_pText = new char[nSize];
		pStm->Read(pThis->m_pText, nSize, &nLength);
	}
	return NOERROR;
}

STDMETHODIMP CTextObject::XPersistStream::Save(LPSTREAM pStm, BOOL fClearDirty)
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	ASSERT_VALID(pThis);
	int nSize = strlen(pThis->m_pText) + 1;
	pStm->Write(pThis->m_pText, nSize, NULL);
	return NOERROR;
}

STDMETHODIMP CTextObject::XPersistStream::GetSizeMax(ULARGE_INTEGER FAR* pcbSize)
{
	METHOD_PROLOGUE(CTextObject, PersistStream)
	ASSERT_VALID(pThis);
	pcbSize->LowPart = strlen(pThis->m_pText) + 1;
	pcbSize->HighPart = 0; // assume < 4 GB
	return NOERROR;
}