VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmSmtp 
   Caption         =   "New Message"
   ClientHeight    =   5940
   ClientLeft      =   4224
   ClientTop       =   3684
   ClientWidth     =   8004
   ClipControls    =   0   'False
   Icon            =   "frmSmtp.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5940
   ScaleWidth      =   8004
   Begin VB.CommandButton cmdClose 
      Caption         =   "C&lose"
      Height          =   375
      Left            =   6840
      TabIndex        =   13
      ToolTipText     =   "Close Window, Return to Main Window"
      Top             =   5400
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog cdgSmtp 
      Left            =   1320
      Top             =   2040
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DialogTitle     =   "Open file Attachment"
      Flags           =   4096
   End
   Begin VB.TextBox txtFrom 
      Height          =   320
      Left            =   780
      TabIndex        =   1
      Top             =   60
      Width           =   3930
   End
   Begin VB.CommandButton cmdSendMail 
      Caption         =   "&Send"
      Default         =   -1  'True
      Height          =   375
      Left            =   5640
      TabIndex        =   12
      ToolTipText     =   "Send Message and Attachments"
      Top             =   5400
      Width           =   1095
   End
   Begin VB.Frame fraSmtp 
      Caption         =   "Bo&dy"
      ClipControls    =   0   'False
      Height          =   2655
      Left            =   60
      TabIndex        =   10
      Top             =   2580
      Width           =   7815
      Begin RichTextLib.RichTextBox rtfSmtp 
         Height          =   3435
         Left            =   135
         TabIndex        =   11
         ToolTipText     =   "Right-click to Bring Up Edit Menu"
         Top             =   270
         Width           =   8205
         _ExtentX        =   14478
         _ExtentY        =   6054
         _Version        =   393217
         ScrollBars      =   3
         TextRTF         =   $"frmSmtp.frx":0442
      End
   End
   Begin VB.TextBox txtSubject 
      Height          =   320
      Left            =   780
      TabIndex        =   9
      Top             =   1500
      Width           =   3930
   End
   Begin VB.TextBox txtBcc 
      Height          =   320
      Left            =   780
      TabIndex        =   7
      Top             =   1140
      Width           =   3930
   End
   Begin VB.TextBox txtCc 
      Height          =   320
      Left            =   780
      TabIndex        =   5
      Top             =   780
      Width           =   3930
   End
   Begin VB.TextBox txtTo 
      Height          =   320
      Left            =   780
      TabIndex        =   3
      Top             =   420
      Width           =   3930
   End
   Begin VB.ListBox lstAttach 
      Height          =   1575
      IntegralHeight  =   0   'False
      Left            =   4920
      TabIndex        =   15
      ToolTipText     =   "Click Here to Add an Attachment"
      Top             =   240
      Width           =   2805
   End
   Begin VB.Label lblFrom 
      AutoSize        =   -1  'True
      Caption         =   "&From:"
      Height          =   195
      Left            =   60
      TabIndex        =   0
      ToolTipText     =   "Enter a Valid E-mail Address for Sender"
      Top             =   120
      Width           =   390
   End
   Begin VB.Label lblAttach 
      AutoSize        =   -1  'True
      Caption         =   "&Attachments:"
      Height          =   195
      Left            =   4920
      TabIndex        =   14
      Top             =   0
      Width           =   930
   End
   Begin VB.Label lblSubject 
      AutoSize        =   -1  'True
      Caption         =   "Su&bject:"
      Height          =   195
      Left            =   60
      TabIndex        =   8
      ToolTipText     =   "Enter a Subject"
      Top             =   1560
      Width           =   585
   End
   Begin VB.Label lblBcc 
      AutoSize        =   -1  'True
      Caption         =   "&Bcc:"
      Height          =   195
      Left            =   0
      TabIndex        =   6
      ToolTipText     =   "Enter Bcc Value"
      Top             =   1200
      Width           =   330
   End
   Begin VB.Label lblCc 
      AutoSize        =   -1  'True
      Caption         =   "&Cc:"
      Height          =   195
      Left            =   60
      TabIndex        =   4
      ToolTipText     =   "Enter Cc Value"
      Top             =   840
      Width           =   240
   End
   Begin VB.Label lblTo 
      AutoSize        =   -1  'True
      Caption         =   "&To:"
      Height          =   195
      Left            =   60
      TabIndex        =   2
      ToolTipText     =   "Enter a Valid E-mail Address for Receiver"
      Top             =   480
      Width           =   240
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileSendMessage 
         Caption         =   "&Send Message"
      End
      Begin VB.Menu mnuFileSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileCancel 
         Caption         =   "C&ancel Send"
      End
      Begin VB.Menu mnuFileSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileAttachment 
         Caption         =   "&Attach File ..."
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEditCut 
         Caption         =   "Cu&t"
         Shortcut        =   ^X
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "&Copy"
         Shortcut        =   ^C
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "&Paste"
         Shortcut        =   ^V
      End
   End
   Begin VB.Menu mnuformat 
      Caption         =   "&Format"
      Begin VB.Menu mnuFormatBold 
         Caption         =   "&Bold"
      End
      Begin VB.Menu mnuFormatItalic 
         Caption         =   "&Italic"
      End
      Begin VB.Menu mnuFormatUnderline 
         Caption         =   "&Underline"
      End
   End
