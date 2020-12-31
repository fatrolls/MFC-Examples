; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListCtrlEx
LastTemplate=CHeaderCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Multiline.h"
LastPage=0

ClassCount=7
Class1=CMultilineApp
Class2=CMultilineDoc
Class3=CMultilineView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_MULTILINE_FORM
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CListCtrlEx
Class7=CHeaderCtrlEx
Resource3=IDR_MAINFRAME

[CLS:CMultilineApp]
Type=0
HeaderFile=Multiline.h
ImplementationFile=Multiline.cpp
Filter=N
LastObject=CMultilineApp

[CLS:CMultilineDoc]
Type=0
HeaderFile=MultilineDoc.h
ImplementationFile=MultilineDoc.cpp
Filter=N

[CLS:CMultilineView]
Type=0
HeaderFile=MultilineView.h
ImplementationFile=MultilineView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CMultilineView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Multiline.cpp
ImplementationFile=Multiline.cpp
Filter=D
LastObject=CAboutDlg

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
Class=CMainFrame
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

[DLG:IDD_MULTILINE_FORM]
Type=1
Class=CMultilineView
ControlCount=4
Control1=IDC_LIST,SysListView32,1350632453
Control2=IDC_LISTEDIT,edit,1350631552
Control3=ID_POPULATE,button,1342242816
Control4=ID_OK,button,1342242816

[CLS:CListCtrlEx]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CListCtrlEx
VirtualFilter=FWC

[CLS:CHeaderCtrlEx]
Type=0
HeaderFile=HeaderCtrlEx.h
ImplementationFile=HeaderCtrlEx.cpp
BaseClass=CHeaderCtrl
Filter=W
LastObject=CHeaderCtrlEx
VirtualFilter=JWC

