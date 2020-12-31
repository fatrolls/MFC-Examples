VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.4#0"; "UTHistory.dll"
Object = "{807D529B-2A6D-11D3-A499-0080C858F182}#1.4#0"; "UTImap4.dll"
Begin VB.Form frmMain
   Caption         =   "Dundas TCP/IP  utaxIMAP4 Client ActiveX Control 4.0 -  Demo Program"
   ClientHeight    =   7848
   ClientLeft      =   360
   ClientTop       =   1020
   ClientWidth     =   8556
   ClipControls    =   0   'False
   Icon            =   "IMAP4Test.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7848
   ScaleWidth      =   8556
   StartUpPosition =   2  'CenterScreen
   Begin UTHISTORYLibCtl.History utaxHistory
      Height          =   1212
      Left            =   120
      OleObjectBlob   =   "IMAP4Test.frx":000C
      TabIndex        =   15
      Top             =   6600
      Width           =   8292
   End
   Begin VB.TextBox txtMsgBodyBx
      Height          =   1332
      Left            =   3000
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   11
      ToolTipText     =   "The body of the message will be decoded and displayed here."
      Top             =   5040
      Width           =   5412
   End
   Begin ComctlLib.TreeView tvwMailBox
      Height          =   4440
      Left            =   132
      TabIndex        =   5
      ToolTipText     =   "List of the folders you have on the specified server for the slected account."
      Top             =   1920
      Width           =   2772
      _ExtentX        =   4890
      _ExtentY        =   7832
      _Version        =   327682
      Indentation     =   529
      LineStyle       =   1
      Style           =   6
      Appearance      =   1
   End
   Begin ComctlLib.ListView lvwMessageList
      Height          =   2652
      Left            =   3000
      TabIndex        =   7
      ToolTipText     =   "A list of the messages available in the selected folder along with thier headers and flags."
      Top             =   1920
      Width           =   5388
      _ExtentX        =   9504
      _ExtentY        =   4678
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Subject"
         Object.Width           =   3881
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Flags"
         Object.Width           =   3528
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "From"
         Object.Width           =   3528
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         Alignment       =   2
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Date"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.Frame fraServerInfo
      Caption         =   "Server Information"
      ClipControls    =   0   'False
      Height          =   1332
      Left            =   120
      TabIndex        =   0
      ToolTipText     =   "Enter server information here."
      Top             =   90
      Width           =   8292
      Begin VB.CommandButton cmdExit
         Cancel          =   -1  'True
         Caption         =   "E&xit"
         Height          =   375
         Left            =   6360
         TabIndex        =   10
         ToolTipText     =   "Exit the Demo Application"
         Top             =   720
         Width           =   1095
      End
      Begin VB.CommandButton cmdConnect
         Caption         =   "&Connect"
         Height          =   375
         Left            =   6360
         TabIndex        =   4
         ToolTipText     =   "Connect to the IMAP server."
         Top             =   225
         Width           =   1095
      End
      Begin VB.TextBox txtPassword
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   3480
         PasswordChar    =   "*"
         TabIndex        =   3
         ToolTipText     =   "Enter the password of the account here."
         Top             =   720
         Width           =   1692
      End
      Begin VB.TextBox txtUser
         Height          =   285
         Left            =   1092
         TabIndex        =   2
         ToolTipText     =   "Enter the utaxIMAP4 user name."
         Top             =   756
         Width           =   1455
      End
      Begin VB.TextBox txtHost
         Height          =   285
         Left            =   1080
         TabIndex        =   1
         ToolTipText     =   "Your utaxIMAP4 Server."
         Top             =   270
         Width           =   4092
      End
      Begin VB.Label lblPassword
         Caption         =   "&Password:"
         Height          =   252
         Left            =   2640
         TabIndex        =   9
         ToolTipText     =   "Enter user password here."
         Top             =   840
         Width           =   828
      End
      Begin VB.Label lblUser
         Caption         =   "&User name:"
         Height          =   252
         Left            =   156
         TabIndex        =   8
         ToolTipText     =   "Enter user name here."
         Top             =   768
         Width           =   948
      End
      Begin VB.Label lblHost
         Caption         =   "&Host name:"
         Height          =   255
         Left            =   135
         TabIndex        =   6
         ToolTipText     =   "Enter host name of utaxIMAP4 server."
         Top             =   285
         Width           =   840
      End
   End
   Begin UTIMAP4LibCtl.IMAP4 utaxIMAP4
      Left            =   5160
      Top             =   1440
      ConnectTimeOut  =   15
      ReceiveTimeOut  =   15
      NewMailCheckInterval=   15
      BlockingMode    =   0   'False
      HostName        =   ""
      UserName        =   ""
      Password        =   ""
   End
   Begin VB.Label lblLabel3
      Caption         =   "Folders"
      Height          =   252
      Left            =   240
      TabIndex        =   14
      Top             =   1560
      Width           =   852
   End
   Begin VB.Label lblLabel2
      Caption         =   "Message headers"
      Height          =   252
      Left            =   3240
      TabIndex        =   13
      Top             =   1560
      Width           =   1332
   End
   Begin VB.Label lblLabel1
      Caption         =   "Message Body"
      Height          =   252
      Left            =   3120
      TabIndex        =   12
      Top             =   4680
      Width           =   1572
   End
   Begin VB.Menu mnuMailBox
      Caption         =   "&MailBox"
      Begin VB.Menu mnuMailBoxCreate
         Caption         =   "&Create"
      End
      Begin VB.Menu mnuMailBoxDelete
         Caption         =   "&Delete"
      End
      Begin VB.Menu mnuMailBoxRename
         Caption         =   "&Rename"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Dundas Software
