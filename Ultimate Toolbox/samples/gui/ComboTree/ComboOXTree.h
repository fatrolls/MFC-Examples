// ComboOXTree.h: interface for the CComboOXTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOOXTREE_H__35306228_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
#define AFX_COMBOOXTREE_H__35306228_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXTreeCtrl.h"
#include "OXComboPickerCtrl.h"

class CComboOXTree : public COXTreeCtrl , public COXComboDropDown 
{
public:
	CComboOXTree();
	virtual ~CComboOXTree();
protected:
	COXDropDownContainer m_container;
	COXComboPickerCtrl* m_pCombo;

	// helper rectangle for flicker-free control
	CRect m_rectValid;

	// last selected item
	HTREEITEM m_hLastSelectedItem;


public:
	void ForwardMouseMessage(UINT message, UINT nFlags, CPoint point);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnLButtonDblClk( UINT nFlags, CPoint point );


public:
	virtual void SetOwnerCombo(COXComboPickerCtrl* pCombo) { m_pCombo=pCombo; }
	inline COXComboPickerCtrl* GetOwnerCombo() const { return m_pCombo; }

	virtual BOOL CanSelectItem(HTREEITEM hItem);

	virtual COXDropDownContainer* GetContainer() { return &m_container; }
	virtual CWnd* GetWindow() { return this; }

	virtual void ShowDropDown(BOOL bShowIt=TRUE);

	virtual void GetDroppedControlRect(LPRECT lprect) const;
	virtual BOOL GetDroppedState() const;
	virtual CRect GetBestRect();
	virtual int GetItemHeight();

	virtual BOOL IsThereSelectedItem();
	virtual CImageList* GetSelectedItemImage();
	virtual CString GetSelectedItemText();
	virtual CFont* GetSelectedItemFont();
	virtual COLORREF GetSelectedItemTextColor();


	virtual void ResetContent();

	virtual BOOL NeedFocus() const { return TRUE; }

	virtual void OnAttachToComboPicker();
	virtual void OnChangeMinMaxWidthHeight();
	virtual void OnChangeOwnerComboSize();

protected:
	virtual void AutoResize();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	virtual void OnKillFocus(CWnd* pNewWnd);
    virtual void OnLButtonDown(UINT nFlags, CPoint point);
    virtual void OnMouseMove(UINT nFlags, CPoint point);
    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // !defined(AFX_COMBOOXTREE_H__35306228_1C37_11D4_AD1F_0050BAAB46B1__INCLUDED_)
