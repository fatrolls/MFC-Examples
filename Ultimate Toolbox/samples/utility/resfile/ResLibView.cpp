// ResLibView.cpp : implementation of the CResLibView class
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "ResFile.h"

#include "ResLibDoc.h"
#include "ResLibView.h"
#include "OXResourceLibrary.h"
#include "OXResourceFile.h"
#include "DlgResEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// we will use this value to distinguish a folder from a resource item in the tree view
// (a resource item stores an index that can be used to fetch type, name and language
// from GetDocument()->m_sTypes, m_sNames and m_nLangs, respectively).
#define TVI_DATA_FOLDER	0xFFFFFFFF

/////////////////////////////////////////////////////////////////////////////
// CResLibView

IMPLEMENT_DYNCREATE(CResLibView, CTreeView)

BEGIN_MESSAGE_MAP(CResLibView, CTreeView)
	//{{AFX_MSG_MAP(CResLibView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResLibView construction/destruction

CResLibView::CResLibView()
{
	m_ilFolder.Create(IDB_IMAGELIST, 16, 0, RGB(255,0,255));
	m_hRootItem = NULL;
	m_nClipFormat = 0;
	m_bModifiable = FALSE;
}

CResLibView::~CResLibView()
{
}

BOOL CResLibView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CResLibView drawing

void CResLibView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	CResLibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CResLibView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl& rTree = GetTreeCtrl();
	rTree.SetImageList(&m_ilFolder, TVSIL_NORMAL); 

	m_nClipFormat = ((CResFileApp*)AfxGetApp())->m_nClipFormat;
	m_pDoc = GetDocument();
	m_pResLib = &m_pDoc->m_ResLib;

	// calling IsModifiable() once instead of repeatedly checking it
	m_bModifiable = m_pResLib->IsModifiable();

	if (m_pResLib == NULL)
		return;

	m_hRootItem = rTree.InsertItem(m_pResLib->GetFileName() + 
		(m_bModifiable ? _T("") : _T(" <<<READ ONLY>>>")));
	rTree.SetItemData(m_hRootItem, TVI_DATA_FOLDER);

	CString sType, sName, sPrevType;
	HTREEITEM hTypeItem = NULL;
	int iImage = 0;
	for (int i = 0; i < m_pDoc->m_sTypes.GetSize(); i++)
	{
		sType = m_pDoc->m_sTypes[i];
		sName = m_pDoc->m_sNames[i];
		if (sType != sPrevType)
		{
			sPrevType = sType;
			GetTypeOutput(sType, iImage);

			hTypeItem = rTree.InsertItem(sType, m_hRootItem);
			rTree.SetItemData(hTypeItem, TVI_DATA_FOLDER);
		}

		GetNameOutput(sName, m_pDoc->m_nLangs[i]);

		ASSERT(hTypeItem);
		HTREEITEM hResItem = rTree.InsertItem(sName, iImage, iImage, hTypeItem);
		rTree.SetItemData(hResItem, (DWORD)i);
	}

	rTree.Expand(m_hRootItem, TVE_EXPAND);
	rTree.SortChildren(m_hRootItem);
}

void CResLibView::GetTypeOutput(CString& sType, int& iImage)
{
	// format output a little bit: incomplete (see WinUser.h)
	switch (COXResourceFile::OXResCStringToInt(sType))
	{
	case (DWORD)RT_CURSOR:		sType = _T("Cursor (hardware-dependent)");
		iImage = 3;  break;
	case (DWORD)RT_BITMAP:		sType = _T("Bitmap");
		iImage = 4;  break;
	case (DWORD)RT_ICON:		sType = _T("Icon (hardware-dependent)");
		iImage = 5;  break;
	case (DWORD)RT_MENU:		sType = _T("Menu");
		iImage = 6;  break;
	case (DWORD)RT_DIALOG:		sType = _T("Dialog");
		iImage = 7;  break;
	case (DWORD)RT_STRING:		sType = _T("String Table");
		iImage = 8;  break;
	case (DWORD)RT_ACCELERATOR:	sType = _T("Accelerator");
		iImage = 9;	 break;
	case (DWORD)RT_RCDATA:		sType = _T("Raw Data");
		iImage = 2;	 break;
	case (DWORD)RT_VERSION:		sType = _T("Version");
		iImage = 10; break;
	case (DWORD)RT_TOOLBAR:		sType = _T("Toolbar");
		iImage = 11; break;
	case (DWORD)RT_GROUP_CURSOR:sType = _T("Cursor (hardware-independent)");
		iImage = 3;  break;
	case (DWORD)RT_GROUP_ICON:	sType = _T("Icon (hardware-independent)");
		iImage = 5;  break;
	case 0: /* string */		sType = CString("\"") + sType + _T("\"");
	default: iImage = 2;
	}
}

