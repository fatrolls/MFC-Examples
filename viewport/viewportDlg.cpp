// viewportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
//#include "viewport.h"
#include "viewportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DECLARE_MESSAGE(UWM_MOUSEMOVE)
DECLARE_MESSAGE(UWM_MOUSEDRAG)
DECLARE_MESSAGE(UWM_MOUSEDRAGSTART)
DECLARE_MESSAGE(UWM_MOUSEDRAGEND)
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        //{{AFX_MSG(CAboutDlg)
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewportDlg dialog

/****************************************************************************
*                         CViewportDlg::CViewportDlg
* Inputs:
*       CWnd * pParent: Parent window
* Effect: 
*       Constructor
****************************************************************************/

CViewportDlg::CViewportDlg(CWnd* pParent /*=NULL*/)
        : CDialog(CViewportDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(CViewportDlg)
        //}}AFX_DATA_INIT
        // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
        m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
        initialized = FALSE;
        dragging = FALSE;
}

void CViewportDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CViewportDlg)
        DDX_Control(pDX, IDC_MAGNIFICATION_Y_CAPTION, x_MagnificationY);
        DDX_Control(pDX, IDC_MAGNIFICATION_X_CAPTION, x_MagnificationX);
        DDX_Control(pDX, IDC_MAGNIFICATION_CAPTION, x_Magnification);
        DDX_Control(pDX, IDC_MAGNIFICATION_Y, c_MagnificationY);
        DDX_Control(pDX, IDC_MAGNIFICATION_X, c_MagnificationX);
        DDX_Control(pDX, IDC_DRAG_LOGICAL_CAPTION, x_DragLogical);
        DDX_Control(pDX, IDC_DRAG_LOGICAL, c_DragLogical);
        DDX_Control(pDX, IDC_DRAG_DEVICE_CAPTION, x_DragDevice);
        DDX_Control(pDX, IDC_DRAG_DEVICE, c_DragDevice);
        DDX_Control(pDX, IDC_DRAG_CAPTION, x_Drag);
        DDX_Control(pDX, IDC_PS_SOLID, c_PS_SOLID);
        DDX_Control(pDX, IDC_PS_DOT, c_PS_DOT);
        DDX_Control(pDX, IDC_PS_DASHDOTDOT, c_PS_DASHDOTDOT);
        DDX_Control(pDX, IDC_PS_DASHDOT, c_PS_DASHDOT);
        DDX_Control(pDX, IDC_PS_DASH, c_PS_DASH);
        DDX_Control(pDX, IDC_GRID, c_GridLines);
        DDX_Control(pDX, IDC_BOTTOMRIGHT, c_BottomRight);
        DDX_Control(pDX, IDC_TOPLEFT, c_TopLeft);
        DDX_Control(pDX, IDC_RESETWINDOWORG, c_ResetWindowOrg);
        DDX_Control(pDX, IDC_RESETVIEWPORTORG, c_ResetViewportOrg);
        DDX_Control(pDX, IDC_WINDOW_PERCENT_Y, c_WindowPercentY);
        DDX_Control(pDX, IDC_WINDOW_PERCENT_X, c_WindowPercentX);
        DDX_Control(pDX, IDC_VIEWPORT_PERCENT_X, c_ViewportPercentX);
        DDX_Control(pDX, IDC_VIEWPORT_PERCENT_Y, c_ViewportPercentY);
        DDX_Control(pDX, IDC_RESETVIEWPORTEXT, c_ResetViewportExt);
        DDX_Control(pDX, IDC_RESETWINDOWEXT, c_ResetWindowExt);
        DDX_Control(pDX, IDC_SPINPOSITIVE, c_SpinPositive);
        DDX_Control(pDX, IDC_POSITIVE, c_Positive);
        DDX_Control(pDX, IDC_SETWINDOWEXT_Y_CAPTION, x_SetWindowExtY);
        DDX_Control(pDX, IDC_SETVIEWPORTEXT_Y_CAPTION, x_SetViewportExtY);
        DDX_Control(pDX, IDC_SETWINDOWEXT_X_CAPTION, x_SetWindowExtX);
        DDX_Control(pDX, IDC_SETVIEWPORTEXT_X_CAPTION, x_SetViewportExtX);
        DDX_Control(pDX, IDC_SETWINDOWEXT_Y, c_SetWindowExtY);
        DDX_Control(pDX, IDC_CANVAS, c_Canvas);
        DDX_Control(pDX, IDC_MM_TWIPS, c_MM_TWIPS);
        DDX_Control(pDX, IDC_MM_TEXT, c_MM_TEXT);
        DDX_Control(pDX, IDC_MM_LOMETRIC, c_MM_LOMETRIC);
        DDX_Control(pDX, IDC_MM_LOENGLISH, c_MM_LOENGLISH);
        DDX_Control(pDX, IDC_MM_ISOTROPIC, c_MM_ISOTROPIC);
        DDX_Control(pDX, IDC_MM_HIMETRIC, c_MM_HIMETRIC);
        DDX_Control(pDX, IDC_MM_HIENGLISH, c_MM_HIENGLISH);
        DDX_Control(pDX, IDC_MM_ANISOTROPIC, c_MM_ANISOTROPIC);
        DDX_Control(pDX, IDC_WINDOW_CAPTION, x_Window);
        DDX_Control(pDX, IDC_VIEWPORT_CAPTION, x_Viewport);
        DDX_Control(pDX, IDC_SPINSETWINDOWORG_Y, c_SpinSetWindowOrgY);
        DDX_Control(pDX, IDC_SPINSETWINDOWORG_X, c_SpinSetWindowOrgX);
        DDX_Control(pDX, IDC_SPINSETWINDOWEXT_Y, c_SpinSetWindowExtY);
        DDX_Control(pDX, IDC_SPINSETWINDOWEXT_X, c_SpinSetWindowExtX);
        DDX_Control(pDX, IDC_SPINSETVIEWPORTORG_Y, c_SpinSetViewportOrgY);
        DDX_Control(pDX, IDC_SPINSETVIEWPORTORG_X, c_SpinSetViewportOrgX);
        DDX_Control(pDX, IDC_SPINSETVIEWPORTEXT_Y, c_SpinSetViewportExtY);
        DDX_Control(pDX, IDC_SPINSETVIEWPORTEXT_X, c_SpinSetViewportExtX);
        DDX_Control(pDX, IDC_SPINDEVICE_GRID, c_SpinDeviceGrid);
        DDX_Control(pDX, IDC_SPINPHYSICAL_Y, c_SpinPhysicalY);
        DDX_Control(pDX, IDC_SPINPHYSICAL_X, c_SpinPhysicalX);
        DDX_Control(pDX, IDC_SPINLOGICAL_Y, c_SpinLogicalY);
        DDX_Control(pDX, IDC_SPINLOGICAL_X, c_SpinLogicalX);
        DDX_Control(pDX, IDC_SPINLOGICAL_GRID, c_SpinLogicalGrid);
        DDX_Control(pDX, IDC_SETWINDOWORG_Y, c_SetWindowOrgY);
        DDX_Control(pDX, IDC_SETWINDOWORG_X, c_SetWindowOrgX);
        DDX_Control(pDX, IDC_SETWINDOWORG_CAPTION, x_SetWindowOrg);
        DDX_Control(pDX, IDC_SETWINDOWEXT_X, c_SetWindowExtX);
        DDX_Control(pDX, IDC_SETWINDOWEXT_CAPTION, x_SetWindowExt);
        DDX_Control(pDX, IDC_SETVIEWPORTORG_Y, c_SetViewportOrgY);
        DDX_Control(pDX, IDC_SETVIEWPORTORG_X, c_SetViewportOrgX);
        DDX_Control(pDX, IDC_SETVIEWPORTORG_CAPTION, x_SetViewportOrg);
        DDX_Control(pDX, IDC_SETVIEWPORTEXT_Y, c_SetViewportExtY);
        DDX_Control(pDX, IDC_SETVIEWPORTEXT_X, c_SetViewportExtX);
        DDX_Control(pDX, IDC_SETVIEWPORTEXT_CAPTION, x_SetViewportExt);
        DDX_Control(pDX, IDC_DEVICE_GRID, c_DeviceGrid);
        DDX_Control(pDX, IDC_PHYSICAL_Y, c_PhysicalY);
        DDX_Control(pDX, IDC_PHYSICAL_X, c_PhysicalX);
        DDX_Control(pDX, IDC_MOUSE_PHYSICAL, c_MousePhysical);
        DDX_Control(pDX, IDC_MOUSE_LOGICAL, c_MouseLogical);
        DDX_Control(pDX, IDC_LPTODP, c_LPtoDP);
        DDX_Control(pDX, IDC_LOGICAL_Y, c_LogicalY);
        DDX_Control(pDX, IDC_LOGICAL_X, c_LogicalX);
        DDX_Control(pDX, IDC_LOGICAL_GRID, c_LogicalGrid);
        DDX_Control(pDX, IDC_DPTOLP, c_DPtoLP);
        DDX_Control(pDX, IDC_CIRCLES, c_Circles);
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewportDlg, CDialog)
        ON_REGISTERED_MESSAGE(UWM_MOUSEMOVE, OnChildMouseMove)
        ON_REGISTERED_MESSAGE(UWM_MOUSEDRAG, OnMouseDrag)
        ON_REGISTERED_MESSAGE(UWM_MOUSEDRAGSTART, OnMouseDragStart)
        ON_REGISTERED_MESSAGE(UWM_MOUSEDRAGEND, OnMouseDragEnd)
        //{{AFX_MSG_MAP(CViewportDlg)
        ON_WM_SYSCOMMAND()
        ON_WM_PAINT()
        ON_WM_QUERYDRAGICON()
        ON_WM_CLOSE()
        ON_BN_CLICKED(IDC_CIRCLES, OnCircles)
        ON_BN_CLICKED(IDC_DPTOLP, OnDptolp)
        ON_EN_CHANGE(IDC_LOGICAL_GRID, OnChangeLogicalGrid)
        ON_EN_CHANGE(IDC_LOGICAL_X, OnChangeLogicalX)
        ON_EN_CHANGE(IDC_LOGICAL_Y, OnChangeLogicalY)
        ON_BN_CLICKED(IDC_LPTODP, OnLptodp)
        ON_BN_CLICKED(IDC_MM_ANISOTROPIC, OnMmAnisotropic)
        ON_BN_CLICKED(IDC_MM_HIENGLISH, OnMmHienglish)
        ON_BN_CLICKED(IDC_MM_HIMETRIC, OnMmHimetric)
        ON_BN_CLICKED(IDC_MM_ISOTROPIC, OnMmIsotropic)
        ON_BN_CLICKED(IDC_MM_LOENGLISH, OnMmLoenglish)
        ON_BN_CLICKED(IDC_MM_LOMETRIC, OnMmLometric)
        ON_BN_CLICKED(IDC_MM_TEXT, OnMmText)
        ON_BN_CLICKED(IDC_MM_TWIPS, OnMmTwips)
        ON_EN_CHANGE(IDC_PHYSICAL_X, OnChangePhysicalX)
        ON_EN_CHANGE(IDC_PHYSICAL_Y, OnChangePhysicalY)
        ON_EN_CHANGE(IDC_DEVICE_GRID, OnChangeDeviceGrid)
        ON_EN_CHANGE(IDC_SETVIEWPORTEXT_X, OnChangeSetviewportextX)
        ON_EN_CHANGE(IDC_SETVIEWPORTEXT_Y, OnChangeSetviewportextY)
        ON_EN_CHANGE(IDC_SETVIEWPORTORG_X, OnChangeSetviewportorgX)
        ON_EN_CHANGE(IDC_SETVIEWPORTORG_Y, OnChangeSetviewportorgY)
        ON_EN_CHANGE(IDC_SETWINDOWEXT_X, OnChangeSetwindowextX)
        ON_EN_CHANGE(IDC_SETWINDOWEXT_Y, OnChangeSetwindowextY)
        ON_EN_CHANGE(IDC_SETWINDOWORG_X, OnChangeSetwindoworgX)
        ON_EN_CHANGE(IDC_SETWINDOWORG_Y, OnChangeSetwindoworgY)
        ON_BN_CLICKED(IDC_RESETVIEWPORTEXT, OnResetviewportext)
        ON_BN_CLICKED(IDC_RESETWINDOWEXT, OnResetwindowext)
        ON_EN_CHANGE(IDC_POSITIVE, OnChangePositive)
        ON_BN_CLICKED(IDC_RESETWINDOWORG, OnResetwindoworg)
        ON_BN_CLICKED(IDC_RESETVIEWPORTORG, OnResetviewportorg)
        ON_BN_CLICKED(IDC_GRID, OnGridLines)
        ON_BN_CLICKED(IDC_PS_DASH, OnPsDash)
        ON_BN_CLICKED(IDC_PS_DASHDOT, OnPsDashdot)
        ON_BN_CLICKED(IDC_PS_DASHDOTDOT, OnPsDashdotdot)
        ON_BN_CLICKED(IDC_PS_DOT, OnPsDot)
        ON_BN_CLICKED(IDC_PS_SOLID, OnPsSolid)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewportDlg message handlers

