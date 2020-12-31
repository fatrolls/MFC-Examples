#pragma once


// CConfigHeaderCtrl

class CConfigHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CConfigHeaderCtrl)

public:
	CConfigHeaderCtrl();
	virtual ~CConfigHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg LRESULT OnLayout(WPARAM wParam, LPARAM lParam);
};


