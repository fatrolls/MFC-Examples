; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLayoutApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "layout.h"
LastPage=0

ClassCount=9
Class1=CChildFrame
Class2=CLayoutApp
Class3=CLayoutDoc
Class4=CLayoutView
Class5=CMainFrame
Class6=CResizingDialog
Class7=CResizingPropPage1
Class8=CResizingPropPage2
Class9=CResizingPropSheet

ResourceCount=6
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3=IDD_RESIZING_DIALOG
Resource4=IDD_LAYOUT_FORM
Resource5=IDD_PAGE1
Resource6=IDD_PAGE2

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CLayoutApp]
Type=0
BaseClass=CWinApp
HeaderFile=Layout.h
ImplementationFile=Layout.cpp
Filter=N
VirtualFilter=AC
LastObject=CLayoutApp

[CLS:CLayoutDoc]
Type=0
BaseClass=CDocument
HeaderFile=LayoutDoc.h
ImplementationFile=LayoutDoc.cpp

[CLS:CLayoutView]
Type=0
BaseClass=CFormView
HeaderFile=LayoutView.h
ImplementationFile=LayoutView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMyFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CResizingDialog]
Type=0
BaseClass=CDialog
HeaderFile=ResizingDialog.h
ImplementationFile=ResizingDialog.cpp
Filter=D
VirtualFilter=dWC
LastObject=CResizingDialog

[CLS:CResizingPropPage1]
Type=0
BaseClass=CPropertyPage
HeaderFile=ResizingPropPage.h
ImplementationFile=ResizingPropPage.cpp

[CLS:CResizingPropPage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=ResizingPropPage.h
ImplementationFile=ResizingPropPage.cpp

[CLS:CResizingPropSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=ResizingPropSheet.h
ImplementationFile=ResizingPropSheet.cpp

[DLG:IDD_LAYOUT_FORM]
Type=1
Class=CLayoutView
ControlCount=12
Control1=IDC_FRAME,button,1342177287
Control2=IDC_PICTURE,static,1342177283
Control3=IDC_EDIT,edit,1350631552
Control4=IDC_BUTTON,button,1342242816
Control5=IDC_TREE,SysTreeView32,1350631424
Control6=IDC_LIST,listbox,1352728835
Control7=IDC_PROGRESS,msctls_progress32,1350565888
Control8=IDC_SLIDER,msctls_trackbar32,1342242864
Control9=IDC_COMBO,combobox,1344340227
Control10=IDC_TEXT,static,1342308352
Control11=IDC_RADIO,button,1342189321
Control12=IDC_PICTURE2,static,1342177283

[DLG:IDD_RESIZING_DIALOG]
Type=1
Class=CResizingDialog
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PICTURE,static,1342177283
Control6=IDC_TEXT,static,1342308864
Control7=IDC_TREE,SysTreeView32,1350631424

[DLG:IDD_PAGE1]
Type=1
Class=CResizingPropPage1
ControlCount=3
Control1=IDC_FRAME,button,1342177287
Control2=IDC_EDIT,edit,1350631552
Control3=IDC_LIST,listbox,1352728835

[DLG:IDD_PAGE2]
Type=1
Class=CResizingPropPage2
ControlCount=3
Control1=IDC_FRAME,button,1342177287
Control2=IDC_EDIT,edit,1350631552
Control3=IDC_TREE,SysTreeView32,1350631424

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=IDM_SHOW_DIALOG
Command6=IDM_SHOW_PROPPAGE
Command7=ID_WINDOW_NEW
Command8=ID_WINDOW_CASCADE
Command9=ID_WINDOW_TILE_HORZ
Command10=ID_WINDOW_ARRANGE
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
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

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

