// MsgMapperDoc.h : interface of the CMsgMapperDoc class
//


#pragma once

#include "utmessage.h"

class CMsgMapperDoc : public CDocument
{
protected: // create from serialization only
	CMsgMapperDoc();
	DECLARE_DYNCREATE(CMsgMapperDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMsgMapperDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

	// Message class for analysis
	CUT_Msg		m_message;
	CString		m_strRawMessage;



};


