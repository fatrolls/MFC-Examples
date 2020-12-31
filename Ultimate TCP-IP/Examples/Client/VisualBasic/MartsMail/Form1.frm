VERSION 5.00
Begin VB.Form frmTop 
   Caption         =   "Message Tops"
   ClientHeight    =   4452
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   7368
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   4452
   ScaleWidth      =   7368
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Height          =   375
      Left            =   6060
      TabIndex        =   2
      Top             =   3840
      Width           =   1095
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   "&Next"
      Default         =   -1  'True
      Height          =   375
      Left            =   4800
      TabIndex        =   1
      Top             =   3840
      Width           =   1095
   End
   Begin VB.TextBox txtTop 
      Height          =   2475
      Left            =   180
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   780
      Width           =   7095
   End
End
Attribute VB_Name = "frmTop"
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
Public intNumMsgs As Integer  'set by frmMain so we know total num of available messages
Dim intCurMsg As Integer  'keeps track of which message we are working with
Public intNumLines As Integer 'set by frmMain, lets us know how many lines of the
                                '    body should be retrieved
                                
Private Sub cmdClose_Click()
    Unload Me
End Sub

Private Sub cmdNext_Click()
        
    'reset public boolean in frmMain, so that we will grab lines in next top
    frmMain.blnGetNextTop = True
    
    'use frmMain's subroutine to retrieve top data
    Call frmMain.GetTop(intCurMsg, intNumLines)
    
    'check to see there is another message to retrieve, if not disable button
    If intCurMsg = intNumMsgs Then cmdNext.Enabled = False
    
    intCurMsg = intCurMsg + 1
           
End Sub

Private Sub Form_Load()
'check to see if there is only 1 message, if so disable Next button
If intNumMsgs = 1 Then cmdNext.Enabled = False

'set intCurMsg to 2, since message#1 taken care of by frmMain
intCurMsg = 2

End Sub

Private Sub Form_Resize()
'resize textbox
On Error Resume Next

txtTop.Left = 100
txtTop.Top = 100
txtTop.Width = Me.ScaleWidth - 200
txtTop.Height = Me.ScaleHeight - 700

cmdClose.Left = Me.ScaleWidth - 1200
cmdNext.Left = cmdClose.Left - 1200
cmdClose.Top = Me.ScaleHeight - 500
cmdNext.Top = cmdClose.Top
If Me.Height < 4800 Then Me.Height = 4800
If Me.Width < 7000 Then Me.Width = 7000

End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set frmTop = Nothing
    
End Sub
