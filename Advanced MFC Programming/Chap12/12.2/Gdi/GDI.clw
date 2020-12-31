; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GDI.h"
LastPage=0

ClassCount=6
Class1=CGDIApp
Class2=CGDIDoc
Class3=CGDIView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CSelDlg
Resource3=IDD_DIALOG_SELECT

[CLS:CGDIApp]
Type=0
HeaderFile=GDI.h
ImplementationFile=GDI.cpp
Filter=N

[CLS:CGDIDoc]
Type=0
HeaderFile=GDIDoc.h
ImplementationFile=GDIDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_CAPTURE_SETTING

[CLS:CGDIView]
Type=0
HeaderFile=GDIView.h
ImplementationFile=GDIView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CGDIView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=GDI.cpp
ImplementationFile=GDI.cpp
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
Command16=ID_CAPTURE_GO
Command17=ID_CAPTURE_SETTING
Command18=ID_APP_ABOUT
CommandCount=18

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

[DLG:IDD_DIALOG_SELECT]
Type=1
Class=CSelDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_CURSOR,static,1342177283
Control4=IDC_STATIC,static,1342308352

[CLS:CSelDlg]
Type=0
HeaderFile=SelDlg.h
ImplementationFile=SelDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelDlg

