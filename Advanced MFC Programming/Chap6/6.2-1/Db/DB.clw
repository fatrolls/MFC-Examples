; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDBDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DB.h"

ClassCount=6
Class1=CDBApp
Class2=CDBDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOG_PAGE2
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_PAGE1
Resource4=IDD_ABOUTBOX
Class4=CPage1
Class5=CPage2
Class6=CPage3
Resource5=IDD_DIALOG_PAGE3

[CLS:CDBApp]
Type=0
HeaderFile=DB.h
ImplementationFile=DB.cpp
Filter=N

[CLS:CDBDlg]
Type=0
HeaderFile=DBDlg.h
ImplementationFile=DBDlg.cpp
Filter=D
LastObject=CDBDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DBDlg.h
ImplementationFile=DBDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_PAGE1]
Type=1
Class=CPage1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PAGE2]
Type=1
Class=CPage2
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_PAGE3]
Type=1
Class=CPage3
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CPage1]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPage1

[CLS:CPage2]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPage2

[CLS:CPage3]
Type=0
HeaderFile=Page.h
ImplementationFile=Page.cpp
BaseClass=CDialog
Filter=D
LastObject=CPage3

