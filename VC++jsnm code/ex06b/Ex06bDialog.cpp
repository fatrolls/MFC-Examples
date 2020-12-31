// Ex06bDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex06b.h"
#include "Ex06bDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06bDialog dialog
double CEx06bDialog::dValue[5] = {4.0, 5.6, 8.0, 11.0, 16.0};


CEx06bDialog::CEx06bDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx06bDialog::IDD, pParent)
{
	m_nProgress = 0;
	m_nTrackbar1 = 0;
	m_nTrackbar2 = 0;

	//{{AFX_DATA_INIT(CEx06bDialog)
	m_dSpin = 0.0;
	//}}AFX_DATA_INIT
}


void CEx06bDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx06bDialog)
	DDX_Text(pDX, IDC_BUDDY_SPIN1, m_dSpin);
	//}}AFX_DATA_MAP

	if (pDX->m_bSaveAndValidate) {
		TRACE("updating trackbar data members\n");
		CSliderCtrl* pSlide1 =
			(CSliderCtrl*) GetDlgItem(IDC_TRACKBAR1);
		m_nTrackbar1 = pSlide1->GetPos();
		CSliderCtrl* pSlide2 =
			(CSliderCtrl*) GetDlgItem(IDC_TRACKBAR2);
		m_nTrackbar2 = pSlide2->GetPos();
	}
}


BEGIN_MESSAGE_MAP(CEx06bDialog, CDialog)
	//{{AFX_MSG_MAP(CEx06bDialog)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVIEW1, OnItemchangedListview1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEW1, OnSelchangedTreeview1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06bDialog message handlers

BOOL CEx06bDialog::OnInitDialog() 
{
	CProgressCtrl* pProg =
		(CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
	pProg->SetRange(0, 100);
	pProg->SetPos(m_nProgress);

	CString strText1;
	CSliderCtrl* pSlide1 =
		(CSliderCtrl*) GetDlgItem(IDC_TRACKBAR1);
	pSlide1->SetRange(0, 100);
	pSlide1->SetPos(m_nTrackbar1);
	strText1.Format("%d", pSlide1->GetPos());
	SetDlgItemText(IDC_STATIC_TRACK1, strText1);

	CString strText2;
	CSliderCtrl* pSlide2 =
		(CSliderCtrl*) GetDlgItem(IDC_TRACKBAR2);
	pSlide2->SetRange(0, 4);
	pSlide2->SetPos(m_nTrackbar2);
	strText2.Format("%3.1f", dValue[pSlide2->GetPos()]);
	SetDlgItemText(IDC_STATIC_TRACK2, strText2);

	CSpinButtonCtrl* pSpin =
		(CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1);
	pSpin->SetRange(0, 100);
	pSpin->SetPos((int) (m_dSpin * 10.0));

	HICON hIcon[8];
	int n;
	m_imageList.Create(16, 16, 0, 8, 8); // 32, 32 for large icons
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_WHITE);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_BLACK);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_RED);
	hIcon[3] = AfxGetApp()->LoadIcon(IDI_BLUE);
	hIcon[4] = AfxGetApp()->LoadIcon(IDI_YELLOW);
	hIcon[5] = AfxGetApp()->LoadIcon(IDI_CYAN);
	hIcon[6] = AfxGetApp()->LoadIcon(IDI_PURPLE);
	hIcon[7] = AfxGetApp()->LoadIcon(IDI_GREEN);
	for (n = 0; n < 8; n++) {
		m_imageList.Add(hIcon[n]);
	}

	static char* color[] = {"white", "black", "red",
	                        "blue", "yellow", "cyan",
	                        "purple", "green"};
	CListCtrl* pList =
		(CListCtrl*) GetDlgItem(IDC_LISTVIEW1);
	pList->SetImageList(&m_imageList, LVSIL_SMALL);
	for (n = 0; n < 8; n++) {
		pList->InsertItem(n, color[n], n);
	}
	pList->SetBkColor(RGB(0, 255, 255)); // UGLY!
	pList->SetTextBkColor(RGB(0, 255, 255));

	CTreeCtrl* pTree =
		(CTreeCtrl*) GetDlgItem(IDC_TREEVIEW1);
	pTree->SetImageList(&m_imageList, TVSIL_NORMAL);
	// tree structure common values
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE
	                     | TVIF_TEXT;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 6;
	tvinsert.item.iSelectedImage = 1;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = 0;
	// top level
	tvinsert.item.pszText = "Homer";
	tvinsert.item.iImage = 2;
	HTREEITEM hDad = pTree ->InsertItem(&tvinsert);
	tvinsert.item.pszText = "Marge";
	HTREEITEM hMom = pTree->InsertItem(&tvinsert);
	// second level
	tvinsert.hParent = hDad;
	tvinsert.item.pszText = "Bart";
	tvinsert.item.iImage = 3;
	pTree->InsertItem(&tvinsert);
	tvinsert.item.pszText = "Lisa";
	pTree->InsertItem(&tvinsert);
	// second level
	tvinsert.hParent = hMom;
	tvinsert.item.pszText = "Bart";
	tvinsert.item.iImage = 4;
	pTree->InsertItem(&tvinsert);
	tvinsert.item.pszText = "Lisa";
	pTree->InsertItem(&tvinsert);
	tvinsert.item.pszText = "Dilbert";
	HTREEITEM hOther = pTree->InsertItem(&tvinsert);
	// third level
	tvinsert.hParent = hOther;
	tvinsert.item.pszText = "Dogbert";
	tvinsert.item.iImage = 7;
	pTree->InsertItem(&tvinsert);
	tvinsert.item.pszText = "Ratbert";
	pTree->InsertItem(&tvinsert);
	
	return CDialog::OnInitDialog();
}