' Dundas TCP/IP 4.0 Demonstration program
'
Option Explicit

Dim nCurMsgNumber As Integer  'number identifying which message is being dealt with
Dim Delimiter As String  'delimiter used by IMAP server
Dim m_initHeight As Long '  initial form Height
Dim m_initWidth As Long ' initial form width

Private Sub cmdConnect_Click()
    
    Dim rt As Long  'return variable, idicates success/failure of operation
    
    ' Initialize connection data
    utaxIMAP4.HostName = txtHost
    utaxIMAP4.UserName = txtUser
    utaxIMAP4.UserPassword = txtPassword
       
    ' Connect to the host
    utaxHistory.AddLine ("Connecting to the mail host ...")
    rt = utaxIMAP4.Connect()
    If rt <> ecSuccess Then
        utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt))
    End If
    
    Me.MousePointer = vbHourglass
    
End Sub

Private Sub cmdExit_Click()
'exit app and close connection
On Error Resume Next
    utaxIMAP4.Close
    Unload Me
    
End Sub

Private Sub Form_Load()
    utaxIMAP4.AboutBox
    txtHost = ""
     txtUser = "User name "
     txtPassword = "Password"
     
    
    
    'initialize current number of message lines
   m_initHeight = Me.Height
   m_initWidth = Me.Width
    nCurMsgNumber = 0
    Form_Resize
    
    
End Sub

Private Sub Form_Resize()
    'need resizing routine for controls on form
    
    If Me.WindowState <> vbMinimized Then
    
     'lastly, do not let user undersize the form
    If Me.Width < m_initWidth Then
    Me.Width = m_initWidth
    Exit Sub
    End If
    
    
    If Me.Height < m_initHeight Then
    Me.Height = m_initHeight
    Exit Sub
    End If
    

    
    Dim lngFormWidth As Long
    Dim lngFormHeight As Long
    
    lngFormWidth = Me.ScaleWidth
    lngFormHeight = Me.ScaleHeight
    
     utaxHistory.Top = lngFormHeight - utaxHistory.Height
     utaxHistory.Width = lngFormWidth - 200
    'first, make sure all leftmost controls are aligned
    utaxHistory.Left = 100
    fraServerInfo.Left = 100
    tvwMailBox.Left = 100
    
    'next, have listview control and frames utilize entire width of form
    fraServerInfo.Width = lngFormWidth - 200
    lvwMessageList.Width = lngFormWidth - 3060
    txtMsgBodyBx.Width = lvwMessageList.Width
        
    'next, have command buttons align to right of frame
    cmdExit.Left = lngFormWidth - 1420
    cmdConnect.Left = cmdExit.Left
    tvwMailBox.Height = tvwMailBox.Height - utaxHistory.Height - 200
    'adjust the heights of the treeview and listview controls
    tvwMailBox.Height = utaxHistory.Top - tvwMailBox.Top
    txtMsgBodyBx.Height = tvwMailBox.Height - lvwMessageList.Height - lblLabel1.Height - 300
    
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release hidden form var
    Set frmMain = Nothing
    
End Sub

Private Sub utaxIMAP4_OnConnect(ByVal Result As Long)
    
    Dim rt As Long  'return variable, indicates success/failure of operation
    
    utaxHistory.AddLine (utaxIMAP4.GetErrorText(Result) + " -- " + utaxIMAP4.GetLastCommandResponseText())
    
    ' If connection was successful
    If Result = ecSuccess Then
        ' Get the list of the mail boxes
        utaxHistory.AddLine ("Getting mailboxes list ...")
        rt = utaxIMAP4.MailBoxList("", "*")
        If rt <> ecSuccess Then
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt))
        End If
    End If
    
    Me.MousePointer = vbNormal
    
End Sub

Private Sub utaxIMAP4_OnMailBoxList(ByVal Result As Long)
    
    Dim Index As Long  'loop counter
    Dim Index2 As Long  'loop counter
    Dim PrevKey, CurKey 'store relative, relationship parameters for Treeview.Add() function
    Dim MBArray   'array of mailbox names
    Dim i As Long  'counter variable
    Dim bFound As Boolean  'flag indicating whether item has been found or not
    Dim intIndex As Long  'index only used when splitting mailbox string
                           ' into different strings if delimiters are found
    Dim strBoxName  'name of mailbox
    Dim strKey As String  'name of key in nodes collection
        
        
    utaxHistory.AddLine (utaxIMAP4.GetErrorText(Result) + " -- " + utaxIMAP4.GetLastCommandResponseText())
   
    ' If command was successful
    If Result = ecSuccess Then
        
        Call tvwMailBox.Nodes.Clear
                
        Index = 0
        While Index < utaxIMAP4.GetMailBoxListSize()
            strBoxName = utaxIMAP4.GetMailBoxListName(Index)
            Delimiter = utaxIMAP4.GetMailBoxListDelimiter(Index)
            tvwMailBox.PathSeparator = Delimiter
            
            Index2 = 0
            PrevKey = Null
            CurKey = ""
            MBArray = Split(strBoxName, Delimiter)
            While Index2 <= UBound(MBArray)
                bFound = False
                CurKey = CurKey + MBArray(Index2) + Str(Index2)
                
                ' Try to find existing node
                i = 1
                While i <= tvwMailBox.Nodes.Count
                    strKey = tvwMailBox.Nodes(i).Key
                    If strKey = CurKey Then
                        bFound = True
                    End If
                i = i + 1
                Wend
                
                If bFound = False Then
                    Call tvwMailBox.Nodes.Add(PrevKey, tvwChild, CurKey, MBArray(Index2))
                End If
                
                PrevKey = CurKey
                Index2 = Index2 + 1
            Wend
            Index = Index + 1
        Wend
        
    End If
    
End Sub


Private Sub utaxIMAP4_OnMailBoxSelect(ByVal Result As Long)
    
    Dim rt As Long  'return variable, indicates success/failure of operation
    
    utaxHistory.AddLine (utaxIMAP4.GetErrorText(Result) & " -- " & utaxIMAP4.GetLastCommandResponseText())
        
    Call lvwMessageList.ListItems.Clear  'clear the listview control
    
    'If MailBoxSelect() was successful then populate history control
    If Result = ecSuccess Then
        'Get messages of the first mail box
        utaxHistory.AddLine ("Getting messages ...")
        rt = utaxIMAP4.MessageFetch("1:*", fiBody)
        'only add items to history control if fetch was successful
        If rt <> ecSuccess Then
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt))
        End If

    End If
    
End Sub

