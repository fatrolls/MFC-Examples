VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{F7FA866F-089C-11D3-A469-0080C858F182}#1.4#0"; "UTMail.dll"
Object = "{663A8A50-6792-11D3-A4E3-0080C858F182}#1.4#0"; "UTMsg.dll"
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   Caption         =   "Dundas TCP/IP 4.0 - Email Demo Application"
   ClientHeight    =   7968
   ClientLeft      =   216
   ClientTop       =   1008
   ClientWidth     =   11736
   ClipControls    =   0   'False
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7968
   ScaleWidth      =   11736
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Height          =   375
      Left            =   6900
      TabIndex        =   10
      ToolTipText     =   "Connect to Pop3 Server"
      Top             =   7140
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog cdgPop3 
      Left            =   10740
      Top             =   540
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
   End
   Begin VB.CommandButton cmdReply 
      Caption         =   "&Reply "
      Height          =   375
      Left            =   8145
      TabIndex        =   9
      Top             =   7155
      Width           =   1095
   End
   Begin VB.CommandButton cmdNewMail 
      Caption         =   "&New Mail "
      Height          =   375
      Left            =   9360
      TabIndex        =   7
      Top             =   7155
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   10575
      TabIndex        =   5
      Top             =   7155
      Width           =   1095
   End
   Begin VB.Frame fraPop3 
      Caption         =   "Body"
      ClipControls    =   0   'False
      Height          =   3030
      Left            =   0
      TabIndex        =   4
      Top             =   3840
      Width           =   11625
      Begin RichTextLib.RichTextBox rtfPop3 
         Height          =   2670
         Left            =   60
         TabIndex        =   6
         Top             =   120
         Width           =   11355
         _ExtentX        =   20024
         _ExtentY        =   4720
         _Version        =   393217
         BackColor       =   16777215
         BorderStyle     =   0
         ScrollBars      =   3
         OLEDragMode     =   0
         OLEDropMode     =   0
         TextRTF         =   $"frmMain.frx":0442
         MouseIcon       =   "frmMain.frx":0518
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   9.6
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
   End
   Begin VB.ListBox lstPop3 
      Height          =   3015
      IntegralHeight  =   0   'False
      ItemData        =   "frmMain.frx":0534
      Left            =   7740
      List            =   "frmMain.frx":0536
      TabIndex        =   3
      ToolTipText     =   "Double-Click on Attachment to Save to Disk"
      Top             =   660
      Width           =   3000
   End
   Begin MSFlexGridLib.MSFlexGrid msgPop3 
      Height          =   3300
      Left            =   120
      TabIndex        =   2
      Top             =   420
      Width           =   7530
      _ExtentX        =   13293
      _ExtentY        =   5821
      _Version        =   393216
      Rows            =   1
      Cols            =   5
      FixedCols       =   0
      BackColorFixed  =   -2147483644
      BackColorBkg    =   -2147483643
      AllowBigSelection=   0   'False
      FocusRect       =   0
      GridLines       =   0
      SelectionMode   =   1
      AllowUserResizing=   1
      FormatString    =   $"frmMain.frx":0538
   End
   Begin MSComctlLib.ImageList imgPop3 
      Left            =   10920
      Top             =   1980
      _ExtentX        =   995
      _ExtentY        =   995
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   12
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0616
            Key             =   "Save"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0A6A
            Key             =   "Retrieve"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0EBE
            Key             =   "Reply"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1312
            Key             =   "New"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1766
            Key             =   "Cut"
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1CAA
            Key             =   "Copy"
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":21EE
            Key             =   "Paste"
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2732
            Key             =   "Bold"
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2846
            Key             =   "Italic"
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":295A
            Key             =   "Underline"
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2A6E
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":2FB2
            Key             =   "Tops"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.StatusBar staPop3 
      Align           =   2  'Align Bottom
      Height          =   372
      Left            =   0
      TabIndex        =   1
      Top             =   7596
      Width           =   11736
      _ExtentX        =   20701
      _ExtentY        =   656
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   20362
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar tlbPop3 
      Align           =   1  'Align Top
      Height          =   336
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   11736
      _ExtentX        =   20701
      _ExtentY        =   593
      ButtonWidth     =   487
      ButtonHeight    =   466
      AllowCustomize  =   0   'False
      Wrappable       =   0   'False
      Appearance      =   1
      ImageList       =   "imgPop3"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   17
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Retrieve"
            Object.ToolTipText     =   "Retrieve Messages"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Tops"
            Object.ToolTipText     =   "Retrieve Message Tops"
            ImageIndex      =   12
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Reply"
            Object.ToolTipText     =   "Reply to a Message"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "Send New message"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "Save File Attachment"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "Cut Text from Body of Message"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "Copy Text from Body of Message"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "Paste Text into Message Body"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Bold"
            Object.ToolTipText     =   "Toggle Bolding of Selected Text"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Italic"
            Object.ToolTipText     =   "Toggle Italicizing of Selected Text"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Underline"
            Object.ToolTipText     =   "Toggle Underlining of Selected Text"
            ImageIndex      =   10
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "Print Headers and Body of Current Message"
            ImageIndex      =   11
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin UTMSGLibCtl.Message mesMessage 
      Left            =   1320
      Top             =   6840
   End
   Begin UTMAILLibCtl.Mail maiPop3 
      Left            =   3240
      Top             =   6960
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   10
      BlockingMode    =   0   'False
      MailHostName    =   ""
      POP3HostName    =   ""
      UserName        =   ""
      Password        =   ""
   End
   Begin VB.Label lblAttach 
      AutoSize        =   -1  'True
      Caption         =   "Attachments:"
      Height          =   195
      Left            =   7740
      TabIndex        =   8
      Top             =   420
      Width           =   930
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileSendMessage 
         Caption         =   "Re&ply ..."
      End
      Begin VB.Menu mnuFileSendNew 
         Caption         =   "Send New Mail ..."
      End
      Begin VB.Menu mnuFileSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileServer 
         Caption         =   "Ser&ver Info ..."
      End
      Begin VB.Menu mnuFileSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSaveAttach 
         Caption         =   "&Save Attachment ..."
      End
      Begin VB.Menu mnuFileSep3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuMessages 
      Caption         =   "&Messages"
      Begin VB.Menu mnuMessagesRetrieve 
         Caption         =   "&Retrieve Messages"
      End
      Begin VB.Menu mnuMessagesSep1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuMessagesTops 
         Caption         =   "Retrieve Message &Tops"
      End
      Begin VB.Menu mnuMessagesSep5 
         Caption         =   "-"
      End
      Begin VB.Menu mnuMessagesDeleteServer 
         Caption         =   "Delete Messages at &Server "
      End
      Begin VB.Menu mnuMessagesUndo 
         Caption         =   "&Undo Server Message Deletion"
      End
      Begin VB.Menu mnuMessagesSep2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuMessagesDelete 
         Caption         =   "&Delete All InBox Messages"
      End
      Begin VB.Menu mnuMessagesDeleteRead 
         Caption         =   "Delete Read &Inbox Messages"
      End
      Begin VB.Menu mnuMessagesDeleteSelected 
         Caption         =   "Delete Selected Message"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit "
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
   Begin VB.Menu mnuOptions 
      Caption         =   "&Options"
      Begin VB.Menu mnuOptionsReceive 
         Caption         =   "&Receive Timeout ..."
      End
      Begin VB.Menu mnuOptionsConnect 
         Caption         =   "&Connect Timeout ..."
      End
   End
   Begin VB.Menu mnuFileHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpContents 
         Caption         =   "&Contents"
      End
      Begin VB.Menu mnuHelpIndex 
         Caption         =   "&Index"
      End
      Begin VB.Menu mnuHelpSearch 
         Caption         =   "&Search"
      End
      Begin VB.Menu mnuSepBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About"
      End
      Begin VB.Menu mnMailCtrl 
         Caption         =   "About Dundas Mail Control"
      End
      Begin VB.Menu mnAbtMsgCtrl 
         Caption         =   "About Dundas Message Contol"
      End
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
Option Base 1

