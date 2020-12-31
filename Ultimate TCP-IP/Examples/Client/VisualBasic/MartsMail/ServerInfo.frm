VERSION 5.00
Begin VB.Form frmServerInfo 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Mail Server Information"
   ClientHeight    =   1560
   ClientLeft      =   4656
   ClientTop       =   6024
   ClientWidth     =   6636
   ClipControls    =   0   'False
   Icon            =   "ServerInfo.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1560
   ScaleWidth      =   6636
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   5445
      TabIndex        =   9
      ToolTipText     =   "Save Information"
      Top             =   540
      Width           =   1095
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "&Ok"
      Default         =   -1  'True
      Height          =   375
      Left            =   5445
      TabIndex        =   8
      ToolTipText     =   "Save Information"
      Top             =   90
      Width           =   1095
   End
   Begin VB.TextBox txtUserPassword 
      Height          =   320
      IMEMode         =   3  'DISABLE
      Left            =   1575
      PasswordChar    =   "*"
      TabIndex        =   7
      Top             =   1107
      Width           =   3615
   End
   Begin VB.TextBox txtUserName 
      Height          =   320
      Left            =   1575
      TabIndex        =   6
      Top             =   747
      Width           =   3615
   End
   Begin VB.TextBox txtPop3 
      Height          =   320
      Left            =   1575
      TabIndex        =   5
      Top             =   387
      Width           =   3615
   End
   Begin VB.TextBox txtSmtp 
      Height          =   320
      Left            =   1575
      TabIndex        =   4
      Top             =   27
      Width           =   3615
   End
   Begin VB.Label lblUserPassword 
      AutoSize        =   -1  'True
      Caption         =   "User &Password:"
      Height          =   195
      Left            =   0
      TabIndex        =   3
      ToolTipText     =   "Enter User Password"
      Top             =   1170
      Width           =   1110
   End
   Begin VB.Label lblUserName 
      AutoSize        =   -1  'True
      Caption         =   "User &Name:"
      Height          =   195
      Left            =   45
      TabIndex        =   2
      ToolTipText     =   "Enter User Name"
      Top             =   810
      Width           =   840
   End
   Begin VB.Label lblPop3 
      AutoSize        =   -1  'True
      Caption         =   "&Pop3 Server Name:"
      Height          =   195
      Left            =   45
      TabIndex        =   1
      ToolTipText     =   "Enter Valid Pop3 Mail Server Address (IP or DNS)"
      Top             =   450
      Width           =   1395
   End
   Begin VB.Label lblSmtp 
      AutoSize        =   -1  'True
      Caption         =   "&Smtp Server Name:"
      Height          =   195
      Left            =   45
      TabIndex        =   0
      ToolTipText     =   "Enter Valid Smtp Mail Server Address (IP or DNS)"
      Top             =   90
      Width           =   1380
   End
End
Attribute VB_Name = "frmServerInfo"
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

Private Sub cmdCancel_Click()
'cancels the "saving server info" operation
    Dim strTemp As String  'temp variable
    
    'indicate to user that values need to be input if they havent been input yet
    If txtUserName = "" Then
        strTemp = "You need to enter these values before" & vbCrLf
        strTemp = strTemp & " sending or receiving mail."
        MsgBox strTemp, vbOKOnly, "Account Information not Stored"
    End If
    
    Unload Me
    
End Sub

Private Sub cmdOk_Click()
    
    Dim myControl As Control
    Dim RegistryReturn As Variant
    Dim strTemp As String
    
    On Error GoTo errhandler
    
    'check to see if all entries have been entered
    For Each myControl In Controls
        If TypeOf myControl Is TextBox Then
            If myControl.Text = "" Then
                MsgBox "Error: Please fill in missing value(s)", vbOKOnly, "Missing Information"
                Exit Sub
            End If
        End If
    Next
    
    'release control object
    Set myControl = Nothing
    
    'values have been filled in, so save them to registry
    SaveSetting "DundasMailDemo", "ServerInfo", "MailHostName", txtSmtp
    SaveSetting "DundasMailDemo", "ServerInfo", "Pop3HostName", txtPop3
    SaveSetting "DundasMailDemo", "ServerInfo", "UserName", txtUserName
    SaveSetting "DundasMailDemo", "ServerInfo", "UserPassword", txtUserPassword
    
    'update public variables in frmMain
    frmMain.strPop3Name = Trim(txtPop3)
    frmMain.strUserName = Trim(txtUserName)
    frmMain.strUserPassword = Trim(txtUserPassword)
    
    'unload form
    Unload Me
    
    Exit Sub

errhandler:
    
    If Err.Number = 91 Then Resume Next 'trap for obj not set error
        
    'unload form
    Unload Me
    
    Exit Sub
        
End Sub


Private Sub Form_Load()
' load server info from registry

Dim varTemp As Variant 'temp variable

varTemp = GetAllSettings("DundasMailDemo", "ServerInfo")

'populate form's textboxes with registry settings if they exist
If Not IsEmpty(varTemp) Then
    txtSmtp = varTemp(0, 1)
    txtPop3 = varTemp(1, 1)
    txtUserName = varTemp(2, 1)
    txtUserPassword = varTemp(3, 1)
End If

End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release hidden form var
    Set frmServerInfo = Nothing
    
End Sub
