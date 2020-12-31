// ParserViewDoc.h : interface of the CParserViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERVIEWDOC_H__8E0F092E_0728_11D3_A9F8_2EA565000000__INCLUDED_)
#define AFX_PARSERVIEWDOC_H__8E0F092E_0728_11D3_A9F8_2EA565000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CParserViewDoc : public CDocument
{
protected: // create from serialization only
	CParserViewDoc();
	DECLARE_DYNCREATE(CParserViewDoc)

// Attributes
public:
    COXParser* GetParser();
    BOOL IsHTML() { return m_bHTML; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParserViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CParserViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    static BOOL ReportError(int nError, LPCTSTR szError, int nLine, int nCol, DWORD dwData);

protected:
    COXParser     m_parser;
    COXHTMLParser m_HTMLparser;
    BOOL          m_bHTML;

// Generated message map functions
protected:
	//{{AFX_MSG(CParserViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSERVIEWDOC_H__8E0F092E_0728_11D3_A9F8_2EA565000000__INCLUDED_)
