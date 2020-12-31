VERSION 5.00
Object = "{19DBFA01-8A29-11D3-82A4-0080AD509054}#1.0#0"; "VirtualControls.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3960
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5325
   LinkTopic       =   "Form1"
   ScaleHeight     =   3960
   ScaleWidth      =   5325
   StartUpPosition =   3  'Windows Default
   Begin VIRTUALCONTROLSLibCtl.VirtualList VirtualList1 
      Height          =   3675
      Left            =   120
      OleObjectBlob   =   "Form.frx":0000
      TabIndex        =   0
      Top             =   120
      Width           =   4935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    VirtualList1.ListCount = 100
End Sub

Private Function VirtualList1_GetItem(ByVal Index As Long) As String
    VirtualList1_GetItem = "Item #" & CStr(Index)
End Function

