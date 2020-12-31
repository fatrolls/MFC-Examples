// HTMLEditDoc.h : interface of the CHTMLEditDoc class
//


#pragma once

class CHTMLEditDoc : public CHtmlEditDoc
{
protected: // create from serialization only
	CHTMLEditDoc();
	DECLARE_DYNCREATE(CHTMLEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();

// Implementation
public:
	virtual ~CHTMLEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


