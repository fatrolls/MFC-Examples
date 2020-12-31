// Copyright (C) BrigSoft, 2003.
// http://www.brigsoft.com
// FilesDragDropView.h : interface of the CFilesDragDropView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESDRAGDROPVIEW_H__A5AED7F9_4E3B_44D5_A7F6_7FA7B64FD08F__INCLUDED_)
#define AFX_FILESDRAGDROPVIEW_H__A5AED7F9_4E3B_44D5_A7F6_7FA7B64FD08F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxole.h>

#include "DropFiles.h"

class CFilesDragDropView : public CListView
{
protected: // create from serialization only
	CFilesDragDropView();
	DECLARE_DYNCREATE(CFilesDragDropView)

// Attributes
public:
	CFilesDragDropDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesDragDropView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilesDragDropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilesDragDropView)
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	BOOL FileNamesToList( HDROP hDrop );
	BOOL DataObjectToList (COleDataObject* const pDataObject); 
	void FileNamesToClipBoard( );
	BOOL PrepareFileBuff(CDropFiles& DropFiles) const;
	void DeleteSelectedFiles();


private:
	COleDropTarget m_DropTarget;

};

#ifndef _DEBUG  // debug version in FilesDragDropView.cpp
inline CFilesDragDropDoc* CFilesDragDropView::GetDocument()
   { return (CFilesDragDropDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESDRAGDROPVIEW_H__A5AED7F9_4E3B_44D5_A7F6_7FA7B64FD08F__INCLUDED_)