void CEx06bDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
	CString strText;

	// Two trackbars are sending
	//  HSCROLL messages (different processing)
	switch(pScrollBar->GetDlgCtrlID()) {
	case IDC_TRACKBAR1:
		strText.Format("%d", pSlide->GetPos());
		SetDlgItemText(IDC_STATIC_TRACK1, strText);
		break;
	case IDC_TRACKBAR2:
		strText.Format("%3.1f", dValue[pSlide->GetPos()]);
		SetDlgItemText(IDC_STATIC_TRACK2, strText);
		break;
	}
}

void CEx06bDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (nSBCode == SB_ENDSCROLL) {
		return; // Reject spurious messages
	}
	// Process scroll messages from IDC_SPIN1 only
	if (pScrollBar->GetDlgCtrlID() == IDC_SPIN1) {
		CString strValue;
		strValue.Format("%3.1f", (double) nPos / 10.0);
		((CSpinButtonCtrl*) pScrollBar)->GetBuddy()
		                               ->SetWindowText(strValue);
	}
}

void CEx06bDialog::OnItemchangedListview1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl* pList =
		(CListCtrl*) GetDlgItem(IDC_LISTVIEW1);
	int nSelected = pNMListView->iItem;
	if (nSelected >= 0) {
		CString strItem = pList->GetItemText(nSelected, 0);
		SetDlgItemText(IDC_STATIC_LISTVIEW1, strItem);
	}
	*pResult = 0;
}

void CEx06bDialog::OnSelchangedTreeview1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCtrl* pTree =
		(CTreeCtrl*) GetDlgItem(IDC_TREEVIEW1);
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
	if (hSelected != NULL) {
		char text[31];
		TV_ITEM item;
		item.mask = TVIF_HANDLE | TVIF_TEXT;
		item.hItem = hSelected;
		item.pszText = text;
		item.cchTextMax = 30;
		VERIFY(pTree->GetItem(&item));
		SetDlgItemText(IDC_STATIC_TREEVIEW1, text);
	}
	*pResult = 0;
}
