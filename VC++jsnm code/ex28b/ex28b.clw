; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex28b.h"
LastPage=0

ClassCount=6
Class1=CEx28bApp
Class2=CAboutDlg
Class3=CEx28bDoc
Class4=CEx28bSet
Class5=CEx28bView
Class6=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Resource3="IDD_EX28B_FORM"

[CLS:CEx28bApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex28b.h
ImplementationFile=ex28b.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex28b.cpp
ImplementationFile=ex28b.cpp
LastObject=CAboutDlg

[CLS:CEx28bDoc]
Type=0
BaseClass=CDocument
HeaderFile=ex28bDoc.h
ImplementationFile=ex28bDoc.cpp

[CLS:CEx28bSet]
Type=0
HeaderFile=ex28bSet.h
ImplementationFile=ex28bSet.cpp

[CLS:CEx28bView]
Type=0
BaseClass=CRecordView
HeaderFile=ex28bView.h
ImplementationFile=ex28bView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DB:CEx28bSet]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EX28B_FORM]
Type=1
Class=CEx28bView

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_RECORD_FIRST
Command7=ID_RECORD_PREV
Command8=ID_RECORD_NEXT
Command9=ID_RECORD_LAST
Command10=ID_RECORD_ADD
Command11=ID_RECORD_CLEARFIELDS
Command12=ID_RECORD_DELETE
Command13=ID_RECORD_UPDATE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
CommandCount=10

[DLG:"IDD_EX28B_FORM"]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ID,edit,1350631552
Control6=IDC_NAME,edit,1350631552
Control7=IDC_ROOM,edit,1350631552

