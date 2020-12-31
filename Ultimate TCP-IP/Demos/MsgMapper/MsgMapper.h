// MsgMapper.h : main header file for the MsgMapper application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMsgMapperApp:
// See MsgMapper.cpp for the implementation of this class
//

class CMsgMapperApp : public CWinApp
{
public:
	CMsgMapperApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewRaw();
	afx_msg void OnBnClickedRawBtn();
	afx_msg void OnBnClickedTextbtn();
	afx_msg void OnBnClickedHtmlbtn();
	afx_msg void OnViewHtml();
	afx_msg void OnViewText();
	afx_msg void OnUpdateViewText(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewHtml(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewRaw(CCmdUI *pCmdUI);

public:
	void SetEditViewTypes(BOOL bText, BOOL bHtml, BOOL bRaw);

private:
	BOOL	m_bCanDisplayRaw;
	BOOL	m_bCanDisplayText;
	BOOL	m_bCanDisplayHtml;

};

extern CMsgMapperApp theApp;