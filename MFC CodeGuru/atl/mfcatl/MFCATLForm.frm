VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   2544
   ClientLeft      =   48
   ClientTop       =   288
   ClientWidth     =   3744
   LinkTopic       =   "Form1"
   ScaleHeight     =   2544
   ScaleWidth      =   3744
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   492
      Left            =   600
      TabIndex        =   0
      Top             =   480
      Width           =   1572
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Dim oATL As Object
Dim oMFC As Object
Set oATL = CreateObject("MFCATLOCX.MyATLObject.1")
Set oATL = Nothing
Set oMFC = CreateObject("MFCATLOCX.MFCATLOCXCtrl.1")
Set oMFC = Nothing
End Sub
