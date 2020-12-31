VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "About Mail Client ActiveX Control"
   ClientHeight    =   3852
   ClientLeft      =   5856
   ClientTop       =   5268
   ClientWidth     =   4272
   ClipControls    =   0   'False
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3852
   ScaleWidth      =   4272
   Tag             =   "About Project1"
   Begin VB.Image imgDundas 
      Appearance      =   0  'Flat
      Height          =   384
      Left            =   3600
      Picture         =   "frmAbout.frx":0442
      Top             =   3240
      Width           =   384
   End
   Begin VB.Label lblDundas 
      ForeColor       =   &H00000000&
      Height          =   1815
      Left            =   90
      TabIndex        =   3
      Tag             =   "App Description"
      Top             =   1935
      UseMnemonic     =   0   'False
      Width           =   4095
   End
   Begin VB.Label lblDescription 
      Caption         =   $"frmAbout.frx":0884
      ForeColor       =   &H00000000&
      Height          =   945
      Left            =   90
      TabIndex        =   2
      Tag             =   "App Description"
      Top             =   855
      Width           =   4095
   End
   Begin VB.Label lblTitle 
      AutoSize        =   -1  'True
      Caption         =   "Dundas Software Mail Client ActiveX Control Demo"
      ForeColor       =   &H00000000&
      Height          =   195
      Left            =   90
      TabIndex        =   1
      Tag             =   "Application Title"
      Top             =   135
      Width           =   3600
      WordWrap        =   -1  'True
   End
   Begin VB.Label lblVersion 
      Caption         =   "Dundas TCP/IP 4.0"
      Height          =   225
      Left            =   90
      TabIndex        =   0
      Tag             =   "Version"
      Top             =   495
      Width           =   4095
   End
End
Attribute VB_Name = "frmAbout"
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

Private Sub Form_Load()
    
    Dim strTemp As String
    
    'initialize lblDundas
    strTemp = "For more information on Dundas Software's products and services, visit us at www.dundas.com"
    strTemp = strTemp & vbCrLf & vbCrLf & "Phone:" & "                               " & "Fax:" _
    & vbCrLf & "(416) 467-5100" & "                  " & "(416) 422-4801" _
    & vbCrLf & "(800) 463-1492"
    
    strTemp = strTemp & vbCrLf & vbCrLf & "Email:" _
    & vbCrLf & "sales@dundas.com"
 
    lblDundas = strTemp
   
End Sub

Private Sub Form_Unload(Cancel As Integer)

    'release form var
    Set frmAbout = Nothing
    
End Sub

