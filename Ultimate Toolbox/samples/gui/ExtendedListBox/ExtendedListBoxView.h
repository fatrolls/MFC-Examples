// ExtendedListBoxView.h : interface of the CExtendedListBoxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXTENDEDLISTBOXVIEW_H__21FF47ED_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
#define AFX_EXTENDEDLISTBOXVIEW_H__21FF47ED_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXColorPickerButton.h"
#include "OXFontPickerButton.h"
#include "OXSeparator.h"
#include "OXFontComboBox.h"


class CExtendedListBoxView : public CFormView
{
protected: // create from serialization only
	CExtendedListBoxView();
	DECLARE_DYNCREATE(CExtendedListBoxView)

public:
	//{{AFX_DATA(CExtendedListBoxView)
	enum { IDD = IDD_EXTENDEDLISTBOX_FORM };
	CSpinButtonCtrl	m_spinMaxNumMRUItems;
	CSpinButtonCtrl	m_spinFontHeight;
	COXFontListBox	m_fontListBox;
	COXFontComboBox	m_fontComboBox;
	COXSeparator	m_sepFontListAndCombo;
	CSpinButtonCtrl	m_spinIndent;
	COXSeparator	m_sepListBox;
	COXSeparator	m_sepItemProperties;
	COXListBoxEx	m_listBoxEx;
	COXColorPickerButton	m_btnListBoxBkColor;
	COXFontPickerButton	m_btnItemFont;
	COXColorPickerButton	m_btnItemBkColor;
	BOOL	m_bHighlightOnlyText;
	UINT	m_nIndent;
	UINT	m_nFontHeight;
	UINT	m_nMaxNumMRUItems;
	//}}AFX_DATA
	COLORREF m_clrListBoxBack;
	COLORREF m_clrItemBack;
	COLORREF m_clrItemText;
	CFont m_fontItem;

protected:
	CArray<CFont*,CFont*> m_arrFonts;

// Attributes
public:
	CExtendedListBoxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendedListBoxView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendedListBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int AddSimpsonsItem(LPCTSTR lpszText, int nImageIndex, int nIndent, 
		COLORREF clrText, LPCTSTR lpszTooltipText, CFont* pFont);

// Generated message map functions
protected:
	//{{AFX_MSG(CExtendedListBoxView)
	afx_msg void OnSelchangeListboxEx();
	afx_msg void OnButtonItemBkColor();
	afx_msg void OnButtonItemFont();
	afx_msg void OnButtonListboxBkColor();
	afx_msg void OnCheckHighlightOnlyText();
	afx_msg void OnChangeEditIndent();
	afx_msg void OnChangeEditFontHeight();
	afx_msg void OnChangeEditMaxnumMruItems();
	afx_msg void OnSelchangeFontCombo();
	afx_msg void OnSelchangeFontListbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ExtendedListBoxView.cpp
inline CExtendedListBoxDoc* CExtendedListBoxView::GetDocument()
   { return (CExtendedListBoxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDLISTBOXVIEW_H__21FF47ED_4AC4_11D3_90BA_9FB68D1A0F05__INCLUDED_)
