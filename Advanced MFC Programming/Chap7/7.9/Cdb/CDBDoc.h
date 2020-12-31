#if !defined(AFX_CDBDOC_H__2D7EBBEA_0A8A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CDBDOC_H__2D7EBBEA_0A8A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "FontDlg.h"
#include "DumDlg.h"

class CCDBDoc : public CDocument
{
protected:
	CCDBDoc();
	DECLARE_DYNCREATE(CCDBDoc)

	MCDummyDlg *m_pFontDmDlg;
	MCDummyDlg *m_pColorDmDlg;
	MCMLFontDialog *m_pFontDlg;
	CColorDialog *m_pColorDlg;
	COLORREF m_colorCur;

public:
	//{{AFX_VIRTUAL(CCDBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

public:
	void ColorDialog(COLORREF colorInit, DWORD dwFlags=0);
	void SetCurrentColor(COLORREF);
	COLORREF GetCurrentColor(){return m_colorCur;}
	virtual ~CCDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CCDBDoc)
	afx_msg void OnFiledialogboxFileopen();
	afx_msg void OnFiledialogboxFilesave();
	afx_msg void OnFiledialogboxCustomizedfileopen();
	afx_msg void OnFiledialogboxCustomizefileopenold();
	afx_msg void OnFiledialogboxDirdialog();
	afx_msg void OnFiledialogboxDirdialogold();
	afx_msg void OnFiledialogboxCustomfiledlg();
	afx_msg void OnColordialogboxInitialize();
	afx_msg void OnColordialogboxDisablefullopen();
	afx_msg void OnColordialogboxFullopen();
	afx_msg void OnColordialogboxChoosebasecolor();
	afx_msg void OnColordialogboxChoosecostumcolor();
	afx_msg void OnFontdialogboxInitialize();
	afx_msg void OnFontdialogboxCustomize();
	afx_msg void OnColordialogboxModeless();
	afx_msg void OnFontdialogboxModeless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CDBDOC_H__2D7EBBEA_0A8A_11D1_9C9A_444553540000__INCLUDED_)
