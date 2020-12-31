; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHyperLink
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "HypLnkEx.h"

ClassCount=4
Class1=CHypLnkExApp
Class2=CHypLnkExDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_HYPLNKEX_DIALOG
Class4=CHyperLink
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDR_MENU1
Resource6=IDD_HYPLNKEX_DIALOG (English (U.S.))

[CLS:CHypLnkExApp]
Type=0
HeaderFile=HypLnkEx.h
ImplementationFile=HypLnkEx.cpp
Filter=N

[CLS:CHypLnkExDlg]
Type=0
HeaderFile=HypLnkExDlg.h
ImplementationFile=HypLnkExDlg.cpp
Filter=D
LastObject=IDC_CHECK1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=HypLnkExDlg.h
ImplementationFile=HypLnkExDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[DLG:IDD_HYPLNKEX_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CHypLnkExDlg

[CLS:CHyperLink]
Type=0
HeaderFile=hyperlink.h
ImplementationFile=hyperlink.cpp
BaseClass=CStatic
LastObject=CHyperLink
Filter=W
VirtualFilter=WC

[DLG:IDD_HYPLNKEX_DIALOG (English (U.S.))]
Type=1
Class=CHypLnkExDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_HYPERLINK1,static,1342242816
Control4=IDC_HYPERLINK2,static,1342242816
Control5=IDC_HYPERLINK3,static,1342242816
Control6=IDC_HYPERLINK4,static,1342242816
Control7=IDC_HYPERLINK5,static,1342177806
Control8=IDC_CHECK1,button,1342242819
Control9=IDC_CHECK2,button,1342242819
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342177294
Control12=IDC_CHECK3,button,1342242819
Control13=IDC_CHECK4,button,1342242819
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU1]
Type=1
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
CommandCount=3

