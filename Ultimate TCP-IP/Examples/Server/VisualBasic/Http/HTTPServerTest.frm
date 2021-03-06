VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.0#0"; "UTHIST~1.DLL"
Object = "{4751AD5A-225A-11D3-A48B-0080C858F182}#1.0#0"; "UTHTTP~1.DLL"
Begin VB.Form frmMain 
   Caption         =   "Ultimate TCP/IP HTTPServ Server ActiveX Control 3.0 - Demo Program"
   ClientHeight    =   5520
   ClientLeft      =   4485
   ClientTop       =   2310
   ClientWidth     =   5565
   ClipControls    =   0   'False
   Icon            =   "HTTPServerTest.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5520
   ScaleWidth      =   5565
   StartUpPosition =   2  'CenterScreen
   Begin UTHISTORYLibCtl.History History 
      Height          =   4395
      Left            =   120
      OleObjectBlob   =   "HTTPServerTest.frx":000C
      TabIndex        =   7
      Top             =   1080
      Width           =   5355
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   4320
      TabIndex        =   8
      ToolTipText     =   "Exit the Deom Application"
      Top             =   585
      Width           =   1095
   End
   Begin VB.TextBox txtPath 
      Height          =   320
      Left            =   720
      TabIndex        =   5
      Text            =   "c:\"
      Top             =   135
      Width           =   1890
   End
   Begin VB.CommandButton cmdStop 
      Cancel          =   -1  'True
      Caption         =   "S&top"
      Height          =   375
      Left            =   3015
      TabIndex        =   4
      ToolTipText     =   "Stop the HTTP Server"
      Top             =   585
      Width           =   1095
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "&Start"
      Default         =   -1  'True
      Height          =   375
      Left            =   3015
      TabIndex        =   3
      ToolTipText     =   "Start the HTTP Server"
      Top             =   90
      Width           =   1095
   End
   Begin VB.CommandButton cmdSetPath 
      Caption         =   "Set &Path"
      Height          =   375
      Left            =   4320
      TabIndex        =   2
      ToolTipText     =   "Set the Path in Textbox"
      Top             =   90
      Width           =   1095
   End
   Begin VB.TextBox txtConnections 
      Height          =   320
      Left            =   1245
      Locked          =   -1  'True
      TabIndex        =   0
      Text            =   "0"
      Top             =   630
      Width           =   1365
   End
   Begin UTHTTPSERVLibCtl.HttpServ HttpServ 
      Left            =   2760
      Top             =   300
      Path            =   "E:\ut30\Examples\Server\VisualBasic\Http\"
      MaxConnections  =   20
      Port            =   80
   End
   Begin VB.Label lblPath 
      Caption         =   "Pat&h:"
      Height          =   255
      Left            =   180
      TabIndex        =   6
      ToolTipText     =   "Current Server Path"
      Top             =   180
      Width           =   375
   End
   Begin VB.Label lblConnections 
      Caption         =   "&Connections:"
      Height          =   255
      Left            =   135
      TabIndex        =   1
      ToolTipText     =   "Current Number of Connections"
      Top             =   675
      Width           =   975
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Ultimate TCP/IP v3.0
' Copyright � Dundas Software 1995-1999, all rights reserved
' ===================================================================
'
Option Explicit

Private Sub cmdExit_Click()
'exit application
    Unload Me
    
End Sub

Private Sub Form_Resize()
'need resize routine

    'first, align leftmost controls
    lblPath.Left = 100
    lblConnections.Left = 100
    History.Left = 100
    
    'next. adjust height of history control
    History.Height = Me.ScaleHeight - History.Top - 100
    
    'adjust width of history control
    History.Width = Me.ScaleWidth - 200
    
    'adjust command buttons
    cmdSetPath.Left = Me.ScaleWidth - 1195
    cmdExit.Left = Me.ScaleWidth - 1195
    cmdStart.Left = cmdExit.Left - 1295
    cmdStop.Left = cmdExit.Left - 1295
    
    'do not let user undersize form
    If Me.Width < 5680 Then Me.Width = 5680
    If Me.Height < 3000 Then Me.Height = 3000
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'if we are connected then close session
    If cmdStop.Enabled = True Then HttpServ.Stop
        
    'release hidden form var
    Set frmMain = Nothing
    
End Sub

Private Sub HttpServ_OnCommandFinished(ByVal CommandID As UTHTTPSERVLibCtl.HttpCommand, _
ByVal Params As String, ByVal Success As Long)
    ' callback called when an HTTP command has finished its execution

    ' Add the output that was generated by the command to the history control
    History.AddLine (HttpServ.GetCommandName(CommandID))
    History.AppendToLine (" command finished. Param = ")
    History.AppendToLine (Params)
    
    'output success/failure to user
    If Success = ecSuccess Then
        History.AppendToLine (". Succeeded")
    Else
        History.AppendToLine (". Failed")
    End If
    
End Sub

Private Sub HttpServ_OnCommandStarted(ByVal CommandID As UTHTTPSERVLibCtl.HttpCommand, _
ByVal Params As String, Continue As Boolean)
    ' callback called when an HTTP command has begun its execution
    
    ' add status to the history control
    History.AddLine (HttpServ.GetCommandName(CommandID))
    History.AppendToLine (" command started. Param = ")
    History.AppendToLine (Params)
    Continue = True
    
End Sub

Private Sub HttpServ_OnConnect()
    ' callback called when a new connection to the server is established
    
    'update number of connections textbox
    txtConnections = HttpServ.Connections
    
End Sub

Private Sub HttpServ_OnStatus(ByVal Message As String)
    ' callback called when a status change occurs
    
    'alert user to status change
    History.AddLine (Message)
    
End Sub

Private Sub Form_Load()
        
    ' set the path of the http server
    '   and start the server
    HttpServ.Path = "c:\"
    Call cmdStart_Click
    
End Sub

Private Sub cmdSetPath_Click()
        
    ' update the server path
    HttpServ.Path = txtPath
    'alert user to update
    Call History.AddLine("Path changed to " & txtPath)
    
End Sub

Private Sub cmdStart_Click()
    
    Dim rt As Long  'return variable, indicates success/failure
    
    ' starts the server
    rt = HttpServ.Start()
    
    ' display error code (if any),or indicate operation ok
    If rt <> 0 Then
        Call History.AddLine(HttpServ.GetErrorText(rt), &HFF)
    Else
        Call History.AddLine("Our Http Server Started Ok...", &H7000)
    End If
    
    'disable the start button
    cmdStart.Enabled = False
    'enable the stop button
    cmdStop.Enabled = True
    
End Sub

Private Sub cmdStop_Click()
    
    ' stop the server
    HttpServ.Stop
    
    'enable the start button
    cmdStart.Enabled = True
    
    'disable the stop button
    cmdStop.Enabled = False
    
End Sub

