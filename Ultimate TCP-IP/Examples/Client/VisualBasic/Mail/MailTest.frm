VERSION 5.00
Object = "{F7FA866F-089C-11D3-A469-0080C858F182}#1.4#0"; "UTMail.dll"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Dundas TCP/IP  utaxMail Client ActiveX Control 4.0 - Demo Program"
   ClientHeight    =   7200
   ClientLeft      =   1476
   ClientTop       =   1596
   ClientWidth     =   10296
   ClipControls    =   0   'False
   Icon            =   "MailTest.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7200
   ScaleWidth      =   10296
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdDeleteMsg 
      Caption         =   "Delete &Msg"
      Height          =   375
      Left            =   7920
      TabIndex        =   33
      ToolTipText     =   "Delete utaxMail Message"
      Top             =   2688
      Width           =   1095
   End
   Begin VB.CommandButton cmdResetDelete 
      Caption         =   "Reset Delete"
      Height          =   375
      Left            =   9120
      TabIndex        =   32
      ToolTipText     =   "Unmark All Messages Marked for Deletion"
      Top             =   2688
      Width           =   1095
   End
   Begin VB.CommandButton cmdDecode 
      Caption         =   "D&ecode"
      Height          =   375
      Left            =   6600
      TabIndex        =   31
      ToolTipText     =   "Decode message and attachments"
      Top             =   2688
      Width           =   1095
   End
   Begin VB.Frame frame1 
      Caption         =   "Frame1"
      Height          =   5052
      Left            =   5160
      TabIndex        =   30
      Top             =   120
      Width           =   12
   End
   Begin VB.TextBox txtMailHost 
      Height          =   285
      Left            =   1560
      TabIndex        =   0
      Top             =   132
      Width           =   2112
   End
   Begin VB.TextBox txtPopHost 
      Height          =   285
      Left            =   6840
      TabIndex        =   9
      Top             =   240
      Width           =   1935
   End
   Begin VB.TextBox txtUser 
      Height          =   285
      Left            =   6840
      TabIndex        =   10
      Top             =   732
      Width           =   1935
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   6840
      PasswordChar    =   "*"
      TabIndex        =   11
      Top             =   1200
      Width           =   1935
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   9000
      TabIndex        =   20
      ToolTipText     =   "Exit Demo Application"
      Top             =   1440
      Width           =   1095
   End
   Begin VB.CommandButton cmdSmtpConnect 
      Caption         =   "C&onnect"
      Height          =   375
      Left            =   3840
      TabIndex        =   6
      ToolTipText     =   "Connect to SMTP server to send utaxMail"
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton cmdSend 
      Caption         =   "Se&nd"
      Height          =   375
      Left            =   3840
      TabIndex        =   7
      ToolTipText     =   "Send email to specified email account"
      Top             =   600
      Width           =   1095
   End
   Begin VB.TextBox txtAttach 
      Height          =   320
      Left            =   1560
      TabIndex        =   4
      Top             =   1740
      Width           =   2112
   End
   Begin VB.TextBox txtSubject 
      Height          =   320
      Left            =   1560
      TabIndex        =   3
      Top             =   1327
      Width           =   2112
   End
   Begin VB.TextBox txtFrom 
      Height          =   320
      Left            =   1560
      TabIndex        =   2
      Top             =   960
      Width           =   2112
   End
   Begin VB.TextBox txtTo 
      Height          =   320
      Left            =   1560
      TabIndex        =   1
      Top             =   507
      Width           =   2112
   End
   Begin VB.TextBox txtMsgBody 
      Height          =   2952
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   5
      ToolTipText     =   "Enter Message Body Here"
      Top             =   2160
      Width           =   4692
   End
   Begin VB.CommandButton cmdSmtpClose 
      Caption         =   "&Disconnect"
      Height          =   375
      Left            =   3840
      TabIndex        =   8
      ToolTipText     =   "Connect to SMTP server to send utaxMail"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.CommandButton cmdPopDisconnect 
      Caption         =   "&Disconnect"
      Height          =   375
      Left            =   9000
      TabIndex        =   13
      ToolTipText     =   "Disconnect from POP3 Server"
      Top             =   720
      Width           =   1095
   End
   Begin VB.CommandButton cmdGetMsg 
      Caption         =   "&Get Msg"
      Height          =   375
      Left            =   5400
      TabIndex        =   16
      ToolTipText     =   "Get utaxMail Message"
      Top             =   2688
      Width           =   1095
   End
   Begin VB.TextBox txtCurMsg 
      Height          =   320
      Left            =   6840
      TabIndex        =   15
      Top             =   2160
      Width           =   1095
   End
   Begin VB.TextBox txtNumMsg 
      Height          =   320
      Left            =   6840
      Locked          =   -1  'True
      TabIndex        =   14
      Top             =   1680
      Width           =   1095
   End
   Begin VB.CommandButton cmdPopConnect 
      Caption         =   "&Connect"
      Height          =   375
      Left            =   9000
      TabIndex        =   12
      ToolTipText     =   "Connect to POP3 Server"
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox txtPopMsg 
      Height          =   1995
      Left            =   5400
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   17
      Top             =   3120
      Width           =   4875
   End
   Begin VB.TextBox txtResults 
      Height          =   1812
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   19
      Top             =   5280
      Width           =   10212
   End
   Begin UTMAILLibCtl.Mail utaxMail 
      Left            =   4800
      Top             =   2040
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   10
      BlockingMode    =   0   'False
      MailHostName    =   ""
      POP3HostName    =   ""
      UserName        =   ""
      Password        =   ""
   End
   Begin VB.Label lblMailHost 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "&Smtp Host name:"
      Height          =   192
      Left            =   240
      TabIndex        =   29
      ToolTipText     =   "Hostname of Smtp server"
      Top             =   180
      Width           =   1212
   End
   Begin VB.Label lblPopHost 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "POP&3 Host name:"
      Height          =   192
      Left            =   5400
      TabIndex        =   28
      ToolTipText     =   "Hostname of Pop3 server"
      Top             =   240
      Width           =   1272
   End
   Begin VB.Label lblUser 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "&User name:"
      Height          =   192
      Left            =   5856
      TabIndex        =   27
      ToolTipText     =   "Username of email account"
      Top             =   780
      Width           =   816
   End
   Begin VB.Label lblPassword 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "&Password:"
      Height          =   192
      Left            =   5940
      TabIndex        =   26
      ToolTipText     =   "Password of email account"
      Top             =   1200
      Width           =   732
   End
   Begin VB.Label lblAttach 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Atta&chments:"
      Height          =   192
      Left            =   516
      TabIndex        =   25
      ToolTipText     =   "Enter Pathname of Attachment to be Sent"
      Top             =   1800
      Width           =   936
   End
   Begin VB.Label lblSubject 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Sub&ject:"
      Height          =   192
      Left            =   864
      TabIndex        =   24
      Top             =   1380
      Width           =   588
   End
   Begin VB.Label lblFrom 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "&From:"
      Height          =   192
      Left            =   1056
      TabIndex        =   23
      ToolTipText     =   "Send utaxMail from this email account"
      Top             =   960
      Width           =   396
   End
   Begin VB.Label lblTo 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "&To:"
      Height          =   192
      Left            =   1212
      TabIndex        =   22
      ToolTipText     =   "Send utaxMail to this email account "
      Top             =   540
      Width           =   240
   End
   Begin VB.Label lblCurMsg 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Cu&rrent message:"
      Height          =   192
      Left            =   5436
      TabIndex        =   21
      ToolTipText     =   "Current message number "
      Top             =   2160
      Width           =   1236
   End
   Begin VB.Label lblNumMsg 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Available messages:"
      Height          =   192
      Left            =   5148
      TabIndex        =   18
      ToolTipText     =   "Number of messages"
      Top             =   1680
      Width           =   1524
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Dundas TCP/IP v4.0
' Copyright © Dundas Software 1995-1999, all rights reserved
' ===================================================================
'
Option Explicit

