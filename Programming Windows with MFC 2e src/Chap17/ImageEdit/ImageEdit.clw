; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImageEdit.h"
LastPage=0

ClassCount=5
Class1=CImageEditApp
Class2=CImageEditDoc
Class3=CImageEditView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CImageEditApp]
Type=0
HeaderFile=ImageEdit.h
ImplementationFile=ImageEdit.cpp
Filter=N

[CLS:CImageEditDoc]
Type=0
HeaderFile=ImageEditDoc.h
ImplementationFile=ImageEditDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CImageEditView]
Type=0
HeaderFile=ImageEditView.h
ImplementationFile=ImageEditView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=ImageEdit.cpp
ImplementationFile=ImageEdit.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_EFFECTS_GRAY_SCALE
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
CommandCount=1

