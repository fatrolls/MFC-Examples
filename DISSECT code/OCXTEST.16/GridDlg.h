//{{AFX_INCLUDES()
#include "gridctrl.h"
//}}AFX_INCLUDES
#if !defined(AFX_GRIDDLG_H__ED5CE7B1_B2C3_11D0_968D_444553540000__INCLUDED_)
#define AFX_GRIDDLG_H__ED5CE7B1_B2C3_11D0_968D_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GridDlg.h : header file
//

#define MAXCOL 7
#define MAXROW 14

/////////////////////////////////////////////////////////////////////////////
// CGridDlg dialog

class CGridDlg : public CDialog
{
// Construction
public:
        CGridDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
        double m_dArray[MAXCOL][MAXROW];
        //{{AFX_DATA(CGridDlg)
        enum { IDD = IDD_GRID };
        CGridCtrl       m_OcxGrid;
        CString m_cellValue;
        //}}AFX_DATA


// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CGridDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:

        // Generated message map functions
        //{{AFX_MSG(CGridDlg)
        virtual BOOL OnInitDialog();
        virtual void OnOK();
        virtual void OnCancel();
        afx_msg void OnUpdatevalue();
        afx_msg void OnSelChangeGrid();
        DECLARE_EVENTSINK_MAP()
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

private:
        void ComputeSums();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDLG_H__ED5CE7B1_B2C3_11D0_968D_444553540000__INCLUDED_)

