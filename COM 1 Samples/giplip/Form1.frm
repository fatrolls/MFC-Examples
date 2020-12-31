VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1530
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7200
   LinkTopic       =   "Form1"
   ScaleHeight     =   1530
   ScaleWidth      =   7200
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton VolumeBtn 
      Caption         =   "Volume"
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Top             =   960
      Width           =   6735
   End
   Begin VB.TextBox Bottom 
      Height          =   405
      Left            =   6000
      TabIndex        =   6
      Text            =   "0"
      Top             =   240
      Width           =   855
   End
   Begin VB.TextBox Right 
      Height          =   405
      Left            =   4320
      TabIndex        =   4
      Text            =   "0"
      Top             =   240
      Width           =   855
   End
   Begin VB.TextBox Top 
      Height          =   405
      Left            =   2640
      TabIndex        =   2
      Text            =   "0"
      Top             =   240
      Width           =   855
   End
   Begin VB.TextBox Left 
      Height          =   405
      Left            =   960
      TabIndex        =   0
      Text            =   "0"
      Top             =   240
      Width           =   855
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Bottom:"
      Height          =   375
      Left            =   5280
      TabIndex        =   7
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Right:"
      Height          =   375
      Left            =   3600
      TabIndex        =   5
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Top:"
      Height          =   375
      Left            =   1920
      TabIndex        =   3
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "Left:"
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub VolumeBtn_Click()
    Dim rct As Rect
    Set rct = New Rect
    rct.SetCoords Left, Top, Right, Bottom
    MsgBox "The volume is " & rct.Volume
End Sub