'module level variables to store pop3 server account information
Public strPop3Name As String
Public strUserName As String    'these var's are public so that they are available to frmServer
Public strUserPassword As String
Dim myMail As Mail  'obj variable to hold reference to dundas Mail client
Dim inttotalnummsg As Integer 'number of messages
Dim intNumAttach As Integer  'number of attachments per message
Dim lngMsgSize As Long  'size of current msg
Dim intCurMsg As Integer 'current msg
Dim strTo As String  'current To: msg field
Dim strFrom As String
Dim strCc As String  'string for Cc field
Dim strSubject As String
Dim strBcc As String
Dim blnReply As Boolean  'use with public property get to configure SendMail form
Dim blnConnected As Boolean  'lets us know if we are connected to pop3 server
Dim blnNotFirstTime  As Boolean  'bln to indicate first message being downloaded
Dim intNextAvailMsgNum As Integer  'indictaes next available msgnumber
Dim intNumRetrievedMsgs As Integer  'number of retrieved msgs
Dim strFileClickedOn As String  'saves which entry (or file) user clicked on in MSFlexgrid
Dim myMessage As Message  'user defined message control variable
Dim strHelpFilePath As String  'stores path to helpfile, if any
Public blnGetNextTop As Boolean  'public so var. can be accessed by frmTop
                                    '   determines whether we should get next line in message top

Private Const HH_DISPLAY_TOC = &H1  'these constants are used when the HtmlHelp api functions
Private Const HH_DISPLAY_INDEX = &H2    '    are called
Private Const HH_DISPLAY_SEARCH = &H3

' UDT for accessing the Search tab
Private Type tagHH_FTS_QUERY
  cbStruct          As Long
  fUniCodeStrings   As Long
  pszSearchQuery    As String
  iProximity        As Long
  fStemmedSearch    As Long
  fTitleOnly        As Long
  fExecute          As Long
  pszWindow         As String
End Type

Private Declare Function HTMLHelp Lib "hhctrl.ocx" _
    Alias "HtmlHelpA" (ByVal hwnd As Long, _
    ByVal lpHelpFile As String, _
    ByVal wCommand As Long, _
    ByVal dwData As Long) As Long

Private Declare Function HTMLHelpCallSearch Lib "hhctrl.ocx" _
    Alias "HtmlHelpA" (ByVal hwnd As Long, _
    ByVal lpHelpFile As String, _
    ByVal wCommand As Long, _
    ByRef dwData As tagHH_FTS_QUERY) As Long

Private Sub cmdConnect_Click()
    'connect to server
    Call Connect
        
End Sub

Private Sub cmdExit_Click()

    'exit app
    Unload Me

End Sub

Private Sub cmdNewMail_Click()
    Dim rt As Long 'return variable
    'load and show the SendMail form
    'first indicate form is to be shown in Send new mail mode
    blnReply = False
    frmSmtp.Show vbModeless, Me
        
End Sub

Private Sub cmdReply_Click()
    'reply to current mail message
    'first set private bln var for property procedure for frmSmtp
    Dim rt As Long  'return var
    
    'if total number of messages is 0 set strFrom, strTo to zerolength string
    If inttotalnummsg = 0 Or msgPop3.Rows = 1 Then
        strTo = ""
        strFrom = ""
        strCc = ""
        strBcc = ""
        strSubject = ""
    End If
    
    'only use readonly ServerInfo property with frmSmtp
    '   if there is at least one entry in flexgrid
    blnReply = False
    If msgPop3.Rows > 1 Then blnReply = True
    
    frmSmtp.Show vbModeless, Me
    'reset boolean
    blnReply = False
        
End Sub

Private Sub Form_Load()
    maiPop3.AboutBox
    mesMessage.AboutBox
    On Error Resume Next
              
    staPop3.Panels(1) = "Idle ..."
    
    Call GetAccountInfo  'prompt user for account details
           
    ' check to see if InBox folder is made, if not create it
    Call MakeInBox
           
    Set myMail = maiPop3  'set object variable to instance of Mail Client control
    Set myMessage = mesMessage 'set obj variable to instance of Message control
    
    'now grab saved messages in InBox folder and populate the flexgrid control
    Call InitializeFlexgrid
    
    'use function in .bas to determine location of helpfile, if not found then
    '   de-activate Help menu items
    'find help file if it exists on users system
    strHelpFilePath = FindPath("HKEY_LOCAL_MACHINE", "SOFTWARE\Dundas\Ultimate TCPIP 3.0 Control Reference\Documentation", "Path")
    'if not found zero-length string is returned, disable help buttons
    If strHelpFilePath = "" Then
        mnuHelpSearch.Enabled = False
        mnuHelpIndex.Enabled = False
        mnuHelpContents.Enabled = False
    End If
                           
End Sub

