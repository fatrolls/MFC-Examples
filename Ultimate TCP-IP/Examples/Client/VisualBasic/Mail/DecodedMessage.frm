VERSION 5.00
Object = "{663A8A50-6792-11D3-A4E3-0080C858F182}#1.4#0"; "UTMsg.dll"
Begin VB.Form frmDecoded
   Caption         =   "Decoded Message"
   ClientHeight    =   7845
   ClientLeft      =   2310
   ClientTop       =   510
   ClientWidth     =   8385
   ClipControls    =   0   'False
   Icon            =   "DecodedMessage.frx":0000
   LinkTopic       =   "Form2"
   ScaleHeight     =   7845
   ScaleWidth      =   8385
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdClose
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Height          =   375
      Left            =   7140
      TabIndex        =   10
      Top             =   120
      Width           =   1095
   End
   Begin VB.ListBox lstAttach
      Height          =   840
      Left            =   1140
      TabIndex        =   9
      ToolTipText     =   "Double-clicking will decode the selected attachment and save it in the temp directory"
      Top             =   1320
      Width           =   5655
   End
   Begin VB.TextBox txtResults
      Height          =   1635
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   8
      Top             =   6120
      Width           =   8235
   End
   Begin VB.TextBox txtTo
      Height          =   320
      Left            =   1140
      TabIndex        =   3
      Top             =   57
      Width           =   5655
   End
   Begin VB.TextBox txtFrom
      Height          =   320
      Left            =   1140
      TabIndex        =   2
      Top             =   477
      Width           =   5655
   End
   Begin VB.TextBox txtSubject
      Height          =   320
      Left            =   1140
      TabIndex        =   1
      Top             =   897
      Width           =   5655
   End
   Begin VB.TextBox txtMsgBody
      Height          =   3495
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Top             =   2520
      Width           =   8235
   End
   Begin UTMSGLibCtl.Message utaxMessage1
      Left            =   7320
      Top             =   1080
   End
   Begin VB.Label lblTo
      AutoSize        =   -1  'True
      Caption         =   "&To:"
      Height          =   195
      Left            =   60
      TabIndex        =   7
      ToolTipText     =   "Message destination"
      Top             =   120
      Width           =   240
   End
   Begin VB.Label lblFrom
      AutoSize        =   -1  'True
      Caption         =   "&From:"
      Height          =   195
      Left            =   60
      TabIndex        =   6
      ToolTipText     =   "Message source"
      Top             =   540
      Width           =   390
   End
   Begin VB.Label lblSubject
      AutoSize        =   -1  'True
      Caption         =   "&Subject:"
      Height          =   195
      Left            =   60
      TabIndex        =   5
      ToolTipText     =   "Subject content"
      Top             =   960
      Width           =   585
   End
   Begin VB.Label lblAttach
      AutoSize        =   -1  'True
      Caption         =   "&Attachments:"
      Height          =   195
      Left            =   60
      TabIndex        =   4
      ToolTipText     =   "Double-click in Listbox to Decode Attachments"
      Top             =   1380
      Width           =   930
   End
End
Attribute VB_Name = "frmDecoded"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Dundas TCP/IP 4.0
' Copyright © Dundas Software 1995-2001, all rights reserved
' ===================================================================
'
'NOTE: notice the Dundas Message Control 4.0 on this form.  This control
'   allows you to code/decode/parse messages one at a time.

Option Explicit

Private Sub cmdClose_Click()
'unload form
    Unload Me
    
End Sub

Private Sub Form_Resize()
'need resizing routine
    Dim lngMeWidth As Long 'scalewidth of form
    
    On Error Resume Next
    
    lngMeWidth = Me.ScaleWidth
    
    cmdClose.Left = lngMeWidth - 1180
    
    txtTo.Width = lngMeWidth - 2550
    txtFrom.Width = lngMeWidth - 2550
    txtSubject.Width = lngMeWidth - 2550
    lstAttach.Width = lngMeWidth - 2550
    
    txtMsgBody.Width = lngMeWidth - 160
    txtResults.Width = lngMeWidth - 160
    
    txtResults.Height = Me.ScaleHeight - 6200
    
    'dont let user undersize form
    If Me.Height < 8000 Then Me.Height = 8000
    If Me.Width < 8000 Then Me.Width = 8000
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
        
    'release hidden form variable
    Set frmDecoded = Nothing
    
End Sub

Private Sub lstAttach_DblClick()

    Dim rt As Long  'return variable, indicates success/failure of operation
    
    ' Decode the attached file associated with the message
    txtResults = txtResults & vbCrLf & "Detaching file c:\temp\" & lstAttach.Text & " ..."
    
    rt = utaxMessage1.DecodeAttachment(lstAttach.ListIndex, "c:\temp\" & lstAttach.Text)
    txtResults = txtResults & vbCrLf & utaxMessage1.GetErrorText(rt)
    
End Sub

Private Sub Form_Load()
        
    Dim rt As Long  'return variable, indicates success/failure of operation
    Dim lngAttachNumber As Long  'stores the current attachment number
    Dim i As Long  'loop counter variable
    Dim strAttachName As String  'string var., stores attachment name
    
    
    On Error GoTo ERROMSG
    
    'clear attachment list of Message Control
   utaxMessage1.AboutBox
    
        
    utaxMessage1.EmptyAttachmentList
    
    'Load the selected message into the Message control so
    '  we can decode it, examine header values and decode attachments
    rt = utaxMessage1.Load("c:\temp\" & Trim(frmMain.CurMessage) & ".txt")
    
    'if not successful, indicate to user via txtResults textbox control
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMessage1.GetErrorText(rt)
        Exit Sub
    Else
    
        ' Get the different portions of the message
        '   including its body, header (to, from, subject), and
        '   the number of attachments
        'NOTICE how the Dundas Message Control 4.0 works with the Mail control
        '
        txtMsgBody = utaxMessage1.GetMessageBody
        txtTo = utaxMessage1.GetHeaderByType(ftTo)
        txtFrom = utaxMessage1.GetHeaderByType(ftFrom)
        txtSubject = utaxMessage1.GetHeaderByType(ftSubject)
        lngAttachNumber = utaxMessage1.GetAttachmentNumber
        lstAttach = " " & Str(lngAttachNumber) & ": "
        
        ' For each attachment, add the file name to
        '   the "lstAttach" window
        'NOTICE THE USE OF THE MESSAGE CONTROL
        For i = 1 To lngAttachNumber
            strAttachName = utaxMessage1.GetAttachmentName(i - 1)
            If (strAttachName = "") Then
                lstAttach.AddItem ("No name " & Str(i))  'if attachment has no name then
            Else                                            '  call it"No name (attachment#)"
                lstAttach.AddItem (strAttachName)
            End If
        Next
    End If
    Exit Sub
ERROMSG:
    MsgBox (Err.Description)
    
End Sub
