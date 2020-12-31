
#if !defined(AFX_COOLSLIDERDLG_H__9BFCB2A9_26CD_44C4_8F48_AF9DFB015887__INCLUDED_)
#define AFX_COOLSLIDERDLG_H__9BFCB2A9_26CD_44C4_8F48_AF9DFB015887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitSlider.h"

class CCoolSliderDlg : public CDialog
{
public:
	CCoolSliderDlg(CWnd* pParent = NULL);
	~CCoolSliderDlg();
public:	
	//{{AFX_DATA(CCoolSliderDlg)
	enum { IDD = IDD_COOLSLIDER_DIALOG };
	CBitSlider		m_ctlVert2;
	CBitSlider		m_ctlVert1;
	CBitSlider		m_ctlShare3;
	CBitSlider		m_ctlShare2;
	CBitSlider		m_ctlShare1;
	CBitSlider		m_ctlSlider;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CCoolSliderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CCoolSliderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnReleasedcaptureCoolSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HCURSOR			GetSysHandCursor();

	void			BuildCoolSlider();
	void			BuildShareSlider();

	void			BuildVerticalSlider();
private:
	HICON			m_hIcon;
	HCURSOR			m_hHandCur;

	CBitItem	*	m_lpThumb;
	CBitItem	*	m_lpActive;
	CBitItem	*	m_lpNormal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLSLIDERDLG_H__9BFCB2A9_26CD_44C4_8F48_AF9DFB015887__INCLUDED_)