Private Sub Form_Resize()
       
    Dim i As Long  'counter var
    Dim lngColumns As Long  'hold widths of all columns except subject column
    
    On Error Resume Next
    'align leftmost controls
      
    'fraPop3.Top = fraPop3.Top - 100
    fraPop3.Left = 100
    msgPop3.Left = 100
       
    'align listbox, and widths
    lstPop3.Width = 2300
    lstPop3.Left = Me.ScaleWidth - 2400
    
    'adjust widths
    msgPop3.Width = Me.ScaleWidth - 2550
    fraPop3.Width = Me.ScaleWidth - 200
    
    'adjust tops
    msgPop3.Top = 440
    lblAttach.Top = 440
    lblAttach.Left = lstPop3.Left
    lstPop3.Top = lblAttach.Top + 270
    lstPop3.Left = lblAttach.Left
       
    'adjust frame
    'fraPop3.Top = Me.ScaleHeight - msgPop3.Height - 200
    fraPop3.Height = Me.ScaleHeight - msgPop3.Height - cmdExit.Height - staPop3.Height - 800
        
    'adjust command buttons
    cmdExit.Left = Me.ScaleWidth - cmdExit.Width - 80
    cmdNewMail.Left = cmdExit.Left - 1150
    cmdReply.Left = cmdNewMail.Left - 1150
    cmdConnect.Left = cmdReply.Left - 1150
    cmdExit.Top = fraPop3.Top + fraPop3.Height + 100
    cmdNewMail.Top = cmdExit.Top
    cmdReply.Top = cmdExit.Top
    cmdConnect.Top = cmdExit.Top
        
    'adjust rtf
    rtfPop3.Width = fraPop3.Width - 250
    rtfPop3.Height = fraPop3.Height - 350
    rtfPop3.Left = 130
    rtfPop3.Top = 230
    
    'don't let user undersize form
    If Me.Width < 10000 Then Me.Width = 10000
    If Me.Height < 8000 Then Me.Height = 8000
        
    'refresh rich text control
    rtfPop3.Refresh
    tlbPop3.Refresh
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'release obj references
    On Error Resume Next
    
    'if we are still connected close connection
    myMail.POP3Close
    
    Set myMail = Nothing
    Set myMessage = Nothing
    Set frmMain = Nothing
    
       
End Sub

Private Sub lstPop3_DblClick()
   'if user double-clicks on file attachment in listbox call SaveAttachment dialog
   Call mnuFileSaveAttach_Click
        
End Sub

Private Sub maiPop3_OnDeleteMsg(ByVal Result As Long)
    'test to see if message was successfully deleted
    If Result <> ecSuccess Then
        MsgBox myMail.GetErrorText(Result), vbOKOnly, "Error: Could Not Delete Message"
        staPop3.Panels(1).Text = "Delete Message Failure."
    Else
        staPop3.Panels(1).Text = "Messages Marked for Deletion"
    End If
    
End Sub

Private Sub maiPop3_OnGetMsgNumber(ByVal MsgNumber As Long, ByVal Result As Long)
' Callback called when a response is received from the
    '   (remote) server regarding a previous call to
    '   GetMsgNumber.
    
    'if error set num. of msg's to 0, otherwise display number of messages on server
    If Result <> ecSuccess Then
        If Result = ecNoConnection Then  'if error because of no connection then reconnect
            blnConnected = False        '   try it again IN GetMsgNumber call
            intNumRetrievedMsgs = 0
            Exit Sub
        End If
        
    Else
        ' MsgNumber is the number of messages waiting on the server
        intNumRetrievedMsgs = MsgNumber
        
    End If
    staPop3.Panels(1) = "Number of new messages is " & MsgNumber
            
End Sub

Private Sub maiPop3_OnGetMsgSize(ByVal MsgSize As Long, ByVal Result As Long)
'callback function raised as a result of a GetMsgSize function call
    If Result <> ecSuccess Then
        MsgBox myMail.GetErrorText(Result)
        lngMsgSize = 0
        Unload frmProgress  'unload progress form
    Else
        lngMsgSize = MsgSize 'size of message
    End If
    
End Sub

Private Sub maiPop3_OnPOP3Connect(ByVal Result As Long)
'raised when a connection attempt has been processed by the mail server
    staPop3.Panels(1).Text = "Connected to " & myMail.POP3HostName & "."
    
End Sub

Private Sub maiPop3_OnReadTopLine(ByVal Line As String, ByVal Result As Long)
'callback event used in conjunction with ReadTopLine method
'Dim i As Long, j As Long

'i = InStr(Line, Chr(13))
'j = InStr(Line, Chr(10))
If (Result = 0) Then
    blnGetNextTop = False
    Exit Sub
End If

frmTop.txtTop = frmTop.txtTop & Line

End Sub

Private Sub maiPop3_OnSaveMsg(ByVal Result As Long)
    'finished getting message, unload progress form if no more messages
    '   else reset the progressbar
    Dim rt As Integer  'return for msgbox
        
    DoEvents  'WHEN USING SYNCHRONOUS MODE THIS DOEVENTS STATEMENT IS CRITICAL
                ' IT ALLOWS WINDOW TO RESPOND WHILE RETRIEVING MESSAGES!!!!!!!
    If intCurMsg = inttotalnummsg Then   'NOT NEEDED FOR ASYNCHRONOUS MODE
                                                       '(BlockingMode = false)
        Unload frmProgress  'unload progress form
    Else
        'just reset progress bar
        frmProgress.proProgress.Value = 0
        tlbPop3.Refresh
    End If
    blnNotFirstTime = False  'reset global boolean for first message indicator
    
End Sub

Private Sub maiPop3_OnSaveMsgProgres(ByVal BytesReceived As Long)
'raised until save operation is complete, used to indicate progress of a message save operation
    Dim intNumPanels As Integer
    Dim rt As Long  'return var
    
    DoEvents
    If blnNotFirstTime = False Then
        'saving message, show progress form
        frmProgress.Show
        frmProgress.Refresh
        blnNotFirstTime = True
    End If
      
    'number of panels
    intNumPanels = CInt((BytesReceived / lngMsgSize) * 20)
    frmProgress.proProgress.Value = intNumPanels
    
End Sub

Private Sub maiPop3_OnSendMail(ByVal Result As Long)
'NOTE : this event is being raised as a result of the frmSmtp form
'   since frmSmtp is making the SendMail call
          
     blnNotFirstTime = False  'message has been sent, set module-level boolean to false
     Unload frmProgress
     Unload frmSmtp  'unload SendMail form after message has been sent or been cancelled
     Me.SetFocus
     
End Sub

Private Sub maiPop3_OnSendMailProgress(ByVal BytesSent As Long, ByVal BytesTotal As Long)
'note : this event is being raised in the frmSmtp form
'   since frmSmtp is making the SendMail call.  The event
'   is raised in this module since this is where the control is located

    Dim intNumPanels As Integer  'number of panels
    Dim rt As Long  'return var
    
    If blnNotFirstTime = False Then
        'saving message, show indicator form
        blnNotFirstTime = True
        frmProgress.Show vbModeless, Me
        frmProgress.Refresh
        
    End If
      
    'number of panels
    intNumPanels = CInt((BytesSent / BytesTotal) * 20)
    frmProgress.proProgress.Value = intNumPanels