End
Attribute VB_Name = "frmSmtp"
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
Public strSmtpName As String  'public var. to hold smtp server name, may be updated by frmServerInfo
Dim strUserName As String  'stores logon of user
Dim strUserPassword As String  'stores password from registry call
Dim strAttach As String  'comma-separated list of file attachments
Dim intNumAttach As Integer 'number of attachments to send
Dim blnConnected As Boolean  'indicates if we are connected
Dim myMail As Mail  'holds reference to Mail control

Private Sub cmdClose_Click()
    
    Unload Me
    
End Sub

Private Sub cmdSendMail_Click()

    Dim RegistryReturn As Variant 'holds value of GetAllSettings registry call
    Dim rt As Long 'return variable
    
    If cmdSendMail.Caption = "Cancel" Then 'cancel operation if we are sending mail
        'we are in asynchronous mode so we can cancel operation
        myMail.CancelMail
        'user cancelled operation, so unload the form
        Unload frmProgress
        Exit Sub
        
    End If
        
    '   get registry values, if not there or not valid then
    '       unload form, prompt user to re-enter from Pop3 form
    RegistryReturn = GetAllSettings("DundasMailDemo", "ServerInfo")
    'we need smtp server name, username and password
    If IsEmpty(RegistryReturn) Then
        MsgBox "Error: Please re-enter Server Info details from" _
        & vbCrLf & "the main form. Closing window.", vbOKOnly, "Error: Login Information" _
        & " not Entered"
        Exit Sub
    Else
        strSmtpName = RegistryReturn(0, 1)
        strUserName = RegistryReturn(2, 1)
        strUserPassword = RegistryReturn(3, 1)
    End If
            
    'first open smtp connection
    rt = OpenServer
    If rt <> ecSuccess Then Exit Sub
        
    'change caption of button to indicate user can cancel
        ' operation with the same command button
    cmdSendMail.Caption = "Cancel"
    cmdSendMail.ToolTipText = "Cancel Asynchronous Send Operation"
    rt = myMail.SendMail(txtTo, txtFrom, txtSubject, rtfSmtp.Text, txtCc, txtBcc, strAttach)
    If rt <> ecSuccess Then
        MsgBox myMail.GetErrorText(rt)
    End If
        
End Sub

Private Sub Form_Load()
    
    Set myMail = frmMain.maiPop3  'get reference to Mail Control
    
    'check frmMain boolean to see if we should display form in
    '   reply mode or new mail mode
    If frmMain.Reply = True Then
        Call PopulateHeaders
    Else
        cmdSendMail.Enabled = False
    End If
          
     'use asynchronous mode
     myMail.BlockingMode = False
    
End Sub

Private Sub Form_Resize()
'write resizing routine
    On Error Resume Next
    
    'first, align leftmost controls
    lblFrom.Left = 100
    lblTo.Left = 100
    lblCc.Left = 100
    lblBcc.Left = 100
    lblSubject.Left = 100
    fraSmtp.Left = 100
    
    'next,adjust attachment listbox
    lstAttach.Top = 248
    lstAttach.Width = Me.ScaleWidth - 5000
    
    'next, adjust height of frame
    fraSmtp.Top = 1900
    fraSmtp.Height = Me.ScaleHeight - 2500
    
    'adjust pos of command buttons
    cmdSendMail.Top = Me.ScaleHeight - 450
    cmdClose.Top = cmdSendMail.Top
    cmdClose.Left = Me.ScaleWidth - 1170
    cmdSendMail.Left = cmdClose.Left - 1170
    
    'adjust frame
    fraSmtp.Width = Me.ScaleWidth - 185
    rtfSmtp.Top = 210
    rtfSmtp.Left = 100
    rtfSmtp.Width = fraSmtp.Width - 200
    rtfSmtp.Height = fraSmtp.Height - 300
    
    
    If Me.Height < 6300 Then Me.Height = 6300
    If Me.Width < 8100 Then Me.Width = 8100
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    On Error Resume Next
    
    'close connection, make sure it closes, also reset blockingmode to true
    myMail.BlockingMode = True
    myMail.SMTPClose
    
    'release hidden form var
    Set myMail = Nothing
    Set frmSmtp = Nothing
    
