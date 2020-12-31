; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHelpDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Help.h"
LastPage=0

ClassCount=6
Class1=CHelpApp
Class2=CHelpDoc
Class3=CHelpView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_DIALOG
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CHelpDlg
Resource3=IDR_MAINFRAME

[CLS:CHelpApp]
Type=0
HeaderFile=Help.h
ImplementationFile=Help.cpp
Filter=N

[CLS:CHelpDoc]
Type=0
HeaderFile=HelpDoc.h
ImplementationFile=HelpDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CHelpDoc

[CLS:CHelpView]
Type=0
HeaderFile=HelpView.h
ImplementationFile=HelpView.cpp
Filter=C
LastObject=ID_HELPTEST_TESTA

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=Help.cpp
ImplementationFile=Help.cpp
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
Command16=ID_HELPTEST_TESTA
Command17=ID_HELPTEST_TESTB
Command18=ID_HELPTEST_TESTC
Command19=ID_HELPTEST_TESTD
Command20=ID_HELPTEST_DIALOG
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

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
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

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
Command8=ID_HELPTEST_TESTA
Command9=ID_HELPTEST_TESTB
Command10=ID_HELPTEST_TESTC
Command11=ID_HELPTEST_TESTD
Command12=ID_APP_ABOUT
Command13=ID_CONTEXT_HELP
CommandCount=13

[DLG:IDD_DIALOG]
Type=1
Class=CHelpDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT,edit,1350631552
Control4=IDC_BUTTON,button,1342242816
Control5=IDC_RADIO,button,1342177289
Control6=IDC_COMBO,combobox,1344340226
Control7=IDC_STATIC,button,1342177287

[CLS:CHelpDlg]
Type=0
HeaderFile=HelpDlg.h
ImplementationFile=HelpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelpDlg
VirtualFilter=dWC