Private Sub utaxIMAP4_OnMessageFetch(ByVal Result As Long)
    
    Dim itmX As ListItem  'listitem object
    Dim Index As Long  'counter used with While...Wend
    Dim rt As Long  'return variable
    Dim strFlags As String  'stores relevant flags
    
    utaxHistory.AddLine (utaxIMAP4.GetErrorText(Result) & " -- " & utaxIMAP4.GetLastCommandResponseText())
    nCurMsgNumber = 0
   
    'update listview control only if MessageFetch() was successful
    If Result = ecSuccess Then
        
        Call lvwMessageList.ListItems.Clear  'clear listview control
        Index = 0
        While Index < utaxIMAP4.GetMessageListSize()  'loop through all messages
            rt = utaxIMAP4.SetCurrentMessage(Index)
            Set itmX = lvwMessageList.ListItems.Add()  'add listitem
            
            'Note: hfSubject is enumerated constant of MsgHeaderFields
            'set new listitem properties
            itmX.Text = utaxIMAP4.GetMsgHeader(hfSubject)
            strFlags = utaxIMAP4.FlagsToString(utaxIMAP4.GetMsgSystemFlags) & utaxIMAP4.GetMsgFlags
            itmX.SubItems(1) = strFlags
            itmX.SubItems(2) = utaxIMAP4.GetMsgHeader(hfFrom)
            itmX.SubItems(3) = utaxIMAP4.GetMsgDate()
          
            Index = Index + 1
        Wend
   
    nCurMsgNumber = Index  'update current message number
    End If
    
End Sub

Private Sub utaxIMAP4_OnRecent(ByVal MsgNumber As Long)
    
    Dim rt As Long  'return variable, indicating success/failure of operation
    
    If MsgNumber > 0 And nCurMsgNumber <> utaxIMAP4.MailBoxMsgNumber Then
        ' Get messages of the first mail box
        utaxHistory.AddLine ("Getting messages ...")
        Call lvwMessageList.ListItems.Clear  'clear listview
        
        rt = utaxIMAP4.MessageFetch("1:*", fiBodyHeader)
        If rt <> ecSuccess Then  'if message was fetched ok add to history control
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt))
        End If
    End If
    
End Sub



Private Sub lvwMessageList_DblClick()
If lvwMessageList.ListItems.Count > 0 Then
utaxIMAP4.SetCurrentMessage lvwMessageList.SelectedItem.Index - 1
txtMsgBodyBx = utaxIMAP4.GetDecodedMsgBody
End If

End Sub

Private Sub tvwMailBox_AfterLabelEdit(Cancel As Integer, NewString As String)
    ' called after Renaming of mail box in treeview
    
    Dim strNewMailBoxName As String  'stores full path of new mailbox name
    Dim iPos As Long  'return of InStr() function
    Dim blnPrevBlockMode As Boolean  'stores blocking mode boolean flag (from BlockingMode() )
    Dim rt As Long  'return variable, indicates success/failure of operation
    
    utaxHistory.AddLine ("Renaming mail box ...")
    strNewMailBoxName = tvwMailBox.SelectedItem.FullPath
   
    'start at position 1, search for delimiter in full pathname of new mailbox name
    '     Delimiter is module level variable
    iPos = InStr(1, strNewMailBoxName, Delimiter)
    'if iPos is greater than zero than Delimiter was found, and iPos indicates position
    '   where it was found
    If iPos > 0 Then
        strNewMailBoxName = Left(strNewMailBoxName, iPos) & NewString
    Else
        strNewMailBoxName = NewString  'delimiter not found in full pathname
    End If
    
    blnPrevBlockMode = utaxIMAP4.BlockingMode  'store blocking mode flag value
    utaxIMAP4.BlockingMode = True  'temporarily set blocking mode to true
    rt = utaxIMAP4.MailBoxRename(tvwMailBox.SelectedItem.FullPath, strNewMailBoxName)
    utaxIMAP4.BlockingMode = blnPrevBlockMode  'reset previous blocking mode
    
    'if mailbox rename unsuccessful then cancel operation and let user know
    '   via the history control
    If rt <> ecSuccess Then
        utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt) & " -- " & utaxIMAP4.GetLastCommandResponseText())
        Cancel = True
    End If
   
End Sub

Private Sub tvwMailBox_Click()
    ' Selects the mail box
    
    Dim rt As Long  'return variable, indicates success/failure
     txtMsgBodyBx.Text = ""
    utaxHistory.AddLine ("Selecting the mailbox ...")
    rt = ecSuccess
    'only proceed if there is a node selected
    If Not tvwMailBox.SelectedItem Is Nothing Then
        rt = utaxIMAP4.MailBoxSelect(tvwMailBox.SelectedItem.FullPath)
        'if MailBoxSelect is not successful then let user know
        '   via history control
        If rt <> ecSuccess Then
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt))
        End If
    End If
    
End Sub


Private Sub mnuMailBoxCreate_Click()
    
    Dim strNewMailBoxName As String  'holds name of new mailbox
    Dim blnPrevBlockMode As Boolean  'stores previous blocking mode
    Dim rt As Long  'return variable, indicates success/failure of operation
    
    'obtain name of mailbox to create from user
    strNewMailBoxName = InputBox("Enter new mail box name..." & vbCrLf _
    & "If you want to create a root mailbox - start it with '\' character.")
    
    'if at least one character was entered then proceed
    If Len(strNewMailBoxName) <> 0 Then
        'check to see if an item is selected or root entry being made
        If tvwMailBox.SelectedItem Is Nothing And Left(strNewMailBoxName, 1) <> "\" Then
            MsgBox "You need to select the mailbox first ..."
        Else
            ' Creating the mail box
            utaxHistory.AddLine ("Creating the mailbox ...")
            
            'store blocking mode, since it must be on when creating new mailbox
            blnPrevBlockMode = utaxIMAP4.BlockingMode
            utaxIMAP4.BlockingMode = True
            'check to see if root entry being created
            If Left(strNewMailBoxName, 1) = "\" Then  'root being made
                rt = utaxIMAP4.MailBoxCreate(Mid(strNewMailBoxName, 1))
            Else
                rt = utaxIMAP4.MailBoxCreate(tvwMailBox.SelectedItem.FullPath + Delimiter + strNewMailBoxName)
            End If
            
            utaxIMAP4.BlockingMode = blnPrevBlockMode 'reset previous blocking mode
            
            'update history control whether it's failed or succeeded
            If rt <> ecSuccess Then
                utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt) & " -- " & utaxIMAP4.GetLastCommandResponseText())
            Else
                utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt) & " -- " & utaxIMAP4.GetLastCommandResponseText())
                Call utaxIMAP4_OnConnect(ecSuccess)
            End If
        End If
    End If
    
End Sub

Private Sub mnuMailBoxDelete_Click()
    
    Dim rt As Long  'return variable, indicates success/failure
    Dim blnPrevBlockMode As Boolean  'stores blocking mode
    
    'check to see if user has selected a node
    If tvwMailBox.SelectedItem Is Nothing Then
        MsgBox "You need to select the mailbox first ..."
    Else
        ' Deleting the mail box
        utaxHistory.AddLine ("Deleting the mailbox ...")
        blnPrevBlockMode = utaxIMAP4.BlockingMode
        utaxIMAP4.BlockingMode = True
        rt = utaxIMAP4.MailBoxDelete(tvwMailBox.SelectedItem.FullPath)
        utaxIMAP4.BlockingMode = blnPrevBlockMode
        
        'update history control according to success/failure of operation
        If rt <> ecSuccess Then
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt) & " -- " & utaxIMAP4.GetLastCommandResponseText())
        Else
            utaxHistory.AddLine (utaxIMAP4.GetErrorText(rt) & " -- " & utaxIMAP4.GetLastCommandResponseText())
            tvwMailBox.Nodes.Remove (tvwMailBox.SelectedItem.Index)  'delete selected node
        End If
    End If
    
End Sub

Private Sub mnuMailBoxRename_Click()
    
    'if user has selected a node then allow operation to proceed
    If tvwMailBox.SelectedItem Is Nothing Then
        MsgBox "You need to select the mailbox first ..."
    Else
        'allow operation to proceed
        tvwMailBox.StartLabelEdit
    End If
    
End Sub