Private Sub cmdDecode_Click()
    
    Dim intNumAttach As Integer  'number of attachments
    On Error Resume Next
    ' Show the DecodedMessage form
    '   but first check to see if there are messages
           
    If txtCurMsg < 1 Or txtCurMsg = "" Then
        MsgBox "Error: There is no current message, " _
        & "can not decode!", vbOKOnly _
        , "Error: No Message to Retrieve"
        Exit Sub
    End If
            
    'so we know there is a valid message
    '   go ahead and decode it!!!
    frmDecoded.Show vbModal
    
End Sub

Private Sub cmdDeleteMsg_Click()
    ' Delete the selected message from the remote server
    
    Dim rt As Long  'return variable, indicates success/failure
    
    If txtNumMsg = "" Then Exit Sub
    'make sure there is at least one message
    If txtNumMsg = 0 Then
        MsgBox "Error: there are no messages to delete.", vbOKOnly, _
        "No Messages to Delete"
        Exit Sub
    End If
        
    txtResults = txtResults & vbCrLf & "Deleting message ..."
    rt = utaxMail.DeleteMsg(txtCurMsg)
    
    'if operation failed alert user
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
        Exit Sub
    End If
    
    'need to update txtcurMsg and txtNumMsg
    txtNumMsg = txtNumMsg - 1
    If txtCurMsg > 0 Then
        txtCurMsg = txtCurMsg - 1
    End If
    'set cursor to last text in txtResults
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdExit_Click()
'exit app
utaxMail.CancelMail
utaxMail.BlockingMode = True
utaxMail.POP3Close
utaxMail.SMTPClose
Unload Me
End Sub