End Sub

Private Sub mnAbtMsgCtrl_Click()
mesMessage.AboutBox
End Sub

Private Sub mnMailCtrl_Click()
maiPop3.AboutBox
End Sub

Private Sub mnuEditCopy_Click()
    
    Clipboard.Clear
    Clipboard.SetText rtfPop3.SelText
    
End Sub

Private Sub mnuEditCut_Click()
    
    Clipboard.Clear
    Clipboard.SetText rtfPop3.SelText
    rtfPop3.SelText = ""
    
End Sub

Private Sub mnuEditPaste_Click()
    
    rtfPop3.SelRTF = Clipboard.GetText
    
End Sub

Private Sub mnuFileExit_Click()
    'call exit button routine
    cmdExit = True
    
End Sub

Private Sub mnuFileSaveAttach_Click()

Dim strFilename
Dim intIndex As Integer  'return var for listindex prop
Dim rt As Long  'return var

On Error GoTo errhandler  'for common dialog cancel operation
    
    'get currently selected item in listbox
    intIndex = lstPop3.ListIndex
    If intIndex = -1 Then
        MsgBox "Error: No attachment has been selected", vbOKOnly, "No Attachment Detected"
        Exit Sub
    Else
        staPop3.Panels(1) = "Saving Attachment ..."
        strFilename = lstPop3.List(intIndex)
    End If
    cdgPop3.FileName = strFilename 'suggest name of file as filename to be saved as
    cdgPop3.Filter = "All Files (*.*)|*.*"
    cdgPop3.DialogTitle = "Save File Attachment"
    cdgPop3.ShowSave
    'save file
    strFilename = cdgPop3.FileName
    rt = myMessage.DecodeAttachment(intIndex, strFilename)
    If rt <> ecSuccess Then
        'error occurred
        MsgBox myMessage.GetErrorText(rt)
        staPop3.Panels(1) = "Idle"
        Exit Sub
    End If
        
    staPop3.Panels(1) = "Idle"
    Exit Sub
errhandler:
    'cancel operation
    Exit Sub
    
End Sub

Private Sub mnuFileSendMessage_Click()

   Call cmdReply_Click

End Sub

Private Sub mnuFileSendNew_Click()
    
    Call cmdNewMail_Click
    
End Sub

Private Sub mnuFileServer_Click()

    'call frmServerInfo
    frmServerInfo.Show vbModal
    
End Sub

Private Sub mnuHelpAbout_Click()
    'show about dialog
    frmAbout.Show vbModal
    
End Sub

Private Sub mnuHelpContents_Click()
'calls appropriate helpfile, opens it with Contents tab open

    HTMLHelp 0, strHelpFilePath & "\utcp3ax.chm", HH_DISPLAY_TOC, 0

End Sub

Private Sub mnuHelpIndex_Click()
'calls appropriate helpfile, opens it with Index tab open

    HTMLHelp 0, strHelpFilePath & "\utcp3ax.chm", HH_DISPLAY_INDEX, 0

End Sub

Private Sub mnuHelpSearch_Click()
'calls appropriate helpfile, opens it with Search tab open

  Dim HH_FTS_QUERY As tagHH_FTS_QUERY

  With HH_FTS_QUERY
    .cbStruct = Len(HH_FTS_QUERY)
    .fStemmedSearch = 0&
    .fTitleOnly = 0&
    .fUniCodeStrings = 0&
    .iProximity = 0&
    .pszSearchQuery = ""
    .pszWindow = ""
    .fExecute = 1&
  End With

  HTMLHelpCallSearch 0, strHelpFilePath & "\utcp3ax.chm", _
          HH_DISPLAY_SEARCH, HH_FTS_QUERY

End Sub

Private Sub mnuMessagesDelete_Click()
    
    inttotalnummsg = 0
    'set boolean to false to indicate to sub to delete all inbox msgs
    Call DeleteInboxMsgs(False)
    'update flexgrid control
    Call InitializeFlexgrid
    inttotalnummsg = 0  'make sure total number of messages is 0
    'set current row to first empty row
    msgPop3.Rows = 2
    'empty rtf, listbox for body and attachments
    rtfPop3.Text = ""
    lstPop3.Clear
    
           
End Sub

Private Sub mnuMessagesDeleteRead_Click()
    
    'set boolean to true so that only read messages are deleted
    '   note that read msgs are indicated by having a hidden file property
    Call DeleteInboxMsgs(True)
    'update flexgrid control
    Call InitializeFlexgrid
    'now update the file attachments and msg body rtf
    
End Sub

Private Sub mnuMessagesDeleteSelected_Click()
    
    Dim strTemp As String  'holds name of file to be deleted
    Dim strTemp2 As String
    
    'row property equates to filenumber to be deleted e.g. 3rd row = File3.txt
    strTemp2 = Dir(App.Path & "\InBox\File" & CStr(msgPop3.row) & ".txt", vbNormal Or vbHidden)
    strTemp = App.Path & "\InBox\" & strTemp2
    If strTemp2 <> "" Then
        SetAttr strTemp, vbNormal
        Kill strTemp
    End If
    'update flexgrid
    Call InitializeFlexgrid
        
End Sub

Private Sub mnuMessagesDeleteServer_Click()
    
    Call DeleteServerMsgs
    
End Sub

Private Sub mnuMessagesRetrieve_Click()
    
    'retrieve messages
    Dim rt As Long  'return variable
    Dim i As Long, j As Long  'counter variables
    Dim strFilename As String
    Dim blnLastMsg As Boolean  'last msg is displayed as default, so mark as being read
                                '    by marking file as Hidden
        
    rt = Connect
    If rt <> ecSuccess Then
        If rt = 99999 Then 'unique return we made up for user declining
                            ' to enter critical account information
            MsgBox "Please Re-Enter Account Information", vbOKOnly, _
            "Missing Account Information"
            staPop3.Panels(1) = "Use File - Server Info ... from the" _
            & " menu to enter account information."
        Else
            MsgBox myMail.GetErrorText(rt)
        End If
        Exit Sub  'we are not connected so exit sub
    End If
        
    'get the number of messages
    staPop3.Panels(1) = "Connected.  Getting messages ..."
    rt = myMail.GetMsgNumber()
        
    'alert user if operation unsuccessful
    If rt <> ecSuccess Then
        If rt = ecNoConnection Then  'trap for failure due to no connection
            MsgBox "Please re-connect to server.", vbOKOnly, "Re-connect to Server"
        Else
            MsgBox myMail.GetErrorText(rt)
        End If
        staPop3.Panels(1) = "Idle."
        blnConnected = False
        Exit Sub
    End If
    inttotalnummsg = inttotalnummsg + intNumRetrievedMsgs
    
    blnConnected = True  'set boolean variable
       
    'now that we have retrieved the number of messages we can
    '   loop through all the messages and use SaveMessage to save
    '   information to textfiles (note for simplicity we are using
    '   one file per message).  first check to see if there were any new msg's
    If intNumRetrievedMsgs = 0 Then Exit Sub
    
    j = 1
    lstPop3.Clear  'clear listbox contents
    For i = intNextAvailMsgNum To inttotalnummsg  'create files but we can't overwrite existing files
        intCurMsg = i
                
        'set the filename
        strFilename = App.Path & "\InBox\" & "File" & i & ".txt"
        
        'call getMsgSize, message size will be obtained in OnGetMsgSize
        rt = myMail.GetMsgSize(j) 'GetMsgSize gets msgsize of message just downloaded
        If rt <> ecSuccess Then
        'failure
            staPop3.Panels(1) = "Idle."
            Exit Sub
        End If
        
        'the last message retrieved is displayed by default, so mark it
        '   as being read*****************************************
        If i = inttotalnummsg Then blnLastMsg = True 'mark last message as having been read
                      
        'next, call SaveMessage to save message to file
        rt = myMail.SaveMsg(j, strFilename)
        If rt <> ecSuccess Then
            MsgBox myMail.GetErrorText(rt)
            staPop3.Panels(1) = "Idle ..."
            Exit Sub
        End If
                
        'now we need to populate controls on the form, so call
        '   Populate function
         rt = Populate(i, strFilename)
         'update progess with status bar panel
        If rt <> ecSuccess Then
            staPop3.Panels(1) = myMail.GetErrorText(rt)
        Else
            staPop3.Panels(1) = "Retrieved message number " & CStr(j)
        End If
        j = j + 1
            
    Next
              
    'update intNextAvailMsgNum in case user decides to retrieve mail more than once
        'during prg execution
    intNextAvailMsgNum = inttotalnummsg + 1
              
    If intNumRetrievedMsgs > 0 Then
        rt = MsgBox("Would you like to delete messages " & vbCrLf & _
        "at the server?", vbYesNo, "Delete Messages from Server?")
        If rt = vbYes Then                  'delete msgs at server so they are not
             Call DeleteServerMsgs          'downloaded next get messages routine
        End If
    End If
    
    staPop3.Panels(1) = "Idle."
    rtfPop3.Refresh
    'update flexgrid control
    Call InitializeFlexgrid
    
End Sub

Private Sub mnuMessagesTops_Click()
'retrieves only part of email messages

Dim i As Integer, j As Integer
Dim intNumLines As Integer 'stores how many lines user wants to retrieve
Dim strTemp As String, strReturn As String




blnGetNextTop = True



'find out how many body lines user wants to retrieve from messages
strTemp = "Enter the number of lines to be retrieved"
strTemp = strTemp & vbCrLf & "from the bodies of the messages.  To retrieve only"
strTemp = strTemp & vbCrLf & "header information enter zero."
Do
    strReturn = InputBox(strTemp, "Number of Body Lines to be Retrieved")
    If strReturn = "" Then Exit Sub  'exit sub if user cancels inputbox
Loop Until IsNumeric(strReturn)

'set public variable in frmTop
frmTop.intNumLines = CInt(strReturn)

'make sure we are connected
Call Connect

'get the number of messages and set public variable in frmTop
staPop3.Panels(1) = "Connected.  Retrieving message tops ..."
myMail.GetMsgNumber

frmTop.intNumMsgs = intNumRetrievedMsgs 'NOTE: intNumRetrievedMsgs is a module
                                        '   level var., set in OnGetMsgNumber

If intNumRetrievedMsgs <> 0 Then
    frmTop.Show
    Call GetTop(1, CInt(strReturn))
End If

End Sub

Private Sub mnuMessagesUndo_Click()
    
    ' Reset delete will unmark all those messages that are flagged for
    '   deletion. Messages which are deleted from a server are not physically
    '   removed until the current session ends. Before a session ends, you
    '   can execute a ResetDelete operation to unmark those messages
    '   to be deleted at the end of the session.
    
    Dim rt As Long  'return var., indicates success/failure
    
    rt = myMail.ResetDelete()
    
    'if initially unsuccessful alert user
    If rt <> ecSuccess Then
        MsgBox myMail.GetErrorText(rt)
    Else
        staPop3.Panels(1).Text = "Messages Unmarked for Deletion"
    End If
        
End Sub

Private Sub mnuOptionsConnect_Click()
'set the Connect Timeout (seconds)
    Dim strTemp As String
    Do
        strTemp = InputBox("Enter new connection timeout: " & vbCrLf & "(seconds)" _
        , "Connection Timeout", myMail.ConnectTimeOut)
        If strTemp = "" Then Exit Sub 'user cancelled operation
    Loop Until IsNumeric(strTemp) 'force user to enter a valid numeric expression
    myMail.ConnectTimeOut = CLng(strTemp) 'set property
    
End Sub

Private Sub mnuOptionsReceive_Click()
'set the Receive Timeout (seconds)
    Dim strTemp As String
    Do
        strTemp = InputBox("Enter new receive timeout: " & vbCrLf & "(seconds)" _
        , "Receive Timeout", myMail.ReceiveTimeOut)
        If strTemp = "" Then Exit Sub 'user cancelled operation
    Loop Until IsNumeric(strTemp)
    myMail.ReceiveTimeOut = CLng(strTemp)

End Sub

