// MyListCtrlDlg.h : header file
//

#if !defined(AFX_MYLISTCTRLDLG_H__92CE8736_DD8F_11D8_B14D_002018574596__INCLUDED_)
#define AFX_MYLISTCTRLDLG_H__92CE8736_DD8F_11D8_B14D_002018574596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrlDlg dialog

#include <vector>
using namespace std;

#include "quicklist.h"
#include "randomtext.h"

#ifdef USEXPTHEMES
#include "theme.h"
#endif

const int IMAGECOUNT = 4;

class CSampleData
{
public:

	CSampleData()
	{
		m_name = RandomText::GetName();
		m_slogan = RandomText::GetSlogan();
		m_result = rand()%101;

		for(int i=0; i<3; i++)
		{
			m_image[i] = rand()%IMAGECOUNT;
			m_check[i] = (rand()%2==0);
		}

		m_bold[0] =m_bold[1] =m_bold[2] = (rand()%2==0);
		m_italic[0] = m_italic[1] = m_italic[2] = (rand()%2==0);

	}

	CString m_name;
	CString m_slogan;
	int m_result;
	int m_image[3];
	bool m_check[3];
	bool m_bold[3];
	bool m_italic[3];
};

class CMyListCtrlDlg : public CDialog
{

// Construction
public:
	void UpdateList();
	CMyListCtrlDlg(CWnd* pParent = NULL);	// standard constructor
	CImageList m_imgList;
	CImageList m_imgLargeList;

	CImageList* m_DragImage;

	vector<CSampleData> m_data;

#ifdef USEXPTHEMES
	CTheme m_themeManager;
#endif

// Dialog Data
	//{{AFX_DATA(CMyListCtrlDlg)
	enum { IDD = IDD_MYLISTCTRL_DIALOG };
	CComboBox	m_keyFind;
	CComboBox	m_selImgList;
	CQuickList m_list;
	BOOL	m_fullrow;
	BOOL	m_image1;
	BOOL	m_image2;
	BOOL	m_image3;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	BOOL	m_progress;
	BOOL	m_winColors;
	BOOL	m_normalStyle;
	BOOL	m_noImgSel;
	BOOL	m_noCheckSel;
	BOOL	m_noSel1;
	BOOL	m_noSel2;
	BOOL	m_noSel3;
	int		m_progBorder;
	BOOL	m_grid;
	BOOL	m_columnNavigation;
	BOOL	m_editonenter;
	BOOL	m_editonf2;
	BOOL	m_editondblclick;
	BOOL	m_editonwriting;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	afx_msg LRESULT OnGetListItem(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnListClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNavigationTest(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHeaderRightClick(WPARAM wParam, LPARAM lParam);

	#ifdef	USEXPTHEMES
	afx_msg LRESULT OnThemeChanged(WPARAM, LPARAM);
	#endif

	virtual void OnSomeCheckbox(UINT nID);

	// Generated message map functions
	//{{AFX_MSG(CMyListCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckFullrow();
	afx_msg void OnButtonAddten();
	afx_msg void OnButtonClear();
	afx_msg void OnSelchangeComboImagelist();
	afx_msg void OnSelchangeComboKeyfind();
	afx_msg void OnOdfinditemList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonColors();
	afx_msg void OnSelchangeComboProgborder();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckGrid();
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnCheckColumnnavigation();
	afx_msg void OnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindragList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRdblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCheckEditonenter();
	afx_msg void OnCheckEditonf2();
	afx_msg void OnCheckEditondblclick();
	afx_msg void OnButtonFullredraw();
	afx_msg void OnHeadermenuColumn1();
	afx_msg void OnHeadermenuColumn2();
	afx_msg void OnHeadermenuColumn3();
	afx_msg void OnCheckEditonwriting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRLDLG_H__92CE8736_DD8F_11D8_B14D_002018574596__INCLUDED_)
