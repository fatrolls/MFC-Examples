// PopupBarDoc.h : interface of the CPopupBarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPUPBARDOC_H__95493CED_F252_11D1_B475_B0D808C10000__INCLUDED_)
#define AFX_POPUPBARDOC_H__95493CED_F252_11D1_B475_B0D808C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "BorderPickerCtrl.h"
#include "LineStylePickerCtrl.h"
#include "DashStylePickerCtrl.h"


class CPopupBarDoc : public CDocument
{
protected: // create from serialization only
	CPopupBarDoc();
	DECLARE_DYNCREATE(CPopupBarDoc)

// Attributes
public:

protected:
	COLORREF m_clrText;
	COLORREF m_clrFill;
	COLORREF m_clrBorder;

	int m_nBorderStyle;
	int m_nLineStyle;
	int m_nDashStyle;

// Operations
public:

	static COLORREF GetDefaultTextColor() { return RGB(0,0,128); }
	COLORREF GetTextColor() { return m_clrText; }
	void SetTextColor(COLORREF clrText) { m_clrText=clrText; SetModifiedFlag(TRUE); }

	static COLORREF GetDefaultFillColor() { return RGB(192,192,192); }
	COLORREF GetFillColor() { return m_clrFill; }
	void SetFillColor(COLORREF clrFill) { m_clrFill=clrFill; SetModifiedFlag(TRUE); }

	static COLORREF GetDefaultBorderColor() { return RGB(0,0,0); }
	COLORREF GetBorderColor() { return m_clrBorder; }
	void SetBorderColor(COLORREF clrBorder) { m_clrBorder=clrBorder; SetModifiedFlag(TRUE); }

	static int GetDefaultBorderStyle() { return ID_BORDER_ALL; }
	int GetBorderStyle() { return m_nBorderStyle; }
	void SetBorderStyle(int nBorderStyle) { m_nBorderStyle=nBorderStyle; SetModifiedFlag(TRUE); }

	static int GetDefaultLineStyle() { return ID_LINE_1PX; }
	int GetLineStyle() { return m_nLineStyle; }
	void SetLineStyle(int nLineStyle) { m_nLineStyle=nLineStyle; SetModifiedFlag(TRUE); }

	static int GetDefaultDashStyle() { return ID_DASH_SOLID; }
	int GetDashStyle() { return m_nDashStyle; }
	void SetDashStyle(int nDashStyle) { m_nDashStyle=nDashStyle; SetModifiedFlag(TRUE); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupBarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL
	virtual BOOL DoFileSave();

// Implementation
public:
	virtual ~CPopupBarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPopupBarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPBARDOC_H__95493CED_F252_11D1_B475_B0D808C10000__INCLUDED_)
