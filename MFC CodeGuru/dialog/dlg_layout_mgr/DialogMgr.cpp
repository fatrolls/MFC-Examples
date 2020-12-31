/////////////////////////////////////////////////////////////////////////////
// CDialogMgr implementation
//
// COPYRIGHT: (c) 1998 ET-Soft - all rights reserved -
//
// A class for smart layouting of Dialogs (inspired by GridBagLayout from 
// Java(tm))
//
// USAGE: See DialogMgr.html
//
// AUTHOR: Erwin Tratar <info@et-soft.de>
//
// LEGAL: You may use and modify this code freely as long (1) this copyright 
// notice remains unmodified (2) you submit all changes to the original
// author and (3) give credits to the author in your Documentation / AboutBox
// THIS SOFTWARE COMES WITH ABSOLUTLY NO WARRANTY NEITHER EXPRESSED NOR
// IMPLIED. USE IT AT YOUR OWN RISK. IN NO WAY SHALL THE AUTHER BE LIABLE FOR
// ANY HARM DONE.
//
//
// HISTORY: 
// 1998/05/1	Initial Release
// 1998/05/13	Added ability to have a Pane with a control
// 1998/05/13	Added better support for TabControls
// 1998/05/14	automatically set Icon to IDR_MAINFRAME

#include "stdafx.h"
#include "DialogMgr.h"

#ifdef _AUTO_SET_ICON
#include "resource.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMgr dialog

CDialogMgr::CDialogMgr(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialog(nID, pParent)
{
	//{{AFX_DATA_INIT(CDialogMgr)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRootPane = NULL;
}

BEGIN_MESSAGE_MAP(CDialogMgr, CDialog)
	//{{AFX_MSG_MAP(CDialogMgr)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDialogMgr message handlers

void CDialogMgr::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	// Re-Layout all controls
	UpdateLayout();
}

void CDialogMgr::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if(m_pRootPane) {
		CRect rcClient;
		GetClientRect(rcClient);

		CRect rcWnd;
		GetWindowRect(rcWnd);
		
		// How much do Window and Client differ
		rcWnd-=rcClient;

		// Take into account that there is a border around the rootPane
		lpMMI->ptMinTrackSize = CPoint(m_pRootPane->getMinConstrainHorz() + rcWnd.Width() + 2*nDefaultBorder,
			m_pRootPane->getMinConstrainVert() + rcWnd.Height() + 2*nDefaultBorder);

	}
}

void CDialogMgr::Layout(CRect& rcClient)
{
	// Does nothing, use IMPLEMENT_LAYOUT in derived class
	// see DialogMgr.h
}

BOOL CDialogMgr::DestroyWindow() 
{
	// Cleanup
	if(m_pRootPane)
		delete m_pRootPane;

	return CDialog::DestroyWindow();
}

void CDialogMgr::UpdateLayout()
{
	// Do the Layout

	CRect rcClient;
	GetClientRect(rcClient);

	// Add a Border around the rootPane
	rcClient.top	+= nDefaultBorder;
	rcClient.bottom -= nDefaultBorder;
	rcClient.left	+= nDefaultBorder;
	rcClient.right	-= nDefaultBorder;

	// Avoid ugly artifacts
	SetRedraw(FALSE);
	Layout(rcClient);
	SetRedraw(TRUE);

	Invalidate();
}

bool CDialogMgr::Save(LPCTSTR lpstrRegKey)
{
	CRect rcWnd;
	GetWindowRect(rcWnd);
	AfxGetApp()->WriteProfileInt( lpstrRegKey, "PosX", rcWnd.left );
	AfxGetApp()->WriteProfileInt( lpstrRegKey, "PosY", rcWnd.top );
	AfxGetApp()->WriteProfileInt( lpstrRegKey, "SizeX", rcWnd.Width() );
	AfxGetApp()->WriteProfileInt( lpstrRegKey, "SizeY", rcWnd.Height() );
	return true;
}

bool CDialogMgr::Load(LPCTSTR lpstrRegKey)
{
	// default to current size
	CRect rcWnd;
	GetWindowRect(rcWnd);

	rcWnd.left	= AfxGetApp()->GetProfileInt( lpstrRegKey, "PosX", rcWnd.left );
	rcWnd.top	= AfxGetApp()->GetProfileInt( lpstrRegKey, "PosY", rcWnd.top );
	rcWnd.right	= rcWnd.left + AfxGetApp()->GetProfileInt( lpstrRegKey, "SizeX", rcWnd.Width() );
	rcWnd.bottom= rcWnd.top  + AfxGetApp()->GetProfileInt( lpstrRegKey, "SizeY", rcWnd.Height() );

	MoveWindow(rcWnd);
	return true;
}


