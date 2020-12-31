; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColourPopup
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ColourPickDemo.h"

ClassCount=4
Class1=CColourPickDemoApp
Class2=CColourPickDemoDlg

ResourceCount=3
Resource2=IDD_COLOURPICKDEMO_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=CColourPicker
Class4=CColourPopup
Resource3=IDD_COLOURPICKDEMO_DIALOG

[CLS:CColourPickDemoApp]
Type=0
HeaderFile=ColourPickDemo.h
ImplementationFile=ColourPickDemo.cpp
Filter=N
LastObject=CColourPickDemoApp

[CLS:CColourPickDemoDlg]
Type=0
HeaderFile=ColourPickDemoDlg.h
ImplementationFile=ColourPickDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CUSTOM_EDIT



[DLG:IDD_COLOURPICKDEMO_DIALOG]
Type=1
Class=CColourPickDemoDlg
ControlCount=10
Control1=IDCANCEL,button,1342242816
Control2=IDC_COLOURPICKER,button,1342242817
Control3=IDC_MODE1,button,1342308361
Control4=IDC_MODE2,button,1342177289
Control5=IDC_TRACK,button,1342242819
Control6=IDC_DISABLE,button,1342242819
Control7=IDC_DEFAULT_EDIT,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDC_CUSTOM_EDIT,edit,1350631552
Control10=IDC_STATIC,static,1342308354

[DLG:IDD_COLOURPICKDEMO_DIALOG (English (U.S.))]
Type=1
Class=CColourPickDemoDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_COLOURPICKER,button,1342242817
Control3=IDC_MODE1,button,1342308361
Control4=IDC_MODE2,button,1342177289
Control5=IDC_TRACK,button,1342242819

[CLS:CColourPicker]
Type=0
HeaderFile=ColourPicker.h
ImplementationFile=ColourPicker.cpp
BaseClass=CButton
Filter=W
LastObject=CColourPicker
VirtualFilter=BWC

[CLS:CColourPopup]
Type=0
HeaderFile=ColourPopup.h
ImplementationFile=ColourPopup.cpp
BaseClass=CWnd
Filter=W
LastObject=CColourPopup
VirtualFilter=WC

