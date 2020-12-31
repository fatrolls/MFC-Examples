; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAdviseDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DDESrv.h"
LastPage=0

ClassCount=6
Class1=CDDESrvApp
Class2=CDDESrvDoc
Class3=CDDESrvView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDD_DIALOG_ADVISE
Class6=CAdviseDialog

[CLS:CDDESrvApp]
Type=0
HeaderFile=DDESrv.h
ImplementationFile=DDESrv.cpp
Filter=N

[CLS:CDDESrvDoc]
Type=0
HeaderFile=DDEDoc.h
ImplementationFile=DDEDoc.cpp
Filter=N

[CLS:CDDESrvView]
Type=0
HeaderFile=DDEView.h
ImplementationFile=DDEView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CDDESrvView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=DDESrv.cpp
ImplementationFile=DDESrv.cpp
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
Command11=ID_DDE_DISCONNECT
Command12=ID_DDE_ADVISE
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

[DLG:IDD_DIALOG_ADVISE]
Type=1
Class=CAdviseDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CAdviseDialog]
Type=0
HeaderFile=Advise.h
ImplementationFile=Advise.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT

