// videocli.h : header file
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:42  $

/////////////////////////////////////////////////////////////////////////////
// CVideoClipDialog dialog

class CVideoClipDialog : public CDialog
{
// Construction
public:
	CVideoClipDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoClipDialog)
	enum { IDD = IDD_VIDEOCLIP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	CMRCAnimateCtrl * m_pSmugVideo;	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoClipDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoClipDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
