; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CActiveXDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex08a.h"
LastPage=0

ClassCount=6
Class1=CEx08aApp
Class2=CEx08aDoc
Class3=CEx08aView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CActiveXDialog
Resource3=IDD_ACTIVEXDIALOG

[CLS:CEx08aApp]
Type=0
HeaderFile=ex08a.h
ImplementationFile=ex08a.cpp
Filter=N

[CLS:CEx08aDoc]
Type=0
HeaderFile=ex08aDoc.h
ImplementationFile=ex08aDoc.cpp
Filter=N

[CLS:CEx08aView]
Type=0
HeaderFile=ex08aView.h
ImplementationFile=ex08aView.cpp
Filter=C
LastObject=CEx08aView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=ex08a.cpp
ImplementationFile=ex08a.cpp
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

[DLG:IDD_ACTIVEXDIALOG]
Type=1
Class=CActiveXDialog
ControlCount=11
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_CALENDAR1,{8E27C92B-1264-101C-8A2F-040224009C02},1342242816
Control4=IDC_SELECTDATE,button,1342242817
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DAY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MONTH,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_YEAR,edit,1350631552
Control11=IDC_NEXTWEEK,button,1342242816

[CLS:CActiveXDialog]
Type=0
HeaderFile=ActiveXDialog.h
ImplementationFile=ActiveXDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DAY

