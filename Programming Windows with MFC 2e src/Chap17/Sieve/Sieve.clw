; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSieveDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Sieve.h"

ClassCount=2
Class1=CSieveApp
Class2=CSieveDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_SIEVE_DIALOG

[CLS:CSieveApp]
Type=0
HeaderFile=Sieve.h
ImplementationFile=Sieve.cpp
Filter=N

[CLS:CSieveDlg]
Type=0
HeaderFile=SieveDlg.h
ImplementationFile=SieveDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SIEVE_DIALOG]
Type=1
Class=CSieveDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_MAX,edit,1350631552
Control3=IDC_RESULT,edit,1350568064
Control4=IDC_START,button,1342242816

