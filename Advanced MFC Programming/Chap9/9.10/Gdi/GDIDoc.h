#if !defined(AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define HINT_DELCHAR_AFTER			100
#define HINT_DELCHAR_BEFORE			101
#define HINT_DELETE_SELECTION		102
#define HINT_PASTE					103
#define HINT_SELECTION				104
#define HINT_UNSELECTION			105
#define HINT_INPUT					106

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
	int m_nTextHorSize;
	int m_nSelIndexBgn;
	int m_nSelIndexEnd;
	int m_nSelIndexBgnOld;
	int m_nSelIndexEndOld;
	
public:
	CString GetText(){return m_szText;}
	CFont *GetFont(){return &m_ftDraw;}
	void ForwardCaret();
	void BackwardCaret();
	void HomeCaret();
	void EndCaret();
	void ForwardCaretToBlank();
	void BackwardCaretToBlank();
	void SetCaret(CPoint);
	void ResetSelection()
	{
		m_nSelIndexBgnOld=m_nSelIndexBgn;
		m_nSelIndexEndOld=m_nSelIndexEnd;
		m_nSelIndexBgn=m_nSelIndexEnd=-1;
		UpdateAllViews(NULL, HINT_UNSELECTION);
		m_nSelIndexBgnOld=m_nSelIndexEndOld=-1;
	}
	BOOL DeleteSelection();
	POINT GetCaretPosition();
	int GetCaretVerSize(){return m_nCaretVerSize;}
	int GetTextHorSize(){return m_nTextHorSize;}
	int GetSelIndexBgn(){return m_nSelIndexBgn;}
	int GetSelIndexEnd(){return m_nSelIndexEnd;}
	int GetSelIndexBgnOld(){return m_nSelIndexBgnOld;}
	int GetSelIndexEndOld(){return m_nSelIndexEndOld;}
	int GetCaretIndex(){return m_nCaretIndex;}
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
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDIDOC_H__F2930DFE_1E22_11D1_9C9A_444553540000__INCLUDED_)