void CResLibView::GetNameOutput(CString& sName, WORD nLang)
{
	if (COXResourceFile::OXResCStringToInt(sName) == 0)
		sName = CString("\"") + sName + _T("\"");

	if (nLang != MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL) && 
		nLang != MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) &&
		nLang != MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT) &&
		nLang != MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))
	{
		CString sLang;
		sLang.Format(_T(" (LangID: %d)"), nLang);
		sName += sLang;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CResLibView diagnostics

#ifdef _DEBUG
void CResLibView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CResLibView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CResLibDoc* CResLibView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResLibDoc)));
	return (CResLibDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResLibView message handlers

void CResLibView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CTreeCtrl& rTree = GetTreeCtrl();
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	int iImage = ((pNMTreeView->itemNew.state & TVIS_EXPANDED) == TVIS_EXPANDED) ? 1 : 0;
	rTree.SetItemImage(hItem, iImage, iImage);
	rTree.SortChildren(hItem);

	*pResult = 0;
}

void CResLibView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UNREFERENCED_PARAMETER(pNMHDR);
	CTreeCtrl& rTree = GetTreeCtrl();
	CPoint pt; GetCursorPos(&pt); ScreenToClient(&pt); UINT nFlag;
	HTREEITEM hItem = rTree.HitTest(pt, &nFlag);
	if (hItem == NULL) return;

	DWORD nIndex = rTree.GetItemData(hItem);

	if (nIndex != TVI_DATA_FOLDER)
	{
		CWaitCursor wait;
		// When dbl-click on a resource that was pasted from a previous copy,
		// we need to fetch the temporary COXResourceFile we created during pasting
		// (those we let m_pResLib handle their destruction in OnEditPaste()).
		COXResourceFile* pResFile = m_pResLib->GetOpenedResFile(m_pDoc->m_sTypes[nIndex], 
			m_pDoc->m_sNames[nIndex], m_pDoc->m_nLangs[nIndex]);
		BOOL bNeedDelete = FALSE; // if it was pasted and managed by the library

		if(pResFile == NULL) // not those pasted items
		{
			pResFile = new COXResourceFile;
			if (!pResFile->Open(CFile::modeReadWrite, m_pResLib, FALSE, m_pDoc->m_sTypes[nIndex], 
				m_pDoc->m_sNames[nIndex], m_pDoc->m_nLangs[nIndex]))
			{
				delete pResFile;
				pResFile = NULL;
				AfxMessageBox(_T("Failed to open the specified resource."));
			}
			else
				// in this demo, the dlg won't edit the file, otherwise, we can leave an
				// edited file without deleting it (but we have to specify AutoDeleteByLib
				// in Open() above), and delete unchanged file (it's ok even if it's set
				// bAutoDeleteByLib)
				bNeedDelete = TRUE;
		}

		if(pResFile)
		{
			CDlgResEdit dlg(pResFile, this);
			dlg.DoModal();
			// this dlg can not really be used to edit binary data directly for simplicity
			// of this demo program; for people who have interest in extending the 
			// functionality of this dialog, please refer to Developer Studio's editor as
			// a good example (to view it, right click on a resource in your resource view,
			// and choose "Open Binary Data")
			// should we have edited the resource, we may have written something like:
			// if(dlg.DoModal() == IDOK) dlg.m_ResFile.Flush();
		}

		if (bNeedDelete)
		{
			pResFile->Abort(); // destructor will call Flush(), which is not necessary here
			delete pResFile;
		}
	}

	*pResult = 0;
}

int CResLibView::GetSelectedResIndex()
{
	CTreeCtrl& rTree = GetTreeCtrl();
	HTREEITEM hItem = rTree.GetSelectedItem();
	if (hItem)
	{
		DWORD nIndex = rTree.GetItemData(hItem);
		if (nIndex != TVI_DATA_FOLDER) return (int)nIndex;
	}
	return -1; // if folder was selected
}

void CResLibView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pResLib && m_bModifiable && GetSelectedResIndex() != -1);	
}

void CResLibView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetSelectedResIndex() != -1);	
}

void CResLibView::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pResLib && m_bModifiable && GetSelectedResIndex() != -1);	
}

void CResLibView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	COleDataObject oleObj;
	pCmdUI->Enable(m_pResLib && m_bModifiable && oleObj.AttachClipboard() &&
		oleObj.IsDataAvailable(m_nClipFormat));
}

void CResLibView::OnEditCut() 
{
	OnEditCopy();
	OnEditClear();
}

