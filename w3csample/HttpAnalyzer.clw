; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHttpAnalyzerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HttpAnalyzer.h"
LastPage=0

ClassCount=6
Class1=CHttpAnalyzerApp
Class2=CHttpAnalyzerDoc
Class3=CHttpAnalyzerView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CAnalyzerDlg
Resource3=IDD_ANALYZER

[CLS:CHttpAnalyzerApp]
Type=0
HeaderFile=HttpAnalyzer.h
ImplementationFile=HttpAnalyzer.cpp
Filter=N

[CLS:CHttpAnalyzerDoc]
Type=0
HeaderFile=HttpAnalyzerDoc.h
ImplementationFile=HttpAnalyzerDoc.cpp
Filter=N

[CLS:CHttpAnalyzerView]
Type=0
HeaderFile=HttpAnalyzerView.h
ImplementationFile=HttpAnalyzerView.cpp
Filter=C
LastObject=CHttpAnalyzerView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=HttpAnalyzer.cpp
ImplementationFile=HttpAnalyzer.cpp
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
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13

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

[DLG:IDD_ANALYZER]
Type=1
Class=CAnalyzerDlg
ControlCount=4
Control1=IDC_GO,button,1342242816
Control2=IDC_URL,edit,1350631552
Control3=IDC_HEADER,edit,1352734788
Control4=IDC_SOURCE,edit,1352734788

[CLS:CAnalyzerDlg]
Type=0
HeaderFile=AnalyzerDlg.h
ImplementationFile=AnalyzerDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAnalyzerDlg

