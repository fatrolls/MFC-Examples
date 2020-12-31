// BCGToolbarComboBoxButton.h: interface for the CBCGToolbarComboBoxButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)
#define AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BCGToolbarButton.h"

class AFX_EXT_CLASS CBCGToolbarComboBoxButton : public CBCGToolbarButton  
{
	DECLARE_SERIAL(CBCGToolbarComboBoxButton)

public:
	CBCGToolbarComboBoxButton();
	CBCGToolbarComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0);
	virtual ~CBCGToolbarComboBoxButton();

// Operations:
	int AddItem (LPCTSTR lpszItem);
	int GetCount () const;
	LPCTSTR GetItem (int iIndex = -1);
	void RemoveAllItems ();

// Overrides:
	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,
						BOOL bHighlight = FALSE);
	virtual void CopyFrom (const CBCGToolbarButton& src);
	virtual void Serialize (CArchive& ar);
	virtual int  OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz);
	virtual BOOL OnClick (CWnd* pWnd);
	virtual void OnChangeParentWnd (CWnd* pWndParent);
	virtual void OnMove ();
	virtual void OnSize (int iSize);
	virtual HWND GetHwnd ()
	{	
		return m_wndCombo.GetSafeHwnd ();
	}
	virtual BOOL NotifyCommand (int iNotifyCode);
	
	virtual BOOL CanBeStretched () const
	{	
		return TRUE;	
	}
	virtual void OnAddToCustomizePage ();
	virtual HBRUSH OnCtlColor(CDC* pDC, UINT nCtlColor);

protected:
	void Initialize ();
	void AdjustRect ();

// Attributes:
protected:
	DWORD		m_dwStyle;
	CComboBox	m_wndCombo;

	CFont		m_Font;
	CStringList	m_lstItems;

	int			m_iWidth;
};

#endif // !defined(AFX_BCGTOOLBARCOMBOBOXBUTTON_H__D5B381B4_CC65_11D1_A648_00A0C93A70EC__INCLUDED_)
