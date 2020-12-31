VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#4.0#0"; "UTHistory.dll"
Object = "{20DA1A60-2288-11D3-A48B-0080C858F182}#4.0#0"; "UTFtpServ.dll"
Begin VB.Form frmMain 
   Caption         =   "Dundas TCP/IP FTP Server ActiveX Control 4.0 - Demo Program"
   ClientHeight    =   5040
   ClientLeft      =   2292
   ClientTop       =   2292
   ClientWidth     =   5496
   ClipControls    =   0   'False
   Icon            =   "FTPServTest.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5040
   ScaleWidth      =   5496
   Begin UTHISTORYLibCtl.History hisHistory 
      Height          =   3915
      Left            =   60
      OleObjectBlob   =   "FTPServTest.frx":000C
      TabIndex        =   5
      Top             =   1080
      Width           =   5355
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   4230
      TabIndex        =   8
      ToolTipText     =   "Exit the Demo Application"
      Top             =   585
      Width           =   1095
   End
   Begin VB.TextBox txtConnections 
      Height          =   320
      Left            =   1260
      Locked          =   -1  'True
      TabIndex        =   4
      Text            =   "0"
      Top             =   72
      Width           =   1365
   End
   Begin VB.CommandButton cmdSetPath 
      Caption         =   "Set &Path"
      Height          =   375
      Left            =   4230
      TabIndex        =   3
      ToolTipText     =   "Set the Server Path"
      Top             =   90
      Width           =   1095
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "&Start"
      Default         =   -1  'True
      Height          =   375
      Left            =   2970
      TabIndex        =   2
      ToolTipText     =   "Start the FTP Server"
      Top             =   90
      Width           =   1095
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "S&top"
      Height          =   375
      Left            =   2970
      TabIndex        =   1
      ToolTipText     =   "Stop the FTP Server"
      Top             =   585
      Width           =   1095
   End
   Begin VB.TextBox txtPath 
      Height          =   320
      Left            =   630
      TabIndex        =   0
      Text            =   "c:\"
      Top             =   507
      Width           =   1980
   End
   Begin UTFTPSERVLibCtl.FtpServ FtpServ 
      Left            =   360
      Top             =   900
      Path            =   "E:\ut30\Examples\Server\VisualBasic\Ftp\"
      MaxConnections  =   20
      Port            =   21
      WelcomeMsg      =   $"FTPServTest.frx":0092
   End
   Begin VB.Label lblConnections 
      Caption         =   "&Connections:"
      Height          =   285
      Left            =   135
      TabIndex        =   7
      ToolTipText     =   "Current number of FTP Connections"
      Top             =   90
      Width           =   1020
   End
   Begin VB.Label lblPath 
      Caption         =   "Pat&h:"
      Height          =   255
      Left            =   135
      TabIndex        =   6
      ToolTipText     =   "Current Server Path"
      Top             =   540
      Width           =   375
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

Private Sub cmdExit_Click()
    
    'exit the app
    Unload Me
    
End Sub

Private Sub Form_Resize()
'add resizing routine
    On Error Resume Next
    
    'align leftmost edges of controls
    lblConnections.Left = 100
    lblPath.Left = 100
    hisHistory.Left = 100
    
    'next adjust width, height of history control
    hisHistory.Height = Me.ScaleHeight - hisHistory.Top - 100
    hisHistory.Width = Me.ScaleWidth - 200
    
    'adjust command buttons
    cmdSetPath.Left = Me.ScaleWidth - 1195
    cmdExit.Left = Me.ScaleWidth - 1195
    cmdStart.Left = cmdSetPath.Left - 1295
    cmdStop.Left = cmdSetPath.Left - 1295
    
    'last, do not let user undersize the form
    If Me.Width < 5600 Then Me.Width = 5600
    If Me.Height < 3000 Then Me.Height = 3000
    
End Sub

Private Sub Form_Unload(Cancel As Integer)

    'release hidden form variable
    Set frmMain = Nothing
    
End Sub

Private Sub FtpServ_OnConnect()
    ' Callback called when a new connection to the server is established
    
    ' Update the number of active connections
    txtConnections = FtpServ.Connections
    
End Sub

Private Sub FtpServ_OnStatus(ByVal Message As String)
    ' Callback called when a status update occurrs
    
    'alert user to status update
    hisHistory.AddLine (Message)
    
End Sub

Private Sub Form_Load()
    FtpServ.AboutBox
    ' Start the FTP server
    
    Call cmdStart_Click
    
End Sub

Private Sub cmdSetPath_Click()
        
    ' Update the server path
    FtpServ.Path = txtPath
    
    hisHistory.AddLine ("Server root directory set to: " & txtPath)
    
End Sub

Private Sub cmdStart_Click()
    
    Dim rt As Long  'return variable, indicates success/failure
    
    
    ' Start the server
    cmdStart.Enabled = False
    cmdStop.Enabled = True
    FtpServ.Path = txtPath.Text
    rt = FtpServ.Start()
    
    'if error occurred alert user, else notify things are ok
    If rt <> 0 Then
        Call hisHistory.AddLine(FtpServ.GetErrorText(rt), &HFF)
    Else
        Call hisHistory.AddLine("Our Ftp Server Started Ok...", &H7000)
    End If
    
End Sub

Private Sub cmdStop_Click()
    
    ' Stop the server
    FtpServ.Stop
    cmdStart.Enabled = True
    cmdStop.Enabled = False
    
End Sub


