; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScrollTipApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "scrolltipdemo.h"
LastPage=0

ClassCount=7
Class1=CChildFrame
Class2=CMainFrame
Class3=CScrollDlg
Class4=CScrollSettingsDlg
Class5=CScrollTipApp
Class6=CScrollTipDoc
Class7=CScrollTipEditView

ResourceCount=5
Resource1=IDR_SCROLLTYPE (Dutch (Belgium))
Resource2=IDR_MAINFRAME (Dutch (Belgium))
Resource3=IDR_SCROLLTYPE_CNTR_IP (Dutch (Belgium))
Resource4=IDD_SCROLL_SETTINGS (Dutch (Belgium))
Resource5=IDD_SCROLL_DLG (Dutch (Belgium))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
LastObject=CChildFrame

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CScrollDlg]
Type=0
BaseClass=CDialog
HeaderFile=ScrollDlg.h
ImplementationFile=ScrollDlg.cpp

[CLS:CScrollSettingsDlg]
Type=0
BaseClass=CDialog
HeaderFile=ScrollSettingsDlg.h
ImplementationFile=ScrollSettingsDlg.cpp

[CLS:CScrollTipApp]
Type=0
BaseClass=CWinApp
HeaderFile=ScrollTipDemo.h
ImplementationFile=ScrollTipDemo.cpp
Filter=N
VirtualFilter=AC
LastObject=CScrollTipApp

[CLS:CScrollTipDoc]
Type=0
BaseClass=CRichEditDoc
HeaderFile=ScrollTipDoc.h
ImplementationFile=ScrollTipDoc.cpp

[CLS:CScrollTipEditView]
Type=0
BaseClass=CRichEditView
HeaderFile=ScrollTipEditView.h
ImplementationFile=ScrollTipEditView.cpp

[DLG:IDD_SCROLL_DLG]
Type=1
Class=CScrollDlg

[DLG:IDD_SCROLL_SETTINGS]
Type=1
Class=CScrollSettingsDlg

[MNU:IDR_MAINFRAME (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_SCROLLTYPE (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_VIEW_STATUS_BAR
Command4=ID_WINDOW_NEW
Command5=ID_WINDOW_CASCADE
Command6=ID_WINDOW_TILE_HORZ
Command7=ID_WINDOW_ARRANGE
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_SCROLL_SETTINGS (Dutch (Belgium))]
Type=1
Class=?
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_HORZ_MASK,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_HORZ_PAGE_ALIGN,button,1342242819
Control8=IDC_HORZ_TOP,button,1342242819
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_VERT_MASK,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_VERT_PAGE_ALIGN,button,1342242819
Control16=IDC_VERT_LEFT,button,1342242819
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816

[DLG:IDD_SCROLL_DLG (Dutch (Belgium))]
Type=1
Class=?
ControlCount=12
Control1=IDCANCEL,button,1342242816
Control2=IDC_HORZ_SCROLL_1,scrollbar,1342177280
Control3=IDC_HORZ_SCROLL_2,scrollbar,1342177280
Control4=IDC_VERT_SCROLL_1,scrollbar,1342177281
Control5=IDC_LIST,listbox,1352728833
Control6=IDC_STATIC,static,1342177294
Control7=IDC_STATIC,static,1342177294
Control8=IDC_STATIC,static,1342177294
Control9=IDC_STATIC,static,1342177294
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[ACL:IDR_MAINFRAME (Dutch (Belgium))]
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
Command9=ID_EDIT_SELECT_ALL
Command10=ID_EDIT_FIND
Command11=ID_EDIT_REPEAT
Command12=ID_EDIT_REPLACE
Command13=ID_OLE_EDIT_PROPERTIES
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_NEXT_PANE
Command19=ID_PREV_PANE
Command20=ID_CANCEL_EDIT_CNTR
CommandCount=20

[ACL:IDR_SCROLLTYPE_CNTR_IP (Dutch (Belgium))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

