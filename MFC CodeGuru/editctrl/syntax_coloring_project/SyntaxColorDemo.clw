; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSyntaxColorDemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SyntaxColorDemo.h"
LastPage=0

ClassCount=5
Class1=CSyntaxColorDemoApp
Class2=CSyntaxColorDemoDoc
Class3=CSyntaxColorDemoView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_SYNTAXCOLORDEMO_FORM
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Resource4=IDR_TEST

[CLS:CSyntaxColorDemoApp]
Type=0
HeaderFile=SyntaxColorDemo.h
ImplementationFile=SyntaxColorDemo.cpp
Filter=N

[CLS:CSyntaxColorDemoDoc]
Type=0
HeaderFile=SyntaxColorDemoDoc.h
ImplementationFile=SyntaxColorDemoDoc.cpp
Filter=N

[CLS:CSyntaxColorDemoView]
Type=0
HeaderFile=SyntaxColorDemoView.h
ImplementationFile=SyntaxColorDemoView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CSyntaxColorDemoView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_SHOW
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=SyntaxColorDemo.cpp
ImplementationFile=SyntaxColorDemo.cpp
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
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=IDM_RETAB
Command4=IDM_SHOW
CommandCount=4

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

[DLG:IDD_SYNTAXCOLORDEMO_FORM]
Type=1
Class=CSyntaxColorDemoView
ControlCount=0

[TB:IDR_MAINFRAME]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=IDM_SHOW
CommandCount=9

[MNU:IDR_TEST]
Type=1
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=IDM_RETAB
Command4=IDM_SHOW
Command5=IDM_TEST
CommandCount=5

