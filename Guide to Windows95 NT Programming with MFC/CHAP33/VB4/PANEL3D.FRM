VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "VB PANEL3D.OCX Test App"
   ClientHeight    =   3255
   ClientLeft      =   4290
   ClientTop       =   2610
   ClientWidth     =   4725
   Height          =   3660
   Icon            =   "Panel3d.frx":0000
   Left            =   4230
   LinkTopic       =   "Form1"
   ScaleHeight     =   217
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   315
   Top             =   2265
   Width           =   4845
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   1
      Left            =   1320
      TabIndex        =   1
      Top             =   120
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   2
      Left            =   2520
      TabIndex        =   2
      Top             =   120
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   3
      Left            =   120
      TabIndex        =   3
      Top             =   1080
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   4
      Left            =   1320
      TabIndex        =   4
      Top             =   1080
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   5
      Left            =   2520
      TabIndex        =   5
      Top             =   1080
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   6
      Left            =   120
      TabIndex        =   6
      Top             =   2040
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   7
      Left            =   1320
      TabIndex        =   7
      Top             =   2040
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   0
   End
   Begin PANEL3DLib.Panel3d Panel3d1 
      Height          =   870
      Index           =   8
      Left            =   2520
      TabIndex        =   8
      Top             =   2040
      Width           =   1095
      _Version        =   65536
      _ExtentX        =   1931
      _ExtentY        =   1535
      _StockProps     =   2
      TextAlignment   =   3
      DrawText3d      =   -1  'True
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
'==================================================================
' Module  : PANEL3D.FRM
'
' Purpose : Demonstrates the use of the PANEL3D.OCX in Visual Basic
'
' Author  : Rob McGregor, rob_mcgregor@compuserve.com
'
' Date    : 07-10-96
'==================================================================



'==================================================================
' Private Sub Form_Load()

Private Sub Form_Load()
   Dim i     As Integer
   Dim lRet  As Long
   
   Me.ScaleMode = 3   ' pixels
   
   ' Size and center the window
   lRet = MoveWindow(Me.hwnd, 0, 0, 640, 480, False)
   Move (Screen.Width - Me.Width) \ 2, (Screen.Height - Me.Height) \ 2

   '
   ' Set varying bevel widths and text alignments
   ' for the array of Panel3d controls
   '
   For i = 0 To 8
      Panel3d1(i).BevelWidth = i + 1
      Panel3d1(i).TextAlignment = i
   Next i
   
   ' Set bevel styles
   Panel3d1(1).BevelStyle = bsRaised
   Panel3d1(3).BevelStyle = bsRaised
   Panel3d1(4).BevelStyle = bsNone
   Panel3d1(5).BevelStyle = bsRaised
   Panel3d1(7).BevelStyle = bsRaised
   
   ' Set captions
   Panel3d1(0).Caption = "taLeftTop - bsInset"
   Panel3d1(1).Caption = "taLeftMid - bsRaised"
   Panel3d1(2).Caption = "taLeftBottom - bsInset"
   Panel3d1(3).Caption = "taCenterTop - bsRaised"
   Panel3d1(4).Caption = "taCenter - bsNone"
   Panel3d1(5).Caption = "taCenterBottom - bsRaised"
   Panel3d1(6).Caption = "taRightTop - bsInset"
   Panel3d1(7).Caption = "taRightMid - bsRaised"
   Panel3d1(8).Caption = "taRightBottom - bsInset"
   
   ' Set 3d beveled text
   Panel3d1(6).DrawText3d = True
   Panel3d1(7).DrawText3d = True
   Panel3d1(8).DrawText3d = True

   ' Set visible borders
   Panel3d1(6).DrawBorder = True
   Panel3d1(7).DrawBorder = True
   Panel3d1(8).DrawBorder = True
End Sub

'==================================================================
' Private Sub Form_Resize()

Private Sub Form_Resize()
   '
   ' Declare some variables
   '
   Dim cx        As Integer
   Dim cy        As Integer
   Dim i         As Integer
   Dim j         As Integer
   Dim nWidth    As Integer
   Dim nHeight   As Integer
   Dim nSpace    As Integer
   Dim nCur      As Integer
   Dim nCurLeft  As Integer
   Dim nCurTop   As Integer
    
   '
   ' Initialize variables
   '
   nSpace = 8
   nWidth = (Me.ScaleWidth - (nSpace * 4)) / 3
   nHeight = (Me.ScaleHeight - (nSpace * 4)) / 3
   nCur = 0
   nCurLeft = nSpace
   nCurTop = nSpace
   
   ' Resize and set positions of panels
   For i = 0 To 2
      For j = 0 To 2
         Panel3d1(nCur).Width = nWidth
         Panel3d1(nCur).Height = nHeight
         Panel3d1(nCur).Left = nCurLeft
         Panel3d1(nCur).Top = nCurTop
         nCurLeft = nCurLeft + nWidth + nSpace
         nCur = nCur + 1
      Next j
      nCurLeft = nSpace
      nCurTop = nCurTop + nHeight + nSpace
   Next i
End Sub