Private Sub msgPop3_Click()
    
    Dim strFilename As String  'filename of msg stored as file to hdd
    '   (for convenience sake this is default to the app directory)
    Dim rt As Long  'return var
    Dim strAttachName As String
    Dim i As Long  'counter var
    Dim strTemp As String  'temp var for Dir call
    
    'if first row is selected and its empty then exit sub
    '   check by call dir
    strTemp = Dir(App.Path & "\InBox\File1.txt", vbNormal Or vbHidden)
    If strTemp = "" Then Exit Sub 'exit sub since there are no msgs stored in InBox
    
    strFileClickedOn = ""  'intialize to zero length string
    
    'if fixed first row was clicked abort operation
    If msgPop3.row = 0 Then Exit Sub
        
    'set current message to row selected in flexgrid
    intCurMsg = msgPop3.row
    
    strFilename = App.Path & "\InBox\" & "File" & msgPop3.row & ".txt"
    
    'NOTE: we need to use the Message control to work with messages
    '   need to use the Message control's Load method before using the Get.... methods(e.g.GetAttachName)
    rt = myMessage.Load(strFilename)
    If rt <> ecSuccess Then
     'failure
        MsgBox myMessage.GetErrorText(rt), vbOKOnly, "Error: Can Not Decode Message"
        Exit Sub
    End If
    intNumAttach = myMessage.GetAttachmentNumber 'get number of attachments
        lstPop3.Clear  'clear listbox
        If intNumAttach > 0 Then
            
            For i = 0 To intNumAttach - 1
                strAttachName = myMessage.GetAttachmentName(i)  'GetAttachmentName is zero based
                If (strAttachName = "") Then
                    'if attachment has no name then indicate this in listbox
                    'strip out "/" and replace with underscore
                    strAttachName = myMessage.GetAttachmentType(i)
                    strAttachName = Replace(strAttachName, "/", "_")
                    lstPop3.AddItem strAttachName
                Else
                    lstPop3.AddItem strAttachName
                End If
            Next
        lstPop3.ListIndex = 0
        End If
        'Once again, to work with elements of a message we use the Message control
        '   abort if there is no messages
        If inttotalnummsg <> 0 Then
            rtfPop3.TextRTF = myMessage.GetMessageBody() 'populate rtf box
        End If
        
        'mark file as having been read by setting the hidden attribute
        SetAttr strFilename, vbHidden
        
        'repaint flexgrid
        Call InitializeFlexgrid(msgPop3.row)
                
End Sub

Private Sub rtfPop3_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    
    If Button = 2 Then
        PopupMenu mnuEdit, vbPopupMenuCenterAlign
    End If
    
End Sub

Private Sub tlbPop3_ButtonClick(ByVal Button As MSComctlLib.Button)

    On Error Resume Next
    
    Select Case Button.Key
        Case "Tops"
            Call mnuMessagesTops_Click
        
        Case "Save"
             Call mnuFileSaveAttach_Click
        
        Case "Cut"
           mnuEditCut_Click
           
        Case "Copy"
           mnuEditCopy_Click
           
        Case "Paste"
           mnuEditPaste_Click
        
        Case "Retrieve"
            mnuMessagesRetrieve_Click
        
        Case "Reply"
            mnuFileSendMessage_Click
        
        Case "New"
            mnuFileSendNew_Click
        
        Case "Bold"
            'toggle on/off
            If rtfPop3.SelBold = False Then
                rtfPop3.SelBold = True
            Else
                rtfPop3.SelBold = False
            End If
        
        Case "Italic"
            'toggle on/off
            If rtfPop3.SelItalic = False Then
                rtfPop3.SelItalic = True
            Else
                rtfPop3.SelItalic = False
            End If
        
        Case "Underline"
            If rtfPop3.SelUnderline = False Then
                rtfPop3.SelUnderline = True
            Else
                rtfPop3.SelUnderline = False
            End If
        
        Case "Print"
            Printer.Print "To: " & msgPop3.TextArray(faIndex(msgPop3.row, 0))
            Printer.Print
            Printer.Print "From: " & msgPop3.TextArray(faIndex(msgPop3.row, 1))
            Printer.Print
            Printer.Print "Date: " & msgPop3.TextArray(faIndex(msgPop3.row, 2))
            Printer.Print
            Printer.Print "Subject: " & msgPop3.TextArray(faIndex(msgPop3.row, 4))
            Printer.Print
            Printer.Print
            Printer.Print rtfPop3.Text
            Printer.EndDoc
    
    End Select

End Sub

Private Function Populate(ByVal intMsgNum As Integer, ByVal strFilename As String, _
Optional blnSavedFiles As Boolean = False) As Long
'populates the flexgrid control
'   the optional parameter is used when form_load initializes flexgrid with saved msg's

    '**************Use the Message control to work with message elements***************
    
    Dim rt As Long  'return var
    Dim myFG As MSFlexGrid
    Dim i As Long  'counter variable
    Dim strAttachName As String  'attachment name, if any
    Dim intMsgRead As Integer  'used for return of GetAttr,  Hidden attribute means
                                    ' message has been read
    Dim dteTemp As Date
    
    On Error GoTo errhandler
    
     Set myFG = frmMain.msgPop3 'set obj var to instance of flexgrid on form
    myFG.Redraw = False
       
    'to decode the message load it with MessageControl.Load
    rt = myMessage.Load(strFilename)
    'if error occurred return value of 1 (ecFailure),
    '   else return 0 (ecSuccess) for success indicator
    If rt <> ecSuccess Then
        'failure
        Populate = ecError
        myFG.Redraw = True
        Set myFG = Nothing
        Exit Function
    End If
        
    'need to increase number of rows in flexgrid to accomodate data
    myFG.Rows = intMsgNum + 1
        
    'clear listbox, repopulate every time this procedure is called
    '   so that the last message (newest message) is displaying its particulars
    
      If strFileClickedOn = App.Path & "\InBox\File0.txt" _
    Or strFilename = strFileClickedOn Then
        'only update controls if this isnt the result of a flexgrid_click operation,
        '   or update if it is because of click operation and the file
        '   matches the file that was clicked on
        rtfPop3 = myMessage.GetMessageBody()  'populate rich text box with message body
        lstPop3.Clear
        intNumAttach = myMessage.GetAttachmentNumber 'get number of attachments
        If intNumAttach > 0 Then
            For i = 0 To intNumAttach - 1
                strAttachName = myMessage.GetAttachmentName(i)  'GetAttachName is zero based
                If (strAttachName = "") Then
                    'if attachment has no name then indicate this in listbox
                    'strip out "\" and replace with underscore
                    strAttachName = myMessage.GetAttachmentType(i)
                    strAttachName = Replace(strAttachName, "/", "_")
                    lstPop3.AddItem strAttachName
                Else
                    lstPop3.AddItem strAttachName
                End If
            Next
        lstPop3.ListIndex = 0
        End If
    End If
    'now populate header info
     
     strTo = myMessage.GetHeaderByType(ftTo) 'store in module level variable, to be passed to SendMail form
    'if blnsavedFiles is true add an icon to the To field if message has not been read
    '   message has been read if the file's Hidden attribute has been set
    If blnSavedFiles = True Then
         intMsgRead = GetAttr(strFilename) And vbHidden 'bitwise operation
         If intMsgRead = 0 Then 'if hidden, msg has been read so do not show icon
            myFG.row = intMsgNum
            myFG.col = 0
            myFG.CellPictureAlignment = flexAlignLeftCenter
            myFG.CellAlignment = flexAlignCenterCenter
            Set myFG.CellPicture = LoadPicture(App.Path & "\bullet1.bmp")
        ElseIf strFilename = App.Path & "\InBox\FILE1.TXT" Or _
        strFilename = App.Path & "\InBox\File1.txt" Then
            'get rid of icon
            myFG.CellAlignment = flexAlignLeftCenter
            Set myFG.CellPicture = LoadPicture  'delete icon  -->for some reason
        End If                                      'i'm being forced to do this for the
                                                    '1st flexgrid entry
        
    End If
    
    'strTo = myMail.GetMsgHeader(hfTo)
    myFG.TextArray(faIndex(intMsgNum, 0)) = strTo
    strFrom = myMessage.GetHeaderByType(ftFrom)
    myFG.TextArray(faIndex(intMsgNum, 1)) = strFrom
    myFG.TextArray(faIndex(intMsgNum, 2)) = myMessage.GetHeaderByType(ftDate)
    strCc = myMessage.GetHeaderByType(ftCC)
    myFG.TextArray(faIndex(intMsgNum, 3)) = strCc
    strSubject = myMessage.GetHeaderByType(ftSubject)
    myFG.TextArray(faIndex(intMsgNum, 4)) = strSubject
        
    myFG.Redraw = True
        
    Set myFG = Nothing
    
    Exit Function
    
