// ChildFrm.h : interface of the CChildFrame class
//


#pragma once

class CMsgMapperView;

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMsgMapperView* GetRightPane();
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
