; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColorSelectorDlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "colorselector.h"
LastPage=0

ClassCount=6
Class1=CColorSelectorApp
Class2=CAboutDlg
Class3=CColorSelectorDlg
Class4=CCustomDrawSliderCtrl

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class5=CBuddiedSliderCtrl
Class6=CSpectrumWnd
Resource2=IDD_COLORSELECTOR_DIALOG

[CLS:CColorSelectorApp]
Type=0
BaseClass=CWinApp
HeaderFile=ColorSelector.h
ImplementationFile=ColorSelector.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ColorSelectorDlg.cpp
ImplementationFile=ColorSelectorDlg.cpp

[CLS:CColorSelectorDlg]
Type=0
BaseClass=CDialog
HeaderFile=ColorSelectorDlg.h
ImplementationFile=ColorSelectorDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CColorSelectorDlg

[CLS:CCustomDrawSliderCtrl]
Type=0
BaseClass=CSliderCtrl
HeaderFile=CustomDrawSliderCtrl.h
ImplementationFile=CustomDrawSliderCtrl.cpp
Filter=W
LastObject=CCustomDrawSliderCtrl
VirtualFilter=KWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_COLORSELECTOR_DIALOG]
Type=1
Class=CColorSelectorDlg
ControlCount=12
Control1=IDC_SLIDER_RED,msctls_trackbar32,1342242827
Control2=IDC_SLIDER_GREEN,msctls_trackbar32,1342242827
Control3=IDC_SLIDER_BLUE,msctls_trackbar32,1342242827
Control4=IDC_SLIDER_LUM,msctls_trackbar32,1342242827
Control5=IDC_BUTTON_COPYVALUE,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDC_PLACEHOLDER,static,1342308352
Control8=IDC_EDIT_RED,edit,1350568065
Control9=IDC_EDIT_GREEN,edit,1350568065
Control10=IDC_EDIT_BLUE,edit,1350568065
Control11=IDC_EDIT_LUM,edit,1350568065
Control12=IDC_STATIC_SAMPLECOLOR,static,1342308865

[CLS:CBuddiedSliderCtrl]
Type=0
HeaderFile=BuddiedSliderCtrl.h
ImplementationFile=BuddiedSliderCtrl.cpp
BaseClass=CCustomDrawSliderCtrl
Filter=W
LastObject=CBuddiedSliderCtrl
VirtualFilter=KWC

[CLS:CSpectrumWnd]
Type=0
HeaderFile=SpectrumWnd.h
ImplementationFile=SpectrumWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CSpectrumWnd

