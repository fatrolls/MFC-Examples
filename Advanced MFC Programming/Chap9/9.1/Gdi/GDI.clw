; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStyleDlg
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
Class6=CStyleDlg
Resource3=IDD_DIALOG_STYLE

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
LastObject=CGDIDoc

[CLS:CGDIView]
Type=0
HeaderFile=GDIView.h
ImplementationFile=GDIView.cpp
Filter=C

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FONT_SELECT



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
Command16=ID_FONT_SELECT
Command17=ID_FONT_STYLE
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

[DLG:IDD_DIALOG_STYLE]
Type=1
Class=CStyleDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_ESP,edit,1350631552
Control5=IDC_CHECK_TRANBK,button,1342242819

[CLS:CStyleDlg]
Type=0
HeaderFile=StyleDlg.h
ImplementationFile=StyleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStyleDlg
VirtualFilter=dWC