/****************************************************************************
*                         CViewportDlg::OnInitDialog
* Result: BOOL
*       TRUE, always (default focus to be used)
* Effect: 
*       Intializes the dialog controls
****************************************************************************/

BOOL CViewportDlg::OnInitDialog()
   {
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
       {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
           {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
           }
       }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);                 // Set big icon
    SetIcon(m_hIcon, FALSE);                // Set small icon
        
    // TODO: Add extra initialization here
    //****************************************************************
    // Intialize SetViewportOrg values
    //****************************************************************
    c_SpinSetViewportOrgX.SetRange32(-5000, 5000);
    c_SpinSetViewportOrgX.SetPos(0);
    c_SpinSetViewportOrgY.SetRange32(-5000, 5000);
    c_SpinSetViewportOrgY.SetPos(0);

    //****************************************************************
    // Initialize SetWindowOrg values
    //****************************************************************
    c_SpinSetWindowOrgX.SetRange32(-5000, 5000);
    c_SpinSetWindowOrgX.SetPos32(0);
    c_SpinSetWindowOrgY.SetRange32(-5000, 5000);
    c_SpinSetWindowOrgY.SetPos32(0);
        
    //****************************************************************
    // Initialize the grid parameter controls
    //****************************************************************
    c_SpinDeviceGrid.SetRange32(1, 5000);
    c_SpinDeviceGrid.SetPos32(50);
    c_Canvas.SetDeviceGrid(c_SpinDeviceGrid.GetPos32());

    c_SpinLogicalGrid.SetRange32(1, 5000);
    c_SpinLogicalGrid.SetPos32(50);
    c_Canvas.SetLogicalGrid(c_SpinLogicalGrid.GetPos32());

    c_SpinPositive.SetRange32(0, 5000);
    c_SpinPositive.SetPos32(100);
    c_Canvas.SetPositive(c_SpinPositive.GetPos32());

    c_GridLines.SetCheck(BST_CHECKED);

    //****************************************************************
    // Initialize the mapping mode buttons
    //****************************************************************
    CheckRadioButton(IDC_MM_TEXT, IDC_MM_ANISOTROPIC, IDC_MM_TEXT);
    c_Canvas.SetMapMode(MM_TEXT);

    //****************************************************************
    // Initialize the window and viewport extents
    //****************************************************************
    SetInitialWindowExt();
    SetInitialViewportExt();

    //****************************************************************
    // Set the line styles
    //****************************************************************
    CheckRadioButton(IDC_PS_SOLID, IDC_PS_DASHDOTDOT, IDC_PS_DOT);
    c_Canvas.SetLineStyle(PS_DOT);

    //****************************************************************
    // Initialize the LPtoDP and DPtoLP controls
    //****************************************************************
    //--------------------------------
    // Set the button arrow directions
    //--------------------------------
    c_LPtoDP.SetDirection(DrawArrow::ARROW_S);
    c_DPtoLP.SetDirection(DrawArrow::ARROW_N);

    //----------------
    // LP <> DP
    //----------------
    c_SpinLogicalX.SetRange32(-5000, 5000);
    c_SpinLogicalX.SetPos(0);
    c_SpinLogicalY.SetRange32(-5000, 5000);
    c_SpinLogicalY.SetPos(0);

    //****************************************************************
    // Initialization is complete
    //****************************************************************
    initialized = TRUE;
    
    OnLptodp(); // Must happen after Initialized is set TRUE

    OnGridLines(); // Must happen after initialized is set TRUE

    updateControls();
        
    return TRUE;  // return TRUE  unless you set the focus to a control
   }

