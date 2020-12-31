; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CYMTestDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "YMTest.h"

ClassCount=4
Class1=CYMTestApp
Class2=CYMTestDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CYMPopUp
Class4=CYMSelector
Resource2=IDD_YMTEST_DIALOG

[CLS:CYMTestApp]
Type=0
HeaderFile=YMTest.h
ImplementationFile=YMTest.cpp
Filter=N

[CLS:CYMTestDlg]
Type=0
HeaderFile=YMTestDlg.h
ImplementationFile=YMTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CYMTestDlg



[DLG:IDD_YMTEST_DIALOG]
Type=1
Class=CYMTestDlg
ControlCount=7
Control1=IDC_BUTTON_YMSELECT,button,1342242827
Control2=IDC_BUTTON_YMSELECT2,button,1342242827
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177296

[CLS:CYMPopUp]
Type=0
HeaderFile=YMSelector.h
ImplementationFile=YMSelector.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CYMPopUp

[CLS:CYMSelector]
Type=0
HeaderFile=ymselector.h
ImplementationFile=ymselector.cpp
BaseClass=CButton
Filter=W
LastObject=CYMSelector
VirtualFilter=BWC

