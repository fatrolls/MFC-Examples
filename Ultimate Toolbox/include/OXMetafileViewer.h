#if !defined(_OXMETAFILEVIEWER_H__)
#define _OXMETAFILEVIEWER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

// OXMetafileViewer.h : header file
//

#include "OXMetaFile.h"
#include "OXScrollWnd.h"

/////////////////////////////////////////////////////////////////////////////
// COXMetafileViewer window

class OX_CLASS_DECL COXMetafileViewer : public COXScrollWnd
{
	DECLARE_DYNAMIC(COXMetafileViewer)
// Construction
public:
	COXMetafileViewer();

// Attributes
public:

protected:
	// metafile image
	COXMetaFile m_MetaFile;
	
// Operations
public:

	BOOL LoadFile(LPCTSTR lpszPathName);
	inline BOOL LoadResource(UINT nIDResource, CString strResType=_T("METAFILE"));

	inline COXMetaFile* GetImage() { return &m_MetaFile; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXMetafileViewer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COXMetafileViewer();

protected:
	CSize GetMetafileSize();

	virtual BOOL InitializeImage(const CSize& sizePage=CSize(100,100),
		const CSize& sizeLine=CSize(10,10));

	BOOL DrawMetafile(CDC* pDC, const CRect& rectSrc);

	// Generated message map functions
protected:
	//{{AFX_MSG(COXMetafileViewer)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_OXMETAFILEVIEWER_H__)
