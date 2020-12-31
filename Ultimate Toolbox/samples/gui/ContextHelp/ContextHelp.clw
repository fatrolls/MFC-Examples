; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CContextHelpApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "contexthelp.h"
LastPage=0

ClassCount=6
Class1=CContextHelpApp
Class2=CContextHelpDlg
Class3=CTest2Page
Class4=CTestDialog
Class5=CTestPage
Class6=CTestSheet

ResourceCount=4
Resource1=IDD_COLOR
Resource2=IDD_TESTBOX
Resource3=IDD_CONTEXTHELP_DIALOG
Resource4=IDD_STYLE

[CLS:CContextHelpApp]
Type=0
BaseClass=CWinApp
HeaderFile=ContextHelp.h
ImplementationFile=ContextHelp.cpp
Filter=N
VirtualFilter=AC
LastObject=CContextHelpApp

[CLS:CContextHelpDlg]
Type=0
BaseClass=CDialog
HeaderFile=ContextHelpDlg.h
ImplementationFile=ContextHelpDlg.cpp

[CLS:CTest2Page]
Type=0
BaseClass=COXContextHelpPropertyPage
HeaderFile=test2page.h
ImplementationFile=test2page.cpp

[CLS:CTestDialog]
Type=0
BaseClass=COXContextHelpDialog
HeaderFile=TestDialog.h
ImplementationFile=TestDialog.cpp
LastObject=1004
Filter=D
VirtualFilter=dWC

[CLS:CTestPage]
Type=0
BaseClass=COXContextHelpPropertyPage
HeaderFile=testpage.h
ImplementationFile=testpage.cpp

[CLS:CTestSheet]
Type=0
BaseClass=COXContextHelpPropertySheet
HeaderFile=TestSheet.h
ImplementationFile=TestSheet.cpp
LastObject=1004

[DLG:IDD_CONTEXTHELP_DIALOG]
Type=1
Class=CContextHelpDlg
ControlCount=2
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816

[DLG:IDD_COLOR]
Type=1
Class=CTest2Page
ControlCount=5
Control1=IDC_SCROLLBAR2,scrollbar,1342177281
Control2=IDC_TESTCHECK1,button,1342242819
Control3=IDC_TESTCOMBO1,combobox,1344341251
Control4=IDC_TESTBUTTON2,button,1342242816
Control5=IDC_LIST1,listbox,1352728835

[DLG:IDD_TESTBOX]
Type=1
Class=CTestDialog
ControlCount=10
Control1=IDOK,button,1342373889
Control2=IDCANCEL,button,1342242816
Control3=IDC_BITMAP,static,1342244878
Control4=IDC_STATIC1,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_STATIC2,button,1342177287
Control7=1004,button,1342242816
Control8=IDC_CHECK1,button,1342242819
Control9=IDC_COMBO1,combobox,1344341251
Control10=IDC_SCROLLBAR1,scrollbar,1342177280

[DLG:IDD_STYLE]
Type=1
Class=CTestPage
ControlCount=5
Control1=IDC_STATIC3,button,1342177287
Control2=IDC_TESTEDIT,edit,1350631552
Control3=IDC_STATIC4,static,1342308364
Control4=IDC_TESTBUTTON,button,1342242816
Control5=IDC_CHECK3,button,1342242819

