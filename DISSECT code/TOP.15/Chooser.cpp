// chooser.cpp : Implements the CDialogChooser class
//

#include "stdafx.h"
#include "Top Studio.h"
#include "chooser.h"
#include "cstm1dlg.h"
#include "Top Studioaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;

	m_pDlgs[1] = GetDialog(APWZDLG_APPTYPE);
	m_pDlgs[2] = GetDialog(APWZDLG_DATABASE);
	m_pDlgs[3] = GetDialog(APWZDLG_OLE);
	m_pDlgs[4] = GetDialog(APWZDLG_DOCAPPOPTIONS);
	m_pDlgs[5] = GetDialog(APWZDLG_PROJOPTIONS);
	m_pDlgs[6] = GetDialog(APWZDLG_CLASSES);
	m_pDlgs[7] = GetDialog(APWZDLG_DLGAPPOPTIONS);

	m_pDlgs[8] = new CCustom1Dlg;

	m_nCurrDlg = 0;
	m_nTrack = 0;
}
// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP 8
#define LAST_CUSTOM_STEP 8

// Set up arrays of indices to simulate behavior of AppWizard (i.e., to have
//  separate "tracks" for an MDI/SDI app and a dialog-based app).
static int nDocTrack[] = {0, 1, 2, 3, 4, 5, 6, 8};
static int nDlgTrack[] = {0, 1, 7, 5, 6, 8};
static int* pnTrack[] = {nDocTrack, nDlgTrack};
static int nLast[] = {7, 5};

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
	// NOTE: Be sure to delete all of your custom steps here, but don't delete
	//  any standard AppWizard steps you got through the GetDialog API.
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(m_nTrack == 0 || m_nTrack == 1);
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	// If the current step is the "project type" step, the AppWizard "track" may
	//  have changed.
	if (m_nCurrDlg == 1)
	{
		CString strTemp;
		m_nTrack = TopStudioaw.m_Dictionary.Lookup(_T("PROJTYPE_DLG"), strTemp) ? 1 : 0;
		SetNumberOfSteps(nLast[m_nTrack]);
	}

	m_nCurrDlg++;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == 1)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(m_nTrack == 0 || m_nTrack == 1);
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= nLast[m_nTrack]);
	ASSERT(pDlg == m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]]);

	m_nCurrDlg--;

	// If the new step is the "project type" step, don't display the max number
	//  of steps.
	if (m_nCurrDlg == 1)
		SetNumberOfSteps(-1);

	return m_pDlgs[(pnTrack[m_nTrack])[m_nCurrDlg]];
}
