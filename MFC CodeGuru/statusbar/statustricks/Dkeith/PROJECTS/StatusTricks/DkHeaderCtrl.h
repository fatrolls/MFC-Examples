#if !defined(AFX_DKHEADERCTRL_H__9ECC7528_51CD_11D1_B853_0020AF6F26D6__INCLUDED_)
#define AFX_DKHEADERCTRL_H__9ECC7528_51CD_11D1_B853_0020AF6F26D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DkHeaderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDkHeaderCtrl window

class CDkHeaderCtrl : public CHeaderCtrl
{
protected:
	//{{AFX_MSG(CDkHeaderCtrl)
	afx_msg void	 OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	 OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	 OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void	 OnBeginTrack(NMHDR *pNotify, LRESULT *result);
	afx_msg void	 OnEndTrack(NMHDR *pNotify, LRESULT *result);

protected:
	CRect			 m_rDragItem;		// rect binding the header being dragged
	CPoint			 m_ptLastDrag;		// position of the mouse at the last drag
	int				 m_nDragItem;		// index of item being dragged
	BOOL			 m_bIsTracking;		// indicates if user is tracking a header

public:
					 CDkHeaderCtrl();
	virtual			~CDkHeaderCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDkHeaderCtrl)
	//}}AFX_VIRTUAL

public:

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DKHEADERCTRL_H__9ECC7528_51CD_11D1_B853_0020AF6F26D6__INCLUDED_)