Private Sub cmdGetMsg_Click()
    
    Dim rt As Long  'return var
    
    txtPopMsg = ""
    
    'trap for zerolength strings
    If txtCurMsg = "" Or txtNumMsg = "" Then Exit Sub
    ' set the location where the message will be saved
    '   first make sure that curmsg is not greater than total number of messages
    If txtCurMsg > txtNumMsg Then
        MsgBox "Error: Invalid current message number!", vbOKCancel, _
        "Invalid Current Message Specified"
        Exit Sub
    ElseIf txtCurMsg <= 0 Then
        MsgBox "Error: There are no current messages.", vbOKCancel, _
        "Invalid Current Message Specified"
        Exit Sub
    End If
        
    'set blockingmode to true so we can error trap SaveMsg call
    '  right after it is made
    
    txtResults = txtResults & vbCrLf & "Retrieving message ...  "

    utaxMail.BlockingMode = True
    rt = utaxMail.SaveMsg(txtCurMsg, "c:\temp\" & Trim(txtCurMsg) & ".txt")
    utaxMail.BlockingMode = False
    
    'error trap for success of SaveMsg call
    If rt <> ecSuccess Then
        'trap for non-existent c:\temp folder
        If rt = ecFileOpenError Then
            MsgBox "Error: you need to create a 'Temp' folder on drive" & _
            " 'c' in order to save messages to disk!", vbOKOnly, "Missing Temp Folder"
            txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
            txtResults.SelStart = 30000
        Else
            MsgBox utaxMail.GetErrorText(rt)
            txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
            txtResults.SelStart = 30000
        End If
        
    Else
        ' Open the message
        rt = utaxMail.OpenMsg(txtCurMsg)
        
        'if unsuccessful alert user
        If rt <> ecSuccess Then
            txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
        End If
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdSmtpClose_Click()
'disconnect from smtp server
    Dim rt As Long  'return variable
        
    rt = utaxMail.SMTPClose
       
    'check to see if we were successful
    If rt = 0 Then
        txtResults = txtResults & vbCrLf & "Disconnect Successful."
    Else
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
        
End Sub

Private Sub Form_Load()
utaxMail.AboutBox
frmDecoded.utaxMessage1.AboutBox

cmdGetMsg.Enabled = False
cmdDecode.Enabled = False
cmdDeleteMsg.Enabled = False
cmdResetDelete.Enabled = False

End Sub

Private Sub Form_Terminate()
utaxMail.BlockingMode = True
utaxMail.CancelMail

End Sub

'Private Sub Form_Resize()
''need resizing routine
'    On Error Resume Next
'
'    Dim lngFrmwidth As Long
'    Dim lngFrmHeight As Long
'
'    lngFrmwidth = Me.ScaleWidth
'    lngFrmHeight = Me.ScaleHeight
'
'    'adjust widths
'    fraServer.Width = lngFrmwidth - 140
'    txtResults.Width = lngFrmwidth - 140
'    fraPop3.Width = lngFrmwidth - fraSmtp.Width - 300
'    'adjust height of txtresults
'    txtResults.Height = lngFrmHeight - 5750
'
'    cmdExit.Left = lngFrmwidth - 1400
'    txtPopMsg.Width = lngFrmwidth - 5000
'
'    cmdResetDelete.Left = fraPop3.Width - 1270
'    cmdDeleteMsg.Left = cmdResetDelete.Left - 1200
'    cmdGetMsg.Left = cmdDeleteMsg.Left - 1200
'    cmdDecode.Left = fraPop3.Width - 1270
'    cmdPopDisconnect.Left = cmdDecode.Left - 1200
'    cmdPopConnect.Left = cmdPopDisconnect.Left - 1200
'
'    'do not let user undersize form
'    If Me.Width < 8000 Then Me.Width = 10000
'    If Me.Height < 10000 Then Me.Height = 8000
'
'End Sub

Private Sub Form_Unload(Cancel As Integer)
utaxMail.BlockingMode = True
utaxMail.CancelMail
    'release hidden form variable
    'Set frmMain = Nothing
    
End Sub

Private Sub utaxMail_OnDeleteMsg(ByVal Result As Long)
    ' Callback called when a response is received from the
    '   (remote) server indicating that a (remote) message was
    '   deleted.
    
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnGetMsgNumber(ByVal MsgNumber As Long, ByVal Result As Long)
    ' Callback called when a response is received from the
    '   (remote) server regarding a previous call to
    '   GetMsgNumber.
  
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    
    'if error set num. of msg's to 0, otherwise display number of messages on server
    If Result <> ecSuccess Then
        txtNumMsg.Text = 0
        txtCurMsg = 0
    Else
        ' MsgNumber is the number of messages waiting on the server
        txtNumMsg.Text = Str(MsgNumber)
        'test to see if there are messages
        If MsgNumber = 0 Then
            txtNumMsg = 0
            txtCurMsg = 0
        Else
            'there is at least one message
            txtNumMsg = MsgNumber
            txtCurMsg = 1   'set current message to first message
        End If
       
    End If
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnOpenMsg(ByVal Result As Long)
    ' Callback called when a reponse is received from the remote
    ' server after a call to retreive (or open) a message.
    
    Dim rt As Long  'return variable, indicates success/failure
    
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    
    'if successful read line
    If (Result = ecSuccess) Then
        rt = utaxMail.ReadMsgLine()
    End If
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnPOP3Close(ByVal Result As Long)
    cmdGetMsg.Enabled = False
        cmdDecode.Enabled = False
        cmdDeleteMsg.Enabled = False
        cmdResetDelete.Enabled = False
    
End Sub

Private Sub utaxMail_OnPOP3Connect(ByVal Result As Long)
    ' Callback called when the connection to the POP3 server is established
        
    Dim rt As Long  'return variable
        
     If Result <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
        cmdGetMsg.Enabled = False
        cmdDecode.Enabled = False
        cmdDeleteMsg.Enabled = False
        cmdResetDelete.Enabled = False
    Else
     ' Display error response (if any) and get the number of messages
    ' waiting on the server
    txtNumMsg.Text = ""
    rt = utaxMail.GetMsgNumber()
    
    'alert user if operation unsuccessful
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
        cmdGetMsg.Enabled = True
        cmdDecode.Enabled = True
        cmdDeleteMsg.Enabled = True
        cmdResetDelete.Enabled = True
    End If
        
  
        
End Sub

Private Sub utaxMail_OnReadMsgLine(ByVal Line As String, ByVal Result As Long)
    ' Callback called when a message line is read
    
    Dim rt As Long  'return variable, indicates success/failure
    
    'if unsuccessful end of msg reached
    If (Result <> ecSuccess) Then
    
        ' The end of the message has been reached. Close it
        rt = utaxMail.CloseMsg()
        
        'if close operation unsuccessful indicate to user the error
        If rt <> ecSuccess Then
            txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
        End If
    Else
    
        ' if no error occurrs, add the line to the txtPopMsg window and
        ' attempt to read another line (by calling Mail.ReadMsgLine())
        ' If a new line can be read, i.e. the e-mail message is in-
        ' complete, this callback will be called again and a new line
        ' will be added to the txtPopMsg window.
        
        txtPopMsg = txtPopMsg & Line
        rt = utaxMail.ReadMsgLine()
    End If
    'have cursor at end of text
    txtResults.SelStart = 30000
    txtPopMsg.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnResetDelete(ByVal Result As Long)
    
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnSendMailProgress(ByVal BytesSent As Long, ByVal BytesTotal As Long)
    ' callback called to indicate the progress of sending an e-mail message
    '   to the server. You may wish to implement a progress control here.
    
    txtResults = txtResults & "X"
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnSendMail(ByVal Result As Long)
    ' callback called when mail is sent
    
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxMail_OnSMTPConnect(ByVal Result As Long)
    ' callback called when a connection is established to the server
    
    txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(Result)
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdPopDisconnect_Click()
    'disconnect from POP3 Server
    Dim rt As Long  'return variable
    
    rt = utaxMail.POP3Close()
    'check to see if we were successful
    If rt = 0 Then
        txtResults = txtResults & vbCrLf & "Disconnect Successful."
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdPopConnect_Click()
    
    Dim rt As Long  'return variable
    
    'initialize textboxes
    txtNumMsg = ""
    txtCurMsg = ""
    
    utaxMail.UserName = txtUser
    utaxMail.UserPassword = txtPassword
    utaxMail.POP3HostName = txtPopHost
    
    txtResults = txtResults & vbCrLf & "Connecting to the POP3 server ..."
    
    ' Attempt a connection to the POP3 server
    rt = utaxMail.POP3Connect()
    
    'if connection unsuccessful alert user
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdResetDelete_Click()
    ' Reset delete will unmark all those messages that are flagged for
    '   deletion. Messages which are deleted from a server are not physically
    '   removed until the current session ends. Before a session ends, you
    '   can execute a ResetDelete operation to unmark those messages
    '   to be deleted at the end of the session.
    
    Dim rt As Long  'return var., indicates success/failure
    
    txtResults = txtResults & vbCrLf & "Reset deleting message ..."
    rt = utaxMail.ResetDelete()
    
    'if initially unsuccessful alert user
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdSend_Click()
    
    Dim rt As Long  'return variable
    
    'if nothing has been entered into the Smtp Hostname textbox then
    If txtMailHost = "" Or txtTo = "" Or txtFrom = "" Then
        MsgBox "Error: One or more fields not entered.", vbOKOnly, "Missing field(s)"
        Exit Sub
    End If
    
    txtResults = txtResults & vbCrLf & "Sending Mail ...  "
    
    ' Send the message
    rt = utaxMail.SendMail(txtTo, txtFrom, txtSubject, txtMsgBody, "", "", txtAttach)
    'if unsuccessful alert user
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Private Sub cmdSmtpConnect_Click()
    
    Dim rt As Long  'return var., indicates success/failure
    
    utaxMail.UserName = txtUser
    utaxMail.UserPassword = txtPassword
    utaxMail.MailHostName = txtMailHost

    ' Connect to the SMTP server
    txtResults = txtResults & vbCrLf & "Connecting to the Mail server ..."
    rt = utaxMail.SMTPConnect
    'if unsuccessful indicate to user error message
    If rt <> ecSuccess Then
        txtResults = txtResults & vbCrLf & utaxMail.GetErrorText(rt)
    End If
    
    'have cursor at end of text
    txtResults.SelStart = 30000
    
End Sub

Public Property Get CurMessage() As Long
'need to let decoding form know which message to retrieve
    CurMessage = Val(Trim(txtCurMsg))

End Property

