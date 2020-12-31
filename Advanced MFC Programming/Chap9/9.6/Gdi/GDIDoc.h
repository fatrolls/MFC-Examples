#if !defined(AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CGDIView;

class CGDIDoc : public CDocument
{
protected:
	CGDIDoc();
	DECLARE_DYNCREATE(CGDIDoc)
	CString m_szText;
	CFont m_ftDraw;
	int m_nCaretIndex;
	int m_nCaretVerSize;
	
public:
	CString GetText(){return m_szText;}
	CFont *GetFont(){return &m_ftDraw;}
	void ForwardCaret();
	void BackwardCaret();
	POINT GetCaretPosition();
	int GetCaretVerSize(){return m_nCaretVerSize;}
	CGDIView *CGDIDoc::GetCGDIView();
	void AddChar(UINT, UINT);
	void DeleteChar(BOOL);
	//{{AFX_VIRTUAL(CGDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

public:
	virtual ~CGDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGDIDoc)
	afx_msg void OnDialogFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_)
