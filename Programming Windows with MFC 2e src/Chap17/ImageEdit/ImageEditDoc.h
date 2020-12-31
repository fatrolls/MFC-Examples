// ImageEditDoc.h : interface of the CImageEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEEDITDOC_H__9D77AEEA_AA14_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_IMAGEEDITDOC_H__9D77AEEA_AA14_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

UINT ThreadFunc (LPVOID pParam);
LOGPALETTE* CreateGrayScale ();

class CImageEditDoc : public CDocument
{
protected: // create from serialization only
	CImageEditDoc();
	DECLARE_DYNCREATE(CImageEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ThreadAborted();
	void ThreadFinished();
	CPalette* GetPalette();
	CBitmap* GetBitmap();
	virtual ~CImageEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CCriticalSection m_cs;
	CEvent m_event;
	HANDLE m_hThread;
	BOOL m_bWorking;
	CPalette m_palette;
	CBitmap m_bitmap;
	//{{AFX_MSG(CImageEditDoc)
	afx_msg void OnGrayScale();
	afx_msg void OnUpdateGrayScale(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEEDITDOC_H__9D77AEEA_AA14_11D2_8E53_006008A82731__INCLUDED_)
