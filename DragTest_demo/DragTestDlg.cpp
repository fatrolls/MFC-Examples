// DragTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DragTest.h"
#include "DragTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragTestDlg dialog

CDragTestDlg::CDragTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDragTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDragTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDragTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDragTestDlg)
	DDX_Control(pDX, IDC_LIST_RIGHT, m_listR);
	DDX_Control(pDX, IDC_LIST_LEFT, m_listL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDragTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDragTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_LEFT, OnBegindragListLeft)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_RIGHT, OnBegindragListRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragTestDlg message handlers

BOOL CDragTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/////////////////////////////////////////////////
	//// Set up columns
	CRect rect;
	m_listL.GetClientRect(&rect);
	int nColWid = ((rect.Width() - 16) / 2); //account for scroll bar
	m_listL.InsertColumn(0, "Words", LVCFMT_LEFT, nColWid);
	m_listL.InsertColumn(1, "Index", LVCFMT_LEFT, nColWid);
	m_listR.InsertColumn(0, "Numbers", LVCFMT_LEFT, nColWid);
	m_listR.InsertColumn(1, "Index", LVCFMT_LEFT, nColWid);
	//Select whole line
	m_listL.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listR.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//// Add some items to the lists
	m_listL.InsertItem(0, "Apple");
	m_listL.SetItemText(0, 1, "1");
	m_listL.InsertItem(1, "Ball");
	m_listL.SetItemText(1, 1, "2");
	m_listL.InsertItem(2, "Candle");
	m_listL.SetItemText(2, 1, "3");
	m_listL.InsertItem(3, "Dog");
	m_listL.SetItemText(3, 1, "4");

	m_listR.InsertItem(0, "111");
	m_listR.SetItemText(0, 1, "1");
	m_listR.InsertItem(1, "222");
	m_listR.SetItemText(1, 1, "2");
	m_listR.InsertItem(2, "333");
	m_listR.SetItemText(2, 1, "3");
	m_listR.InsertItem(3, "444");
	m_listR.SetItemText(3, 1, "4");

	
	/////////////////////////////////////////////
	//// Set up initial variables
	m_bDragging = false;
	m_nDragIndex = -1;
	m_nDropIndex = -1;
	m_pDragImage = NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDragTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDragTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDragTestDlg::OnBegindragListLeft(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//This routine sets the parameters for a Drag and Drop operation.
	//It sets some variables to track the Drag/Drop as well
	// as creating the drag image to be shown during the drag.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//// Save the index of the item being dragged in m_nDragIndex
	////  This will be used later for retrieving the info dragged
	m_nDragIndex = pNMListView->iItem;

	//// Create a drag image
	POINT pt;
	int nOffset = -10; //offset in pixels for drag image (positive is up and to the left; neg is down and to the right)
	if(m_listL.GetSelectedCount() > 1) //more than one item is selected
	pt.x = nOffset;
	pt.y = nOffset;

	m_pDragImage = m_listL.CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pDragImage); //make sure it was created
	//We will call delete later (in LButtonUp) to clean this up

	CBitmap bitmap;
	if(m_listL.GetSelectedCount() > 1) //more than 1 item in list is selected
		//bitmap.LoadBitmap(IDB_BITMAP_MULTI);
		bitmap.LoadBitmap(IDB_BITMAP_MULTI_BOXES);
	else
		bitmap.LoadBitmap(IDB_BITMAP_BOX);
	m_pDragImage->Replace(0, &bitmap, &bitmap);

	//// Change the cursor to the drag image
	////	(still must perform DragMove() in OnMouseMove() to show it moving)
	m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset - 4));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMListView->ptAction);
	
	//// Set dragging flag and others
	m_bDragging = TRUE;	//we are in a drag and drop operation
	m_nDropIndex = -1;	//we don't have a drop index yet
	m_pDragList = &m_listL; //make note of which list we are dragging from
	m_pDropWnd = &m_listL;	//at present the drag list is the drop list

	//// Capture all mouse messages
	SetCapture ();

	*pResult = 0;
}


void CDragTestDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	//While the mouse is moving, this routine is called.
	//This routine will redraw the drag image at the present
	// mouse location to display the dragging.
	//Also, while over a CListCtrl, this routine will highlight
	// the item we are hovering over.

	//// If we are in a drag/drop procedure (m_bDragging is true)
	if (m_bDragging)
	{
		//// Move the drag image
		CPoint pt(point);	//get our current mouse coordinates
		ClientToScreen(&pt); //convert to screen coordinates
		m_pDragImage->DragMove(pt); //move the drag image to those coordinates
		// Unlock window updates (this allows the dragging image to be shown smoothly)
		m_pDragImage->DragShowNolock(false);

		//// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT(pDropWnd); //make sure we have a window

		//// If we drag outside current window we need to adjust the highlights displayed
		if (pDropWnd != m_pDropWnd)
		{
			if (m_nDropIndex != -1) //If we drag over the CListCtrl header, turn off the hover highlight
			{
				TRACE("m_nDropIndex is -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				VERIFY (pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED));
				// redraw item
				VERIFY (pList->RedrawItems (m_nDropIndex, m_nDropIndex));
				pList->UpdateWindow ();
				m_nDropIndex = -1;
			}
			else //If we drag out of the CListCtrl altogether
			{
				TRACE("m_nDropIndex is not -1\n");
				CListCtrl* pList = (CListCtrl*)m_pDropWnd;
				int i = 0;
				int nCount = pList->GetItemCount();
				for(i = 0; i < nCount; i++)
				{
					pList->SetItemState(i, 0, LVIS_DROPHILITED);
				}
				pList->RedrawItems(0, nCount);
				pList->UpdateWindow();
			}
		}

		// Save current window pointer as the CListCtrl we are dropping onto
		m_pDropWnd = pDropWnd;

		// Convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient(&pt);

		//If we are hovering over a CListCtrl we need to adjust the highlights
		if(pDropWnd->IsKindOf(RUNTIME_CLASS (CListCtrl)))
		{			
			//Note that we can drop here
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			UINT uFlags;
			CListCtrl* pList = (CListCtrl*)pDropWnd;

			// Turn off hilight for previous drop target
			pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
			// Redraw previous item
			pList->RedrawItems (m_nDropIndex, m_nDropIndex);
			
			// Get the item that is below cursor
			m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest(pt, &uFlags);
			// Highlight it
			pList->SetItemState(m_nDropIndex, LVIS_DROPHILITED, LVIS_DROPHILITED);
			// Redraw item
			pList->RedrawItems(m_nDropIndex, m_nDropIndex);
			pList->UpdateWindow();
		}
		else
		{
			//If we are not hovering over a CListCtrl, change the cursor
			// to note that we cannot drop here
			SetCursor(LoadCursor(NULL, IDC_NO));
		}
		// Lock window updates
		m_pDragImage->DragShowNolock(true);
	}
		
	CDialog::OnMouseMove(nFlags, point);
}


void CDragTestDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//This routine is the end of the drag/drop operation.
	//When the button is released, we are to drop the item.
	//There are a few things we need to do to clean up and
	// finalize the drop:
	//	1) Release the mouse capture
	//	2) Set m_bDragging to false to signify we are not dragging
	//	3) Actually drop the item (we call a separate function to do that)

	//If we are in a drag and drop operation (otherwise we don't do anything)
	if (m_bDragging)
	{
		// Release mouse capture, so that other controls can get control/messages
		ReleaseCapture ();

		// Note that we are NOT in a drag operation
		m_bDragging = FALSE;

		// End dragging image
		m_pDragImage->DragLeave (GetDesktopWindow ());
		m_pDragImage->EndDrag ();
		delete m_pDragImage; //must delete it because it was created at the beginning of the drag

		CPoint pt (point); //Get current mouse coordinates
		ClientToScreen (&pt); //Convert to screen coordinates
		// Get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd); //make sure we have a window pointer
		// If window is CListCtrl, we perform the drop
		if (pDropWnd->IsKindOf (RUNTIME_CLASS (CListCtrl)))
		{
			m_pDropList = (CListCtrl*)pDropWnd; //Set pointer to the list we are dropping on
			DropItemOnList(m_pDragList, m_pDropList); //Call routine to perform the actual drop
		}
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDragTestDlg::DropItemOnList(CListCtrl* pDragList, CListCtrl* pDropList)
{
	//This routine performs the actual drop of the item dragged.
	//It simply grabs the info from the Drag list (pDragList)
	// and puts that info into the list dropped on (pDropList).
	//Send:	pDragList = pointer to CListCtrl we dragged from,
	//		pDropList = pointer to CListCtrl we are dropping on.
	//Return: nothing.

	////Variables


	// Unhilight the drop target
	pDropList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);

	//Set up the LV_ITEM for retrieving item from pDragList and adding the new item to the pDropList
	char szLabel[256];
	LVITEM lviT;
	LVITEM* plvitem;

	ZeroMemory(&lviT, sizeof (LVITEM)); //allocate and clear memory space for LV_ITEM
	lviT.iItem		= m_nDragIndex;
	lviT.mask		= LVIF_TEXT;
	lviT.pszText		= szLabel;
	lviT.cchTextMax	= 255;

	lvItem* pItem;
	lvItem lvi;
	lvi.plvi = &lviT;
	lvi.plvi->iItem = m_nDragIndex;
	lvi.plvi->mask = LVIF_TEXT;
	lvi.plvi->pszText = szLabel;
	lvi.plvi->cchTextMax = 255;

	if(pDragList->GetSelectedCount() == 1)
	{
		// Get item that was dragged
		pDragList->GetItem (lvi.plvi);
		lvi.sCol2 = pDragList->GetItemText(lvi.plvi->iItem, 1);

		// Delete the original item (for Move operation)
		// This is optional. If you want to implement a Copy operation, don't delete.
		// This works very well though for re-arranging items within a CListCtrl.
		// It is written at present such that when dragging from one list to the other
		//  the item is copied, but if dragging within one list, the item is moved.
		if(pDragList == pDropList)
		{
			pDragList->DeleteItem (m_nDragIndex);
			if(m_nDragIndex < m_nDropIndex) m_nDropIndex--; //decrement drop index to account for item
															//being deleted above it
		}

		// Insert item into pDropList
		// if m_nDropIndex == -1, iItem = GetItemCount() (inserts at end of list), else iItem = m_nDropIndex
		lvi.plvi->iItem = (m_nDropIndex == -1) ? pDropList->GetItemCount () : m_nDropIndex;
		pDropList->InsertItem (lvi.plvi);
		pDropList->SetItemText(lvi.plvi->iItem, 1, (LPCTSTR)lvi.sCol2);

		// Select the new item we just inserted
		pDropList->SetItemState (lvi.plvi->iItem, LVIS_SELECTED, LVIS_SELECTED);
	}
	else //more than 1 item is being dropped
	{
		//We have to parse through all of the selected items from the DragList
		//1) Retrieve the info for the items and store them in memory
		//2) If we are reordering, delete the items from the list
		//3) Insert the items into the list (either same list or different list)

		CList<lvItem*, lvItem*> listItems;
		POSITION listPos;
			
		//Retrieve the selected items
		POSITION pos = pDragList->GetFirstSelectedItemPosition(); //iterator for the CListCtrl
		while(pos) //so long as we have a valid POSITION, we keep iterating
		{
			plvitem = new LVITEM;
			ZeroMemory(plvitem, sizeof(LVITEM));
			pItem = new lvItem;
			//ZeroMemory(pItem, sizeof(lvItem)); //If you use ZeroMemory on the lvItem struct, it creates an error when you try to set sCol2
			pItem->plvi = plvitem;
			pItem->plvi->iItem = m_nDragIndex;
			pItem->plvi->mask = LVIF_TEXT;
			pItem->plvi->pszText = new char; //since this is a pointer to the string, we need a new pointer to a new string on the heap
			pItem->plvi->cchTextMax = 255;

			m_nDragIndex = pDragList->GetNextSelectedItem(pos);

			//Get the item
			pItem->plvi->iItem = m_nDragIndex; //set the index in the drag list to the selected item
			pDragList->GetItem(pItem->plvi); //retrieve the information
			pItem->sCol2 = pDragList->GetItemText(pItem->plvi->iItem, 1);

			//Save the pointer to the new item in our CList
			listItems.AddTail(pItem);
		} //EO while(pos) -- at this point we have deleted the moving items and stored them in memory

		if(pDragList == pDropList) //we are reordering the list (moving)
		{
			//Delete the selected items
			pos = pDragList->GetFirstSelectedItemPosition();
			while(pos)
			{
				pos = pDragList->GetFirstSelectedItemPosition();
				m_nDragIndex = pDragList->GetNextSelectedItem(pos);

				pDragList->DeleteItem(m_nDragIndex); //since we are MOVING, delete the item
				if(m_nDragIndex < m_nDropIndex) m_nDropIndex--; //must decrement the drop index to account
																//for the deleted items
			} //EO while(pos)
		} //EO if(pDragList...

		//Iterate through the items stored in memory and add them back into the CListCtrl at the drop index
		listPos = listItems.GetHeadPosition();
		while(listPos)
		{
			pItem = listItems.GetNext(listPos);

			m_nDropIndex = (m_nDropIndex == -1) ? pDropList->GetItemCount() : m_nDropIndex;
			pItem->plvi->iItem = m_nDropIndex;
			pDropList->InsertItem(pItem->plvi); //add the item
			pDropList->SetItemText(pItem->plvi->iItem, 1, pItem->sCol2);

			pDropList->SetItemState(pItem->plvi->iItem, LVIS_SELECTED, LVIS_SELECTED); //highlight/select the item we just added

			m_nDropIndex++; //increment the index we are dropping at to keep the dropped items in the same order they were in in the Drag List
			//If we dont' increment this, the items are added in reverse order
		} //EO while(listPos)

	}
}

