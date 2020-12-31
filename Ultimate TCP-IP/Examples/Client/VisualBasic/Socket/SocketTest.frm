VERSION 5.00
Object = "{D23EA52C-0D35-11D3-A46D-0080C858F182}#1.4#0"; "UTSocket.dll"
Begin VB.Form frmMain
   Caption         =   "Ultimate TCP/IP utaxSocket Client ActiveX Control 4.0 - Demo Application"
   ClientHeight    =   2448
   ClientLeft      =   2748
   ClientTop       =   2472
   ClientWidth     =   5880
   ClipControls    =   0   'False
   Icon            =   "SocketTest.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2448
   ScaleWidth      =   5880
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdFinger
      Caption         =   "&Finger"
      Default         =   -1  'True
      Height          =   375
      Left            =   2520
      TabIndex        =   2
      ToolTipText     =   "Finger the Specified Address"
      Top             =   585
      Width           =   1095
   End
   Begin VB.TextBox txtResults
      BeginProperty Font
         Name            =   "Courier New"
         Size            =   8.4
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2895
      Left            =   90
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Top             =   1125
      Width           =   5940
   End
   Begin VB.CommandButton cmdExit
      Caption         =   "E&xit"
      Height          =   375
      Left            =   3780
      TabIndex        =   3
      ToolTipText     =   "Exit Demo"
      Top             =   585
      Width           =   1095
   End
   Begin VB.TextBox txtAddress
      Height          =   320
      Left            =   1485
      TabIndex        =   1
      Top             =   102
      Width           =   3360
   End
   Begin UTSOCKETLibCtl.Socket utaxSocket
      Left            =   240
      Top             =   480
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   30
      BlockingMode    =   0   'False
      SocketType      =   1
      SocketProtocol  =   0
      SocketFamily    =   2
   End
   Begin VB.Label lblExample
      Caption         =   "e.g. SomeFingerServer.com"
      Height          =   255
      Left            =   1485
      TabIndex        =   5
      Top             =   540
      Width           =   2235
   End
   Begin VB.Label lblAddress
      Caption         =   "Address to finger:"
      Height          =   255
      Left            =   90
      TabIndex        =   0
      ToolTipText     =   "Enter Address to be Fingered"
      Top             =   135
      Width           =   1335
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Dundas TCP/IP v4.0
' Copyright © Dundas Software 1995-2001, all rights reserved
' ===================================================================
'
Option Explicit

Private Sub cmdFinger_Click()
    
    Dim rt As Long  'return var, indicates operation success/failure
    Dim strDomain As String  'Domain name
    
    On Error Resume Next  'enable inline error trapping
        
    txtResults = ""
    txtResults = txtResults & "Connecting ..."
    ' get the address from the address name
    strDomain = utaxSocket.GetAddressFromName(txtAddress)
    ' connect to the server
    
    rt = utaxSocket.Connect(strDomain, 79)
    
    ' check the error code
    If (rt <> ecSuccess) Then
        txtResults = txtResults & vbTab & utaxSocket.GetErrorText(rt)
    End If
    
    'set cursor position
    txtResults.SelStart = 10000
    
End Sub

Private Sub cmdExit_Click()

    
    utaxSocket.CloseConnection
    'unload form
    Unload Me
    
End Sub

Private Sub Form_Load()
    
utaxSocket.AboutBox
    'set timeouts
    utaxSocket.ReceiveTimeOut = 100
    utaxSocket.SendTimeOut = 100
    
End Sub

Private Sub Form_Resize()
'add resizing routine
    On Error Resume Next
    
    'first, align controls to be left-justified
    lblAddress.Left = 100
    txtResults.Left = 100
    
    'next, adjust height of textbox
    txtResults.Height = Me.ScaleHeight - txtResults.Top - 100
    
    'set width of textboxes, hor. position of command buttons
    txtResults.Width = Me.ScaleWidth - 220
    txtAddress.Width = Me.ScaleWidth - txtAddress.Left - 270
    cmdExit.Left = Me.ScaleWidth - 1350
    cmdFinger.Left = cmdExit.Left - 1190
    
    lblExample.Left = txtAddress.Left
    
    'lastly, do not let user undersize form
    If Me.Height < 4450 Then Me.Height = 4450
    If Me.Width < 6255 Then Me.Width = 6255
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release form variable
    Set frmMain = Nothing
    
End Sub

Private Sub utaxSocket_OnConnect(ByVal Result As Long)
    ' callback called when the connection to the server is established
    
    Dim rt As Long  'return var
    
    txtResults = txtResults & vbTab & utaxSocket.GetErrorText(Result) & vbCrLf & vbCrLf
    If Result = ecSuccess Then
        ' send data to the server
        rt = utaxSocket.SendAsLine(vbCrLf)
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & utaxSocket.GetErrorText(rt)
        End If
    End If
    
      
    'set cursor to end of text
    txtResults.SelStart = 10000
    
End Sub


Private Sub utaxSocket_OnReceiveLine(ByVal Line As String, ByVal LineLength As Long)
    ' callback called when data is ready to be read from the server
    
    Dim rt As Long  'return var, indicates success/failure
    
    ' call the ReceiveLine method to read information from the socket
    If LineLength > 0 Then
        txtResults = txtResults & Line
        
        ' Calling receive line will trigger another Socket_OnReceiveLine callback
        ' to be called. If no more data exists the connection is closed (see below)
        rt = utaxSocket.ReceiveLine()
    Else
        ' if there is no data to read, close the connection and
        '   display the status to the user
        rt = utaxSocket.CloseConnection()
        txtResults = txtResults & vbCrLf & "*** Done ***"
    End If

    'set cursor to end of text
    txtResults.SelStart = 10000

End Sub

Private Sub utaxSocket_OnSendAsLine(ByVal Result As Long)
    Dim rt As Long  'return var
    
    rt = utaxSocket.ReceiveLine()

    'if unsuccessful inform user
    If (rt <> ecSuccess) Then
        txtResults = txtResults & vbCrLf & utaxSocket.GetErrorText(rt)
    End If
   
    'set cursor to end of text
    txtResults.SelStart = 10000

End Sub
