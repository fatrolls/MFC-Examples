
#ifndef __LISTCTLX_H__
#define __LISTCTLX_H__

#ifdef _AFX_NO_AFXCMN_SUPPORT
	#error Windows Common Control classes not supported in this library variant.
#endif

#ifndef __AFXWIN_H__
	#include <afxwin.h>
#endif

class CListItem;
class CListCtrlEx;

/////////////////////////////////////////////////////////////////////////////
// CListItem

typedef LV_ITEM* PLV_ITEM;

class CListItem
{
	// Attributes
protected:
	LV_ITEM	m_ListItem;
	CListCtrlEx	*m_pList;
	CString m_szText;

	// Implementation
protected:
	void Copy(PLV_ITEM pListItem);
	// Operation
public:
	CListItem();
	CListItem(PLV_ITEM pListItem, CListCtrlEx* pList);
	CListItem(const CListItem& posSrc);
	~CListItem();

	const CListItem& operator =(const CListItem& posSrc);
	operator PLV_ITEM();

	CListItem GetItem(int nItem = 0,int nSubItem = 0);
	BOOL SetItem();
	int InsertItem();

	// properties
	UINT &State();
	int &Image();
	LPCSTR Text();
	LPCSTR Text(LPCSTR text);

};

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx


class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)
// Construction
public:
	CListCtrlEx();

// Attributes
protected:

public:

public:
	CImageList* SetImageList(CImageList* pImageList, int nImageListType = TVSIL_NORMAL);

	BOOL AddColumn(
		LPCTSTR strItem,int nItem,int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT);

	BOOL AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);

	CListItem GetItem(int nItem = 0,int nSubItem = 0);
	
	int SelItemRange(BOOL bSelect, int nFirstItem, int nLastItem);

	void SetExtendedStyles(DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | /*LVS_EX_SUBITEMIMAGES |*/
						LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT);
// Operations
public:

// Overrides

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
protected:

public:
	virtual ~CListCtrlEx();


	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


#include "ListCtrlEx.inl"

#endif 
