// ImageViewerDoc.cpp : implementation of the CImageViewerDoc class
//

#include "stdafx.h"
#include "ImageViewer.h"

#include "ImageViewerDoc.h"
#include "ImageViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageViewerDoc

IMPLEMENT_DYNCREATE(CImageViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CImageViewerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageViewerDoc construction/destruction

CImageViewerDoc::CImageViewerDoc()
{
	// TODO: add one-time construction code here

}

CImageViewerDoc::~CImageViewerDoc()
{
}

BOOL CImageViewerDoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageViewerDoc serialization

void CImageViewerDoc::Serialize(CArchive& ar)
{
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
// CImageViewerDoc diagnostics

#ifdef _DEBUG
void CImageViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageViewerDoc commands

BOOL CImageViewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	POSITION pos=GetFirstViewPosition();
	ASSERT(pos!=NULL);
	CImageViewerView* pView=(CImageViewerView*)GetNextView(pos);
	ASSERT(pView!=NULL);
#ifdef OXDIB_SUPPORTJPEG
	if(!pView->GetImageViewer()->LoadJPEGFile(lpszPathName))
#endif //  OXDIB_SUPPORTJPEG
		pView->GetImageViewer()->LoadFile(lpszPathName);

	return TRUE;
}

BOOL CImageViewerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	POSITION pos=GetFirstViewPosition();
	ASSERT(pos!=NULL);
	CImageViewerView* pView=(CImageViewerView*)GetNextView(pos);
	ASSERT(pView!=NULL);
#ifdef OXDIB_SUPPORTJPEG
	return pView->GetImageViewer()->GetImage()->WriteJPEG(lpszPathName);
#else
	return pView->GetImageViewer()->GetImage()->Write(lpszPathName);
#endif //  OXDIB_SUPPORTJPEG
}
