// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MIDIGenerator.h"

#include "MainFrm.h"
#include "InputDialog.h"
#include <fstream.h>
#include "Collect.h"
#include "Midi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_BEARBEITEN_MIDIDATEIGENERIEREN, OnCreateMIDIFile)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnCreateMIDIFile() 
{
	CInputDialog dlg(this);
	dlg.m_Prompt1 = _T("Zeichenkette:");
	dlg.m_Prompt2 = _T("Kanal (0-63):");
	dlg.m_Prompt3 = _T("Instrument (0-127):");
	dlg.m_Prompt4 = _T("Lautstärke (0-127):");
	dlg.m_Prompt5 = _T("Copyright:");
	dlg.m_InputLine2 = _T("0");
	dlg.m_InputLine3 = _T("0");
	dlg.m_InputLine4 = _T("96");
	dlg.m_InputLine5 = _T("Copyright (C) 1997 Andreas Jaeger  e-mail: JaegerA@aol.com");
	if (dlg.DoModal()==IDOK)
	{
		CFileDialog dlg1(FALSE, _T("mid"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Midi-Sequenzen (*.mid)|*.mid||"), this);	
		if (dlg1.DoModal()==IDOK)
		{
			CMidiFile midifile(96);
			CMidiTrack* miditrack = new CMidiTrack;
			miditrack->Copyright(dlg.m_InputLine5);
			miditrack->TimeSignature(0x04, 0x02, 0x18, 0x08);
			miditrack->Tempo(120);
			miditrack->Insert(new CMidiEventCommandProgramChange (atoi(dlg.m_InputLine2), 0, atoi(dlg.m_InputLine3)));

			miditrack->PlayString(atoi(dlg.m_InputLine2), dlg.m_InputLine1);

			miditrack->EndOfTrack();
			midifile.Insert(miditrack);
			midifile.WriteToFile(dlg1.GetPathName());
			AfxMessageBox(_T("Das Midi-File wurde erzeugt!"));
		}
	}
}