errhandler:
    MsgBox "Err num = " & Err.Number & "Err desc = " & Err.Description
    Resume Next

End Function
Private Function faIndex(ByVal row As Integer, ByVal col As Integer) As Long
'use this function to use with flexgrid's textArray function
     faIndex = row * msgPop3.Cols + col
          
End Function

Private Function Connect() As Long
' Attempt a connection to the POP3 server
' returns a long indicating success/failure of the connection attempt -- zero is returned if
'   operation was successful.
    
    Dim strTemp As String
    Dim rt As Long  'return value
    
    '   first check to see if user has entered server details, if not
    '   prompt user to enter them
    
    'get user to enter server logon properties
    If strPop3Name = "" Or strUserName = "" Or _
    strUserPassword = "" Then
        Call GetAccountInfo
        'check to saee if user did not enter values, if so exit and indicate failure
        If strPop3Name = "" Or strUserName = "" Or _
        strUserPassword = "" Then
            Connect = 99999  'define unique error code to indicate user has declined to enter
            Exit Function     ' critical account information
        End If
    End If
            
     staPop3.Panels(1) = "Connecting to server ..."
        
    'set necessary properties from registry entries
    myMail.UserName = strUserName
    myMail.UserPassword = strUserPassword
    myMail.POP3HostName = strPop3Name
       
    rt = myMail.POP3Connect()
    
    'if connection unsuccessful alert user
    If rt <> ecSuccess Then
        staPop3.Panels(1) = "Idle ..."
        Connect = rt
        Exit Function
    End If
    blnConnected = True
    Connect = rt
    
End Function

Public Property Get ServerInfo() As Variant
    'returns a 1 - based array  containing server details
    '  such as servername,username, password, etc.
    'this is called by frmSmtp to populate frmSmtp header info when replying to a message
    
    Dim strArray() As String
    ReDim strArray(6)
    strArray(1) = msgPop3.TextArray(faIndex(msgPop3.row, 1))
    strArray(2) = strCc
    strArray(3) = strBcc
    strArray(4) = strSubject
    strArray(5) = rtfPop3.Text
    strArray(6) = msgPop3.TextArray(faIndex(msgPop3.row, 0))
    ServerInfo = strArray
    
End Property

Public Property Get Reply() As Boolean
'frmSmtp will call this in order to determine if its being
'   displayed for a new message or a reply
Reply = blnReply

End Property

Private Sub DeleteServerMsgs()
'used to mark messages for deletion (at the server)
 
    Dim i As Long  'counter var
    Dim rt As Long 'return var
    
    For i = 1 To intNumRetrievedMsgs
        staPop3.Panels(1).Text = "Deleting message number " _
        & i & " from server."
        rt = myMail.DeleteMsg(i)
        'check for error
        If rt <> ecSuccess Then
            staPop3.Panels(1).Text = myMail.GetErrorText(rt)
        End If
        
    Next
             
End Sub
Private Sub MakeInBox()
'makes Inbox folder if it does not already exist

    Dim strRet As String  'return variable for Dir() call
    
    ChDir App.Path
    strRet = Dir("InBox", vbDirectory)
    If strRet = "" Then
        MkDir App.Path & "\InBox"
    End If
    
End Sub

