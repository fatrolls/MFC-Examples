// HexDoc.h : interface of the CHexDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXDOC_H__3A83FDFE_A3E6_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_HEXDOC_H__3A83FDFE_A3E6_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHexDoc : public CDocument
{
protected: // create from serialization only
	CHexDoc();
	DECLARE_DYNCREATE(CHexDoc)

// Attributes
public:

// Operations
public:
	UINT GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer);
	UINT GetDocumentLength();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BYTE* m_pFileData;
	UINT m_nDocLength;
	//{{AFX_MSG(CHexDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXDOC_H__3A83FDFE_A3E6_11D2_8E53_006008A82731__INCLUDED_)
