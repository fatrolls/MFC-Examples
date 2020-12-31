#pragma once
// popupscrolllist.h : header file
//

#include "CellDropDown.h"
#include "CellComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CPopUpScrollList window
#include "ListCtrlCellWnd.h"

#define EMPTY_BOX_HEIGHT			::GetSystemMetrics(SM_CYVTHUMB)

class CPopUpScrollList : public CListCtrlCellWnd
{
	friend class CCellComboBox;
// Construction
private:
	CPopUpScrollList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopUpScrollList)
	//}}AFX_VIRTUAL

// Implementation
private:
	virtual ~CPopUpScrollList();
	virtual void Create(HWND hParentWnd, CCellDropDown *pCellDropDown);
	virtual void OnEnter();
	void OnOpenDropDown();

private:
	inline BOOL ShowScrollBar() const {return m_pCellComboBox->m_lDisplayedRows < m_pCellComboBox->m_astrItems.GetSize();}
	void ResetScrollInfo();

protected:
	CCellComboBox	*m_pCellComboBox;
	LONG			m_lFirstPos,
					m_lSelectedItem;
	CScrollBar		m_ScrollBar;
	BOOL			m_bActivated;
	// Generated message map functions
protected:
	void SelectAndClose();
	//{{AFX_MSG(CPopUpScrollList)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
