// scribdoc.h : interface of the CScribDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


class CStroke;

class CScribDoc : public CDocument
{
protected: // create from serialization only
	CScribDoc();
	DECLARE_DYNCREATE(CScribDoc)

// Attributes
protected:
	CObList         m_strokeList;   // Each member of the list is a CStroke

	// The document keeps track of the current pen width on behalf of
	// all views. We'd like the user interface of Scribble to be such
	// that if the user chooses the Draw Thick Line command, it will apply
	// to all views, not just the view that currently has the focus.

	BOOL            m_bThickPen;        // TRUE if current pen is thick
	UINT            m_nThinWidth;
	UINT            m_nThickWidth;
	CPen            m_penCur;           // pen created according to
										// user-selected pen style (width)
public:
	UINT            m_nPenWidth;        // current user-selected pen width
	CPen*           GetCurrentPen() { return &m_penCur; }

protected:
	CRect           m_rectDoc;
public:
	CRect& GetDocRect() { return m_rectDoc; }

// Operations
public:
	void DeleteContents();
	CStroke* NewStroke();
	POSITION GetFirstStrokePos();
	CStroke* GetNextStroke(POSITION& pos);

// Implementation
protected:
	void ReplacePen();

public:
	virtual ~CScribDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	void            InitDocument();
	virtual BOOL    OnNewDocument();
	virtual BOOL    OnOpenDocument(LPCTSTR pszPathName);

// Generated message map functions
protected:
	//{{AFX_MSG(CScribDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnPenThickOrThin();
	afx_msg void OnUpdatePenThickOrThin(CCmdUI* pCmdUI);
	afx_msg void OnPenWidths();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// class CStroke
//
// A stroke is a series of connected points in the scribble drawing.
// A scribble document may have multiple strokes.

class CStroke : public CObject
{
public:
	CStroke(UINT nPenWidth);

protected:
	CStroke();
	DECLARE_SERIAL(CStroke)

// Attributes
	UINT                m_nPenWidth;    // one pen width applies to entire stroke
	CDWordArray         m_pointArray;   // series of connected points
	CRect               m_rectBounding; // smallest rect that surrounds all
										// of the points in the stroke
										// measured in MM_LOENGLISH units
										// (0.01 inches, with Y-axis inverted)
public:
	CRect& GetBoundingRect() { return m_rectBounding; }

// Operations
public:
	void AddPoint(CPoint pt);
	BOOL DrawStroke(CDC* pDC);
	void FinishStroke();

// Helper functions
protected:
	CPoint GetPoint(int i) const { return CPoint(m_pointArray[i]); }

public:
	virtual void Serialize(CArchive& ar);
};
