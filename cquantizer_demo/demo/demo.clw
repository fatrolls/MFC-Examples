; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=DlgDecBpp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"
LastPage=0

ClassCount=11
Class1=CDemoApp
Class2=CDemoDoc
Class3=CDemoView
Class4=CMainFrame

ResourceCount=12
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_DEMOTYPE
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_DIALOG4
Resource5=IDR_DEMOTYPE (Neutral)
Resource6=IDD_DIALOG3 (Neutral)
Class7=DlgRotate
Resource7=IDM_CXIMAGE1
Class8=DlgCapture
Resource8=IDD_DIALOG1 (Neutral)
Resource9=IDD_DIALOG5
Class9=DlgResample
Resource10=IDR_MAINFRAME (Neutral)
Class10=DlgDecBpp
Resource11=IDD_DIALOG2 (Neutral)
Class11=DlgIncBpp
Resource12=IDD_ABOUTBOX (Neutral)

[CLS:CDemoApp]
Type=0
HeaderFile=demo.h
ImplementationFile=demo.cpp
Filter=W
LastObject=CDemoApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CDemoDoc]
Type=0
HeaderFile=demoDoc.h
ImplementationFile=demoDoc.cpp
Filter=N
LastObject=IDC_RADIO1
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDemoView]
Type=0
HeaderFile=demoView.h
ImplementationFile=demoView.cpp
Filter=C
LastObject=ID_CXIMAGE_INCREASEBPP
BaseClass=CScrollView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=ID_CXIMAGE_LOADJPEGRESOURCE
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=demo.cpp
ImplementationFile=demo.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_DEMOTYPE]
Type=1
Class=CDemoView
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
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

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
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[CLS:DlgRotate]
Type=0
HeaderFile=DlgRotate.h
ImplementationFile=DlgRotate.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DlgRotate

[CLS:DlgCapture]
Type=0
HeaderFile=dlgcapture.h
ImplementationFile=dlgcapture.cpp
BaseClass=CDialog
LastObject=DlgCapture
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX (Neutral)]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308480
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_DEMOTYPE (Neutral)]
Type=1
Class=CDemoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_SELECTSOURCE
Command7=ID_FILE_ACQUIRE
Command8=ID_FILE_CAPTURE
Command9=ID_FILE_PRINT
Command10=ID_FILE_PRINT_PREVIEW
Command11=ID_FILE_PRINT_SETUP
Command12=ID_FILE_MRU_FILE1
Command13=ID_APP_EXIT
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_REDO
Command16=ID_EDIT_CUT
Command17=ID_EDIT_COPY
Command18=ID_EDIT_PASTE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_STRETCH_MODE
Command22=ID_VIEW_ZOOMIN
Command23=ID_VIEW_ZOOMOUT
Command24=ID_VIEW_NORMALVIEWING11
Command25=ID_IMAGE_FROM_BITMAP
Command26=ID_TRANSFORM_ELLIPSE
Command27=ID_CXIMAGE_MIRROR
Command28=ID_CXIMAGE_FLIP
Command29=ID_CXIMAGE_NEGATIVE
Command30=ID_CXIMAGE_ROTATE
Command31=ID_CXIMAGE_RESAMPLE
Command32=ID_CXIMAGE_SETTRANSPARENCY
Command33=ID_CXIMAGE_REMOVETRANSPARENCY
Command34=ID_CXIMAGE_GRAYSCALE
Command35=ID_CXIMAGE_DECREASEBPP
Command36=ID_CXIMAGE_INCREASEBPP
Command37=ID_WINDOW_NEW
Command38=ID_WINDOW_CASCADE
Command39=ID_WINDOW_TILE_HORZ
Command40=ID_WINDOW_ARRANGE
Command41=ID_WINDOW_CLOSEALL
Command42=ID_WINDOW_DUPLICATE
Command43=ID_APP_ABOUT
CommandCount=43

[TB:IDR_MAINFRAME (Neutral)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_REDO
Command9=ID_FILE_PRINT
Command10=ID_APP_ABOUT
CommandCount=10

[MNU:IDR_MAINFRAME (Neutral)]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SELECTSOURCE
Command4=ID_FILE_ACQUIRE
Command5=ID_FILE_CAPTURE
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_PASTE
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_IMAGE_FROM_BITMAP
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME (Neutral)]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_VIEW_ZOOMIN
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_VIEW_NORMALVIEWING11
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_ZOOMOUT
Command16=ID_EDIT_CUT
Command17=ID_EDIT_REDO
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_DIALOG1 (Neutral)]
Type=1
Class=DlgRotate
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG2 (Neutral)]
Type=1
Class=DlgCapture
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_STATIC,static,1342308352

[MNU:IDM_CXIMAGE1]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_CXIMAGE_MIRROR
Command6=ID_CXIMAGE_FLIP
Command7=ID_CXIMAGE_NEGATIVE
Command8=ID_CXIMAGE_ROTATE
Command9=ID_CXIMAGE_RESAMPLE
Command10=ID_CXIMAGE_SETTRANSPARENCY
Command11=ID_CXIMAGE_REMOVETRANSPARENCY
Command12=ID_CXIMAGE_GRAYSCALE
Command13=ID_CXIMAGE_DECREASEBPP
Command14=ID_CXIMAGE_INCREASEBPP
CommandCount=14

[DLG:IDD_DIALOG3 (Neutral)]
Type=1
Class=DlgResample
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECK1,button,1342242819

[CLS:DlgResample]
Type=0
HeaderFile=DlgResample.h
ImplementationFile=DlgResample.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=dWC

[DLG:IDD_DIALOG4]
Type=1
Class=DlgDecBpp
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO4,button,1342308361
Control9=IDC_RADIO5,button,1342177289
Control10=IDC_CHECK1,button,1342242819
Control11=IDC_CHECK2,button,1342242819
Control12=IDC_EDIT1,edit,1350631552

[CLS:DlgDecBpp]
Type=0
HeaderFile=DlgDecBpp.h
ImplementationFile=DlgDecBpp.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK1

[DLG:IDD_DIALOG5]
Type=1
Class=DlgIncBpp
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=65535,button,1342177287
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289

[CLS:DlgIncBpp]
Type=0
HeaderFile=DlgIncBpp.h
ImplementationFile=DlgIncBpp.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

