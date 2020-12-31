; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EZPrint.h"
LastPage=0

ClassCount=9
Class1=CEZPrintApp
Class2=CEZPrintDoc
Class3=CEZPrintView
Class4=CMainFrame
Class9=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CEZPrintApp]
Type=0
HeaderFile=EZPrint.h
ImplementationFile=EZPrint.cpp
Filter=N

[CLS:CEZPrintDoc]
Type=0
HeaderFile=EZPrintDoc.h
ImplementationFile=EZPrintDoc.cpp
Filter=N

[CLS:CEZPrintView]
Type=0
HeaderFile=EZPrintView.h
ImplementationFile=EZPrintView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=EZPrint.cpp
ImplementationFile=EZPrint.cpp
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
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
CommandCount=1

