
#define CTLEXT_INLINE inline


/////////////////////////////////////////////////////////////////////////////
// CListItem CTLEXT_INLINE functions

CTLEXT_INLINE CListItem::CListItem() : m_pList(NULL)
	{ }
CTLEXT_INLINE CListItem::CListItem(PLV_ITEM pListItem, CListCtrlEx* pList) : m_pList(pList)
	{ Copy(pListItem); }
CTLEXT_INLINE CListItem::CListItem(const CListItem& posSrc)
	{ *this = posSrc; }
CTLEXT_INLINE CListItem::~CListItem()
	{ }
CTLEXT_INLINE CListItem::operator PLV_ITEM()
	{ return &m_ListItem; }

CTLEXT_INLINE CListItem CListItem::GetItem(int nItem,int nSubItem)
	{ return m_pList->GetItem(nItem,nSubItem); }

CTLEXT_INLINE BOOL CListItem::SetItem()
	{ return m_pList->SetItem(*this); }

CTLEXT_INLINE int CListItem::InsertItem()
	{ return m_pList->InsertItem(*this); }

CTLEXT_INLINE UINT &CListItem::State()
	{ return m_ListItem.state; }

CTLEXT_INLINE int &CListItem::Image()
	{ return m_ListItem.iImage; }

CTLEXT_INLINE LPCSTR CListItem::Text()
	{ return m_ListItem.pszText; }



/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx CTLEXT_INLINE functions

CTLEXT_INLINE CImageList* CListCtrlEx::SetImageList(CImageList* pImageList, int nImageListType)
 { return CListCtrl::SetImageList(pImageList,nImageListType); }
