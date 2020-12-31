; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpecialFileDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex07b.h"
LastPage=0

ClassCount=6
Class1=CEx07bApp
Class2=CEx07bDoc
Class3=CEx07bView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDD_FILESPECIAL
Class6=CSpecialFileDialog

[CLS:CEx07bApp]
Type=0
HeaderFile=ex07b.h
ImplementationFile=ex07b.cpp
Filter=N

[CLS:CEx07bDoc]
Type=0
HeaderFile=ex07bDoc.h
ImplementationFile=ex07bDoc.cpp
Filter=N

[CLS:CEx07bView]
Type=0
HeaderFile=ex07bView.h
ImplementationFile=ex07bView.cpp
Filter=C
LastObject=CEx07bView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=ex07b.cpp
ImplementationFile=ex07b.cpp
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

[DLG:IDD_FILESPECIAL]
Type=1
Class=CSpecialFileDialog
ControlCount=2
Control1=IDC_DELETE,button,1342242816
Control2=stc32,button,1073741831

[CLS:CSpecialFileDialog]
Type=0
HeaderFile=SpecFileDlg.h
ImplementationFile=SpecFileDlg.cpp
BaseClass=CFileDialog
Filter=D
LastObject=CSpecialFileDialog
VirtualFilter=dWC

