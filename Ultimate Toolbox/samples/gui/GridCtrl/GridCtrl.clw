; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COXGridEdit
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gridctrl.h"
LastPage=0

ClassCount=8
Class1=COXGridEdit
Class2=COXGridHeader
Class3=COXGridList
Class4=CGridCtrlDoc
Class5=CGridCtrlApp
Class6=CAboutDlg
Class7=CGridCtrlView
Class8=CMainFrame

ResourceCount=7
Resource1=IDR_GRIDCTTYPE (English (U.S.))
Resource2=IDR_MAINFRAME (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_GRIDCTRL_FORM (Dutch (Belgium))
Resource5=IDR_MAINFRAME
Resource6=IDR_GRIDCTTYPE
Resource7=IDD_ABOUTBOX

[CLS:COXGridEdit]
Type=0
BaseClass=CEdit
HeaderFile=\Ultimate ToolBox\Include\oxgridedit.h
ImplementationFile=\Ultimate ToolBox\Source\oxgridedit.cpp
LastObject=COXGridEdit

[CLS:COXGridHeader]
Type=0
BaseClass=CHeaderCtrl
HeaderFile=\Ultimate ToolBox\Include\OXGridHdr.h
ImplementationFile=\Ultimate ToolBox\Source\OXGridHdr.cpp

[CLS:COXGridList]
Type=0
BaseClass=CListCtrl
HeaderFile=\Ultimate ToolBox\Include\OXGridList.h
ImplementationFile=\Ultimate ToolBox\Source\OXGridList.cpp
LastObject=COXGridList

[CLS:CGridCtrlDoc]
Type=0
BaseClass=CDocument
HeaderFile=GridCdoc.h
ImplementationFile=GridCdoc.cpp

[CLS:CGridCtrlApp]
Type=0
BaseClass=CWinApp
HeaderFile=GridCtrl.h
ImplementationFile=GridCtrl.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GridCtrl.cpp
ImplementationFile=GridCtrl.cpp
LastObject=CAboutDlg

[CLS:CGridCtrlView]
Type=0
BaseClass=CFormView
HeaderFile=GridCvw.h
ImplementationFile=GridCvw.cpp
LastObject=CGridCtrlView

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp
LastObject=CMainFrame

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[DLG:IDD_GRIDCTRL_FORM]
Type=1
Class=CGridCtrlView

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_GRIDCTTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889

[DLG:IDD_GRIDCTRL_FORM (Dutch (Belgium))]
Type=1
Class=?
ControlCount=32
Control1=IDC_GENERIC1,SysListView32,1082328069
Control2=IDC_STATIC,static,1342308352
Control3=IDC_NUM_ROWS,edit,1350631552
Control4=IDC_NUM_ROWS_SPIN,msctls_updown32,1342177334
Control5=IDC_INSERT,button,1342242816
Control6=IDC_CLEAR,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_IMAGE_COLUMN,edit,1350633600
Control9=IDC_IMAGE_COLUMN_SPIN,msctls_updown32,1342177334
Control10=IDC_STATIC,button,1342177287
Control11=IDC_MULCHECK,button,1342242819
Control12=IDC_SHOW_SELECTION,button,1342242819
Control13=IDC_EDITCHECK,button,1342242819
Control14=IDC_AUTO_EDIT,button,1342242819
Control15=IDC_CHECKABLE,button,1342242822
Control16=IDC_SORTABLE,button,1342242819
Control17=IDC_GRIDLINES,button,1342242819
Control18=IDC_HORIZONTAL_GRID,button,1342242819
Control19=IDC_VERTICAL_GRID,button,1342242819
Control20=IDC_STATIC,button,1342177287
Control21=IDC_TEXT_COLOR,button,1342308361
Control22=IDC_TEXT_BK_COLOR,button,1342177289
Control23=IDC_GRID_BK_COLOR,button,1342177289
Control24=IDC_GRID_LINES_COLOR,button,1342177289
Control25=IDC_COLOR_BUTTON,button,1342373888
Control26=IDC_STATIC,button,1342177287
Control27=IDC_SET_FONT,button,1342242816
Control28=IDC_RESET_FONT,button,1342242816
Control29=IDC_GRIDCOLRESIZE,button,1342242819
Control30=IDC_RADIOLEFT,button,1342308361
Control31=IDC_RADIOCENTER,button,1342177289
Control32=IDC_RADIORIGHT,button,1342177289

[MNU:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_GRIDCTTYPE]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

