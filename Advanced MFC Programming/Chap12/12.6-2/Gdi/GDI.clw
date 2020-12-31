; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPrnDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GDI.h"
LastPage=0

ClassCount=7
Class1=CGDIApp
Class2=CGDIDoc
Class3=CGDIView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_DIALOG_SELECT
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CSelDlg
Resource3=IDD_ABOUTBOX
Class7=CPrnDlg
Resource4=PRINTDLG

[CLS:CGDIApp]
Type=0
HeaderFile=GDI.h
ImplementationFile=GDI.cpp
Filter=N
LastObject=ID_APP_ABOUT
BaseClass=CWinApp
VirtualFilter=AC

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
LastObject=1024

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

[CLS:CPrnDlg]
Type=0
HeaderFile=PrnDlg.h
ImplementationFile=PrnDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=1024

[DLG:PRINTDLG]
Type=1
Class=CPrnDlg
ControlCount=20
Control1=1093,static,1342308352
Control2=1088,static,1342308352
Control3=1072,button,1342177287
Control4=1056,button,1342373892
Control5=1057,button,1342177284
Control6=1058,button,1342177284
Control7=1089,static,1342308354
Control8=1152,edit,1350631426
Control9=1090,static,1342308354
Control10=1153,edit,1350631426
Control11=1091,static,1342308352
Control12=1136,combobox,1352859651
Control13=1092,static,1342308352
Control14=1154,edit,1350631426
Control15=1040,button,1342373891
Control16=1041,button,1342373891
Control17=IDOK,button,1342373889
Control18=IDCANCEL,button,1342373888
Control19=1024,button,1342373888
Control20=1038,button,1342373888

