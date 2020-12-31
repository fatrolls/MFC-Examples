VERSION 5.00
Object = "{D4A19873-EBE6-11D2-A440-0080C858F182}#1.4#0"; "UTFinger.dll"
Begin VB.Form frmMain 
   Caption         =   "Dundas TCP/IP  Finger Client Control 4.0 - Demo Program"
   ClientHeight    =   5400
   ClientLeft      =   1896
   ClientTop       =   1776
   ClientWidth     =   8784
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   5400
   ScaleWidth      =   8784
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   7560
      TabIndex        =   7
      ToolTipText     =   "Exit the Demo Application"
      Top             =   945
      Width           =   1095
   End
   Begin VB.TextBox txtStatus 
      Height          =   320
      Left            =   840
      Locked          =   -1  'True
      TabIndex        =   3
      ToolTipText     =   "Status information is displayed here"
      Top             =   870
      Width           =   5400
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Enabled         =   0   'False
      Height          =   375
      Left            =   7560
      TabIndex        =   2
      ToolTipText     =   "Cancel the finger operation"
      Top             =   525
      Width           =   1095
   End
   Begin VB.CommandButton cmdFinger 
      Caption         =   "&Finger"
      Default         =   -1  'True
      Height          =   375
      Left            =   7560
      TabIndex        =   1
      ToolTipText     =   "Finger the specified address"
      Top             =   105
      Width           =   1095
   End
   Begin VB.TextBox txtResults 
      Height          =   3810
      Left            =   105
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   4
      Top             =   1485
      Width           =   8535
   End
   Begin VB.TextBox txtAddress 
      Height          =   320
      Left            =   840
      TabIndex        =   0
      Text            =   "help@berkeley.edu"
      Top             =   105
      Width           =   5400
   End
   Begin UTFINGERLibCtl.Finger utaxFingerControl 
      Left            =   6480
      Top             =   720
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   5
      BlockingMode    =   0   'False
   End
   Begin VB.Label lblInstruct 
      AutoSize        =   -1  'True
      Caption         =   "e.g. [textfile]@fingerserver "
      Height          =   195
      Left            =   840
      TabIndex        =   8
      Top             =   480
      Width           =   1890
   End
   Begin VB.Label lblStatus 
      Caption         =   "&Status:"
      Height          =   255
      Left            =   105
      TabIndex        =   6
      ToolTipText     =   "Displays Status of Finger Operation"
      Top             =   900
      Width           =   555
   End
   Begin VB.Label lblAddress 
      Caption         =   "&Address:"
      Height          =   255
      Left            =   105
      TabIndex        =   5
      ToolTipText     =   "Address to Finger [textfile]@fingerserver"
      Top             =   138
      Width           =   660
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
Option Compare Text  'used when converting vbLf to vbCrLf

Private Sub cmdCancel_Click()
    ' Cancel the previous finger operation
    txtStatus = ""
    utaxFingerControl.CancelFinger
    cmdFinger.Enabled = True
    cmdCancel.Enabled = False
        
End Sub

Private Sub cmdCancel_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)

    cmdCancel.MousePointer = vbArrow

End Sub

Private Sub cmdExit_Click()

    'exit demo application
    Unload Me
    
End Sub

Private Sub cmdFinger_Click()
    
    Dim Result As Long  'returned value from finger operation
    
    txtResults = ""
    cmdFinger.Enabled = False
    cmdCancel.Enabled = True
    
    ' Finger the specified host
    Result = utaxFingerControl.Finger(txtAddress)
    
    ' Check for an error
    If (Result = FingerErrorCodes.ecSuccess) Then
        txtStatus = "Waiting for response event ..."
    Else
        txtStatus = utaxFingerControl.GetErrorText(Result)
    End If
    
    Me.MousePointer = vbHourglass
    
End Sub
' // Disable the button if the text is empty
Private Sub txtAddress_Change()
If txtAddress.Text = "" Then
    cmdFinger.Enabled = False
Else
cmdFinger.Enabled = True
End If


End Sub

Private Sub utaxFingerControl_OnFinger(ByVal Result As Long)
    ' This callback is called when the finger lookup
    '   is complete.
       
    Dim lngLineCount As Long  'number of returned lines
    Dim strLine As String  'returned string value of GetReturnLine()
    Dim i As Long, j As Long 'counter variables
    Dim strTemp As String  'temp string variable
    Dim intSame As Integer  'return from StrCmp()
    
    ' Output the list of return lines to the txtResults
    ' field edit window
    If (Result = FingerErrorCodes.ecSuccess) Then
        lngLineCount = utaxFingerControl.NumberReturnLines
    
        'retrieve text line by line
        For i = 0 To (lngLineCount - 1)
            txtResults = txtResults & utaxFingerControl.GetReturnLine(i) & vbCrLf
        Next i
    ElseIf Result <> ecSuccess Then
        ' Get the error message from the lookup
        txtResults = utaxFingerControl.GetErrorText(Result)
    End If
    
    cmdFinger.Enabled = True
    cmdCancel.Enabled = False
    txtStatus = utaxFingerControl.GetErrorText(Result)
    
    Me.MousePointer = vbNormal
    
End Sub



Private Sub Form_Load()
    utaxFingerControl.AboutBox
    cmdCancel.Enabled = False
    
End Sub

Private Sub Form_Resize()
    'resize controls when form is resized
    On Error Resume Next
    
    'first make sure all controls are 80 twips from leftmost edge of form
    lblAddress.Left = 80
    lblStatus.Left = 80
    txtResults.Left = 80
    
    'always have command buttons aligned to right of form, 80 twips away from
    '   rightmost edge
    cmdFinger.Left = Me.ScaleWidth - 80 - cmdFinger.Width
    cmdCancel.Left = Me.ScaleWidth - 80 - cmdCancel.Width
    cmdExit.Left = Me.ScaleWidth - 80 - cmdExit.Width
    
    'next, adjust height of txtResults to use all available space,
    '   keeping 80 twips away from bottom of form
    txtResults.Height = Me.ScaleHeight - txtResults.Top - 80
    
    'adjust width of txtResults to always be 80 twips from rightmost edge of form
    txtResults.Width = Me.ScaleWidth - 160
    
    'do not allow user to undersize the form
    If Me.Height < 4000 Then Me.Height = 4000
    If Me.Width < 8000 Then Me.Width = 8000
    
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'set hidden form var to nothing
    Set frmMain = Nothing
    
End Sub
