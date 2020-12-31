//---------------------------------------------------------------------------
// Copyright (C) 1997, Interscope Ltd. All rights reserved.
// This software is protected by copyright law. Unauthorised reproduction
// or distribution of this program, or any portion of it, may result in
// severe civil or criminal penalties. For more information, contact:
//
// Interscope Ltd., 5 Culturii St., 5th floor, 4800 Baia Mare, Romania
//    Phone/Fax: +40(62)415023
//    E-mail: office@interscope.ro
//
//   $Author: Levente Farkas $
//     $Date: 11/07/97 11:53p $
//  $Modtime: 11/07/97 11:28p $
// $Revision: 2 $
//  $Archive: /Interscope/Thebe/SetupWizard/StatusBarWithProgress.Hpp $
// $Workfile: StatusBarWithProgress.Hpp $
//---------------------------------------------------------------------------

#ifndef __StatusBarWithProgress_Hpp__
#define __StatusBarWithProgress_Hpp__


//--- A status bar with a progress indicator --------------------------------

// The progress indicator is initially hidden, you can show it by 
// calling the ShowProgress member
// When it is visible, th progress bar is positioned after 
// the text in the first pane

class CStatusBarWithProgress : public CStatusBar
{
    DECLARE_DYNCREATE(CStatusBarWithProgress)

// Data members
protected:
    CProgressCtrl m_Progress;
    int           m_nProgressWidth;
    BOOL          m_bProgressVisible;

// Construction
public:
    CStatusBarWithProgress(int nProgressBarWidth =100);
    virtual BOOL Create(CWnd *pParentWnd, DWORD dwStyle =WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID =AFX_IDW_STATUS_BAR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusBarWithProgress)
	//}}AFX_VIRTUAL

// Implementation
public:
    BOOL IsProgressBarVisible() const     { return m_bProgressVisible; }
    void SetProgressBarWidth(int nWidth)  { m_nProgressWidth =nWidth;  }
    BOOL ShowProgressBar(BOOL bShow =TRUE);

    void SetRange(int nLower, int nUpper) { m_Progress.SetRange(nLower,nUpper); }
    int  SetPos(int nPos)                 { return m_Progress.SetPos(nPos);     }
    int  OffsetPos(int nPos)              { return m_Progress.OffsetPos(nPos);  }
    int  SetStep(int nStep)               { return m_Progress.SetStep(nStep);   }
    int  StepIt()                         { return m_Progress.StepIt();         }

// Helpers
private:
    void AdjustProgressBarPosition();

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusBarWithProgress)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif

