; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "docktest.h"
LastPage=0

ClassCount=8
Class1=CDockChildWnd
Class2=CDocktestDoc
Class3=CDocktestApp
Class4=CAboutDlg
Class5=CDocktestView
Class6=CLogoDlg
Class7=CMainFrame
Class8=CMyListBoxBar

ResourceCount=6
Resource1=IDD_ABOUTBOX (English (U.K.))
Resource2=IDR_DOCKTETYPE (English (U.K.))
Resource3=IDD_DIALOGBAR (English (U.K.))
Resource4=IDR_MAINFRAME (English (U.K.))
Resource5=IDD_DIALOGBAR2 (English (U.K.))
Resource6=IDD_DIALOGBAR3 (English (U.K.))

[CLS:CDockChildWnd]
Type=0
BaseClass=COXMDIChildWndSizeDock
HeaderFile=DOCKCHIL.H
ImplementationFile=DOCKCHIL.CPP
Filter=M
VirtualFilter=mfWC
LastObject=CDockChildWnd

[CLS:CDocktestDoc]
Type=0
BaseClass=CDocument
HeaderFile=DOCKTDOC.H
ImplementationFile=DOCKTDOC.CPP

[CLS:CDocktestApp]
Type=0
BaseClass=CWinApp
HeaderFile=DOCKTEST.H
ImplementationFile=DOCKTEST.CPP
Filter=N
VirtualFilter=AC
LastObject=CDocktestApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DOCKTEST.CPP
ImplementationFile=DOCKTEST.CPP
LastObject=ID_LISTBOXBAR

[CLS:CDocktestView]
Type=0
BaseClass=CView
HeaderFile=DOCKTVW.H
ImplementationFile=DOCKTVW.CPP

[CLS:CLogoDlg]
Type=0
BaseClass=COXSizeDialogBar
HeaderFile=LogoDlg.h
ImplementationFile=LogoDlg.cpp
LastObject=CLogoDlg

[CLS:CMainFrame]
Type=0
BaseClass=MainFrameParent
HeaderFile=MAINFRM.H
ImplementationFile=MAINFRM.CPP
LastObject=CMainFrame
Filter=W
VirtualFilter=fWC

[CLS:CMyListBoxBar]
Type=0
BaseClass=COXSizeControlBar
HeaderFile=MYSIZEBA.H
ImplementationFile=MYSIZEBA.CPP

[DLG:IDD_DIALOGBAR3]
Type=1
Class=CLogoDlg

[DLG:IDD_DIALOGBAR (English (U.K.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_STATIC,static,1342177283

[DLG:IDD_DIALOGBAR2 (English (U.K.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOGBAR3 (English (U.K.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_OXBUTTON,button,1342243595
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,static,1342177283
Control5=IDC_STATIC,button,1342177287

[MNU:IDR_DOCKTETYPE (English (U.K.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_STATUS_BAR
Command16=ID_SIZEDLGBAR
Command17=ID_LOGOBAR
Command18=ID_FIXEDDLGBAR
Command19=ID_LISTBOXBAR
Command20=ID_VIEW_TILEDOCKBARS
Command21=ID_ArrangeTopLeft
Command22=ID_ArrangeTopRight
Command23=ID_ArrangeBottomLeft
Command24=ID_ArrangeBottomRight
Command25=ID_WINDOW_NEW
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_TILE_HORZ
Command28=ID_WINDOW_ARRANGE
Command29=ID_APP_ABOUT
CommandCount=29

[MNU:IDR_MAINFRAME (English (U.K.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_STATUS_BAR
Command7=ID_SIZEDLGBAR
Command8=ID_FIXEDDLGBAR
Command9=ID_LISTBOXBAR
Command10=ID_VIEW_TILEDOCKBARS
Command11=ID_ArrangeTopLeft
Command12=ID_ArrangeTopRight
Command13=ID_ArrangeBottomLeft
Command14=ID_ArrangeBottomRight
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME (English (U.K.))]
Type=1
Class=?
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

[DLG:IDD_ABOUTBOX (English (U.K.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDOK,button,1342373889
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

