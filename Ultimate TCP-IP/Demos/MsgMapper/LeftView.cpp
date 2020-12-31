// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "MsgMapper.h"

#include "MsgMapperDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
END_MESSAGE_MAP()


// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

	// add buttons and lines
	cs.style |= TVS_HASLINES | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM hRoot = tree.InsertItem(_T("Message attributes"));

	HTREEITEM hHeaders = tree.InsertItem(_T("Message headers"), hRoot);
	HTREEITEM hAttachments = tree.InsertItem(_T("Attachment information"), hRoot);

	// grab ze doc
	CMsgMapperDoc *doc = GetDocument();

	// get standard headers
	
	int count = 0;
	HTREEITEM hTemp;
	_TCHAR strName[MAX_PATH+1];
	size_t size;
	int i = (int)(HeaderFieldID)UTM_MESSAGE_ID;
	for ( i; i < (int)(HeaderFieldID)UTM_CUSTOM_FIELD; ++i) {
		count = doc->m_message.GetHeaderCount((HeaderFieldID)i);
		if(count > 0) {
			doc->m_message.GetFieldName(strName, MAX_PATH, (HeaderFieldID)i, &size);
			hTemp = tree.InsertItem(strName, hHeaders, TVI_SORT);
			for(int index = 0; index < count; ++index) {
				char test[76];
				doc->m_message.DecodeHeader((HeaderFieldID)i, test);
				//if(test != NULL ) _asm int 3;
				doc->m_message.GetHeaderByType(strName, MAX_PATH, (HeaderFieldID)i, index, &size);
				tree.InsertItem(strName, hTemp);
			}
			tree.Expand(hTemp, TVE_EXPAND);
		}		
	}

	// now, get so called 'custom' headers
	// Multiline custom headers are returned concatenated, so we'll maintan a 
	// list to ensure we make only one call for each custom header name.
#if defined _UNICODE
	CUT_TStringList tsl;
#else
	CUT_StringList tsl;
#endif
	count = doc->m_message.GetHeaderCount(UTM_CUSTOM_FIELD);
	if(count > 0) {
		for (i = 0; i < count; ++i) {
			_TCHAR strCustomHeader[1024];
			char szCharSet[76];
			doc->m_message.GetCustomFieldName(strName, MAX_PATH, i, &size);
			if(!tsl.Exists(strName)) {
				tsl.AddString(strName);
				hTemp = tree.InsertItem(strName, hHeaders, TVI_SORT);
				doc->m_message.DecodeHeader(strName, szCharSet);
				doc->m_message.GetHeaderByName(strName, strCustomHeader, 1024);
				tree.InsertItem(strCustomHeader, hTemp);
				tree.Expand(hTemp, TVE_EXPAND);
			}
		}
	}
	tree.Expand(hRoot, TVE_EXPAND);

	/**/

	// ok, get some attachment info 
	count = doc->m_message.GetAttachmentNumber();
	if(count > 0) {
		tsl.ClearList();
		_TCHAR	strType[MAX_PATH];
		for (i = 0; i < count; ++i) {
			doc->m_message.GetAttachmentInfo(i,strName, MAX_PATH, strType, MAX_PATH, &tsl);
			tree.InsertItem(strName, hAttachments);
			tree.InsertItem(strType, hAttachments);
		}
		tree.Expand(hAttachments, TVE_EXPAND);
	}







}


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMsgMapperDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsgMapperDoc)));
	return (CMsgMapperDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeftView message handlers