void CResLibView::OnEditClear() 
{
	CTreeCtrl& rTree = GetTreeCtrl();
	HTREEITEM hItem = rTree.GetSelectedItem();
	if (hItem == NULL) return;

	DWORD nIndex = rTree.GetItemData(hItem);
	if (nIndex == TVI_DATA_FOLDER) return;

	m_pResLib->DeleteResource(m_pDoc->m_sTypes[nIndex], m_pDoc->m_sNames[nIndex],
		m_pDoc->m_nLangs[nIndex]);

	// ... we set its name to empty to indicate it's deleted, useful when checking
	// if a type folder has been added
	m_pDoc->m_sNames[nIndex].Empty();
	m_pDoc->SetModifiedFlag();

	HTREEITEM hTypeItem = rTree.GetParentItem(hItem);
	ASSERT(hTypeItem);
	rTree.DeleteItem(hItem);
	if (rTree.GetChildItem(hTypeItem) == NULL)
		rTree.DeleteItem(hTypeItem);
}

void CResLibView::OnEditCopy() 
{
	int nIndex = GetSelectedResIndex();
	if (nIndex == -1) return;

	COXResourceFile resFile;
	if (!resFile.Open(CFile::modeRead, m_pResLib, FALSE, m_pDoc->m_sTypes[nIndex], 
		m_pDoc->m_sNames[nIndex], m_pDoc->m_nLangs[nIndex]))
	{
		TRACE0("Failed to open the specified resource to copy.\n");
		return;
	}

	// we definitely want to include tags (type, name and lang) in the hGlobal
	HGLOBAL hGlobal = resFile.DetachEx();
	if (hGlobal == NULL)
	{
		TRACE0("Failed to load data from the specified resource to copy.\n");
		return;
	}

	COleDataSource* pOleSource = new COleDataSource;
	pOleSource->CacheGlobalData(m_nClipFormat, hGlobal);
	pOleSource->SetClipboard();
}

void CResLibView::OnEditPaste() 
{
	COleDataObject oleObj;
	if (!oleObj.AttachClipboard() || !oleObj.IsDataAvailable(m_nClipFormat))
		return;

	HGLOBAL hGlobal = oleObj.GetGlobalData(m_nClipFormat);
	if (hGlobal == NULL)
		return;

	COXResourceFile* pResFile = new COXResourceFile;
	if(!pResFile->SetHandleEx(hGlobal))
	{
		TRACE0("Failed to load resource from clipboard.\n");
		delete pResFile;
		return;
	}

	// 1st TRUE to make sure when m_pResLib goes out of scope, pResFile will be deleted;
	// 2nd TRUE to make sure we are adding, not replacing
	pResFile->SetResourceLibrary(m_pResLib, TRUE, TRUE);
	// you could ask user to input a unique name here, but
	// the default implementation is quite exhaustive already

	m_pDoc->SetModifiedFlag();

	BOOL bTypeExist = FALSE;
	UINT i = 0;
	for (i = 0; i < (UINT)m_pDoc->m_sTypes.GetSize(); i++)
	{
		if (!m_pDoc->m_sNames[i].IsEmpty() && 
			m_pDoc->m_sTypes[i] == pResFile->GetResType())
		{
			bTypeExist = TRUE;
			break;
		}
	}

	DWORD nIndexNewItem = (DWORD)m_pDoc->m_sTypes.Add(pResFile->GetResType());
	m_pDoc->m_sNames.Add(pResFile->GetResName());
	m_pDoc->m_nLangs.Add(pResFile->GetResLanguage());

	CString sType, sName; int iImage;
	sType = pResFile->GetResType();
	sName = pResFile->GetResName();
	GetTypeOutput(sType, iImage);
	GetNameOutput(sName, pResFile->GetResLanguage());

	CTreeCtrl& rTree = GetTreeCtrl();
	HTREEITEM hTypeItem = NULL;
	if (bTypeExist)
	{
		hTypeItem = FindTypeHItem(i);
	}
	else
	{
		hTypeItem = rTree.InsertItem(sType, m_hRootItem);
		rTree.SetItemData(hTypeItem, TVI_DATA_FOLDER);
	}

	ASSERT(hTypeItem);
	HTREEITEM hResItem = rTree.InsertItem(sName, iImage, iImage, hTypeItem);
	rTree.SortChildren(hTypeItem);
	rTree.EnsureVisible(hResItem);
	rTree.SelectItem(hResItem);
	rTree.SetItemData(hResItem, (DWORD)nIndexNewItem);
}

HTREEITEM CResLibView::FindTypeHItem(UINT nIndex)
{
	CTreeCtrl& rTree = GetTreeCtrl();

	for (HTREEITEM hTypeIter = rTree.GetChildItem(m_hRootItem); hTypeIter; 
		hTypeIter = rTree.GetNextSiblingItem(hTypeIter))
	{
		for (HTREEITEM hResIter = rTree.GetChildItem(hTypeIter); hResIter;
			hResIter = rTree.GetNextSiblingItem(hResIter))
		{
			if (rTree.GetItemData(hResIter) == nIndex)
				return hTypeIter;
		}
	}

	return NULL;
}

