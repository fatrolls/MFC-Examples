// ==========================================================================
// 							Class Specification : COXPreviewDialog
// ==========================================================================

// Header file : OXPrvDlg.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CFileDialog

//	YES	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	YES	Has a message map
//	YES  Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class extends the Common File Dialog with a specific 
//	custom template in order to have a preview area in this dialog.  To implement a
//  dialog that previews BMP's, derive a class from this class and implement two 
//  virtual functions : OnNewFileSelect() and 
//  OnPaintPreview(CDC* pDC, const CRect& paintRect)

// Remark:
//	This file uses resources.
//	The reserved ID ranges are : 23080 -> 23099 and 53080 -> 53099

// Prerequisites (necessary conditions):
//	

/////////////////////////////////////////////////////////////////////////////
#ifndef __OXPRVDLG_H__
#define __OXPRVDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


class OX_CLASS_DECL COXPreviewDialog : public CFileDialog
{
DECLARE_DYNAMIC(COXPreviewDialog)

// Data members -------------------------------------------------------------
public:
	
protected:
	CStatic		m_previewFrame;
	BOOL		m_bPreview;
	BOOL		m_bPrevPreview;
	CString		m_sSelectedFile;
	CString		m_sPrevSelectedFile;

	class OX_CLASS_DECL COXPreview : public CButton
	{
	// Data Members
	public:
	protected:
	private:
	// Member Functions
	public:
		COXPreview();
		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	private:
	} m_preview;


private:

friend COXPreview;

// Member functions ---------------------------------------------------------
public:
	COXPreviewDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	// --- In  : see constructor MFC CFiledialog
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object

	virtual ~COXPreviewDialog();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of object


protected:      
	virtual void OnNewFileSelect(const CString& sFilename);
	virtual void OnPaintPreview(CDC* pDC, const CRect& paintRect);
	virtual void OnDoRealizePalette(CWnd* pFocusWnd);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void CheckFileSelection();

#ifdef WIN32
	BOOL IsWin95();
	virtual void OnFileNameChange();
	CString GetFilePath() const;
#endif
  
	afx_msg void OnPreview();
	virtual BOOL OnInitDialog();

	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	DECLARE_MESSAGE_MAP()

private:
	virtual void OnLBSelChangedNotify( UINT nIDBox, UINT iCurSel, UINT nCode);

};

#endif //__OXPRVDLG_H__

