// datenDlg.h : header file
//

#include "dtime.h"

/////////////////////////////////////////////////////////////////////////////
// CDatentryDlg dialog

class CDatentryDlg : public CDialog
{
// Construction
public:
  CDatentryDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
  //{{AFX_DATA(CDatentryDlg)
  enum { IDD = IDD_DATENTRY_DIALOG };
    // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CDatentryDlg)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  HICON m_hIcon;

  CDateControl m_ctrlCDate;
  CLTimeSpanControl m_ctrlCLTimeSpan;
  CLTimeOfDayControl m_ctrlCLTimeOfDay;
  CLDateControl m_ctrlCLDate;

  CDate m_CDate;
  CLTimeSpan m_CLTimeSpan;
  CLTimeOfDay m_CLTimeOfDay;
  CLDate m_CLDate;


  // Generated message map functions
  //{{AFX_MSG(CDatentryDlg)
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();                        
  //}}AFX_MSG                                                 
  #ifndef _WIN32
  afx_msg void OnEditButton();
  #endif
  DECLARE_MESSAGE_MAP()
};
