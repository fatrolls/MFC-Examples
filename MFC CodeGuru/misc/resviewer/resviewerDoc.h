// resviewerDoc.h : interface of the CResviewerDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "persrc.h"
#if !defined(AFX_RESVIEWERDOC_H__213309CB_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
#define AFX_RESVIEWERDOC_H__213309CB_AD73_11D1_8358_00A0244DBC26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



class CResviewerDoc : public CDocument
{
protected: // create from serialization only
	CResviewerDoc();
	DECLARE_DYNCREATE(CResviewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResviewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCurrentItem(LPRESINFO lpRes);
	PERsrcTbl* GetPERsrc();
	PERsrcTbl* m_PeResource;
	virtual ~CResviewerDoc();
	virtual BOOL RouteCmdToAllViews (CView*, UINT, int, void*,
        AFX_CMDHANDLERINFO*);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResviewerDoc)
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CreateCURFile(LPCTSTR pszFile,LPBITMAPINFOHEADER pbi,DWORD RsrcSize);
	BOOL CreateDLGFile(LPCTSTR pszFile,PVOID pdlg,DWORD RsrcSize);
	BOOL CreateICOFile(LPCTSTR pszFile, LPBITMAPINFOHEADER pbi, DWORD RsrcSize);
	BOOL CreateBMPFile(LPCTSTR pszFile, LPBITMAPINFOHEADER pbih);
	CHAR m_currentresName[255];
	DWORD m_currentresID;
	DWORD m_currentresType;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESVIEWERDOC_H__213309CB_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
