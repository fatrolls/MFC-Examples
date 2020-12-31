; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEditCtrlView
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "outlookstyle.h"
LastPage=0

ClassCount=10
Class1=CMainFrame
Class2=COutLookStyleApp
Class3=CAboutDlg
Class4=COutLookStyleDoc
Class5=COutLookStyleView
Class6=CRightPaneFrame

ResourceCount=5
Resource1=IDD_LISTCTRLVIEW
Resource2=IDD_TREEVIEW
Class7=CLeftPaneView
Resource3=IDR_MAINFRAME
Class8=CSplitterView
Class9=CListCtrlView
Resource4=IDD_ABOUTBOX
Resource5=IDD_EDITVIEW
Class10=CEditCtrlView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:COutLookStyleApp]
Type=0
BaseClass=CWinApp
HeaderFile=OutLookStyle.h
ImplementationFile=OutLookStyle.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=OutLookStyle.cpp
ImplementationFile=OutLookStyle.cpp
LastObject=CAboutDlg

[CLS:COutLookStyleDoc]
Type=0
BaseClass=CDocument
HeaderFile=OutLookStyleDoc.h
ImplementationFile=OutLookStyleDoc.cpp

[CLS:COutLookStyleView]
Type=0
BaseClass=CView
HeaderFile=OutLookStyleView.h
ImplementationFile=OutLookStyleView.cpp

[CLS:CRightPaneFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=RightPaneFrame.h
ImplementationFile=RightPaneFrame.cpp
Filter=T
VirtualFilter=fWC
LastObject=CRightPaneFrame

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

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

[CLS:CLeftPaneView]
Type=0
HeaderFile=LeftPaneView.h
ImplementationFile=LeftPaneView.cpp
BaseClass=CFormView
Filter=D
LastObject=CLeftPaneView
VirtualFilter=VWC

[CLS:CSplitterView]
Type=0
HeaderFile=SplitterView.h
ImplementationFile=SplitterView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CSplitterView

[CLS:CListCtrlView]
Type=0
HeaderFile=ListCtrlView.h
ImplementationFile=ListCtrlView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CListCtrlView

[DLG:IDD_LISTCTRLVIEW]
Type=1
Class=CListCtrlView
ControlCount=1
Control1=IDC_LIST,SysListView32,1350631425

[DLG:IDD_TREEVIEW]
Type=1
Class=CLeftPaneView
ControlCount=1
Control1=IDC_TREE,SysTreeView32,1350631463

[DLG:IDD_EDITVIEW]
Type=1
Class=CEditCtrlView
ControlCount=1
Control1=IDC_EDIT,edit,1350631556

[CLS:CEditCtrlView]
Type=0
HeaderFile=EditCtrlView.h
ImplementationFile=EditCtrlView.cpp
BaseClass=CFormView
Filter=D
LastObject=CEditCtrlView
VirtualFilter=VWC