Private Sub InitializeFlexgrid(Optional ByVal intFlexGridRow As Integer = 0)
'called from form_load, initializes flexgrid with messages saved in InBox folder
'also called whenever flexgrid needs to be updated
'Note: if intFlexGridRow is not zero it represents the row to be highlighted (selected)
    
    Dim strTemp As String  'temp var
    Dim i As Long  'counter variable
    Dim strTemp2 As String  '2nd temp string var
    Dim strLastMsg As String  'save the filename of each message, so when Dir
                                'call returns empty we know which file is the last file
                                'to be displayed, mark it has hidden to indicate its been read
        
    'make sure saved messages
    '   are named properly
    Call RenameSavedFiles
    
    'set the module level var which records which file is to
    '   have its body and attachments displayed
    strFileClickedOn = App.Path & "\InBox\File" & CStr(intFlexGridRow) & ".txt"
    
    i = 1
    'use dir to loop through all files in InBox directory,populate listbox while we go
    '   we need to make sure that File1, File2.txt etc. are loaded in order
    '   so we will use a for loop with a counter
    
    strTemp2 = App.Path & "\InBox\"
    strTemp = Dir(App.Path & "\InBox\" & "File" & i & ".txt", vbNormal Or vbHidden) 'keep calling dir until all files
    If strTemp <> "" Then                       ' have been iterated thru  'vbNormal Or vbHidden
        'indicate to user saved messages are being displayed
        staPop3.Panels(1) = "Unread Messages Indicated by Icon."
        Do
            'use populate function to enter each message into the flexgrid
            strTemp = strTemp2 & strTemp
            Populate i, strTemp, True   'set blnSavedFiles to true to let Populate
            i = i + 1            '  procedure know file(s) in flexgrid are saved messages
            'keep calling dir
            '   but save the previous filename so we know what file to mark as being read
            strLastMsg = strTemp
            strTemp = Dir(App.Path & "\InBox\" & "File" & i & ".txt", vbNormal Or vbHidden)
        Loop Until strTemp = ""
    End If
    
    'last message is always displayed so mark as a hidden file to indicate
    '   it has been read
   
    If strLastMsg <> "" Then
         SetAttr strLastMsg, vbHidden
        'get rid of icon indicating last loaded msg as not read, which it has been
        If msgPop3.row = msgPop3.Rows - 1 Then
            Set msgPop3.CellPicture = LoadPicture
            msgPop3.CellAlignment = flexAlignLeftCenter
        End If
    End If
        
    'we need to know what the next available message number will be if user
        'downloads new messages for the CreateFile subroutine
        'otherwise we will overwrite existing saved messages
    intNextAvailMsgNum = i
    
    If intFlexGridRow = 0 Then 'set focus to last row in flexgrid
        If msgPop3.Rows > 1 Then 'dont set row 0 as selected, so only do this if Rows>0
            msgPop3.row = msgPop3.Rows - 1 'make last (latest) message the selected one
            msgPop3.ColSel = 4
        End If
    Else
        msgPop3.row = intFlexGridRow
        msgPop3.ColSel = 4
    End If
    
    'record total number of messages saved to InBox folder
    inttotalnummsg = msgPop3.Rows - 1
    
End Sub

Private Sub DeleteInboxMsgs(ByVal blnRead As Boolean)
'if blnRead Msgs is false then delete all saved Inbox messages,
'   if true then delete only messages which have been read
    
    'delete messages which were saved to demo application directory
    '   they will be named File1.txt. File2.txt, etc.
    
    Dim strTempFile As String  'used with Dir
    Dim intIsHidden As Integer  'used with GetAttr call, see if Hidden file attribute exist
    Dim strTemp As String  'used to hold filename return of Dir call
    
    'see if file exists
    strTemp = Dir(App.Path & "\InBox\" & "File*.txt", vbNormal Or vbHidden)
            
    Do
    'loop through app directory and delete all
    '  files or only messages that have been read, depending on blnSavedMsg
       If strTemp <> "" Then
            strTempFile = App.Path & "\InBox\" & strTemp
            intIsHidden = GetAttr(strTempFile) And vbHidden 'bitwise op, to see if hidden attr is set
            If blnRead = False Then 'delete all saved inbox files
                'turn off hidden attribute so we can kill file
                SetAttr strTempFile, vbNormal
                Kill strTempFile
            Else
                If intIsHidden Then  'file is marked as hidden, so it has been read
                    'get rid of hidden attribute
                    SetAttr strTempFile, vbNormal
                    Kill strTempFile
                    If msgPop3.Rows > 2 Then
                        msgPop3.Rows = msgPop3.Rows - 1
                    End If
                End If         'delete message which has been read
            End If
       strTemp = Dir
       End If
       
       
    Loop Until strTemp = ""
    
    
End Sub

Private Sub GetAccountInfo()
'retrieves account information from the registry

    Dim RegistryReturn As Variant  'saves server information settings
        
    'retrieve and store info for Pop3 server
    '   by retrieving from registry
    RegistryReturn = GetAllSettings("DundasMailDemo", "ServerInfo")
    If IsEmpty(RegistryReturn) Then
    'then user hasnt entered values required for send mail operation
    '   which are the username, password and pop3server
        'show the server info form
        frmServerInfo.Show vbModal
    End If
    'retrieve and store info for Pop3 server
    '   by retrieving from registry (user should have entered values from frmServerInfo
    RegistryReturn = GetAllSettings("DundasMailDemo", "ServerInfo")
    
    'check to see if user has declined to save values, if so
    '   entries will have to be entered later
    If Not IsEmpty(RegistryReturn) Then
        strPop3Name = RegistryReturn(1, 1)
        strUserName = RegistryReturn(2, 1)
        strUserPassword = RegistryReturn(3, 1)
        
    End If
    
End Sub

Private Sub RenameSavedFiles()
'all saved files are be named in sequential order
'   e.g. File1.txt, File2.txt, File3.txt, etc...
'   so this must be called whenever any files are deleted from Inbox folder
    
    Dim intNumFiles As Integer  'stores total number of saved messages
    Dim strTemp As String  'used to hold return value of Dir call
    Dim strTemp2 As String 'used to change filename to full pathname
    Dim i As Integer  'counter variable
    Dim intLowestAvailNum As Integer  'keeps track of lowest available number
                                        'for the renaming of a file
    Dim blnRename  As Boolean 'indicates whether rename operation should take place
                                                                   
                                        
    'find out how many files are in Inbox folder
    '  keep calling dir until all files
    strTemp = Dir(App.Path & "\InBox\" & "File" & "*.txt", vbNormal Or vbHidden)
    If strTemp = "" Then
        'clear msflexgrid control
        msgPop3.Clear
        msgPop3.FormatString = "<To:                                        " & _
        "|<From:                                      |<Date:                      " & _
        "|<Cc:                  |<Subject:                                                  "
        Exit Sub 'if no messages in InBox, exit this subroutine
    End If
    While strTemp <> ""
        intNumFiles = intNumFiles + 1
        strTemp = Dir
    Wend
        
    'now we know total number of saved messages, rename files
    '   that arent in sequential order
    i = 1
    intLowestAvailNum = 1
    Do
        'now make Dir call, look for File1.txt
        strTemp = ""
        strTemp = Dir(App.Path & "\InBox\" & "File" & i & ".txt", vbNormal Or vbHidden)
        strTemp2 = App.Path & "\InBox\" & strTemp 'change to full pathname
        If strTemp = "" Then
            blnRename = True
            If intLowestAvailNum >= i Then
                intLowestAvailNum = i
            End If
        Else
            
            intNumFiles = intNumFiles - 1
            'if we looked for a file and it wasnt present then we need to rename
            If blnRename Then
              Name strTemp2 As App.Path & "\InBox\" & "File" & intLowestAvailNum & ".txt"
              blnRename = False
              i = i - 1
            End If
            intLowestAvailNum = intLowestAvailNum + 1
        End If
        i = i + 1 'increment counter
    Loop Until intNumFiles = 0
    'update total number of files saved to hard drive
    
        
End Sub

Public Sub GetTop(ByVal intMsgNum As Integer, ByVal intNumLines As Integer)
'fills frmTop with next message top, this sub is called first from frmMain, then
'   from frmTop for all other msg tops
'intMsgNum is the message to get top from, while intNumLines is the
'   number of body lines to be retrieved per message

Dim i As Integer

myMail.OpenTop intMsgNum, intNumLines

frmTop.txtTop = ""

Do While blnGetNextTop = True
    i = myMail.ReadTopLine
Loop


'Do While i <> 0
   '  i = myMail.ReadTopLine
'Loop
    
myMail.CloseTop 'sdsda

End Sub
