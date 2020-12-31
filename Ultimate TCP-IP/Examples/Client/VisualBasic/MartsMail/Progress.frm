VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmProgress 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Progress of Mail Operation"
   ClientHeight    =   972
   ClientLeft      =   3756
   ClientTop       =   3360
   ClientWidth     =   4512
   ClipControls    =   0   'False
   HasDC           =   0   'False
   Icon            =   "Progress.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   NegotiateMenus  =   0   'False
   ScaleHeight     =   972
   ScaleWidth      =   4512
   StartUpPosition =   2  'CenterScreen
   Begin MSComctlLib.ProgressBar proProgress 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   420
      Width           =   4275
      _ExtentX        =   7535
      _ExtentY        =   656
      _Version        =   393216
      Appearance      =   1
      Max             =   20
   End
   Begin VB.Label lblProgress 
      AutoSize        =   -1  'True
      Caption         =   "Progress:"
      Height          =   195
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   660
   End
End
Attribute VB_Name = "frmProgress"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Dundas TCP/IP v4.0
' Copyright © Dundas Software 1995-2001, all rights reserved
' ===================================================================
'

Private Sub Form_Load()
    
    'cause form to repaint
    Me.Refresh
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
'release form variable
Set frmProgress = Nothing

End Sub
