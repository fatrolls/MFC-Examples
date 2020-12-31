; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScribbleApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "scribble.h"
LastPage=0

ClassCount=5
Class1=CMainFrame
Class2=CPenWidthsDlg
Class3=CScribbleApp
Class4=CScribDoc
Class5=CScribView

ResourceCount=3
Resource1=IDD_PEN_WIDTHS
Resource2=IDR_MAINFRAME
Resource3=IDR_SCRIBTYPE

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MAINFRM.H
ImplementationFile=MAINFRM.CPP
LastObject=CMainFrame

[CLS:CPenWidthsDlg]
Type=0
BaseClass=CDialog
HeaderFile=PENDLG.H
ImplementationFile=PENDLG.CPP

[CLS:CScribbleApp]
Type=0
BaseClass=CWinApp
HeaderFile=SCRIBBLE.H
ImplementationFile=SCRIBBLE.CPP
LastObject=CScribbleApp

[CLS:CScribDoc]
Type=0
BaseClass=CDocument
HeaderFile=SCRIBDOC.H
ImplementationFile=SCRIBDOC.CPP

[CLS:CScribView]
Type=0
BaseClass=COXZoomView
HeaderFile=SCRIBVW.H
ImplementationFile=SCRIBVW.CPP

[DLG:IDD_PEN_WIDTHS]
Type=1
Class=CPenWidthsDlg
ControlCount=7
Control1=IDC_THIN_PEN_WIDTH,edit,1350631552
Control2=IDC_THICK_PEN_WIDTH,edit,1350631552
Control3=IDOK,button,1342373889
Control4=IDCANCEL,button,1342373888
Control5=IDC_DEFAULT_PEN_WIDTHS,button,1342373888
Control6=IDC_STATIC,static,1342373888
Control7=IDC_STATIC,static,1342373888

[MNU:IDR_SCRIBTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CLEAR_ALL
Command12=ID_PEN_THICK_OR_THIN
Command13=ID_PEN_WIDTHS
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_WINDOW_NEW
Command17=ID_WINDOW_CASCADE
Command18=ID_WINDOW_TILE_HORZ
Command19=ID_WINDOW_DUPLICATE
Command20=ID_WINDOW_ARRANGE
Command21=ID_ZOOM_UP
Command22=ID_ZOOM_DOWN
Command23=ID_ZOOM_TOWINDOW
Command24=ID_ZOOM_100
Command25=ID_APP_ABOUT
CommandCount=25

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_VIEW_TOOLBAR
Command5=ID_VIEW_STATUS_BAR
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_HELP
Command9=ID_CONTEXT_HELP
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

