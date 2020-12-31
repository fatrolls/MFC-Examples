; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogGLApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DialogGL.h"

ClassCount=3
Class1=CDialogGLApp
Class2=CDialogGLDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOGGL_DIALOG
Resource4=IDR_ACCELERATOR1
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=CG_IDR_POPUP_DIALOG_GLDLG
Resource7=IDD_DIALOGGL_DIALOG (English (U.S.))

[CLS:CDialogGLApp]
Type=0
HeaderFile=DialogGL.h
ImplementationFile=DialogGL.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDialogGLApp

[CLS:CDialogGLDlg]
Type=0
HeaderFile=DialogGLDlg.h
ImplementationFile=DialogGLDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDialogGLDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=DialogGLDlg.h
ImplementationFile=DialogGLDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_DIALOGGL_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CDialogGLDlg

[DLG:IDD_DIALOGGL_DIALOG (English (U.S.))]
Type=1
Class=CDialogGLDlg
ControlCount=0

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:CG_IDR_POPUP_DIALOG_GLDLG]
Type=1
Command1=ID_POPUP_TEXTUREFILE
Command2=ID_POPUP_ROTATE
Command3=ID_POPUP_SIZE_INCREASE
Command4=ID_POPUP_SIZE_DECREASE
Command5=ID_POPUP_ABOUT
CommandCount=5

[ACL:IDR_ACCELERATOR1]
Type=1
Command1=ID_POPUP_SIZE_INCREASE
Command2=ID_POPUP_SIZE_DECREASE
CommandCount=2

