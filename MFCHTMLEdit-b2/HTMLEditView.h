// HTMLEditView.h : interface of the CHTMLEditView class
//


#pragma once


class CHTMLEditView : public CHtmlEditView
{
protected: // create from serialization only
	CHTMLEditView();
	DECLARE_DYNCREATE(CHTMLEditView)

// Attributes
public:
	CHTMLEditDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CHTMLEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bDesignMode;

// Generated message map functions
protected:
	DECLARE_DHTMLEDITING_CMDMAP(CHTMLEditView)
	DECLARE_MESSAGE_MAP()
public:
	void OnToggleBrowse(void);
	void OnInitialUpdate(void);
	void OnModeEdit(void);
	void OnUpdateModeEdit(CCmdUI *pCmdUI);
	void OnModeView(void);
	void OnUpdateModeView(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in HTMLEditView.cpp
inline CHTMLEditDoc* CHTMLEditView::GetDocument() const
   { return reinterpret_cast<CHTMLEditDoc*>(m_pDocument); }
#endif

