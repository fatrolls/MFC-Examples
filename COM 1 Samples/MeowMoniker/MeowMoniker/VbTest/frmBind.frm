VERSION 5.00
Begin VB.Form frmBind 
   Caption         =   "Show Me The Moniker!"
   ClientHeight    =   624
   ClientLeft      =   48
   ClientTop       =   372
   ClientWidth     =   6948
   LinkTopic       =   "Form1"
   ScaleHeight     =   624
   ScaleWidth      =   6948
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdBind 
      Caption         =   "&Bind"
      Default         =   -1  'True
      Height          =   372
      Left            =   5880
      TabIndex        =   2
      Top             =   120
      Width           =   972
   End
   Begin VB.TextBox txtMoniker 
      Height          =   372
      Left            =   1920
      TabIndex        =   1
      Top             =   120
      Width           =   3852
   End
   Begin VB.Label Label1 
      Caption         =   "CoPoint display name:"
      Height          =   372
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1692
   End
End
Attribute VB_Name = "frmBind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdBind_Click()
    Dim pt As CoPoint
    Set pt = GetObject(txtMoniker)
    pt.x = 100
    pt.y = 200
    pt.Translate 50, 50
    pt.Invert
    MsgBox pt.x & ", " & pt.y, vbOKOnly, "Quon!"
End Sub
