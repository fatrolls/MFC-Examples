Attribute VB_Name = "Module1"
'==================================================================
' Module  : PANEL3D.BAS
'
' Purpose : Constants, etc. for using PANEL3D.OCX in Visual Basic
'
' Author  : Rob McGregor, rob_mcgregor@compuserve.com
'
' Date    : 07-10-96
'==================================================================

'
' Constants for bevel styles
'
Public Const bsNone = 0
Public Const bsInset = 1
Public Const bsRaised = 2

'
' Constants for text alignment
'
Public Const taLeftTop = 0
Public Const taLeftMid = 1
Public Const taLeftBottom = 2
Public Const taCenterTop = 3
Public Const taCenter = 4
Public Const taCenterBottom = 5
Public Const taRightTop = 6
Public Const taRightMid = 7
Public Const taRightBottom = 8

' Win32 API functions
Declare Function MoveWindow Lib "user32" (ByVal hwnd As Long, _
   ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, _
   ByVal nHeight As Long, ByVal bRepaint As Long) As Long


