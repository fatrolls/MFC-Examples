// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D2552D12_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_MAINFRM_H__D2552D12_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TreeFilesDlg.h"
#include "DIBManagerDoc.h"

#include "OXFrameWndDock.h"
#include "OXSizeToolBar.h"
#include "OXSizeDlgBar.h"
#include "OXSizeDockBar.h"
#include "OXBitmapMenuOrganizer.h"
#include "xstatus4.h"

#include "OXCoolToolBar.h"
#include "OXCoolBar.h"

#include "OXCaptionPainter.h"
#include "OXTabClientWnd.h"
#include "OXMenuBar.h"

class CMainFrame : public COXMenuBarFrame<COXMDIFrameWndSizeDock,COXSizeDockBar>
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
//	CButtonsPaneDlg m_ButtonsPaneBar;
	// TreeFilesDlg - dialog with tree control to show all opened window
	CTreeFilesDlg m_TreeFilesBar;
	// special statusbar with progressbar
	COXStatusBar  m_wndStatusBar;

	// defines if roll-up ZoomLevel Dialog is active
	BOOL m_bShowZoomLevelDlg;

// Operations
public:
	void LoadWorkspace();
	void SaveWorkspace();

	BOOL IniProgress(WORD nToDo, WORD nStep=1);
	void ShowProgress();
	void ResetProgress();
	void GetNumColors();

	void CreateDocumentFromOpenedFile(CString sFileName, 
		CDIBManagerDoc::TypeFile tf=CDIBManagerDoc::TF_DIB);
	void CreateDocumentFromOpenedFile(CFile* pFile, CString sFileName, 
		CDIBManagerDoc::TypeFile tf=CDIBManagerDoc::TF_JPEG); 
	BOOL CheckFileAlreadyOpened(CString sFileName, BOOL bNotify);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	COXCaptionPainter m_Caption;
	COXCoolToolBar m_wndToolBar;
//	COXCoolToolBar m_wndToolBar1;
//	COXCoolBar m_wndCoolBar;
	// to show bitmaps in menu
	COXBitmapMenuOrganizer Organizer;
	// to trace the progress of some process
	// tightly tied witn mainframe and statusbar window
	class CShowProgress* m_pShowProgress;

	// MTI client window
	COXTabClientWnd m_MTIClientWnd;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd*);
	afx_msg void OnWindowSynchronize();
	afx_msg void OnUpdateWindowSynchronize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSize(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI* pCmdUI);
	afx_msg void OnFileImport();
	afx_msg void OnUpdateFileProtected(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomLevelDlg(CCmdUI* pCmdUI);
	afx_msg void OnHandleDummy();
	//}}AFX_MSG
	afx_msg BOOL OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID);
	afx_msg void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

// Progress Class to iterates step of working of some cycle process 
// and showing it in progress bar of COXStatusBar control
class CShowProgress
{
public:
	CShowProgress() {}
	CShowProgress(CMainFrame* pMainFrame, WORD nProgressIndex) 
	{ 
		m_pMainFrame=pMainFrame; 
		m_nProgressIndex=nProgressIndex; 
	}
	~CShowProgress() {}

protected:
	// the size of step
	UINT m_nStep;
	// iterator within 0 to m_nStep-1
	UINT m_nStepIterator;
	// steps done
	UINT m_nDone;
	// steps to do
	UINT m_nToDo;

	// index of progressbar pane in statusbar
	UINT m_nProgressIndex;
	// owner window
	CMainFrame* m_pMainFrame;

public:
	void SetStep(UINT nStep) { m_nStep=nStep; }
	void SetStepIterator(UINT nStepIterator) { m_nStepIterator=nStepIterator; }
	void SetDone(UINT nDone) { m_nDone=nDone; }
	void SetToDo(UINT nToDo) { m_nToDo=nToDo; }
	void Initialize(UINT nToDo, UINT nStep=1)
	{
		SetStep(nStep);
		SetToDo(nToDo/nStep);
		SetStepIterator(0);
		SetDone(0);
		m_pMainFrame->m_wndStatusBar.ResetBar(m_nProgressIndex);
	}
	void Reset()
	{
		SetStep(0);
		SetToDo(0);
		SetStepIterator(0);
		SetDone(0);
		m_pMainFrame->m_wndStatusBar.ResetBar(m_nProgressIndex);
	}
	void Iterate()
	{
		m_nStepIterator++;
		if(m_nStepIterator==m_nStep)
		{
			SetStepIterator(0);
			m_nDone++;
			DWORD wPercent=((DWORD)m_nDone*(DWORD)100)/(DWORD)m_nToDo;
			if(wPercent>100)
			{
				wPercent=100;
			}
			m_pMainFrame->m_wndStatusBar.
				SetBarProgress(m_nProgressIndex,TRUE,100,wPercent);
		}
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D2552D12_7143_11D1_A3D5_0080C83F712F__INCLUDED_)