End Sub

Public Sub PopulateHeaders()
    
    'we are replying to a message so populate textboxes
    txtTo = Trim(frmMain.ServerInfo(1))
    txtCc = Trim(frmMain.ServerInfo(2))
    txtBcc = Trim(frmMain.ServerInfo(3))
    txtSubject = Trim(frmMain.ServerInfo(4))
    rtfSmtp = Trim(frmMain.ServerInfo(5))
    txtFrom = Trim(frmMain.ServerInfo(6))
    
End Sub

Private Function OpenServer() As Long
'returns the return of the Open procedure
    Dim rt As Long  'return variable
       
    'if connected, exit sub
    If blnConnected = True Then OpenServer = ecSuccess
       
    'note that the Property "MailHostname" specifies the smtp server
    'initialize mail properties
    myMail.MailHostName = strSmtpName
    myMail.UserName = strUserName
    myMail.UserPassword = strUserPassword
        
    rt = myMail.SMTPConnect
    If rt <> ecSuccess Then
        MsgBox myMail.GetErrorText(rt)
        OpenServer = ecError
        Exit Function
    End If
        
    'success
    blnConnected = True
    OpenServer = ecSuccess
    
End Function

Private Sub lstAttach_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    'add an attachment
    Call mnuFileAttachment_Click
    
End Sub

Private Sub mnuEditCopy_Click()
    Clipboard.Clear
    Clipboard.SetText rtfSmtp.SelRTF

End Sub

Private Sub mnuEditCut_Click()
    
    Clipboard.Clear
    Clipboard.SetText rtfSmtp.SelRTF
    rtfSmtp.SelText = ""
    
End Sub

Private Sub mnuEditPaste_Click()
    
    rtfSmtp.SelRTF = Clipboard.GetText
    
End Sub

Private Sub mnuFileAttachment_Click()
    
    On Error GoTo CancelError 'trap for cancel
    
    cdgSmtp.Filter = "All files (*.*)|*.*"
    'call open common dialog
    cdgSmtp.ShowOpen
    'assign filename to strAttach,need to separate with ","
    If intNumAttach <> 0 Then strAttach = strAttach & ","
    strAttach = strAttach & cdgSmtp.FileName
    lstAttach.AddItem strAttach
    intNumAttach = intNumAttach + 1
    
    Exit Sub
    
CancelError:
    strAttach = ""
        
End Sub

Private Sub mnuFileCancel_Click()
    'only cancel operation if an operation is in progress
    If cmdSendMail.Caption <> "Cancel" Then
        Exit Sub
    Else
        myMail.BlockingMode = True
        myMail.CancelMail
        Unload Me
    End If
    
End Sub

Private Sub mnuFileSendMessage_Click()
    
    cmdSendMail.Value = True
    
End Sub

Private Sub mnuFormatBold_Click()
'toggle bold for selected text on and off
If rtfSmtp.SelBold Then
    rtfSmtp.SelBold = False
Else
'turn bold on
    rtfSmtp.SelBold = True
End If

End Sub

Private Sub mnuFormatItalic_Click()
'toggle italics on/off
If rtfSmtp.SelItalic Then
    rtfSmtp.SelItalic = False
Else
    rtfSmtp.SelItalic = True
End If

End Sub

Private Sub mnuFormatUnderline_Click()
'toggle underline on/off
If rtfSmtp.SelUnderline Then
    rtfSmtp.SelUnderline = False
Else
    rtfSmtp.SelUnderline = True
End If

End Sub

Private Sub rtfSmtp_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    If Button = 2 Then
        PopupMenu mnuEdit, vbPopupMenuCenterAlign
    End If
    
End Sub

Private Sub txtFrom_Change()
    
    'enable command button if something in txtFrom and txtTo
    If txtTo <> "" And txtFrom <> "" Then cmdSendMail.Enabled = True
    
End Sub

Private Sub txtTo_Change()
    
    'enable command button if something in txtFrom and txtTo
    If txtTo <> "" And txtFrom <> "" Then cmdSendMail.Enabled = True
    
End Sub
