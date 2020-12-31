; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyPropertyPage2
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestDialog.h"

ClassCount=6
Class1=CTestDialogApp
Class2=CTestDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTDIALOG_DIALOG
Resource4=IDD_PROPPAGE1 (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_PROPPAGE1
Resource7=IDD_PROPPAGE2
Class4=CMyPropertySheet
Class5=CMyPropertyPage1
Class6=CMyPropertyPage2
Resource8=IDD_TESTDIALOG_DIALOG (English (U.S.))
Resource9=IDD_PROPPAGE2 (English (U.S.))

[CLS:CTestDialogApp]
Type=0
HeaderFile=TestDialog.h
ImplementationFile=TestDialog.cpp
Filter=N

[CLS:CAboutDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
Filter=D
BaseClass=cdxCSizingDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_TESTDIALOG_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CTestDlg

[DLG:IDD_TESTDIALOG_DIALOG (English (U.S.))]
Type=1
Class=CTestDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RESIZE,static,1342312961
Control4=IDC_NONE,static,1342312961
Control5=IDC_REL,static,1342312961
Control6=IDC_REPOS2,static,1342312961
Control7=IDC_REPOS,static,1342312961
Control8=IDC_REL2,static,1342312961
Control9=IDC_HEADER,static,1342308353

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CTestDlg]
Type=0
HeaderFile=testdlg.h
ImplementationFile=testdlg.cpp
BaseClass=cdxCSizingDialog
LastObject=IDCANCEL
Filter=D
VirtualFilter=dWC

[DLG:IDD_PROPPAGE1]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352
Class=CMyPropertyPage1

[DLG:IDD_PROPPAGE2]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352
Class=CMyPropertyPage2

[CLS:CMyPropertySheet]
Type=0
HeaderFile=MyPropertySheet.h
ImplementationFile=MyPropertySheet.cpp
BaseClass=CPropertySheet

[CLS:CMyPropertyPage1]
Type=0
HeaderFile=MyPropertyPage1.h
ImplementationFile=MyPropertyPage1.cpp
BaseClass=cdxCSizingPropPage
LastObject=CMyPropertyPage1

[CLS:CMyPropertyPage2]
Type=0
HeaderFile=MyPropertyPage1.h
ImplementationFile=MyPropertyPage1.cpp
BaseClass=cdxCSizingPropPage
LastObject=CMyPropertyPage2

[DLG:IDD_PROPPAGE1 (English (U.S.))]
Type=1
Class=CMyPropertyPage1
ControlCount=1
Control1=IDC_EDIT,edit,1350631556

[DLG:IDD_PROPPAGE2 (English (U.S.))]
Type=1
Class=CMyPropertyPage2
ControlCount=2
Control1=IDC_VSCROLLBAR,scrollbar,1342177281
Control2=IDC_HSCROLLBAR,scrollbar,1342177280

