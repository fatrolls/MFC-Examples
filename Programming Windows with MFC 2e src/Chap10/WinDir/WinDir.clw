; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPathDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinDir.h"
LastPage=0

ClassCount=6
Class1=CWinDirApp
Class2=CWinDirDoc
Class3=CFileView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CPathDialog
Resource3=IDD_NEWDIR

[CLS:CWinDirApp]
Type=0
HeaderFile=WinDir.h
ImplementationFile=WinDir.cpp
Filter=N

[CLS:CWinDirDoc]
Type=0
HeaderFile=WinDirDoc.h
ImplementationFile=WinDirDoc.cpp
Filter=N

[CLS:CFileView]
Type=0
HeaderFile=FileView.h
ImplementationFile=FileView.cpp
Filter=C
BaseClass=CListView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=WinDir.cpp
ImplementationFile=WinDir.cpp
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
Command1=ID_FILE_NEW_DIR
Command2=ID_APP_EXIT
Command3=ID_VIEW_LARGE_ICONS
Command4=ID_VIEW_SMALL_ICONS
Command5=ID_VIEW_LIST
Command6=ID_VIEW_DETAILS
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW_DIR
CommandCount=1

[DLG:IDD_NEWDIR]
Type=1
Class=CPathDialog
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PATH,edit,1350631552

[CLS:CPathDialog]
Type=0
HeaderFile=PathDialog.h
ImplementationFile=PathDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CPathDialog
VirtualFilter=dWC

