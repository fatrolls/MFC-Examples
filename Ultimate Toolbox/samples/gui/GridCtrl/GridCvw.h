// GridCvw.h : interface of the CGridCtrlView class
//
/////////////////////////////////////////////////////////////////////////////

#include "OxGridList.h"
#include "OXGridEdit.h"
//#include "OXBitmapButton.h"

class CGridCtrlView : public CFormView
{
protected: // create from serialization only
	CGridCtrlView();
	DECLARE_DYNCREATE(CGridCtrlView)

public:
	//{{AFX_DATA(CGridCtrlView)
	enum { IDD = IDD_GRIDCTRL_FORM };
//	COXBitmapButton	m_btnCustomize;
	CSpinButtonCtrl	m_wndImageColumnSpin;
	CSpinButtonCtrl	m_wndNumRowsSpin;
	COXGridList	m_GridCtrl;
	BOOL		m_bGridLines;
	BOOL		m_bEditCheck;
	BOOL		m_bMulti;
	int			m_nRegion;
	BOOL		m_bSort;
	int			m_iNumberOfRows;
	int		m_iImageColumn;
	BOOL	m_bCheckable;
	BOOL	m_bAutoEdit;
	BOOL	m_bShowSel;
	BOOL	m_bHorizontal;
	BOOL	m_bVertical;
	BOOL	m_bResize;
	//}}AFX_DATA

protected:
	BOOL m_bInitialized;
	CImageList m_ImageSmall;
	COXGridEdit m_gridEdit;
	CImageList m_stateImages;

// Attributes
public:
	CGridCtrlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridCtrlView)
	afx_msg void OnSetFont();
	afx_msg void OnResetFont();
	afx_msg void OnColorButton();
	afx_msg void OnClear();
	afx_msg void OnInsert();
	afx_msg void OnSortable();
	afx_msg void OnMulcheck();
	afx_msg void OnEditcheck();
	afx_msg void OnGridLines();
	afx_msg void OnCheckable();
	afx_msg void OnTraceNotification(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAutoEdit();
	afx_msg void OnShowSelection();
	afx_msg void OnChangeImageColumn();
	afx_msg void OnHorizontalGrid();
	afx_msg void OnVerticalGrid();
	afx_msg void OnGridcolresize();
	afx_msg void OnRadiocenter();
	afx_msg void OnRadioleft();
	afx_msg void OnRadioright();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GridCvw.cpp
inline CGridCtrlDoc* CGridCtrlView::GetDocument()
   { return (CGridCtrlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
