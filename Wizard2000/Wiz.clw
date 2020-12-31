; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHardwarePage
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Wiz.h"

ClassCount=8
Class1=CWizApp
Class2=CWizDlg

ResourceCount=6
Resource2=IDD_WIZARD
Resource1=IDR_MAINFRAME
Class3=CSetupPage
Resource3=IDW_HARDWARE
Class4=CMasterDlg
Resource4=IDD_WIZ_DIALOG
Resource5=IDW_SETUP
Class5=CPrinterPage
Class6=CHardwarePage
Class7=CNewWizDialog
Class8=CNewWizPage
Resource6=IDW_PRINTER

[CLS:CWizApp]
Type=0
HeaderFile=Wiz.h
ImplementationFile=Wiz.cpp
Filter=N

[CLS:CWizDlg]
Type=0
HeaderFile=WizDlg.h
ImplementationFile=WizDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDB_DIALOG_WIZ



[DLG:IDD_WIZ_DIALOG]
Type=1
Class=CWizDlg
ControlCount=1
Control1=IDB_DIALOG_WIZ,button,1342242816

[DLG:IDD_WIZARD]
Type=1
Class=CMasterDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=ID_WIZFINISH,button,1342242816
Control3=ID_WIZNEXT,button,1342242816
Control4=ID_WIZBACK,button,1342242816
Control5=IDC_SHEETRECT,static,1342177298

[CLS:CMasterDlg]
Type=0
HeaderFile=MasterDlg.h
ImplementationFile=MasterDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMasterDlg
VirtualFilter=dWC

[CLS:CNewWizDialog]
Type=0
HeaderFile=NewWizDialog.h
ImplementationFile=NewWizDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewWizDialog

[CLS:CNewWizPage]
Type=0
HeaderFile=NewWizPage.h
ImplementationFile=NewWizPage.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewWizPage
VirtualFilter=dWC

[DLG:IDW_SETUP]
Type=1
Class=CSetupPage
ControlCount=6
Control1=IDC_STATIC,static,1342177294
Control2=IDC_EDIT1,edit,1352728580
Control3=ST_CAPTION,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=RB_ACCEPT,button,1342177289
Control6=RB_DECLINE,button,1342177289

[CLS:CSetupPage]
Type=0
HeaderFile=SetupPage.h
ImplementationFile=SetupPage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=ST_CAPTION

[DLG:IDW_HARDWARE]
Type=1
Class=CHardwarePage
ControlCount=5
Control1=IDC_STATIC,static,1342177294
Control2=ST_CAPTION,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=CB_ALLOW_FINISH,button,1342242819

[CLS:CHardwarePage]
Type=0
HeaderFile=HardwarePage.h
ImplementationFile=HardwarePage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=CB_ALLOW_FINISH

[DLG:IDW_PRINTER]
Type=1
Class=CPrinterPage
ControlCount=3
Control1=IDC_STATIC,static,1342177294
Control2=ST_CAPTION,static,1342308352
Control3=IDC_STATIC,static,1342308352

[CLS:CPrinterPage]
Type=0
HeaderFile=PrinterPage.h
ImplementationFile=PrinterPage.cpp
BaseClass=CNewWizPage
Filter=D
LastObject=CPrinterPage

