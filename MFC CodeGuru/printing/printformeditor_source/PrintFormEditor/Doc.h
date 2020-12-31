// Doc.h : interface of the Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOC_H__17660EB1_0940_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_DOC_H__17660EB1_0940_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <fstream.h>

enum { pfoStatic = 0, pfoEdit, pfoLine, pfoRect, pfoFrame, pfoImage, pfoRadio, pfoCheck, pfoVLine, pfoHLine, pfoSubForm };
enum { bdrNoBorder = 0, bdrSingle = 1, bdrDouble = 2, bdrDot = 3 };

class CPrintFormObject
{
public:
	void Input(CString &cs);
	void Output(ofstream &ofs);
	void Print(CDC * pDC, CPoint offset);
	CFont * CreateFont(CFont &ft, CDC * pDC, const int iDiv);
	void Draw(CDC * pDC, int xos, int yos, int div);
	CPrintFormObject();
	CPrintFormObject(const CPrintFormObject * p);
	CPrintFormObject(const int tpe);
	virtual ~CPrintFormObject();

	CRect		rc;
	char		cId[64];
	char		cCond[64];
	char		cId2[64];

	bool		bBold, bItalic, bUnderline;
	char		cFont[64];
	int			iSize;
	int			iType;
	int			iBack;
	COLORREF	crBack, crFront, crBdr;
	int			exInfo;
	int			iBorder, iBorderSize;
	UINT		uiTextFormat;

	bool		bSelected;
};

extern CPrintFormObject ** ppClipObjs;
extern int iClipFormObj;

class CPage
{
public:
	CPage();
	virtual ~CPage();

	CString name;
	CRect rcPaper; // in 10th of MM
	CPrintFormObject ** ppObjs;
	int iFormObj;
};

class Doc : public CDocument
{
protected: // create from serialization only
	Doc();
	DECLARE_DYNCREATE(Doc)

// Attributes
public:
	CString name;
	CRect	rcPaper; // in 10th of MM

	CPrintFormObject ** ppObjs;
	int iFormObj;

	int iPages, iSelpage;
	CPage ** pPages;

	int AddPage();
	void RemovePage(const int p);
	void SelectPage(const int p);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPageRect(CRect &rc);
	void RenamePage(const int idx, CString cs);
	void FillList();
	void PasteClip();
	void CopySelected();
	void RemoveSelected();
	int HitTest(CPoint &pt, CRect &rc, int &idx);
	int SelectObject(CRect rcBound);
	int GetSelectedCount();
	void ClearSelection();
	CPrintFormObject * AddObject(const int tpe);
	virtual ~Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(Doc)
	afx_msg void OnAddPage();
	afx_msg void OnUpdateAddPage(CCmdUI* pCmdUI);
	afx_msg void OnRemovePage();
	afx_msg void OnUpdateRemovePage(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOC_H__17660EB1_0940_11D2_840B_0000B43382FE__INCLUDED_)