/////////////////////////////////////////////////////////////////////////////
// CDialogMgr::CPaneItem implementation


CDialogMgr::CPaneItem::CPaneItem(CWnd* pWnd, DWORD modeResize/*=GREEDY*/, int sizeX /*=0*/, int sizeY /*=0*/) 
{
	m_modeResize	= modeResize;
	m_pCtrl			= pWnd;


	if(!pWnd) {			// only Dummy!
		m_sizeX = sizeX;
		m_sizeY = sizeY;
	}
	else {
		CRect rcControl;
		pWnd->GetWindowRect(&rcControl);

		if(sizeX == 0) {
			m_sizeX			= rcControl.Width();
		}
		else {
			m_sizeX = sizeX;
		}

		if(sizeY == 0) {
			m_sizeY			= rcControl.Height();
		}
		else {
			m_sizeY = sizeY;
		}
	}
}

CDialogMgr::CPaneItem::CPaneItem( UINT nID, CDialogMgr* pMgr, DWORD modeResize/*=GREEDY*/, int sizeX/*=0*/, int sizeY/*=0*/)
{
	CWnd* pWnd = pMgr->GetDlgItem(nID);
	m_modeResize	= modeResize;
	m_pCtrl			= pWnd;

	if(!pWnd) {			// only Dummy!
		m_sizeX = sizeX;
		m_sizeY = sizeY;
	}
	else {
		CRect rcControl;
		pWnd->GetWindowRect(&rcControl);

		if(sizeX == 0) {
			m_sizeX			= rcControl.Width();
		}
		else {
			m_sizeX = sizeX;
		}

		if(sizeY == 0) {
			m_sizeY			= rcControl.Height();
		}
		else {
			m_sizeY = sizeY;
		}
	}
}

int CDialogMgr::CPaneItem::getConstrainHorz(int sizeParent) 
{
	if(m_modeResize & ABSOLUTE_HORZ) {
		return m_sizeX;	
	}
	if(m_modeResize & RELATIVE_HORZ) {
		return (sizeParent * m_sizeX) / 100;	
	}
	return -1;
}

int CDialogMgr::CPaneItem::getConstrainVert(int sizeParent) 
{
	if(m_modeResize & ABSOLUTE_VERT) {
		return m_sizeY;	
	}
	if(m_modeResize & RELATIVE_VERT) {
		return (sizeParent * m_sizeY) / 100;	
	}
	return -1;
}

int CDialogMgr::CPaneItem::getMinConstrainHorz() 
{
	if(m_modeResize & ABSOLUTE_HORZ) {
		return m_sizeX;	
	}
	return 0;
}

int CDialogMgr::CPaneItem::getMinConstrainVert() 
{
	if(m_modeResize & ABSOLUTE_VERT) {
		return m_sizeY;	
	}
	return 0;	
}

bool CDialogMgr::CPaneItem::resizeTo(CRect& rcNewArea) 
{
	if(m_pCtrl) {
		m_pCtrl->MoveWindow( rcNewArea );
	}
	return true;
}


/////////////////////////////////////////////////////////////////////////////
// CDialogMgr::CPaneTab implementation


CDialogMgr::CPaneTab::CPaneTab( CTabCtrl* pTab, layOrientation orientation, int sizeBorder /*= nDefaultBorder*/, int sizeExtraBorder /*= 0*/ )
: CDialogMgr::CPane(orientation, sizeBorder, sizeExtraBorder)
{
	ASSERT(pTab);
	m_pTab = pTab;
}

int CDialogMgr::CPaneTab::getConstrainHorz(int sizeParent)
{
	CRect rcTab;
	m_pTab->AdjustRect(TRUE, &rcTab);

	if(rcTab.Width() > sizeParent)
		return rcTab.Width();

	return CPane::getConstrainHorz(sizeParent - rcTab.Width());
}

int CDialogMgr::CPaneTab::getConstrainVert(int sizeParent)
{
	CRect rcTab;
	m_pTab->AdjustRect(TRUE, &rcTab);

	if(rcTab.Height() > sizeParent)
		return rcTab.Height();

	return CPane::getConstrainVert(sizeParent - rcTab.Height());
}

int CDialogMgr::CPaneTab::getMinConstrainHorz()
{
	CRect rcTab(0,0,0,0);
	m_pTab->AdjustRect(TRUE, &rcTab);

	return CPane::getMinConstrainHorz() + rcTab.Width();
}

int CDialogMgr::CPaneTab::getMinConstrainVert()
{
	CRect rcTab(0,0,0,0);
	m_pTab->AdjustRect(TRUE, &rcTab);

	return CPane::getMinConstrainVert() + rcTab.Height();
}

bool CDialogMgr::CPaneTab::resizeTo(CRect& rcNewArea)
{
	m_pTab->MoveWindow(rcNewArea);
	m_pTab->AdjustRect(FALSE,rcNewArea);

	return CPane::resizeTo(rcNewArea);
}

/////////////////////////////////////////////////////////////////////////////
// CDialogMgr::CPane implementation

CDialogMgr::CPane::CPane( layOrientation orientation, int sizeBorder /* = nDefaultBorder */, int sizeExtraBorder /*= 0*/) 
{
	m_Orientation	= orientation;
	m_sizeBorder	= sizeBorder;
	m_sizeSecondary	= 0;
	m_modeResize	= 0;
	m_sizeExtraBorder= sizeExtraBorder;
}


CDialogMgr::CPane::~CPane() 
{
	// Destroy all items
	for(int i=0; i<m_paneItems.GetSize(); delete m_paneItems[i++]);
	m_paneItems.RemoveAll();
}


bool CDialogMgr::CPane::addItem( CPane* pSubpane, DWORD modeResize, int sizeSecondary /* = 0 */) 
{
	if( pSubpane->getOrientation() == m_Orientation)
		return false;

	pSubpane->m_modeResize = modeResize;

	if(m_Orientation==HORIZONTAL && (modeResize & ABSOLUTE_HORZ) ) {
		if(sizeSecondary == 0) {
			pSubpane->m_sizeSecondary = pSubpane->getMinConstrainHorz();
		}
	}
	else if(m_Orientation==HORIZONTAL && (modeResize & RELATIVE_HORZ) ) {
		pSubpane->m_sizeSecondary = sizeSecondary;
	}
	else if(m_Orientation==VERTICAL && (modeResize & ABSOLUTE_VERT) ) {
		if(sizeSecondary == 0) {
			pSubpane->m_sizeSecondary = pSubpane->getMinConstrainVert();
		}
	}
	else if(m_Orientation==VERTICAL && (modeResize & RELATIVE_VERT) ) {
		pSubpane->m_sizeSecondary = sizeSecondary;
	}

	m_paneItems.Add(pSubpane);

	return true;
}

bool CDialogMgr::CPane::addItem( CPaneBase* pItem ) 
{
	m_paneItems.Add(pItem);
	return true;
}

int CDialogMgr::CPane::getConstrainHorz(int sizeParent) 
{
	ASSERT( m_Orientation == VERTICAL);

	if( m_modeResize & RELATIVE_HORZ ) {
		return (sizeParent * m_sizeSecondary) / 100;
	}
	else if( m_modeResize & ABSOLUTE_HORZ ){
		return m_sizeSecondary;
	}
	else
		return 0;
}


int CDialogMgr::CPane::getConstrainVert(int sizeParent) 
{
	ASSERT( m_Orientation == HORIZONTAL);

	if( m_modeResize & RELATIVE_VERT ) {
		return (sizeParent * m_sizeSecondary) / 100;
	}
	else if( m_modeResize & ABSOLUTE_VERT ) {
		return m_sizeSecondary;
	}
	else {
		return 0;
	}
}


int CDialogMgr::CPane::getMinConstrainHorz() 
{
	if(m_Orientation == HORIZONTAL) {
		int nMaxConstr = 0;
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			nMaxConstr += pItem->getMinConstrainHorz();
		}
		return nMaxConstr + (m_paneItems.GetUpperBound()*m_sizeBorder) + 2*m_sizeExtraBorder;
	}
	else if( m_modeResize & ABSOLUTE_HORZ && m_sizeSecondary!=0) {
		return m_sizeSecondary + 2*m_sizeExtraBorder;
	}
	else {
		int nMaxConstr = 0;
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			nMaxConstr = max(nMaxConstr,pItem->getMinConstrainHorz());
		}
		return nMaxConstr + 2*m_sizeExtraBorder;
	}
}

