; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLayoutManagerApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "layoutmanager.h"
LastPage=0

ClassCount=5
Class1=CDlgDemo
Class2=CLayoutManagerApp
Class3=CMainFrame
Class4=CLayoutManagerDoc
Class5=CLayoutManagerView

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_DEMO (Neutral)

[CLS:CDlgDemo]
Type=0
BaseClass=CDialog
HeaderFile=DlgDemo.h
ImplementationFile=DlgDemo.cpp
LastObject=CDlgDemo
Filter=D
VirtualFilter=dWC

[CLS:CLayoutManagerApp]
Type=0
BaseClass=CWinApp
HeaderFile=LayoutManager.h
ImplementationFile=LayoutManager.cpp
LastObject=CLayoutManagerApp
Filter=N
VirtualFilter=AC

[CLS:CLayoutManagerDoc]
Type=0
BaseClass=CDocument
HeaderFile=LayoutManagerDoc.h
ImplementationFile=LayoutManagerDoc.cpp

[CLS:CLayoutManagerView]
Type=0
BaseClass=CView
HeaderFile=LayoutManagerView.h
ImplementationFile=LayoutManagerView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DLG:IDD_DEMO]
Type=1
Class=CDlgDemo

[DLG:IDD_DEMO (Neutral)]
Type=1
Class=CDlgDemo
ControlCount=4
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_BUTTON3,button,1342242816
Control4=IDC_BUTTON4,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

