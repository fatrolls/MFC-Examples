; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DriveTree.h"
LastPage=0

ClassCount=9
Class1=CDriveTreeApp
Class2=CDriveTreeDoc
Class3=CDriveTreeView
Class4=CMainFrame
Class9=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CDriveTreeApp]
Type=0
HeaderFile=DriveTree.h
ImplementationFile=DriveTree.cpp
Filter=N

[CLS:CDriveTreeDoc]
Type=0
HeaderFile=DriveTreeDoc.h
ImplementationFile=DriveTreeDoc.cpp
Filter=N

[CLS:CDriveTreeView]
Type=0
HeaderFile=DriveTreeView.h
ImplementationFile=DriveTreeView.cpp
Filter=C
BaseClass=CTreeView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=DriveTree.cpp
ImplementationFile=DriveTree.cpp
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
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

