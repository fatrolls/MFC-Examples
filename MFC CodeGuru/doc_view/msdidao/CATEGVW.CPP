// CategVw.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoBmp.h"
#include "DaoSet.h"
#include "CategSet.h"
#include "DaoDoc.h"

#include "CategVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE CopyHandle(HANDLE handle)
{
  LPBYTE  lpCopy;
  LPBYTE  lp;
  HANDLE  hCopy;
  DWORD   dwLen;

  if (handle == NULL) return NULL;
  dwLen = GlobalSize((HGLOBAL)handle);
  if ((hCopy = (HANDLE)GlobalAlloc(GHND, dwLen)) != NULL)
  {
    lpCopy = (LPBYTE)GlobalLock((HGLOBAL)hCopy);
    lp	   = (LPBYTE)GlobalLock((HGLOBAL)handle);
    while (dwLen--) *lpCopy++ = *lp++;
    GlobalUnlock((HGLOBAL)hCopy);
    GlobalUnlock((HGLOBAL)handle);
  }
  return hCopy;
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesView

IMPLEMENT_DYNCREATE(CCategoriesView, CDaoRecordView)

CCategoriesView::CCategoriesView()
	: CDaoRecordView(CCategoriesView::IDD)
{
	//{{AFX_DATA_INIT(CCategoriesView)
	//}}AFX_DATA_INIT
	m_pCategoriesSet = NULL;
}

CCategoriesView::~CCategoriesView()
{
}

void CCategoriesView::DoDataExchange(CDataExchange* pDX)
{
	CDaoRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCategoriesView)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_CATEG_ID, m_pCategoriesSet->m_CategoryID);
	DDX_Text(pDX, IDC_CATEG_NAME, m_pCategoriesSet->m_CategoryName);
	DDX_Text(pDX, IDC_CATEG_DESCRIPTION, m_pCategoriesSet->m_Description);
}

BEGIN_MESSAGE_MAP(CCategoriesView, CDaoRecordView)
	//{{AFX_MSG_MAP(CCategoriesView)
	ON_WM_PAINT()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCategoriesView::OnInitialUpdate() 
{
  CMSDIDaoDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);
  m_pCategoriesSet = pDoc->OpenCategories();
  CDaoRecordView::OnInitialUpdate();
}

void CCategoriesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (pHint && pHint != m_pCategoriesSet) return;
	UpdateData(FALSE);
}

CDaoRecordset *CCategoriesView::OnGetRecordset()
{
	return (CDaoRecordset*)m_pCategoriesSet;
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesView diagnostics

#ifdef _DEBUG
void CCategoriesView::AssertValid() const
{
	CDaoRecordView::AssertValid();
}

void CCategoriesView::Dump(CDumpContext& dc) const
{
	CDaoRecordView::Dump(dc);
}

CMSDIDaoDoc* CCategoriesView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDIDaoDoc)));
	return (CMSDIDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCategoriesView message handlers

void CCategoriesView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// lock picture
	if (m_pCategoriesSet && m_pCategoriesSet->m_Picture.Lock())
	{
	  // get bitmap
	  CBitmap *pBitmap, *poldbmp;
 
	  // Load the bitmap
	  pBitmap = m_pCategoriesSet->m_Picture.GetBitmap(&dc);
 
	  // Create a compatible memory DC
	  CDC memdc;
	  memdc.CreateCompatibleDC(&dc);
 
	  // Select the bitmap into the DC
	  poldbmp = memdc.SelectObject(pBitmap);

	  // Copy (BitBlt) bitmap from memory DC to screen DC
	  DWORD Widht = m_pCategoriesSet->m_Picture.Width();
	  DWORD Height = m_pCategoriesSet->m_Picture.Height();
	  CWnd* pWnd = GetDlgItem(IDC_CATEG_PICTURE);
	  CRect rect; pWnd->GetWindowRect(&rect);
	  ScreenToClient(rect);
	  dc.BitBlt(rect.left, rect.top, Widht, Height, &memdc, 0, 0, SRCCOPY);
 
	  memdc.SelectObject(poldbmp);
	  m_pCategoriesSet->m_Picture.Unlock();
	}
}

void CCategoriesView::OnEditCopy() 
{
	// only for test but of interess
	if (m_pCategoriesSet->m_Picture.Lock())
	{
	  m_pCategoriesSet->m_Picture.CopyToClipboard(m_hWnd);
	  m_pCategoriesSet->m_Picture.Unlock();
	}
}

void CCategoriesView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pCategoriesSet != NULL);
}

void CCategoriesView::InvalidateDlgRect(UINT nID)
{
	CWnd* pWnd = GetDlgItem(nID);
	CRect rect; pWnd->GetWindowRect(&rect);
	ScreenToClient(rect);
	rect.right = rect.left + 172; // normaly lock/unlock
	rect.bottom = rect.top + 120; // picture and get width/height
	InvalidateRect(&rect);
}

BOOL CCategoriesView::OnMove(UINT nIDMoveCommand)
{
	BOOL bRet = CDaoRecordView::OnMove(nIDMoveCommand);
        InvalidateDlgRect(IDC_CATEG_PICTURE);
	return bRet;
}