void CDragTestDlg::OnBegindragListRight(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//This routine sets the parameters for a Drag and Drop operation.
	//It sets some variables to track the Drag/Drop as well
	// as creating the drag image to be shown during the drag.

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//// Save the index of the item being dragged in m_nDragIndex
	////  This will be used later for retrieving the info dragged
	m_nDragIndex = pNMListView->iItem;

	//// Create a drag image
	POINT pt;
	int nOffset = -10; //offset in pixels for drag image
	pt.x = nOffset;
	pt.y = nOffset;

	m_pDragImage = m_listR.CreateDragImage(m_nDragIndex, &pt);
	ASSERT(m_pDragImage); //make sure it was created
	//We will call delete later (in LButtonUp) to clean this up

		CBitmap bitmap;
	if(m_listR.GetSelectedCount() > 1) //more than 1 item in list is selected
		//bitmap.LoadBitmap(IDB_BITMAP_MULTI);
		bitmap.LoadBitmap(IDB_BITMAP_MULTI_BOXES);
	else
		bitmap.LoadBitmap(IDB_BITMAP_BOX);
	m_pDragImage->Replace(0, &bitmap, &bitmap);

	//// Change the cursor to the drag image
	////	(still must perform DragMove() in OnMouseMove() to show it moving)
	m_pDragImage->BeginDrag(0, CPoint(nOffset, nOffset - 4));
	m_pDragImage->DragEnter(GetDesktopWindow(), pNMListView->ptAction);
	
	//// Set dragging flag and others
	m_bDragging = TRUE;	//we are in a drag and drop operation
	m_nDropIndex = -1;	//we don't have a drop index yet
	m_pDragList = &m_listR; //make note of which list we are dragging from
	m_pDropWnd = &m_listR;	//at present the drag list is the drop list

	//// Capture all mouse messages
	SetCapture ();

	*pResult = 0;
}
