#include "stdafx.h"
#include "StatusMessage.h"

// StatusBarMessage() - Writes to status bar using sprintf syntax.
//
// Author: Keith Rule -- keithr@europa.com
//
// Copyright (c) 1995-1997, Keith Rule
// May be freely used provided this comment
// is included with the source and all derived
// versions of this source.

void StatusBarMessage(int pane, char* fmt, ...)
{
	if (AfxGetApp() != NULL && AfxGetApp()->m_pMainWnd != NULL) {
		char buffer[256];
		CStatusBar* pStatus = (CStatusBar*) 
			AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		va_list argptr;
		va_start(argptr, fmt);
		vsprintf(buffer, fmt, argptr);
		va_end(argptr);
		if (pStatus != NULL) {
			pStatus->SetPaneText(pane, buffer);
			pStatus->UpdateWindow();
		}
	}
}

void StatusBarMessage(char* fmt, ...)
{
	if (AfxGetApp() != NULL && AfxGetApp()->m_pMainWnd != NULL) {
		char buffer[256];
		CStatusBar* pStatus = (CStatusBar*) 
			AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
		va_list argptr;
		va_start(argptr, fmt);
		vsprintf(buffer, fmt, argptr);
		va_end(argptr);
		if (pStatus != NULL) {
			pStatus->SetPaneText(0, buffer);
			pStatus->UpdateWindow();
		}
	}
}