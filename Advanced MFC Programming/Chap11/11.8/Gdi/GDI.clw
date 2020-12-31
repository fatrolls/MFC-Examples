; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGDIView
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GDI.h"
LastPage=0

ClassCount=8
Class1=CGDIApp
Class2=CGDIDoc
Class3=CGDIView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CColorButton
Class7=CColorBar
Class8=CFBButton
Resource3=IDD_DIALOG_COLORBAR
Resource4=IDR_DRAWTOOLBAR

[CLS:CGDIApp]
Type=0
HeaderFile=GDI.h
ImplementationFile=GDI.cpp
Filter=N

[CLS:CGDIDoc]
Type=0
HeaderFile=GDIDoc.h
ImplementationFile=GDIDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_BUTTON_LINE

[CLS:CGDIView]
Type=0
HeaderFile=GDIView.h
ImplementationFile=GDIView.cpp
Filter=C
LastObject=CGDIView
BaseClass=CScrollView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=GDI.cpp
ImplementationFile=GDI.cpp
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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

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
Command7=ID_ZOOM_IN
Command8=ID_ZOOM_OUT
Command9=ID_GRID
Command10=ID_FILE_PRINT
Command11=ID_APP_ABOUT
CommandCount=11

[DLG:IDD_DIALOG_COLORBAR]
Type=1
Class=CColorBar
ControlCount=21
Control1=IDC_BUTTON_FB,button,1342242827
Control2=IDC_BUTTON_COLOR1,button,1342242827
Control3=IDC_BUTTON_COLOR2,button,1342242827
Control4=IDC_BUTTON_COLOR3,button,1342242827
Control5=IDC_BUTTON_COLOR4,button,1342242827
Control6=IDC_BUTTON_COLOR5,button,1342242827
Control7=IDC_BUTTON_COLOR6,button,1342242827
Control8=IDC_BUTTON_COLOR7,button,1342242827
Control9=IDC_BUTTON_COLOR8,button,1342242827
Control10=IDC_BUTTON_COLOR9,button,1342242827
Control11=IDC_BUTTON_COLOR10,button,1342242827
Control12=IDC_BUTTON_COLOR11,button,1342242827
Control13=IDC_BUTTON_COLOR12,button,1342242827
Control14=IDC_BUTTON_COLOR13,button,1342242827
Control15=IDC_BUTTON_COLOR14,button,1342242827
Control16=IDC_BUTTON_COLOR15,button,1342242827
Control17=IDC_BUTTON_COLOR16,button,1342242827
Control18=IDC_BUTTON_COLOR17,button,1342242827
Control19=IDC_BUTTON_COLOR18,button,1342242827
Control20=IDC_BUTTON_COLOR19,button,1342242827
Control21=IDC_BUTTON_COLOR20,button,1342242827

[CLS:CColorButton]
Type=0
HeaderFile=Button.h
ImplementationFile=Button.cpp
BaseClass=CButton
Filter=W
LastObject=CColorButton
VirtualFilter=BWC

[CLS:CColorBar]
Type=0
HeaderFile=ColorBar.h
ImplementationFile=ColorBar.cpp
BaseClass=CDialogBar
Filter=W
LastObject=CColorBar
VirtualFilter=dWC

[CLS:CFBButton]
Type=0
HeaderFile=button.h
ImplementationFile=button.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CFBButton

[TB:IDR_DRAWTOOLBAR]
Type=1
Command1=ID_BUTTON_FREESEL
Command2=ID_BUTTON_RECTSEL
Command3=ID_BUTTON_PEN
Command4=ID_BUTTON_LINE
CommandCount=4

