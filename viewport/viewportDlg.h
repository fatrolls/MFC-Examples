// viewportDlg.h : header file
//

#if !defined(AFX_VIEWPORTDLG_H__53E3F86A_053B_417A_92E7_F381C66754D9__INCLUDED_)
#define AFX_VIEWPORTDLG_H__53E3F86A_053B_417A_92E7_F381C66754D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ArrowButton.h"
#include "DPLPDisplay.h"
#include "SpinButtonCtrl7.h"

/////////////////////////////////////////////////////////////////////////////
// CViewportDlg dialog

class CViewportDlg : public CDialog
{
// Construction
public:
        CViewportDlg(CWnd* pParent = NULL);     // standard constructor

// Dialog Data
        //{{AFX_DATA(CViewportDlg)
        enum { IDD = IDD_VIEWPORT_DIALOG };
        CStatic x_MagnificationY;
        CStatic x_MagnificationX;
        CButton x_Magnification;
        CStatic c_MagnificationY;
        CStatic c_MagnificationX;
        CStatic x_DragLogical;
        CStatic c_DragLogical;
        CStatic x_DragDevice;
        CStatic c_DragDevice;
        CButton x_Drag;
        CButton c_PS_SOLID;
        CButton c_PS_DOT;
        CButton c_PS_DASHDOTDOT;
        CButton c_PS_DASHDOT;
        CButton c_PS_DASH;
        CButton c_GridLines;
        CStatic c_BottomRight;
        CStatic c_TopLeft;
        CButton c_ResetWindowOrg;
        CButton c_ResetViewportOrg;
        CStatic c_WindowPercentY;
        CStatic c_WindowPercentX;
        CStatic c_ViewportPercentX;
        CStatic c_ViewportPercentY;
        CButton c_ResetViewportExt;
        CButton c_ResetWindowExt;
        CSpinButtonCtrl7 c_SpinPositive;
        CEdit   c_Positive;
        CStatic x_SetWindowExtY;
        CStatic x_SetViewportExtY;
        CStatic x_SetWindowExtX;
        CStatic x_SetViewportExtX;
        CStatic x_SetWIndowExtX;
        CStatic x_SetVIewportExtY;
        CEdit   c_SetWindowExtY;
        CStatic x_SetViewportY;
        CDPLPDisplay    c_Canvas;
        CButton c_MM_TWIPS;
        CButton c_MM_TEXT;
        CButton c_MM_LOMETRIC;
        CButton c_MM_LOENGLISH;
        CButton c_MM_ISOTROPIC;
        CButton c_MM_HIMETRIC;
        CButton c_MM_HIENGLISH;
        CButton c_MM_ANISOTROPIC;
        CButton x_Window;
        CButton x_Viewport;
        CSpinButtonCtrl7 c_SpinSetWindowOrgY;
        CSpinButtonCtrl7 c_SpinSetWindowOrgX;
        CSpinButtonCtrl7 c_SpinSetWindowExtY;
        CSpinButtonCtrl7 c_SpinSetWindowExtX;
        CSpinButtonCtrl7 c_SpinSetViewportOrgY;
        CSpinButtonCtrl7 c_SpinSetViewportOrgX;
        CSpinButtonCtrl7 c_SpinSetViewportExtY;
        CSpinButtonCtrl7 c_SpinSetViewportExtX;
        CSpinButtonCtrl7 c_SpinDeviceGrid;
        CSpinButtonCtrl7 c_SpinPhysicalY;
        CSpinButtonCtrl7 c_SpinPhysicalX;
        CSpinButtonCtrl7 c_SpinLogicalY;
        CSpinButtonCtrl7 c_SpinLogicalX;
        CSpinButtonCtrl7 c_SpinLogicalGrid;
        CEdit   c_SetWindowOrgY;
        CEdit   c_SetWindowOrgX;
        CButton x_SetWindowOrg;
        CEdit   c_SetWindowExtX;
        CButton x_SetWindowExt;
        CEdit   c_SetViewportOrgY;
        CEdit   c_SetViewportOrgX;
        CButton x_SetViewportOrg;
        CEdit   c_SetViewportExtY;
        CEdit   c_SetViewportExtX;
        CButton x_SetViewportExt;
        CEdit   c_DeviceGrid;
        CEdit   c_PhysicalY;
        CEdit   c_PhysicalX;
        CStatic c_MousePhysical;
        CStatic c_MouseLogical;
        CArrowButton c_LPtoDP;
        CEdit   c_LogicalY;
        CEdit   c_LogicalX;
        CEdit   c_LogicalGrid;
        CArrowButton c_DPtoLP;
        CButton c_Circles;
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CViewportDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        HICON m_hIcon;
        void updateControls();
        BOOL initialized;
        BOOL dragging;
        afx_msg LRESULT OnChildMouseMove(WPARAM, LPARAM);
        afx_msg LRESULT OnMouseDrag(WPARAM, LPARAM);
        afx_msg LRESULT OnMouseDragStart(WPARAM, LPARAM);
        afx_msg LRESULT OnMouseDragEnd(WPARAM, LPARAM);
        void SetInitialViewportExt();
        void SetInitialWindowExt();

        CPoint anchorD; // Device coordinates
        CPoint anchorL; // Logical coordinates
        CPoint anchorOrg;

        typedef enum {Viewport, Window} DragType;
        DragType DragMode;
        
        // Generated message map functions
        //{{AFX_MSG(CViewportDlg)
        virtual BOOL OnInitDialog();
        afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
        afx_msg void OnPaint();
        afx_msg HCURSOR OnQueryDragIcon();
        virtual void OnCancel();
        virtual void OnOK();
        afx_msg void OnClose();
        afx_msg void OnCircles();
        afx_msg void OnDptolp();
        afx_msg void OnChangeLogicalGrid();
        afx_msg void OnChangeLogicalX();
        afx_msg void OnChangeLogicalY();
        afx_msg void OnLptodp();
        afx_msg void OnMmAnisotropic();
        afx_msg void OnMmHienglish();
        afx_msg void OnMmHimetric();
        afx_msg void OnMmIsotropic();
        afx_msg void OnMmLoenglish();
        afx_msg void OnMmLometric();
        afx_msg void OnMmText();
        afx_msg void OnMmTwips();
        afx_msg void OnChangePhysicalX();
        afx_msg void OnChangePhysicalY();
        afx_msg void OnChangeDeviceGrid();
        afx_msg void OnChangeSetviewportextX();
        afx_msg void OnChangeSetviewportextY();
        afx_msg void OnChangeSetviewportorgX();
        afx_msg void OnChangeSetviewportorgY();
        afx_msg void OnChangeSetwindowextX();
        afx_msg void OnChangeSetwindowextY();
        afx_msg void OnChangeSetwindoworgX();
        afx_msg void OnChangeSetwindoworgY();
        afx_msg void OnResetviewportext();
        afx_msg void OnResetwindowext();
        afx_msg void OnChangePositive();
        afx_msg void OnResetwindoworg();
        afx_msg void OnResetviewportorg();
        afx_msg void OnGridLines();
        afx_msg void OnPsDash();
        afx_msg void OnPsDashdot();
        afx_msg void OnPsDashdotdot();
        afx_msg void OnPsDot();
        afx_msg void OnPsSolid();
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORTDLG_H__53E3F86A_053B_417A_92E7_F381C66754D9__INCLUDED_)
