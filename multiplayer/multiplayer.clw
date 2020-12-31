; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMultiplayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "multiplayer.h"

ClassCount=3
Class1=CMultiplayerApp
Class2=CMultiplayerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_MULTIPLAYER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDM_MENU

[CLS:CMultiplayerApp]
Type=0
HeaderFile=multiplayer.h
ImplementationFile=multiplayer.cpp
Filter=N

[CLS:CMultiplayerDlg]
Type=0
HeaderFile=multiplayerDlg.h
ImplementationFile=multiplayerDlg.cpp
Filter=D
LastObject=IDC_BTNFADEOUT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=multiplayerDlg.h
ImplementationFile=multiplayerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_MULTIPLAYER_DIALOG]
Type=1
Class=CMultiplayerDlg
ControlCount=32
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LISTEVENT,listbox,1352728833
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBOPLAYLIST,combobox,1344340226
Control5=IDC_STATIC,button,1342308359
Control6=IDC_BTNNORMAL,button,1342177289
Control7=IDC_BTNFADEIN,button,1342177289
Control8=IDC_BTNFADEOUT,button,1342177289
Control9=IDC_STATIC,button,1342308359
Control10=IDC_BTNPLAYNORMAL,button,1342177289
Control11=IDC_BTNPLAYLOOP,button,1342177289
Control12=IDC_STATIC,button,1342308359
Control13=IDC_BTNPLAY,button,1342177289
Control14=IDC_BTNSTOP,button,1342177289
Control15=IDC_STATIC,button,1342178055
Control16=IDC_BTNSPEEDUP,button,1342242816
Control17=IDC_BTNSPEEDDOWN,button,1342242816
Control18=IDC_STATIC,button,1342178055
Control19=IDC_BTNVOLUMEUP,button,1342242816
Control20=IDC_BTNVOLUMEDOWN,button,1342242816
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,static,1342308352
Control23=IDC_BTNLEFTUP,button,1342242816
Control24=IDC_BTNLEFTDOWN,button,1342242816
Control25=IDC_BTNPANCENTER,button,1342242816
Control26=IDC_STATIC,static,1342308352
Control27=IDC_BTNRIGHTUP,button,1342242816
Control28=IDC_BTNRIGHTDOWN,button,1342242816
Control29=IDC_BTNRESET,button,1342242816
Control30=IDC_PLAYALL,button,1342242816
Control31=IDC_STOPALL,button,1342242816
Control32=IDCANCEL,button,1342242816

[MNU:IDM_MENU]
Type=1
Class=?
Command1=IDM_FILEOPEN
CommandCount=1

