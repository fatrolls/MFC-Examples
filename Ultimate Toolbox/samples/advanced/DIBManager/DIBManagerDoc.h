// DIBManagerDoc.h : interface of the CDIBManagerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBMANAGERDOC_H__D2552D16_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_DIBMANAGERDOC_H__D2552D16_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXdib.h"

class CDIBManagerDoc : public CDocument
{
protected: // create from serialization only
	CDIBManagerDoc();
	DECLARE_DYNCREATE(CDIBManagerDoc)

// Attributes
public:
	enum TypeFile { TF_DIB, TF_JPEG };

	// our DIB image
	COXDIB m_dib;
	// special DIB object that we use to render the image on the screen
	// in the case when the current system palette is no more than 8 bits
	// and image consist of no less than 256 colors
	COXDIB m_dibDither;
	// full file name of the document
	CString m_sNameFile;
	// type of image file
	// currently available only:
	// BITMAP = TF_DIB
	// JPEG	= TF_JPEG
	TypeFile m_tf;
	// defines if image is currently protected
	BOOL m_bProtected;
	// defines if image was initially protected
	BOOL m_bInitiallyProtected;
	// defines image length in byte
	DWORD m_dwImageSize;
	// the number of all pages to put it on screen
	UINT m_nDIBNumPage;
	// the number of pages in different direction
	UINT m_nXPage;
	UINT m_nYPage;

	BOOL OpenDocument(LPCTSTR lpszPathName, TypeFile tf=TF_DIB);
	BOOL OpenDocument(CFile* m_pFile, CString sFileName, TypeFile tf=TF_JPEG);

	CPalette* GetDIBPalette();
	CSize GetDIBSize();
	UINT CalcDIBNumPage(class CDIBManagerView* pView, CDC* pDC);

	DWORD CalcDIBSizeInMemory();
	BOOL CheckUseDithered();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIBManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIBManagerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBMANAGERDOC_H__D2552D16_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
