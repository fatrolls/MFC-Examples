// ex07bView.cpp : implementation of the CEx07bView class
//

#include "stdafx.h"
#include "ex07b.h"

#include "ex07bDoc.h"
#include "ex07bView.h"
#include "SpecFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07bView

IMPLEMENT_DYNCREATE(CEx07bView, CView)

BEGIN_MESSAGE_MAP(CEx07bView, CView)
	//{{AFX_MSG_MAP(CEx07bView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07bView construction/destruction

CEx07bView::CEx07bView()
{
	// TODO: add construction code here

}

CEx07bView::~CEx07bView()
{
}

BOOL CEx07bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx07bView drawing

void CEx07bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx07bView diagnostics

#ifdef _DEBUG
void CEx07bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx07bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx07bDoc* CEx07bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx07bDoc)));
	return (CEx07bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx07bView message handlers

void CEx07bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CSpecialFileDialog dlgFile(TRUE, NULL, "*.obj");
	CString strMessage;
	int nModal = dlgFile.DoModal();
	if ((nModal == IDCANCEL) && (dlgFile.m_bDeleteAll)) {
		strMessage.Format(
			"Are you sure you want to delete all %s files?",
			dlgFile.m_strFilename);
		if (AfxMessageBox(strMessage, MB_YESNO) == IDYES) {
			HANDLE h;
			WIN32_FIND_DATA fData;
			while((h = ::FindFirstFile(dlgFile.m_strFilename, &fData))
			        != (HANDLE) 0xFFFFFFFF) { // no MFC equivalent
				if (::DeleteFile(fData.cFileName) == FALSE) {
					strMessage.Format("Unable to delete file %s\n",
						fData.cFileName);
					AfxMessageBox(strMessage);
					break;
				}
			}
		}
	}
	else if (nModal == IDOK) {
		CString strSingleFilename = dlgFile.GetPathName();
		strMessage.Format(
			"Are you sure you want to delete %s?", strSingleFilename);
		if (AfxMessageBox(strMessage, MB_YESNO) == IDYES) {
			CFile::Remove(strSingleFilename);
		}
	}
}