void CViewportDlg::OnSysCommand(UINT nID, LPARAM lParam)
   {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
       {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
       }
    else
       {
        CDialog::OnSysCommand(nID, lParam);
       }
   }

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CViewportDlg::OnPaint() 
   {
    if (IsIconic())
       {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
       }
    else
       {
        CDialog::OnPaint();
       }
   }

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CViewportDlg::OnQueryDragIcon()
   {
    return (HCURSOR) m_hIcon;
   }

/****************************************************************************
*                            CViewportDlg::OnCancel
* Result: void
*       
* Effect: 
*       Does nothing. Overridden to keep <esc> key from terminating application
****************************************************************************/

void CViewportDlg::OnCancel() 
{
}

/****************************************************************************
*                             CViewportDlg::OnOK
* Result: void
*       
* Effect: 
*       Does nothing. Overridden to keep <enter> key from terminating application
****************************************************************************/

void CViewportDlg::OnOK() 
{
}

/****************************************************************************
*                            CViewportDlg::OnClose
* Result: void
*       
* Effect: 
*       Terminates the dialog. Allows the [x] button to close the dialog
****************************************************************************/

void CViewportDlg::OnClose() 
   {
    CDialog::OnOK();
   }

/****************************************************************************
*                           CViewportDlg::OnCircles
*                          CViewportDlg::OnGridLines
* Result: void
*       
* Effect: 
*       Enables/disables rectangular and circular grid line displays
****************************************************************************/

void CViewportDlg::OnCircles() 
   {
    c_Canvas.SetCircles(c_Circles.GetCheck() == BST_CHECKED);
   }

void CViewportDlg::OnGridLines() 
   {
    c_Canvas.SetGridLines(c_GridLines.GetCheck() == BST_CHECKED);
   }

/****************************************************************************
*                           CViewportDlg::OnDptolp
* Result: void
*       
* Effect: 
*       Implements DPtoLP given a set of input coordinates and the current
*       mapping mode
****************************************************************************/

void CViewportDlg::OnDptolp() 
   {
    CPoint pt;
    pt.x = c_SpinPhysicalX.GetPos32();
    pt.y = c_SpinPhysicalY.GetPos32();

    c_Canvas.DPtoLP(pt);

    c_SpinLogicalX.SetPos32(pt.x);
    c_SpinLogicalY.SetPos32(pt.y);
   }

/****************************************************************************
*                                  OnLptodp
* Result: void
*       
* Effect: 
*       Translates the points from logical to physical
****************************************************************************/

void CViewportDlg::OnLptodp() 
   {
    CPoint pt;
    pt.x = c_SpinLogicalX.GetPos32();
    pt.y = c_SpinLogicalY.GetPos32();

    c_Canvas.LPtoDP(pt);

    c_SpinPhysicalX.SetPos32(pt.x);
    c_SpinPhysicalY.SetPos32(pt.y);
   }

/****************************************************************************
*                      CViewportDlg::OnChangeLogicalGrid
* Result: void
*       
* Effect: 
*       Responds to changes in the device or logical grid sizes
****************************************************************************/

void CViewportDlg::OnChangeLogicalGrid() 
   {
    if(!initialized)
       return;
    c_Canvas.SetLogicalGrid(c_SpinLogicalGrid.GetPos32());
   }

void CViewportDlg::OnChangeDeviceGrid() 
   {
    if(!initialized)
        return;
    int n = c_SpinDeviceGrid.GetPos32();
    c_Canvas.SetDeviceGrid(n);
   }

/*****************************************************************************
*                              Manage LP/DP values
*****************************************************************************/
void CViewportDlg::OnChangeLogicalX() 
   {
   }

void CViewportDlg::OnChangeLogicalY() 
   {
   }

void CViewportDlg::OnChangePhysicalX() 
   {
    // TODO: Add your control notification handler code here
   }

void CViewportDlg::OnChangePhysicalY() 
   {
    // TODO: Add your control notification handler code here
   }

/*****************************************************************************
                             Setting mapping modes
                                 MM_ANISOTROPIC
                                  MM_ISOTROPIC
                                  MM_HIENGLISH
                                  MM_LOENGLISH
                                  MM_HIMETRIC
                                  MM_LOMETRIC
                                    MM_TEXT
                                    MM_TWIPS
*****************************************************************************/

void CViewportDlg::OnMmAnisotropic() 
   {
    c_Canvas.SetMapMode(MM_ANISOTROPIC);
    updateControls();
   }

void CViewportDlg::OnMmHienglish() 
   {
    c_Canvas.SetMapMode(MM_HIENGLISH);
    updateControls();
   }

void CViewportDlg::OnMmHimetric() 
   {
    c_Canvas.SetMapMode(MM_HIMETRIC);
    updateControls();
   }

void CViewportDlg::OnMmIsotropic() 
   {
    c_Canvas.SetMapMode(MM_ISOTROPIC);
    updateControls();
   }

void CViewportDlg::OnMmLoenglish() 
   {
    c_Canvas.SetMapMode(MM_LOENGLISH);
    updateControls();
   }

void CViewportDlg::OnMmLometric() 
   {
    c_Canvas.SetMapMode(MM_LOMETRIC);
    updateControls();
   }

void CViewportDlg::OnMmText() 
   {
    c_Canvas.SetMapMode(MM_TEXT);
    updateControls();
   }

void CViewportDlg::OnMmTwips() 
   {
    c_Canvas.SetMapMode(MM_TWIPS);
    updateControls();
   }


void CViewportDlg::OnChangeSetviewportextX() 
   {
    if(!initialized)
       return;
    c_Canvas.SetViewportExt(c_SpinSetViewportExtX.GetPos32(), c_SpinSetViewportExtY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetviewportextY() 
   {
    if(!initialized)
       return;
    c_Canvas.SetViewportExt(c_SpinSetViewportExtX.GetPos32(), c_SpinSetViewportExtY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetviewportorgX() 
   {
    if(!initialized)
        return;
    c_Canvas.SetViewportOrg(c_SpinSetViewportOrgX.GetPos32(), c_SpinSetViewportOrgY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetviewportorgY() 
   {
    if(!initialized)
        return;
    c_Canvas.SetViewportOrg(c_SpinSetViewportOrgX.GetPos32(), c_SpinSetViewportOrgY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetwindowextX() 
   {
    if(!initialized)
       return;
    c_Canvas.SetWindowExt(c_SpinSetWindowExtX.GetPos32(), c_SpinSetWindowExtY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetwindowextY() 
   {
    if(!initialized)
       return;
    c_Canvas.SetWindowExt(c_SpinSetWindowExtX.GetPos32(), c_SpinSetWindowExtY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetwindoworgX() 
   {
    if(!initialized)
        return;
    c_Canvas.SetWindowOrg(c_SpinSetWindowOrgX.GetPos32(), c_SpinSetWindowOrgY.GetPos32());
    updateControls();
   }

void CViewportDlg::OnChangeSetwindoworgY() 
   {
    if(!initialized)
        return;
    c_Canvas.SetWindowOrg(c_SpinSetWindowOrgX.GetPos32(), c_SpinSetWindowOrgY.GetPos32());
    updateControls();
   }

/****************************************************************************
*                        CViewportDlg::updateControls
* Result: void
*       
* Effect: 
*       Updates the controls
****************************************************************************/

void CViewportDlg::updateControls()
    {
     if(!initialized)
        return;
     BOOL AnyIsotropic = c_MM_ISOTROPIC.GetCheck() == BST_CHECKED ||
                         c_MM_ANISOTROPIC.GetCheck() == BST_CHECKED;

     BOOL Anisotropic = c_MM_ANISOTROPIC.GetCheck() == BST_CHECKED;

     //****************************************************************
     // +--SetWindowExt---------------+
     // |                             |
     // |  x   [ value ] [s]     100% |
     // |                    [R]      |
     // |  y   [ value ] [s]     100% |
     // +-----------------------------+
     //****************************************************************
     x_SetWindowExt.EnableWindow(AnyIsotropic);
     c_SpinSetWindowExtX.EnableWindow(AnyIsotropic);
     c_SetWindowExtX.EnableWindow(AnyIsotropic);
     x_SetWindowExtX.EnableWindow(AnyIsotropic);
     c_WindowPercentX.EnableWindow(AnyIsotropic);

     c_SpinSetWindowExtY.EnableWindow(AnyIsotropic);
     c_SetWindowExtY.EnableWindow(AnyIsotropic);
     x_SetWindowExtY.EnableWindow(AnyIsotropic);
     c_WindowPercentY.EnableWindow(AnyIsotropic);

     c_ResetWindowExt.EnableWindow(AnyIsotropic);

     //****************************************************************
     // +--SetViewportExt-------------+
     // |                             |
     // |  x   [ value ] [s]     100% |
     // |                    [R]      |
     // |  y   [ value ] [s]     100% |
     // +-----------------------------+
     //****************************************************************

     x_SetViewportExt.EnableWindow(AnyIsotropic);
     c_SpinSetViewportExtX.EnableWindow(AnyIsotropic);
     c_SetViewportExtX.EnableWindow(AnyIsotropic);
     x_SetViewportExtX.EnableWindow(AnyIsotropic);
     c_ViewportPercentX.EnableWindow(AnyIsotropic);

     c_SpinSetViewportExtY.EnableWindow(AnyIsotropic);
     c_SetViewportExtY.EnableWindow(AnyIsotropic);
     x_SetViewportExtY.EnableWindow(AnyIsotropic);
     c_ViewportPercentY.EnableWindow(AnyIsotropic);

     c_ResetViewportExt.EnableWindow(AnyIsotropic);
     
     //*****************************************************************************
     // Show the magnification factor
     //*****************************************************************************
     UINT show = AnyIsotropic ? SW_SHOW : SW_HIDE;

     x_Magnification.ShowWindow(show);

     c_MagnificationX.ShowWindow(show);
     x_MagnificationX.ShowWindow(show);

     c_MagnificationY.ShowWindow(show);
     x_MagnificationY.ShowWindow(show);
     //*****************************************************************************
     // Display the percentages of magnification
     //*****************************************************************************
     CRect r;
     c_Canvas.GetClientRect(&r);
     double pct;
     CString s;

     pct = 100.0 * (double)c_SpinSetViewportExtX.GetPos32() / (double)r.Width();
     s.Format(_T("%3.1f%%"), pct);
     c_ViewportPercentX.SetWindowText(s);

     pct = 100.0 * (double)c_SpinSetViewportExtY.GetPos32() / (double)r.Height();
     s.Format(_T("%3.1f%%"), pct);
     c_ViewportPercentY.SetWindowText(s);

     pct = 100.0 * (double)c_SpinSetWindowExtX.GetPos32() / (double)r.Width();
     s.Format(_T("%3.1f%%"), pct);
     c_WindowPercentX.SetWindowText(s);
     
     pct = 100.0 * (double)c_SpinSetWindowExtY.GetPos32() / (double)r.Height();
     s.Format(_T("%3.1f%%"), pct);
     c_WindowPercentY.SetWindowText(s);
     
     pct = 100.0 * (double)c_SpinSetViewportExtX.GetPos32() / (double)c_SpinSetWindowExtX.GetPos32();
     s.Format(_T("%3.1f%%"), pct);
     c_MagnificationX.SetWindowText(s);
     
     pct = 100.0 * (double)c_SpinSetViewportExtY.GetPos32() / (double)c_SpinSetWindowExtY.GetPos32();
     s.Format(_T("%3.1f%%"), pct);
     c_MagnificationY.SetWindowText(s);

     //*****************************************************************************
     // Display the window rect coordinates in logical coordinates
     //*****************************************************************************
     c_Canvas.DPtoLP(r);

     s.Format(_T("(%d, %d)"), r.left, r.top);
     c_TopLeft.SetWindowText(s);

     s.Format(_T("(%d, %d)"), r.right, r.bottom);
     c_BottomRight.SetWindowText(s);

     //*****************************************************************************
     // If in drag mode, show the drag windows, otherwise hide them
     //*****************************************************************************
     show = dragging ? SW_SHOW : SW_HIDE;
     x_Drag.ShowWindow(show);
     c_DragDevice.ShowWindow(show);
     x_DragDevice.ShowWindow(show);
     c_DragLogical.ShowWindow(show);
     x_DragLogical.ShowWindow(show);

    } // CViewportDlg::updateControls

/****************************************************************************
*                       CViewportDlg::OnChildMouseMove
* Inputs:
*       WPARAM: (WPARAM)(CPoint *)
*       LPARAM: 0
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Records the mouse position
****************************************************************************/

LRESULT CViewportDlg::OnChildMouseMove(WPARAM wParam, LPARAM)
    {
     CPoint * pt = (CPoint *)wParam;

     CString s;
     s.Format(_T("%d, %d"), pt->x, pt->y);
     c_MousePhysical.SetWindowText(s);

     c_Canvas.DPtoLP(*pt);

     s.Format(_T("%d, %d"), pt->x, pt->y);
     c_MouseLogical.SetWindowText(s);
     return 0;
    } // CViewportDlg::OnChildMouseMove

/****************************************************************************
*                      CViewportDlg::SetInitialWindowExt
* Result: void
*       
* Effect: 
*       Sets the initial window extent
****************************************************************************/

void CViewportDlg::SetInitialWindowExt()
    {
     CRect r;
     c_Canvas.GetClientRect(&r);

     c_SpinSetWindowExtX.SetRange32(-5000, 5000);
     c_SpinSetWindowExtX.SetPos32(r.Width());

     c_SpinSetWindowExtY.SetRange32(-5000, 5000);
     c_SpinSetWindowExtY.SetPos32(r.Height());
     
    } // CViewportDlg::SetInitialWindowExt

/****************************************************************************
*                     CViewportDlg::SetInitialViewportExt
* Result: void
*       
* Effect: 
*       Sets the initial Viewport ext
****************************************************************************/

void CViewportDlg::SetInitialViewportExt()
    {
     CRect r;
     c_Canvas.GetClientRect(&r);

     c_SpinSetViewportExtX.SetRange32(-5000, 5000);
     c_SpinSetViewportExtX.SetPos32(r.Width());

     c_SpinSetViewportExtY.SetRange32(-5000, 5000);
     c_SpinSetViewportExtY.SetPos32(r.Height());
    } // CViewportDlg::SetInitialViewportExt

/****************************************************************************
*                          CViewportDlg::OnMouseDrag
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) current position, client coordinates
*       LPARAM: (LPARAM)(CPoint *) current position, logical coordinates
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Drags the item around by adjusting the viewport (CTRL) or window org 
****************************************************************************/

LRESULT CViewportDlg::OnMouseDrag(WPARAM wParam, LPARAM lParam)
    {
     CPoint * dpt = (CPoint *)wParam;
     CPoint * lpt = (CPoint *)lParam;
     
     CSize motionD = CSize(dpt->x - anchorD.x, dpt->y - anchorD.y);
     TRACE2("motionD(%d, %d)\n", motionD.cx, motionD.cy);

     CString s;
     s.Format(_T("%d, %d"), motionD.cx, motionD.cy);
     c_DragDevice.SetWindowText(s);

     CSize motionL = motionD;

     switch(DragMode)
        { /* adjust sign */
         case Window:
            { /* window */
             c_Canvas.DPtoLP(motionL);
             CSize sign = c_Canvas.GetSign();
             motionL.cx *= sign.cx;
             motionL.cy *= sign.cy;
            } /* window */
            break;
         case Viewport:
            motionL.cx = -motionL.cx;
            motionL.cy = -motionL.cy;
            break;
        } /* adjust sign */

     s.Format(_T("%d, %d"), motionL.cx, motionL.cy);
     c_DragLogical.SetWindowText(s);
     
     TRACE2("motionL(%d, %d)\n", motionL.cx, motionL.cy);

     CPoint npt = CPoint(anchorOrg.x - motionL.cx, anchorOrg.y - motionL.cy);

     switch(DragMode)
        { /* DragMode */
         case Viewport:
            c_SpinSetViewportOrgX.SetPos32(npt.x);
            c_SpinSetViewportOrgY.SetPos32(npt.y);
            break;
         case Window:
            TRACE2("new SetWindowOrg(%d, %d)\n", npt.x, npt.y);
            c_SpinSetWindowOrgX.SetPos32(npt.x);
            c_SpinSetWindowOrgY.SetPos32(npt.y);
            break;
        } /* DragMode */

     return 0;
    } // CViewportDlg::OnMouseDrag

/****************************************************************************
*                       CViewportDlg::OnMouseDragStart
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) anchor point in client coordinates
*       LPARAM: (LPARAM)(CPoint *) anchor point in logical coordinates
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Records the anchor point
****************************************************************************/

LRESULT CViewportDlg::OnMouseDragStart(WPARAM wParam, LPARAM lParam)
    {
     CPoint * dpt = (CPoint *)wParam;
     CPoint * lpt = (CPoint *)lParam;
     anchorD = *dpt;
     anchorL = *lpt;
     //-----------------------------------------------------------------------------
     // Note that we set the drag mode at the START of the drag. If we tested
     // GetKeyState later and the user released the CTRL key, it could confuse the
     // mode of the drag, because we set our AnchorOrg based on the type of
     // drag we have initiated. One solution to this would be to store both
     // forms, but I chose to set the mode at the time of the drag start and
     // ignore the CTRL key state thereafter
     //-----------------------------------------------------------------------------
     if(::GetKeyState(VK_CONTROL) < 0)
        { /* viewport */
         anchorOrg = CPoint(c_SpinSetViewportOrgX.GetPos32(), c_SpinSetViewportOrgY.GetPos32());
         DragMode = Viewport;
        } /* viewport */
     else
        { /* window */
         anchorOrg = CPoint(c_SpinSetWindowOrgX.GetPos32(), c_SpinSetWindowOrgY.GetPos32());
         DragMode = Window;
        } /* window */
     dragging = TRUE;
     updateControls();
     return 0;
    } // CViewportDlg::OnMouseDragStart

/****************************************************************************
*                        CViewportDlg::OnMouseDragEnd
* Inputs:
*       WPARAM: (WPARAM)(CPoint *) anchor point in client coordinates
*       LPARAM: (LPARAM)(CPoint *) anchor point in logical coordinates
* Result: LRESULT
*       Logically void, 0, always
* Effect: 
*       Handles notification of drag-end
****************************************************************************/

LRESULT CViewportDlg::OnMouseDragEnd(WPARAM wParam, LPARAM lParam)
    {
     dragging = FALSE;
     updateControls();
     return 0;
    } // CViewportDlg::OnMouseDragEnd

/****************************************************************************
*                      CViewportDlg::OnResetviewportext
*                       CViewportDlg::OnResetwindowext
*                       CViewportDlg::OnResetwindoworg
*                      CViewportDlg::OnResetviewportorg
* Result: void
*       
* Effect: 
*       Resets the appropriate set of coordinates
****************************************************************************/

void CViewportDlg::OnResetviewportext() 
   {
    SetInitialViewportExt();
    updateControls();
   }

void CViewportDlg::OnResetwindowext() 
   {
    SetInitialWindowExt();
    updateControls();
   }

void CViewportDlg::OnResetwindoworg() 
   {
    c_SpinSetWindowOrgX.SetPos32(0);
    c_SpinSetWindowOrgY.SetPos32(0);
   }

void CViewportDlg::OnResetviewportorg() 
   {
    c_SpinSetViewportOrgX.SetPos32(0);
    c_SpinSetViewportOrgY.SetPos32(0);
   }

void CViewportDlg::OnChangePositive() 
   {
    if(!initialized)
        return;
    c_Canvas.SetPositive(c_SpinPositive.GetPos32());
    updateControls();
   }

/****************************************************************************
*                           CViewportDlg::OnPsDash
*                          CViewportDlg::OnPsDashdot
*                         CViewportDlg::OnPsDashdotdot
*                            CViewportDlg::OnPsDot
*                           CViewportDlg::OnPsSolid
* Result: void
*       
* Effect: 
*       Selects the desired line style
****************************************************************************/

void CViewportDlg::OnPsDash() 
   {
    c_Canvas.SetLineStyle(PS_DASH);
   }

void CViewportDlg::OnPsDashdot() 
   {
    c_Canvas.SetLineStyle(PS_DASHDOT);
   }

void CViewportDlg::OnPsDashdotdot() 
   {
    c_Canvas.SetLineStyle(PS_DASHDOTDOT);
   }

void CViewportDlg::OnPsDot() 
   {
    c_Canvas.SetLineStyle(PS_DOT);
   }

void CViewportDlg::OnPsSolid() 
   {
    c_Canvas.SetLineStyle(PS_SOLID);
   }
