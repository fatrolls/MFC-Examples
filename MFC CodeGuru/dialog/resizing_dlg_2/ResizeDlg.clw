; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSampleDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ResizeDlg.h"
LastPage=0

ClassCount=6
Class1=CResizeDlgApp
Class2=CResizeDlgDoc
Class3=CResizeDlgView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CSampleDlg
Resource2=IDD_DIALOG1

[CLS:CResizeDlgApp]
Type=0
HeaderFile=ResizeDlg.h
ImplementationFile=ResizeDlg.cpp
Filter=N

[CLS:CResizeDlgDoc]
Type=0
HeaderFile=ResizeDlgDoc.h
ImplementationFile=ResizeDlgDoc.cpp
Filter=N

[CLS:CResizeDlgView]
Type=0
HeaderFile=ResizeDlgView.h
ImplementationFile=ResizeDlgView.cpp
Filter=C
LastObject=CResizeDlgView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_RESIZE_DLG



[CLS:CAboutDlg]
Type=0
HeaderFile=ResizeDlg.cpp
ImplementationFile=ResizeDlg.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_RESIZE_DLG
CommandCount=1

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CSampleDlg
ControlCount=7
Control1=IDOK,button,1342373889
Control2=IDCANCEL,button,1342373888
Control3=IDC_DO_NOTHING,static,1350701056
Control4=IDC_LEFT_RESIZE,edit,1350631556
Control5=IDC_BOTTOM_ANCHORE,button,1342242816
Control6=IDC_RIGHT_VER_RESIZE,edit,1350631552
Control7=IDC_SLIDER1,msctls_trackbar32,1342242842

[CLS:CSampleDlg]
Type=0
HeaderFile=SampleDlg.h
ImplementationFile=SampleDlg.cpp
BaseClass=CResizingDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

