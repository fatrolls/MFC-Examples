VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.0#0"; "UTHIST~1.DLL"
Object = "{178D93F5-232D-11D3-A48E-0080C858F182}#1.0#0"; "UTMAIL~1.DLL"
Begin VB.Form frmMain 
   Caption         =   "Ultimate TCP/IP MailServ Server ActiveX Control 3.0 - Demo Application"
   ClientHeight    =   5085
   ClientLeft      =   1800
   ClientTop       =   2220
   ClientWidth     =   7035
   ClipControls    =   0   'False
   Icon            =   "MailServerTest.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5085
   ScaleWidth      =   7035
   StartUpPosition =   2  'CenterScreen
   Begin UTHISTORYLibCtl.History History 
      Height          =   4935
      Left            =   120
      OleObjectBlob   =   "MailServerTest.frx":000C
      TabIndex        =   0
      Top             =   120
      Width           =   5535
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Default         =   -1  'True
      Height          =   375
      Left            =   5760
      TabIndex        =   2
      ToolTipText     =   "Exit the Demo Application"
      Top             =   585
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdmin 
      Caption         =   "&Administrator"
      Height          =   375
      Left            =   5760
      TabIndex        =   1
      ToolTipText     =   "Show the Administrator Window"
      Top             =   120
      Width           =   1095
   End
   Begin UTMAILSERVLibCtl.MailServ MailServ 
      Left            =   5880
      Top             =   1500
      RootKey         =   "SOFTWARE\EMAIL_S"
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

Private Sub cmdAdmin_Click()
    
    frmAdmin.Show vbModal
    
End Sub

Private Sub cmdExit_Click()
'close app
    
    'first stop server from running
    
    Unload Me
    
End Sub

Private Sub Form_Load()
    
    Dim rt As Long  'return variable, indicates success/failure
    
    ' start the mail server
    rt = MailServ.Start()
    If rt <> ecSuccess Then
        History.AddLine (MailServ.GetErrorText(rt))
    End If
    History.AddLine "Registry Key Is: " & MailServ.RegistryRootKey
    
End Sub

Private Sub Form_Resize()
'add resizing routine
    On Error Resume Next
    
    Dim lngFormWidth As Long  'form's scalewidth
    Dim lngFormHeight As Long  'form's scaleheight
    
    lngFormWidth = Me.ScaleWidth
    lngFormHeight = Me.ScaleHeight
    
    History.Left = 100
     
    'adjust width, height of history control
     History.Height = lngFormHeight - History.Top - 100
     History.Width = lngFormWidth - 1500
    
    'adjust command buttons
    cmdExit.Left = lngFormWidth - 1195
    cmdAdmin.Left = lngFormWidth - 1195
    
    'last, do not let user undersize form
    If Me.Width < 7155 Then Me.Width = 7155
    If Me.Height < 3000 Then Me.Height = 3000
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release hidden form variable
    Set frmMain = Nothing
    
End Sub

Private Sub MailServ_OnStatus(ByVal Message As String)
    ' callback called each time status on the server
    ' changes
    
    ' indicate status change via the history control
    History.AddLine (Message)
    
End Sub
