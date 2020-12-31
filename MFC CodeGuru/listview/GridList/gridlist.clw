; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGridListCtrl
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gridlist.h"
LastPage=0

ClassCount=9
Class1=CGridlistApp
Class2=CGridlistDoc
Class3=CGridlistView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=TestDlg
Class7=CGridList
Class8=CGridListCtrl
Class9=CVirtualGridListCtrl
Resource3=IDD_DIALOG1

[CLS:CGridlistApp]
Type=0
HeaderFile=gridlist.h
ImplementationFile=gridlist.cpp
Filter=N

[CLS:CGridlistDoc]
Type=0
HeaderFile=gridlistDoc.h
ImplementationFile=gridlistDoc.cpp
Filter=N

[CLS:CGridlistView]
Type=0
HeaderFile=gridlistView.h
ImplementationFile=gridlistView.cpp
Filter=C
LastObject=CGridlistView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=gridlist.cpp
ImplementationFile=gridlist.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_TEST_GRIDLIST
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_APP_ABOUT
CommandCount=14

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG1]
Type=1
Class=TestDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350631945

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

[CLS:TestDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST

[CLS:CGridList]
Type=0
HeaderFile=GridList.h
ImplementationFile=GridList.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CGridList

[CLS:CGridListCtrl]
Type=0
HeaderFile=GridListCtrl.h
ImplementationFile=GridListCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CGridListCtrl
VirtualFilter=FWC

[CLS:CVirtualGridListCtrl]
Type=0
HeaderFile=VirtualGridListCtrl.h
ImplementationFile=VirtualGridListCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CVirtualGridListCtrl
VirtualFilter=FWC

