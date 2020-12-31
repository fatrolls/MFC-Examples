#if !defined(AFX_CHOOSER_H__B0E47995_AF67_11D0_968D_444553540000__INCLUDED_)
#define AFX_CHOOSER_H__B0E47995_AF67_11D0_968D_444553540000__INCLUDED_

// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#define LAST_DLG 8

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CTopStudioAppWiz::Next
	//  & CTopStudioAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
	// Current step's index into the current track (defined in chooser.cpp).
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];

	// Current track (MDI/SDI app or dialog-based app; see chooser.cpp).
	int m_nTrack;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSER_H__B0E47995_AF67_11D0_968D_444553540000__INCLUDED_)
