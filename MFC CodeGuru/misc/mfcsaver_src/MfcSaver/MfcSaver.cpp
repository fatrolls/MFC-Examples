// MfcSaver.cpp : Defines the class behaviors for the application.
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#include "StdAfx.h"

#include "MfcSaver.h"
#include "MfcSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

//
// The screen saver controls a number of icon graphics that bounce around
// on a black background.  Set some basic defaults and initialize the random
// number generator with srand().  Later, our RestoreOptions() will be called
// to recall earlier option settings.
//

BEGIN_MESSAGE_MAP(CMfcSaver, CScreenSaverWnd)
	//{{AFX_MSG_MAP(CMfcSaver)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// As required of CScreenSaverWnd-based screen savers, these are the two
// global instances of screen saver objects.  One is the saver itself,
// and one is the dialog for configuring the options of the screen saver.
//
// Unlike most MFC applications, there is no instance of any CWinApp object.
//
CMfcSaver theSaver;
CMfcSaverDlg theSaverDialog;

CMfcSaver::CMfcSaver()
{
	m_nIcons = 8;
	m_nSpeed = 8;
	srand(time(NULL));
}

CMfcSaver::~CMfcSaver()
{
}

/////////////////////////////////////////////////////////////////////////////

//
// The CMfcSaverDlg will need to be able to access our customizable
// attributes.  We call OnInitialUpdate() again to reorganize internally if
// any of these change.
//
// The options need to be saved and restored between runs.
// Probably the biggest thing you might miss from having no CWinApp object
// will be CWinApp::WriteProfileInt() which saves things to the registry
// without complicated registry code.
//
// For simplicity, we just create an mfcsaver.ini file with the options.
//

int CMfcSaver::GetIconCount() const
{
	return m_nIcons;
}

void CMfcSaver::SetIconCount(int nIcons)
{
	m_nIcons = nIcons;
	OnInitialUpdate();
}

int CMfcSaver::GetIconSpeed() const
{
	return m_nSpeed;
}

void CMfcSaver::SetIconSpeed(int nSpeed)
{
	m_nSpeed = nSpeed;
	OnInitialUpdate();
}

void CMfcSaver::SaveOptions()
{
	CString s;
	s.Format("%d", GetIconCount());
	::WritePrivateProfileString(
		"MfcSaver", "Count", s, "mfcsaver.ini");
	s.Format("%d", GetIconSpeed());
	::WritePrivateProfileString(
		"MfcSaver", "Speed", s, "mfcsaver.ini");
}

void CMfcSaver::RestoreOptions()
{
	SetIconCount(::GetPrivateProfileInt(
		"MfcSaver", "Count", 8, "mfcsaver.ini"));
	SetIconSpeed(::GetPrivateProfileInt(
		"MfcSaver", "Speed", 8, "mfcsaver.ini"));
}

/////////////////////////////////////////////////////////////////////////////

//
// While this is just demonstrating how to override the virtual functions of
// CScreenSaverWnd, it also shows something about using CImageList to
// draw from a library of simple images.
//
// When our timer goes off, we just invalidate the window.  The OnDraw()
// override will be called appropriately when the system has some free cycles
// to spend on drawing.  Remember:  a screen saver should share the CPU, so
// the computer can work on other tasks like downloading or numbercrunching.
//

void CMfcSaver::OnInitialUpdate()
{
	if (!m_hWnd)
		return;

	// Flush all the icons we have, if any.
	m_aIcon.RemoveAll();
	if (m_ilIcons.m_hImageList)
		m_ilIcons.DeleteImageList();

	// Set up for the desired number of icons.
	m_aIcon.SetSize(m_nIcons);
	m_ilIcons.Create(IDB_ICONS, 32, 0, RGB(128, 0, 128));

	int i;
	for (i = 0; i < m_nIcons; i++)
		SetupMfcSaverIcon(i);

	m_nSpeed = max(1, m_nSpeed);
	SetTimer(1, 2000 / m_nSpeed, NULL);
}

void CMfcSaver::OnDraw(CDC* pDC)
{
	int i;
	for (i = 0; i < m_nIcons; i++)
	{
		EraseMfcSaverIcon(i, pDC);
		UpdateMfcSaverIconPosition(i);
		if (IsMfcSaverIconOffscreen(i))
			SetupMfcSaverIcon(i);
		DrawMfcSaverIcon(i, pDC);
	}
}

void CMfcSaver::EraseMfcSaverIcon(int i, CDC* pDC)
{
	CRect rcIcon = CRect(m_aIcon[i].ptP, CSize(32, 32));
	pDC->FillSolidRect(&rcIcon, RGB(0, 0, 0));
}

void CMfcSaver::DrawMfcSaverIcon(int i, CDC* pDC)
{
	m_ilIcons.Draw(pDC, m_aIcon[i].iImage, m_aIcon[i].ptP, ILD_NORMAL);
}

void CMfcSaver::OnTimer(UINT nIDEvent) 
{
	CScreenSaverWnd::OnTimer(nIDEvent);

	Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////

//
// Compute the movement of these little square icons.
// They move until they fall offscreen, then are reinitialized randomly.
// If they would collide on any move, they don't move but they change
// direction instead.  If they seem hopelessly stuck, they are recycled.
//
// With a bit more work, you could make these icons pass over each other
// smoothly, or you could double-buffer them to draw with less flicker.
//

BOOL CMfcSaver::IsMfcSaverIconColliding(int i, CPoint ptP)
{
	CRect rcI = CRect(ptP, CSize(32, 32));

	int j;
	for (j = 0; j < m_nIcons; j++)
	{
		if (j == i)
			continue;

		CRect rcJ = CRect(m_aIcon[j].ptP, CSize(32, 32));
		if (rcJ.IntersectRect(&rcJ, &rcI))
			return TRUE;
	}

	return FALSE;
}

BOOL CMfcSaver::IsMfcSaverIconOffscreen(int i)
{
	CRect rcI = CRect(m_aIcon[i].ptP, CSize(32, 32));
	CRect rcC;
	GetClientRect(&rcC);

	return !rcC.IntersectRect(&rcC, &rcI);
}

void CMfcSaver::UpdateMfcSaverIconPosition(int i)
{
	CPoint ptP;

	ptP = m_aIcon[i].ptP + m_aIcon[i].szV;
	if (IsMfcSaverIconColliding(i, ptP))
	{
		m_aIcon[i].nStuck++;
		BounceMfcSaverIcon(i);
		if (m_aIcon[i].nStuck > 5)
			SetupMfcSaverIcon(i);
		return;
	}

	m_aIcon[i].nStuck = 0;
	m_aIcon[i].ptP = ptP;
}

void CMfcSaver::BounceMfcSaverIcon(int i)
{
	do
	{
		m_aIcon[i].szV.cx = (rand() % 5) - 2;
		m_aIcon[i].szV.cy = (rand() % 5) - 2;
	} while (m_aIcon[i].szV.cx == 0 && m_aIcon[i].szV.cy == 0);
}

void CMfcSaver::SetupMfcSaverIcon(int i)
{
	int count = max(1, m_ilIcons.GetImageCount());

	int breakout = 10;
	do
	{
		m_aIcon[i].iImage = (rand() % count);
		m_aIcon[i].ptP.x =
			(rand() % ::GetSystemMetrics(SM_CXSCREEN));
		m_aIcon[i].ptP.y =
			(rand() % ::GetSystemMetrics(SM_CXSCREEN));
		BounceMfcSaverIcon(i);
		m_aIcon[i].nStuck = 0;

	} while (breakout > 0 &&
	         IsMfcSaverIconColliding(i, m_aIcon[i].ptP));
}

