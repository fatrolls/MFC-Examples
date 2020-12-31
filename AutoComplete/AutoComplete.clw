; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CACListWnd
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AutoComplete.h"

ClassCount=8
Class1=CAutoCompleteApp
Class2=CAutoCompleteDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CAutoCompleteListBox
Class5=CACListWnd
Class6=CACWnd
Class7=CACStatusBar
Class8=CACEdit
Resource3=IDD_AUTOCOMPLETE_DIALOG

[CLS:CAutoCompleteApp]
Type=0
HeaderFile=AutoComplete.h
ImplementationFile=AutoComplete.cpp
Filter=N
LastObject=CAutoCompleteApp

[CLS:CAutoCompleteDlg]
Type=0
HeaderFile=AutoCompleteDlg.h
ImplementationFile=AutoCompleteDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON2

[CLS:CAboutDlg]
Type=0
HeaderFile=AutoCompleteDlg.h
ImplementationFile=AutoCompleteDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AUTOCOMPLETE_DIALOG]
Type=1
Class=CAutoCompleteDlg
ControlCount=30
Control1=IDC_EDIT2,edit,1350635648
Control2=IDC_EDIT1,edit,1350635648
Control3=IDC_LIST1,listbox,1352745217
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344340290
Control7=IDC_COMBO2,combobox,1344340290
Control8=IDC_EDIT3,edit,1352728644
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350635648
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342177297
Control15=IDC_STATIC,static,1342177296
Control16=IDC_EDIT5,edit,1350631552
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT6,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT7,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308864
Control24=IDC_EDIT8,edit,1350633600
Control25=IDC_EDIT9,edit,1350631552
Control26=IDC_BUTTON2,button,1342242816
Control27=IDC_EDIT10,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342177296

[CLS:CAutoCompleteListBox]
Type=0
HeaderFile=AutoCompleteListBox.h
ImplementationFile=AutoCompleteListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CAutoCompleteListBox

[CLS:CACWnd]
Type=0
HeaderFile=ACWnd.h
ImplementationFile=ACWnd.cpp
BaseClass=CWnd
Filter=W
LastObject=CACWnd
VirtualFilter=WC

[CLS:CACStatusBar]
Type=0
HeaderFile=ACStatusBar.h
ImplementationFile=ACStatusBar.cpp
BaseClass=CStatusBarCtrl
Filter=W
VirtualFilter=WC
LastObject=CACStatusBar

[CLS:CACEdit]
Type=0
HeaderFile=ACEdit.h
ImplementationFile=ACEdit.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CACEdit

[CLS:CACListWnd]
Type=0
HeaderFile=ACListWnd.h
ImplementationFile=ACListWnd.cpp
BaseClass=CWnd
LastObject=CACListWnd