int CDialogMgr::CPane::getMinConstrainVert() 
{
	if(m_Orientation == VERTICAL) {
		int nMaxConstr = 0;
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			nMaxConstr += pItem->getMinConstrainVert();
		}
		return nMaxConstr + (m_paneItems.GetUpperBound()*m_sizeBorder) + 2*m_sizeExtraBorder;
	}
	else if( m_modeResize & ABSOLUTE_VERT && m_sizeSecondary!=0) {
		return m_sizeSecondary + 2*m_sizeExtraBorder;
	}
	else {
		int nMaxConstr = 0;
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			nMaxConstr = max(nMaxConstr,pItem->getMinConstrainVert());
		}
		return nMaxConstr + 2*m_sizeExtraBorder;
	}
}

bool CDialogMgr::CPane::resizeTo(CRect& rcNewArea) 
{
	ASSERT(m_paneItems.GetSize());

	CArray<int,int>	sizePrimary;
	sizePrimary.SetSize(m_paneItems.GetSize());

	// Is it the primary Orientation?
	if( m_Orientation == HORIZONTAL ) {

		int availX = rcNewArea.Width() - (m_paneItems.GetUpperBound()*m_sizeBorder);
		availX -= 2*m_sizeExtraBorder;

		rcNewArea.top		+= m_sizeExtraBorder;
		rcNewArea.bottom	-= m_sizeExtraBorder;

		int nGreedy = 0;
		// first all absolute items
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(pItem->modeResize() & ABSOLUTE_HORZ) {
				availX -= (sizePrimary[i] = pItem->getConstrainHorz(0));
			}

			// count Greedy items for later
			if(!(pItem->modeResize() & ABSOLUTE_HORZ) && !(pItem->modeResize() & RELATIVE_HORZ)) {
				nGreedy++;
			}
		}

		// Must not be negative
		availX = max(availX, 0);

		// Then all relative items
		int availRelX = availX;
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(pItem->modeResize() & RELATIVE_HORZ) {
				availX -= (sizePrimary[i] = pItem->getConstrainHorz(availRelX));
			}
		}


		// lastly all Greedy items
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(!(pItem->modeResize() & ABSOLUTE_HORZ) && !(pItem->modeResize() & RELATIVE_HORZ)) {
				sizePrimary[i] = availX / nGreedy;
			}
		}

		// Now reposition all items:
		int nOffset = rcNewArea.left + m_sizeExtraBorder;
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];

			CRect rcPane(nOffset, rcNewArea.top, nOffset+sizePrimary[i], rcNewArea.bottom);
			pItem->resizeTo( rcPane );

			nOffset += m_sizeBorder + sizePrimary[i];
		}				
	}
	else {

		int availY = rcNewArea.Height() - (m_paneItems.GetUpperBound()*m_sizeBorder);
		availY-= 2*m_sizeExtraBorder;

		rcNewArea.left	+= m_sizeExtraBorder;
		rcNewArea.right	-= m_sizeExtraBorder;

		int nGreedy = 0;
		// first all absolute items
		for(int i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(pItem->modeResize() & ABSOLUTE_VERT) {
				availY -= (sizePrimary[i] = pItem->getConstrainVert(0));
			}

			// count Greedy items for later
			if(!(pItem->modeResize() & ABSOLUTE_VERT) && !(pItem->modeResize() & RELATIVE_VERT)) {
				nGreedy++;
			}
		}

		// Must not be negative
		availY = max(availY, 0);

		// Then all relative items
		int availRelY = availY;
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(pItem->modeResize() & RELATIVE_VERT) {
				availY -= (sizePrimary[i] = pItem->getConstrainVert(availRelY));
			}
		}


		// lastly all Greedy items
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];
			if(!(pItem->modeResize() & ABSOLUTE_VERT) && !(pItem->modeResize() & RELATIVE_VERT)) {
				sizePrimary[i] = availY / nGreedy;
			}
		}

		// Now reposition all items:
		int nOffset = rcNewArea.top + m_sizeExtraBorder;
		for(i=0; i<m_paneItems.GetSize(); i++) {
			CPaneBase* pItem = m_paneItems[i];

			CRect rcPane(rcNewArea.left, nOffset, rcNewArea.right, nOffset+sizePrimary[i]);
			pItem->resizeTo( rcPane );

			nOffset += m_sizeBorder + sizePrimary[i];
		}				
	}
	return true;			
}

#ifdef _AUTO_SET_ICON
BOOL CDialogMgr::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon( AfxGetApp()->LoadIcon(IDR_MAINFRAME) ,FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
#endif
