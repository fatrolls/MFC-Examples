; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMRichView
LastTemplate=CRichEditView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "splitter.h"
LastPage=0

ClassCount=7
Class1=CSplitterApp
Class2=CSplitterDoc
Class3=CSplitterView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMFormView
Resource3=IDD_DIALOG
Class7=CMRichView

[CLS:CSplitterApp]
Type=0
HeaderFile=splitter.h
ImplementationFile=splitter.cpp
Filter=N

[CLS:CSplitterDoc]
Type=0
HeaderFile=splitterDoc.h
ImplementationFile=splitterDoc.cpp
Filter=N
LastObject=CSplitterDoc

[CLS:CSplitterView]
Type=0
HeaderFile=splitterView.h
ImplementationFile=splitterView.cpp
Filter=C
LastObject=CSplitterView
BaseClass=CTreeView
VirtualFilter=VWC

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
HeaderFile=splitter.cpp
ImplementationFile=splitter.cpp
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
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_APP_ABOUT
CommandCount=10

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

[DLG:IDD_DIALOG]
Type=1
Class=CMFormView
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_RADIO1,button,1342177289
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_RADIO3,button,1342177289
Control9=IDC_STATIC,button,1342177287

[CLS:CMFormView]
Type=0
HeaderFile=CMFormView.h
ImplementationFile=CMFormView.cpp
BaseClass=CFormView
Filter=D

[CLS:CMRichView]
Type=0
HeaderFile=CMRichView.h
ImplementationFile=CMRichView.cpp
BaseClass=CRichEditView
Filter=C

