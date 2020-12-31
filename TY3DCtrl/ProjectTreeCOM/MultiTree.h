/////////////////////////////////////////////////////////////////////////////
// 
// CMultiTree - A WTL tree control with Windows Vista style item selection.
//
// Revision:      1.2
// Last modified: 5th April 2006
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include <atlctl.h>
#include <atlwin.h>
#include <atlstr.h>
#include "wtl/atlapp.h"
#include "wtl/atlgdi.h"
#include "wtl/atlctrls.h"
#include "wtl/atlframe.h"
#include "wtl/atltheme.h"
#include "wtl/atlcrack.h"
#include "wtl/atlmisc.h"
#include "DragDropImpl.h"
using namespace ATL;

#define _WTL_NO_CSTRING
//_WTL_USE_CSTRING
#define END_MSG_MAP_EX	END_MSG_MAP
//#ifdef _DEBUG
//#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
//#endif
#define RECT_BORDER	10
class CMultiTree;
class CTreeDropTarget : public CIDropTarget
{
public:
	CTreeDropTarget(HWND hTargetWnd, CMultiTree* pTreeCtrl);
	
	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect);

	virtual HRESULT STDMETHODCALLTYPE DragOver( 
        /* [in] */ DWORD grfKeyState,
        /* [in] */ POINTL pt,
        /* [out][in] */ DWORD __RPC_FAR *pdwEffect);
	virtual HRESULT STDMETHODCALLTYPE DragLeave(void);
private:
		CMultiTree *m_pSourceTreeCtrl;
};

class CMultiTree : public CWindowImpl< CMultiTree, WTL::CTreeViewCtrl >
				  //,public WTL::CCustomDraw< CMultiTree >
				  //,public WTL::CDoubleBufferImpl< CMultiTree >
{

public:
    DECLARE_WND_SUPERCLASS(_T("MultiTree"), GetWndClassName())
	CMultiTree();
	
	~CMultiTree();

protected:
	BOOL m_bShowThemed;
	BOOL m_bMultipleSelect;
	BOOL m_bCtrlKey;
	BOOL m_bShiftKey;
	HTREEITEM m_hFirstSelected;
	
	COLORREF m_rgbBackground;
	COLORREF m_rgbItemText;
	COLORREF m_rgbSelectOuter;
	COLORREF m_rgbSelectInner;
	COLORREF m_rgbSelectTop;
	COLORREF m_rgbSelectBottom;
	COLORREF m_rgbNoFocusTop;
	COLORREF m_rgbNoFocusBottom;
	COLORREF m_rgbNoFocusOuter;
	COLORREF m_rgbNoFocusInner;
	UINT m_uFlags;
	WTL::CFont m_fntTreeFont;
    CImageList m_ilItemImages;
    CImageList m_ilItemStates;
	CIDropTarget* m_pDropTarget;
    BOOL        m_bEnableDrag;
public:
    BOOL SetFont(LOGFONT ft);
    void EnableDrop(BOOL bEanble = TRUE){m_bEnableDrag = bEanble;}
	BOOL Initialise();

	//BOOL SubclassWindow( HWND hWnd );
	
	//void ShowThemed( BOOL bShowThemed = TRUE );
	
	//void SetMultipleSelect( BOOL bMultipleSelect );
	
	//BOOL SelectItem( HTREEITEM hItem );

	//void GetSelectedItems( CSimpleArray < HTREEITEM >& aSelectedItems );
		
	//HTREEITEM GetSelectedItems( HTREEITEM hItem, CSimpleArray < HTREEITEM >& aSelectedItems );

	//void ResetSelected( HTREEITEM hItem );

	//BOOL SelectItems( HTREEITEM hItemFrom, HTREEITEM hItemTo );
	
	BOOL LoadSettings();
	
	BEGIN_MSG_MAP_EX(CMultiTree)

        MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		//MSG_WM_SETFOCUS(OnSetFocus)
		//MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_KEYDOWN(OnKeyDown)
		//MSG_WM_SETTINGCHANGE(OnSettingsChange)
		//MSG_WM_SYSCOLORCHANGE(OnSettingsChange)
		//MSG_WM_FONTCHANGE(OnSettingsChange)
		//MSG_WM_THEMECHANGED(OnSettingsChange)
        //MSG_WM_PAINT(OnPaint)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_CUSTOMDRAW, OnCustomDraw)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_CLICK, OnStateIconClick)
		//REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_DBLCLK, OnDblClick)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_KEYDOWN, OnKeydown)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_BEGINDRAG, OnBeginDrag)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		//CHAIN_MSG_MAP_ALT(CCustomDraw< CMultiTree >, 1)
		//CHAIN_MSG_MAP(CDoubleBufferImpl< CMultiTree >)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP_EX()
    LRESULT OnCustomDraw(LPNMHDR pNMHDR);

	LRESULT OnStateIconClick(LPNMHDR pNMHDR);
    LRESULT OnKeydown(LPNMHDR pNMHDR);
	int OnCreate( LPCREATESTRUCT lpCreateStruct );
	
	void OnSettingsChange( UINT nFlags, LPCTSTR lpszSection );
	
	void OnSettingsChange();
	
	void OnSetFocus( HWND hOldWnd );

	void OnKillFocus( HWND hNewWnd );

	void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );
	
	LRESULT OnBeginDrag( LPNMHDR lpNMHDR );
	bool InitDragDrop();
    virtual BOOL DealDragTree(HTREEITEM& hBranch, HTREEITEM& hNewParent,HTREEITEM& hAfter){return TRUE;}
    virtual void OnDragComplete(HTREEITEM hItem){}
    virtual void OnStateChange(HTREEITEM hItem){}
	//LRESULT OnDblClick( LPNMHDR lpNMHDR );
	
	void OnLButtonDown( UINT nFlags, WTL::CPoint point );

	void OnLButtonUp( UINT nFlags, WTL::CPoint point );
	virtual void OnItemDraw(WTL::CDCHandle pDC, HTREEITEM hItem){}
    //void OnPaint(WTL::CDCHandle dc);
	//void DoPaint( WTL::CDCHandle dcPaint );
	
	//DWORD OnPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw );
	
	//DWORD OnItemPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw );
	
	//virtual DWORD OnItemPostPaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw );
    //====================================//
    bool IsFullCheck(HTREEITEM hItem);
    bool IsCheck(HTREEITEM hItem);
    void CheckItem(HTREEITEM hItem,BOOL bCheck);
    void TravelSiblingAndParent(HTREEITEM hItem, int nState);
    BOOL GetItemBold(HTREEITEM hItem);
    
    BOOL SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch);

    void TravelChild(HTREEITEM hItem, int nState);
    HTREEITEM MoveItem(HTREEITEM hItem, HTREEITEM hNewParent, HTREEITEM hAfter = TVI_LAST);
    HTREEITEM MoveBranch(HTREEITEM hBranch, HTREEITEM hNewParent, HTREEITEM hAfter = TVI_LAST);

    void DeleteBranch(HTREEITEM hItem);

	LRESULT OnDestroy( );
};
