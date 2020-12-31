; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MCFileDialog
LastTemplate=CFileDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CDB.h"
LastPage=0

ClassCount=6
Class1=CCDBApp
Class2=CCDBDoc
Class3=CCDBView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=MCFileDialog
Resource2=IDR_MAINFRAME
Resource3=IDD_DIR

[CLS:CCDBApp]
Type=0
HeaderFile=CDB.h
ImplementationFile=CDB.cpp
Filter=N

[CLS:CCDBDoc]
Type=0
HeaderFile=CDBDoc.h
ImplementationFile=CDBDoc.cpp
Filter=N
LastObject=ID_FILEDIALOGBOX_DIRDIALOGOLD
BaseClass=CDocument
VirtualFilter=DC

[CLS:CCDBView]
Type=0
HeaderFile=CDBView.h
ImplementationFile=CDBView.cpp
Filter=C
LastObject=CCDBView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=CDB.cpp
ImplementationFile=CDB.cpp
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
Command16=ID_FILEDIALOGBOX_FILEOPEN
Command17=ID_FILEDIALOGBOX_FILESAVE
Command18=ID_FILEDIALOGBOX_CUSTOMIZEDFILEOPEN
Command19=ID_FILEDIALOGBOX_CUSTOMIZEFILEOPENOLD
Command20=ID_FILEDIALOGBOX_DIRDIALOG
Command21=ID_FILEDIALOGBOX_DIRDIALOGOLD
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

[CLS:MCFileDialog]
Type=0
HeaderFile=FileDlg.h
ImplementationFile=FileDlg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_DIR]
Type=1
Class=MCFileDialog
ControlCount=14
Control1=1090,static,1342308352
Control2=1152,edit,1350632576
Control3=1120,listbox,1352732755
Control4=65535,static,1342308352
Control5=1088,static,1342308480
Control6=1121,listbox,1352732755
Control7=1089,static,1342308352
Control8=1136,combobox,1352728643
Control9=1091,static,1342308352
Control10=1137,combobox,1352729427
Control11=IDOK,button,1342373889
Control12=IDCANCEL,button,1342373888
Control13=1038,button,1342373888
Control14=1040,button,1342373891

