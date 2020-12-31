 

#pragma once
#include "afxwin.h"

#include "mxcom.h"

class CMapDemoDlg : public CDialog 
{
// Construction
public:
	CMapDemoDlg(CWnd* pParent = NULL);	// standard constructor
    ~CMapDemoDlg();
// Dialog Data
	enum { IDD = IDD_MAPDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
 
// Implementation
protected:
	HICON m_hIcon;
    BOOL PreTranslateMessage(MSG* pMsg);
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()


protected:
    CMxScene mScene;
    CMxTree mProjTree;
    void  OnDestroy();
    ISceneCtrlPtr mScenePtr;
    IProjectTreeCtrlPtr mTreePtr;

    DECLARE_EVENTSINK_MAP()



};
