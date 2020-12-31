VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.0#0"; "UTHIST~1.DLL"
Object = "{1D8EC240-1E9E-11D3-A487-0080C858F182}#1.0#0"; "UTFING~1.DLL"
Begin VB.Form frmMain 
   Caption         =   "Ultimate TCP/IP  FingerServ Server ActiveX Control 3.0 - Demo Program"
   ClientHeight    =   4320
   ClientLeft      =   4590
   ClientTop       =   1770
   ClientWidth     =   5490
   ClipControls    =   0   'False
   FillColor       =   &H00FFFFFF&
   Icon            =   "FingerServTest.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4320
   ScaleWidth      =   5490
   Begin UTHISTORYLibCtl.History hisHistory 
      Height          =   3315
      Left            =   60
      OleObjectBlob   =   "FingerServTest.frx":000C
      TabIndex        =   7
      Top             =   960
      Width           =   5415
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   4230
      TabIndex        =   8
      ToolTipText     =   "Exit the Application"
      Top             =   513
      Width           =   1095
   End
   Begin VB.TextBox txtConnections 
      Height          =   320
      Left            =   1260
      Locked          =   -1  'True
      TabIndex        =   6
      Text            =   "0"
      Top             =   90
      Width           =   1410
   End
   Begin VB.CommandButton cmdSetPath 
      Caption         =   "Set &Path"
      Height          =   375
      Left            =   4230
      TabIndex        =   4
      ToolTipText     =   "Set the Path to Finger Information"
      Top             =   63
      Width           =   1095
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "&Start"
      Default         =   -1  'True
      Height          =   375
      Left            =   2970
      TabIndex        =   3
      ToolTipText     =   "Enable the Finger Server"
      Top             =   63
      Width           =   1095
   End
   Begin VB.CommandButton cmdStop 
      Cancel          =   -1  'True
      Caption         =   "S&top"
      Height          =   375
      Left            =   2970
      TabIndex        =   2
      ToolTipText     =   "Disable Finger Server"
      Top             =   513
      Width           =   1095
   End
   Begin VB.TextBox txtPath 
      Height          =   320
      Left            =   720
      TabIndex        =   1
      Text            =   "c:\"
      Top             =   540
      Width           =   1980
   End
   Begin UTFINGERSERVLibCtl.FingerServ FingerServ 
      Left            =   2820
      Top             =   480
      Path            =   "E:\ut30\Examples\Server\VisualBasic\Finger\"
      MaxConnections  =   20
      Port            =   79
   End
   Begin VB.Label lblConnections 
      Caption         =   "&Connections:"
      Height          =   255
      Left            =   135
      TabIndex        =   5
      ToolTipText     =   "Number of Current Finger Connections"
      Top             =   123
      Width           =   1020
   End
   Begin VB.Label lblPath 
      Caption         =   "Path:"
      Height          =   255
      Left            =   135
      TabIndex        =   0
      ToolTipText     =   "Path to Finger Information"
      Top             =   573
      Width           =   375
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Ultimate TCP/IP v3.0
' Copyright © Dundas Software 1995-1999, all rights reserved
' ===================================================================
'
Option Explicit

Private Sub cmdExit_Click()
    
    'exit app
    Unload Me
    
End Sub

Private Sub FingerServ_OnConnect()
    ' Callback called each time a new connection to the server
    '   is established. Update the connections window to display
    '   the current number of connections
        
    txtConnections = FingerServ.Connections
    
End Sub

Private Sub FingerServ_OnMaxConnect()

    ' Too many users are actively connected to the server
   hisHistory.AddLine "Maximum number of users reached, " & _
   "unable to serve one or more users"
   
End Sub

Private Sub FingerServ_OnStatus(ByVal Message As String)
    ' Callback called when the status changes
    
    'update hisHistory control
    hisHistory.AddLine (Message)
        
End Sub

Private Sub Form_Load()
        
    ' Set the finger path and start the server
    Call cmdSetPath_Click
    Call cmdStart_Click
    
End Sub

Private Sub Form_Resize()
'utilize resizing routine

    'align leftmost edge of controls
    lblConnections.Left = 100
    lblPath.Left = 100
    hisHistory.Left = 100
    
    'resize history control
    hisHistory.Height = Me.ScaleHeight - hisHistory.Top - 100
    hisHistory.Width = Me.ScaleWidth - 200

    cmdExit.Left = Me.ScaleWidth - 1195
    cmdSetPath.Left = Me.ScaleWidth - 1195
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    If (cmdStart.Enabled) Then
        ' Stop the server when quitting
        FingerServ.Stop
    End If
    
    'unload form var
    Set frmMain = Nothing
    
End Sub

Private Sub cmdSetPath_Click()
    
    ' Update the server path
    FingerServ.Path = txtPath
    'update hisHistory control
    hisHistory.AddLine ("New path set to " & txtPath)
    
End Sub

Private Sub cmdStart_Click()
        
    Dim rt As Long  'return variable, indicates success/failure
    
    ' Start the finger server
    rt = FingerServ.Start()
    
    'if error occurs notify user
    If rt <> 0 Then
        ' Display error text if the server could not be started
        Call hisHistory.AddLine(FingerServ.GetErrorText(rt), &HFF)
    Else
        cmdStart.Enabled = False
        cmdStop.Enabled = True
        Call hisHistory.AddLine("Finger Server Started. Waiting for connections...", &H7000)
    End If
    
End Sub

Private Sub cmdStop_Click()
        
    ' Stop the server from running
    cmdStop.Enabled = False
    cmdStart.Enabled = True
    FingerServ.Stop
    
    'update the number of connections textbox
    txtConnections = "0"
    
End Sub

