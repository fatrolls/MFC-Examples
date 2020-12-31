; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCoolButton
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PrintManager.h"

ClassCount=9
Class1=CPrintManagerApp
Class2=CPrintManagerDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PRINTMANAGER_DIALOG
Resource4=IDD_LISTPAGE1
Resource5=IDD_PRINT_STATUS
Resource6=IDD_ABOUTBOX (English (U.S.))
Class5=CListPrintPage2
Resource7=IDD_LISTPAGE2
Class6=CListPrintSetup
Resource8=IDD_PRINTMANAGER_DIALOG (English (U.S.))
Class7=CPrintStatus
Class4=CListPrintPage1
Class8=CFontCombo
Class9=CCoolButton
Resource9=IDD_LISTSETUP

[CLS:CPrintManagerApp]
Type=0
HeaderFile=PrintManager.h
ImplementationFile=PrintManager.cpp
Filter=N

[CLS:CPrintManagerDlg]
Type=0
HeaderFile=PrintManagerDlg.h
ImplementationFile=PrintManagerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

[CLS:CAboutDlg]
Type=0
HeaderFile=PrintManagerDlg.h
ImplementationFile=PrintManagerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_PRINTMANAGER_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CPrintManagerDlg

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PRINTMANAGER_DIALOG (English (U.S.))]
Type=1
Class=CPrintManagerDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1342275585

[DLG:IDD_LISTPAGE1]
Type=1
Class=CListPrintPage1
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDHEAD,edit,1350631620
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDPAGE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CBFHEAD,combobox,1344341523
Control7=IDC_CBSHEAD,combobox,1344340994
Control8=IDC_EDFOOTER,edit,1350631620
Control9=IDC_CBFFOOTER,combobox,1344341523
Control10=IDC_CBSFOOTER,combobox,1344340994
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CBFCORPO,combobox,1344341523
Control13=IDC_CBSCORPO,combobox,1344340994
Control14=IDC_STATIC,static,1342177296
Control15=IDC_STATIC,static,1342177296

[CLS:CListPrintPage1]
Type=0
HeaderFile=ListPrintPage1.h
ImplementationFile=ListPrintPage1.cpp
BaseClass=CDialog

[DLG:IDD_LISTPAGE2]
Type=1
Class=CListPrintPage2
ControlCount=13
Control1=65535,static,1342177294
Control2=65535,static,1342308352
Control3=IDC_ED_MMUP,edit,1350631552
Control4=IDC_SPIN1,msctls_updown32,1342177334
Control5=65535,static,1342308352
Control6=IDC_ED_MMDX,edit,1350631552
Control7=IDC_SPIN2,msctls_updown32,1342177334
Control8=65535,static,1342308352
Control9=IDC_ED_MMSX,edit,1350631552
Control10=IDC_SPIN3,msctls_updown32,1342177334
Control11=65535,static,1342308352
Control12=IDC_ED_MMDOWN,edit,1350631552
Control13=IDC_SPIN4,msctls_updown32,1342177334

[CLS:CListPrintPage2]
Type=0
HeaderFile=ListPrintPage2.h
ImplementationFile=ListPrintPage2.cpp
BaseClass=CDialog

[DLG:IDD_LISTSETUP]
Type=1
Class=CListPrintSetup
ControlCount=6
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_BT_PRINTOPT,button,1342242827
Control4=IDC_STATIC,static,1342177296
Control5=IDC_STATIC,static,1342177297
Control6=IDC_TAB1,SysTabControl32,1342177280

[CLS:CListPrintSetup]
Type=0
HeaderFile=ListPrintSetup.h
ImplementationFile=ListPrintSetup.cpp
BaseClass=CDialog

[DLG:IDD_PRINT_STATUS]
Type=1
Class=CPrintStatus
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_ANIMATE1,SysAnimate32,1342177286
Control3=IDC_PROGRESS1,msctls_progress32,1342177280
Control4=IDC_PC,static,1342308354
Control5=IDC_TEXT1,static,1342308352
Control6=IDC_PAGES,static,1342308352

[CLS:CPrintStatus]
Type=0
HeaderFile=PrintStatus.h
ImplementationFile=PrintStatus.cpp
BaseClass=CDialog

[CLS:CFontCombo]
Type=0
HeaderFile=FontCombo.h
ImplementationFile=FontCombo.cpp
BaseClass=CComboBox

[CLS:CCoolButton]
Type=0
HeaderFile=CoolButton.h
ImplementationFile=CoolButton.cpp
BaseClass=CButton

