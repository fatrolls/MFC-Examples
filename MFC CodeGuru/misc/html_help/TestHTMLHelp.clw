; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataSheet
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestHTMLHelp.h"

ClassCount=5
Class1=CTestHTMLHelpApp
Class2=CTestHTMLHelpDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTHTMLHELP_DIALOG
Resource4=IDD_TESTHTMLHELP_DIALOG (English (U.S.))
Resource5=IDD_HELP_PAGE
Resource6=IDD_DATA
Class4=CDataPage
Class5=CDataSheet
Resource7=IDD_ABOUTBOX (English (U.S.))

[CLS:CTestHTMLHelpApp]
Type=0
HeaderFile=TestHTMLHelp.h
ImplementationFile=TestHTMLHelp.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CTestHTMLHelpDlg]
Type=0
HeaderFile=TestHTMLHelpDlg.h
ImplementationFile=TestHTMLHelpDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TestHTMLHelpDlg.h
ImplementationFile=TestHTMLHelpDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_TESTHTMLHELP_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CTestHTMLHelpDlg

[DLG:IDD_TESTHTMLHELP_DIALOG (English (U.S.))]
Type=1
Class=CTestHTMLHelpDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_TEST,button,1342242816
Control3=IDC_STATIC,static,1342308353

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DATA]
Type=1
Class=CDataPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CDataPage]
Type=0
HeaderFile=DataPage.h
ImplementationFile=DataPage.cpp
BaseClass=CPropertyPage
Filter=D

[DLG:IDD_HELP_PAGE]
Type=1
Class=?
ControlCount=0

[CLS:CDataSheet]
Type=0
HeaderFile=DataSheet.h
ImplementationFile=DataSheet.cpp
BaseClass=CPropertySheet
Filter=W

