
// ProgressBar.h : header file
//

#ifndef _INCLUDE_PROGRESSBAR_H_
#define _INCLUDE_PROGRESSBAR_H_


/////////////////////////////////////////////////////////////////////////////
// CProgressBar -  status bar progress control
//
// Written by Chris Maunder, 1997
// Please feel free to use and distribute.

class CProgressBar: public CProgressCtrl
// Creates a ProgressBar in the status bar
{
public:
	CProgressBar();
	CProgressBar(LPCTSTR strMessage, int nSize=100, int MaxValue=100);
	~CProgressBar();
	BOOL Create(LPCTSTR strMessage, int nSize=100, int MaxValue=100);

	DECLARE_DYNCREATE(CProgressBar)

// operations
public:
	BOOL Success() {return m_bSuccess;}			// Was the creation successful?

	void SetRange(int nLower, int nUpper, int nStep = 1);
	void SetText(LPCTSTR strMessage) { m_strMessage = strMessage; Resize(); }
	void SetSize(int nSize)			 { m_nSize = nSize; Resize(); }
	int  SetPos(int nPos);
	int  OffsetPos(int nPos);
	int  SetStep(int nStep);
	int  StepIt();
	void Clear();

// Overrides
	//{{AFX_VIRTUAL(CProgressBar)
	//}}AFX_VIRTUAL

// implementation
protected:
	BOOL		m_bSuccess;		// Successfully created?
	int			m_nSize;		// Percentage size of control
	CString		m_strMessage;	// Message to display to left of control	

	CStatusBar *GetStatusBar();
	void Resize();

// Generated message map functions
protected:
	//{{AFX_MSG(CProgressBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif
/////////////////////////////////////////////////////////////////////////////