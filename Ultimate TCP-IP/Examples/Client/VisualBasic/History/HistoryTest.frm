VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.4#0"; "UTHistory.dll"
Begin VB.Form frmMain
   Caption         =   "Dundas  TCP/IP  utaxHistory ActiveX Control 4.0 - Demo Program"
   ClientHeight    =   6180
   ClientLeft      =   2736
   ClientTop       =   1992
   ClientWidth     =   7524
   ForeColor       =   &H8000000D&
   LinkTopic       =   "Form1"
   ScaleHeight     =   6180
   ScaleWidth      =   7524
   StartUpPosition =   2  'CenterScreen
   Begin UTHISTORYLibCtl.History utaxHistory
      Height          =   3972
      Left            =   120
      OleObjectBlob   =   "HistoryTest.frx":0000
      TabIndex        =   16
      Top             =   1920
      Width           =   7332
   End
   Begin VB.TextBox txttimeStmpFrmt
      Height          =   324
      Left            =   4440
      TabIndex        =   14
      Text            =   "Time %X Date %x"
      Top             =   600
      Width           =   1452
   End
   Begin VB.CheckBox chkTimeStamp
      Alignment       =   1  'Right Justify
      Caption         =   "Time Stamp"
      Height          =   372
      Left            =   4560
      TabIndex        =   13
      Top             =   960
      Width           =   1332
   End
   Begin VB.CommandButton cmdSetLogName
      Caption         =   "Set Log"
      Height          =   372
      Left            =   6360
      TabIndex        =   12
      Top             =   1440
      Width           =   1092
   End
   Begin VB.CheckBox chkEnableLog
      Alignment       =   1  'Right Justify
      Caption         =   "Enable Log"
      Height          =   372
      Left            =   4560
      TabIndex        =   11
      Top             =   1440
      Width           =   1332
   End
   Begin VB.TextBox txtLogName
      Height          =   320
      Left            =   1575
      TabIndex        =   10
      Text            =   "c:\Historylog.txt"
      Top             =   1440
      Width           =   2640
   End
   Begin VB.TextBox txtText
      Height          =   320
      Left            =   1575
      TabIndex        =   9
      Text            =   "Text1"
      Top             =   105
      Width           =   4320
   End
   Begin VB.CommandButton cmdExit
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   6360
      TabIndex        =   5
      ToolTipText     =   "Exit the Demo Application"
      Top             =   945
      Width           =   1095
   End
   Begin VB.CommandButton cmdClear
      Caption         =   "&Clear "
      Height          =   375
      Left            =   6348
      TabIndex        =   7
      ToolTipText     =   "Clear utaxHistory Control Contents"
      Top             =   525
      Width           =   1095
   End
   Begin VB.ComboBox cboBackColor
      Height          =   288
      Left            =   1560
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   969
      Width           =   1575
   End
   Begin VB.ComboBox cboForeColor
      Appearance      =   0  'Flat
      ForeColor       =   &H00000000&
      Height          =   288
      Left            =   1560
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   600
      Width           =   1575
   End
   Begin VB.CommandButton cmdAddLine
      Caption         =   "&Add line"
      Default         =   -1  'True
      Height          =   375
      Left            =   6348
      TabIndex        =   6
      ToolTipText     =   "Add A Line to Control with Current Settings"
      Top             =   105
      Width           =   1095
   End
   Begin VB.Label lblLabel2
      Caption         =   "Stamp Format"
      Height          =   252
      Left            =   3240
      TabIndex        =   15
      Top             =   600
      Width           =   1092
   End
   Begin VB.Label lblLabel1
      Alignment       =   1  'Right Justify
      Caption         =   "Log File"
      Height          =   252
      Left            =   720
      TabIndex        =   8
      Top             =   1440
      Width           =   612
   End
   Begin VB.Label lblBackColor
      Caption         =   "Background color:"
      Height          =   252
      Left            =   0
      TabIndex        =   3
      ToolTipText     =   "Choose Background Color"
      Top             =   960
      Width           =   1452
   End
   Begin VB.Label lblForeColor
      Caption         =   "Foreground color:"
      Height          =   252
      Left            =   120
      TabIndex        =   1
      ToolTipText     =   "Choose Foreground Color"
      Top             =   600
      Width           =   1332
   End
   Begin VB.Label lblText
      Caption         =   "Text to add:"
      Height          =   270
      Left            =   105
      TabIndex        =   0
      ToolTipText     =   "Add Text Here"
      Top             =   130
      Width           =   1095
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

Private Sub chkEnableLog_Click()
If txtLogName.Enabled Then
txtLogName.Enabled = False
Else
txtLogName.Enabled = True
End If
utaxHistory.EnableLog = txtLogName.Enabled
cmdSetLogName.Enabled = txtLogName.Enabled
End Sub

Private Sub cmdAddLine_Click()
    
    If (txtText <> "") Then
       
        Dim ForegroundColor As OLE_COLOR
        Dim BackgroundColor As OLE_COLOR
        
        ' Determine which color the user
        ' has selected
        If (cboForeColor.Text = "Red") Then
            ForegroundColor = RGB(255, 0, 0)
        Else
            If (cboForeColor.Text = "Green") Then
                ForegroundColor = RGB(0, 255, 0)
            Else
                If (cboForeColor.Text = "Blue") Then
                    ForegroundColor = RGB(0, 0, 255)
                Else
                    ForegroundColor = RGB(0, 0, 0)
                End If
            End If
        End If
        If (cboBackColor.Text = "Red") Then
            BackgroundColor = RGB(255, 0, 0)
        Else
            If (cboBackColor.Text = "Green") Then
                BackgroundColor = RGB(0, 255, 0)
            Else
                If (cboBackColor.Text = "Blue") Then
                    BackgroundColor = RGB(0, 0, 255)
                Else
                    BackgroundColor = RGB(255, 255, 255)
                End If
            End If
        End If
        
        ' Output the text to the history control (in the specified
        ' foreground and background colors)
        If chkTimeStamp Then
        utaxHistory.TimeStampFormat = Trim$(txttimeStmpFrmt)
        utaxHistory.AddStampedLine txtText.Text, ForegroundColor, BackgroundColor
        Else
        utaxHistory.AddLine txtText, ForegroundColor, BackgroundColor
        End If
        
    End If
    
End Sub

Private Sub cmdClear_Click()
    
    'clear History control
    utaxHistory.ClearHistory
    
End Sub

Private Sub cmdExit_Click()
    
    'unload form
    Unload Me
    
End Sub

Private Sub cmdSetLogName_Click()
    utaxHistory.LogName = Trim$(txtLogName)
   
End Sub

Private Sub Form_Load()
    
    ' Add the neccessary items to the combo
    ' boxes
    utaxHistory.AboutBox
    
    cboForeColor.AddItem ("Red")
    cboForeColor.AddItem ("Green")
    cboForeColor.AddItem ("Blue")
    cboForeColor.AddItem ("Black")
    
    
    cboBackColor.AddItem ("White")
    cboBackColor.AddItem ("Red")
    cboBackColor.AddItem ("Green")
    cboBackColor.AddItem ("Blue")
    
    txtText = "Add your text here."
    utaxHistory.AddLine ("Dundas Software, Dundas TCP/IP 4.0" & vbCrLf)
    utaxHistory.TabIndex = 6
    'initialize combo's
    cboBackColor = "Red"
    cboForeColor = "Blue"
    utaxHistory.EnableLog = False
    cmdSetLogName.Enabled = False
    txtLogName.Enabled = False
    utaxHistory.TimeStampFormat = "%x at %X"
    txttimeStmpFrmt = "%x at %X"
End Sub

Private Sub Form_Resize()
    'add routine to resize controls on form
    On Error Resume Next
    
    Dim lngFormWidth As Long
    lngFormWidth = Me.ScaleWidth
    
    'first make sure all controls have leftmost edges aligned
    utaxHistory.Left = 80
    lblText.Left = 80
    lblForeColor.Left = 80
    lblBackColor.Left = 80
    
    'next adjust width of history control
    utaxHistory.Width = lngFormWidth - 160
    
    'adjust height of History control
    utaxHistory.Height = Me.ScaleHeight - utaxHistory.Top - 70
    
    'adjust command buttons to stay to rightmost edge of form
    cmdExit.Left = lngFormWidth - 1095 - 80
    cmdAddLine.Left = lngFormWidth - 1095 - 80
    cmdClear.Left = lngFormWidth - 1095 - 80
    cmdSetLogName.Left = lngFormWidth - 1095 - 80
    'last,do not allow user to undersize form
    If Me.Width < 7200 Then Me.Width = 7200
    If Me.Height < 5000 Then Me.Height = 5000
    
End Sub

