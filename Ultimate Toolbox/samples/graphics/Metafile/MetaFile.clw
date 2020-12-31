; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMetaFileApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MetaFile.h"
LastPage=0

ClassCount=5
Class1=CMetaFileApp
Class2=CMetaFileDoc
Class3=CMetaFileView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_EMFTYPE
Class5=CChildFrame
Resource2=IDR_MAINFRAME (English (U.S.))
Resource3=IDR_EMFTYPE (English (U.S.))
Resource4=IDR_MAINFRAME

[CLS:CMetaFileApp]
Type=0
HeaderFile=MetaFile.h
ImplementationFile=MetaFile.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CMetaFileApp

[CLS:CMetaFileDoc]
Type=0
HeaderFile=MetaFileDoc.h
ImplementationFile=MetaFileDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMetaFileDoc

[CLS:CMetaFileView]
Type=0
HeaderFile=MetaFileView.h
ImplementationFile=MetaFileView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_VIEW_RATIO

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

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
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_APP_ABOUT
CommandCount=4

[MNU:IDR_EMFTYPE]
Type=1
Class=CMetaFileView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CREATE_METAFILE
Command4=ID_FILE_CLOSE
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_VIEW_RATIO
Command13=ID_WINDOW_NEW
Command14=ID_WINDOW_CASCADE
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_WINDOW_ARRANGE
Command17=ID_APP_ABOUT
CommandCount=17

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

[MNU:IDR_EMFTYPE (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CREATE_METAFILE
Command4=ID_FILE_CLOSE
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_VIEW_TOOLBAR
Command11=ID_VIEW_STATUS_BAR
Command12=ID_VIEW_RATIO
Command13=ID_WINDOW_NEW
Command14=ID_WINDOW_CASCADE
Command15=ID_WINDOW_TILE_HORZ
Command16=ID_WINDOW_ARRANGE
Command17=ID_APP_ABOUT
CommandCount=17

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

