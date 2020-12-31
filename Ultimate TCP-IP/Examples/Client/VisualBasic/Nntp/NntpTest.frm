VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.4#0"; "UTHistory.dll"
Object = "{ADAD3636-07A3-11D3-A468-0080C858F182}#1.4#0"; "UTNntp.dll"
Begin VB.Form frmMain
   Caption         =   "Dundas TCP/IP NNTP ActiveX Control 4.0 Demo Program"
   ClientHeight    =   8328
   ClientLeft      =   1836
   ClientTop       =   1368
   ClientWidth     =   8832
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   8328
   ScaleWidth      =   8832
   StartUpPosition =   2  'CenterScreen
   Begin UTHISTORYLibCtl.History utaxHistory1
      Height          =   972
      Left            =   120
      OleObjectBlob   =   "NntpTest.frx":0000
      TabIndex        =   11
      Top             =   7320
      Width           =   6972
   End
   Begin VB.CommandButton cmdCmParseNDecode
      Caption         =   "Parse && Decode"
      Height          =   372
      Left            =   7320
      TabIndex        =   10
      Top             =   7440
      Width           =   1452
   End
   Begin VB.TextBox txtMessageBody
      Height          =   3372
      Left            =   4080
      MultiLine       =   -1  'True
      TabIndex        =   9
      ToolTipText     =   "The body of the message as sent by the server"
      Top             =   3840
      Width           =   4692
   End
   Begin VB.TextBox txtHostName
      Height          =   372
      Left            =   1560
      TabIndex        =   7
      Text            =   "msnews.microsoft.com"
      Top             =   120
      Width           =   3852
   End
   Begin VB.TextBox txtTempDirTxt
      Height          =   372
      Left            =   1560
      TabIndex        =   5
      Text            =   "c:\nntpDemo.tmp"
      Top             =   600
      Width           =   3852
   End
   Begin VB.ListBox lstNewsGroupsList
      Height          =   5808
      Left            =   120
      TabIndex        =   4
      ToolTipText     =   "List of the news groups available on the server"
      Top             =   1200
      Width           =   3732
   End
   Begin ComctlLib.ListView lvwArticlesList
      Height          =   2532
      Left            =   4080
      TabIndex        =   3
      ToolTipText     =   "List of articles available on the selected server for the selected news group"
      Top             =   1200
      Width           =   4572
      _ExtentX        =   8065
      _ExtentY        =   4466
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   8
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Article ID"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Subject"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Author"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Date"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   4
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Msg ID"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(6) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   5
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Refer"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(7) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   6
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Lines"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(8) {0713E8C7-850A-101B-AFC0-4210102A8DA7}
         SubItemIndex    =   7
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "Byte count"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.CommandButton cmdExit
      Caption         =   "E&xit"
      Height          =   375
      Left            =   7320
      TabIndex        =   2
      ToolTipText     =   "Exit the Demo Application"
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton cmdClose
      Caption         =   "Cl&ose"
      Height          =   375
      Left            =   6000
      TabIndex        =   1
      ToolTipText     =   "Close Current NNTP Session"
      Top             =   600
      Width           =   1095
   End
   Begin VB.CommandButton cmdConnect
      Caption         =   "Co&nnect"
      Height          =   375
      Left            =   6000
      TabIndex        =   0
      ToolTipText     =   "Connect To NNTP Server"
      Top             =   120
      Width           =   1095
   End
   Begin UTNNTPLibCtl.Nntp utaxNntpControl
      Left            =   7200
      Top             =   600
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   5
      BlockingMode    =   0   'False
      HostName        =   ""
      UserName        =   ""
      Password        =   ""
   End
   Begin VB.Label lblLabel2
      Alignment       =   1  'Right Justify
      Caption         =   "NNTP Server"
      Height          =   252
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   1212
   End
   Begin VB.Label lblLabel1
      Alignment       =   1  'Right Justify
      Caption         =   "Temp file Name"
      Height          =   252
      Left            =   0
      TabIndex        =   6
      Top             =   600
      Width           =   1332
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Option Explicit
Dim lngM_AlertColour As Long  ' hmmm or is it color  ;-)
Dim lngM_ColorGreen As Long
Dim lngM_initHeight As Long '  initial form Height
Dim lngM_initWidth As Long ' initial form width
'The user clicks on an article to read
' we will store the article to a message object then we parse it an display the information
Private Sub lvwArticlesList_DblClick()
 Dim lngRt As Long  'return variable, indicates success/failure

    'test for no article selected
    If lvwArticlesList.SelectedItem.Text = "" Then Exit Sub

     utaxHistory1.AddLine "Getting article ..."

    ' Get the article from the server. The article is specified
    ' by the Unique ID as listed in the group
    ' The article is saved to the file C:\temp.txt
    lngRt = utaxNntpControl.GetArticle(lvwArticlesList.SelectedItem.Text, Trim$(txtTempDirTxt))
    If lngRt <> ecSuccess Then
        utaxHistory1.AddLine utaxNntpControl.GetErrorText(lngRt), lngM_AlertColour
    End If

  
    frmMain.MousePointer = vbHourglass
End Sub

Private Sub cmdClose_Click()
        
    Dim lngRt As Long  'return variable, indicates success/failure of operation
    
    ' Close the connection to the NNTP server
    lngRt = utaxNntpControl.Close()
    
    'if unsuccessful alert user
    If lngRt <> ecSuccess Then
        utaxHistory1.AddLine "***   Error   *** -> " & vbTab & utaxNntpControl.GetErrorText(lngRt), lngM_AlertColour
    End If
      
End Sub

Private Sub cmdConnect_Click()
    
    Dim lngRt As Long  'return variable
    
      If lvwArticlesList.ListItems.Count > 0 Then lvwArticlesList.ListItems.Clear     ' clear the list
      If lstNewsGroupsList.ListCount > 0 Then lstNewsGroupsList.Clear
     utaxHistory1.AddLine "Connecting to " & txtHostName & " ..."
    
    ' Set the host name
    utaxNntpControl.HostName = txtHostName
        
    ' Connect to the NNTP server
    lngRt = utaxNntpControl.Connect()
    
    'alert user if unsuccessful
    If lngRt <> ecSuccess Then
         utaxHistory1.AddLine "***   Error   *** -> " + vbTab + utaxNntpControl.GetErrorText(lngRt), lngM_AlertColour
    End If
    
   
    
End Sub


Private Sub cmdExit_Click()
    
    'unload form
    Unload Me

End Sub


Private Sub Form_Load()
utaxHistory1.AboutBox
utaxNntpControl.AboutBox

 lngM_initHeight = Me.Height
 lngM_initWidth = Me.Width
 lngM_ColorGreen = RGB(0, 200, 0)
 lngM_AlertColour = RGB(200, 0, 0)
 
End Sub

Private Sub Form_Resize()
    Dim lngFormWidth As Long
    Dim lngFormHeight As Long
   
    If Me.WindowState <> vbMinimized Then
    
     'lastly, do not let user undersize the form
    If Me.Width < lngM_initWidth Then
    Me.Width = lngM_initWidth
    Exit Sub
    End If
    
    
    If Me.Height < lngM_initHeight Then
    Me.Height = lngM_initHeight
    Exit Sub
    End If
        
   
    lngFormWidth = Me.ScaleWidth
    lngFormHeight = Me.ScaleHeight
    
     utaxHistory1.Top = lngFormHeight - utaxHistory1.Height
     cmdCmParseNDecode.Top = utaxHistory1.Top
     utaxHistory1.Width = lngFormWidth - cmdCmParseNDecode.Width
     utaxHistory1.Width = utaxHistory1.Width - 200
    cmdCmParseNDecode.Left = utaxHistory1.Left + utaxHistory1.Width + 80
     
    'first, make sure all leftmost controls are aligned
    utaxHistory1.Left = 100
    lstNewsGroupsList.Left = 100
    
    'next, have listview control and frames utilize entire width of form
   ' fraServerInfo.Width = lngFormWidth - 200
    lvwArticlesList.Width = lngFormWidth - lstNewsGroupsList.Width
    lvwArticlesList.Width = lvwArticlesList.Width - 300
    txtMessageBody.Width = lvwArticlesList.Width
        
    'next, have command buttons align to right of frame
    lstNewsGroupsList.Height = lstNewsGroupsList.Height - utaxHistory1.Height - 200
    'adjust the heights of the treeview and listview controls
    lstNewsGroupsList.Height = utaxHistory1.Top - lstNewsGroupsList.Top
    txtMessageBody.Height = lstNewsGroupsList.Height - lvwArticlesList.Height - 200
    End If
    
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release hidden form variable
    Set frmMain = Nothing
        
End Sub


'The user Double clicks on a specified news group
' to initiate a get article list and informations operation
Private Sub lstNewsGroupsList_DblClick()
 Dim lngRt As Long  'return variable
 Dim strSelectedNewsGroup As String
    Dim blnPrevMode As Boolean  'stores current blocking mode
    strSelectedNewsGroup = lstNewsGroupsList.Text
    'error trap for no group selected
    
    If strSelectedNewsGroup = "" Then Exit Sub
    If lvwArticlesList.ListItems.Count > 0 Then lvwArticlesList.ListItems.Clear     ' clear the list
    
    utaxHistory1.AddLine strSelectedNewsGroup & "Setting current News Group ...", lngM_ColorGreen
    
    blnPrevMode = utaxNntpControl.BlockingMode
    utaxNntpControl.BlockingMode = True
    
    ' select the specified newsgroup
    lngRt = utaxNntpControl.SelectNewsGroup(strSelectedNewsGroup)
    
    'restore blocking mode to previous setting
    utaxNntpControl.BlockingMode = blnPrevMode
    
    'if news group could not be selected then alert user
    If lngRt <> ecSuccess Then
        utaxHistory1.AddLine "***   Error   *** -> " & vbTab & utaxNntpControl.GetErrorText(lngRt), lngM_AlertColour
    
    End If
    utaxHistory1.AddLine "Getting articles ...", lngM_ColorGreen
    
    ' Get the list of all articles -- itRequestAll (enumerated constant)
    lngRt = utaxNntpControl.GetArticleList(itRequestAll)
    'if unable to get list then alert user
    If lngRt <> ecSuccess Then
         utaxHistory1.AddLine "***   Error   *** -> " & vbTab & utaxNntpControl.GetErrorText(lngRt)
    End If
    
    
    frmMain.MousePointer = vbHourglass

End Sub

Private Sub utaxNntpControl_OnClose(ByVal Result As Long)
    ' Callback called when the connection to the NNTP server
    ' is closed
    
     utaxHistory1.AddLine "*** Close Conn *** -> " & vbTab & _
    utaxNntpControl.GetErrorText(Result)
   
End Sub

Private Sub utaxNntpControl_OnConnect(ByVal Result As Long)
    ' Callback called when the connection to the NNTP server
    ' is established
    
     utaxHistory1.AddLine "*** Connection *** -> " & vbTab & _
    utaxNntpControl.GetErrorText(Result)
    
    
    If Result = ecSuccess Then
    ' we should be updating the News Group list here
    utaxHistory1.AddLine "receiving News Group List.... this may take few minutes,please wait"
    frmMain.MousePointer = vbHourglass
    utaxNntpControl.GetNewsGroupList itRequestAll
    End If
       
End Sub

Private Sub utaxNntpControl_OnGetArticleList(ByVal Result As Long)
    ' Callback called when the server responds to the "Get list of
    ' all articles" operation.

    ' For the sake of simplicity, instead of dumping all articles here,
    ' we limit the maximum output to twenty. Obviously in a real
    ' application one would want to output the entire list to the user.

    Dim lngMaxArticles As Long  'we are setting a maximum number of articles to return
    Dim lngMaxIndex As Long
    Dim lngIndex As Long
    lvwArticlesList.ListItems.Clear ' clear the list
    Dim itmX As ListItem  'listitem object
    Dim blnPrevMode As Boolean  'stores current blocking mode
    'if articles were retreived successfully output to user
    If Result = ecSuccess Then
    blnPrevMode = utaxNntpControl.BlockingMode
    utaxNntpControl.BlockingMode = True
        utaxNntpControl.ResetArticleInfoEnum
         
         Dim errcode As Long
         errcode = 0
        lngMaxIndex = utaxNntpControl.NewsGroupCount
        For lngIndex = 0 To lngMaxIndex
            errcode = utaxNntpControl.EnumArticleInfo()
            If errcode <> ecSuccess Then Exit For
            
            Set itmX = lvwArticlesList.ListItems.Add()  'add listitem
            itmX.Text = utaxNntpControl.ArticleInfo_ID  ' Article ID ' count
            'Note: hfSubject is enumerated constant of MsgHeaderFields
            'set new listitem properties
            itmX.SubItems(1) = utaxNntpControl.ArticleInfo_Subject
            itmX.SubItems(2) = utaxNntpControl.ArticleInfo_Author
            itmX.SubItems(3) = utaxNntpControl.ArticleInfo_Date
            itmX.SubItems(4) = utaxNntpControl.ArticleInfo_MsgID
            itmX.SubItems(5) = utaxNntpControl.ArticleInfo_Refer
            itmX.SubItems(6) = utaxNntpControl.ArticleInfo_LineCount
            itmX.SubItems(7) = utaxNntpControl.ArticleInfo_ByteCount
            lngIndex = lngIndex + 1
             utaxHistory1.AddLine vbTab & utaxNntpControl.GetNewsGroupTitle(lngIndex)
        Next
        utaxNntpControl.BlockingMode = blnPrevMode
    Else
        'else output error to user
         utaxHistory1.AddLine "*** Get Article *** -> " & _
        vbTab & utaxNntpControl.GetErrorText(Result)
    End If
    frmMain.MousePointer = vbNormal

End Sub

Private Sub utaxNntpControl_OnGetArticle(ByVal Result As Long)
    ' Callback called when an article is ready to be read
    ' from the server

    Dim A As String 'temp string variable freefile
    Dim intFileNum As Integer  'next free file number
    Dim tempFileName As String

    'test results param for errors
    If Result <> 0 Then
         utaxHistory1.AddLine utaxNntpControl.GetErrorText(Result), lngM_AlertColour
        frmMain.MousePointer = vbNormal
        Exit Sub
    End If
'
'    'get next file number
    intFileNum = FreeFile
    txtMessageBody.Text = " "
    ' output the article body
    
    Open Trim$(txtTempDirTxt) For Input As #intFileNum   ' Open file.
    While Not EOF(1)                      ' EOF?
        Line Input #intFileNum, A                   ' No, read next line.
        txtMessageBody = txtMessageBody & A & vbCrLf
    Wend                                  ' Repeat until end of file.
    Close #intFileNum

     utaxHistory1.AddLine "*** Get Article *** -> " & _
    vbTab & utaxNntpControl.GetErrorText(Result)
    frmMain.MousePointer = vbNormal

End Sub

Private Sub utaxNntpControl_OnGetNewsGroupList(ByVal Result As Long)
    ' Get the list of newsgroups. Limit the output to twenty lines
    ' (again, for simplicity)
    lstNewsGroupsList.Clear   'clear list box
    frmMain.MousePointer = vbHourglass
    Dim MaxIndex As Long  'total number of news groups
    Dim index As Long  'for loop counter
    Dim itmX As ListItem  'listitem object
    Dim x As Long
    x = 0
    If Result = ecSuccess Then
    index = utaxNntpControl.NewsGroupCount
    For x = 0 To index
       lstNewsGroupsList.AddItem utaxNntpControl.GetNewsGroupTitle(x)
     Next x
    Else
        'indicate failure to user
         utaxHistory1.AddLine "*** Get News Groups *** -> " & _
        vbTab & utaxNntpControl.GetErrorText(Result)
    End If
    frmMain.MousePointer = vbNormal

End Sub


Private Sub utaxNntpControl_OnSelectNewsGroup(ByVal Result As Long)
     utaxHistory1.AddLine "News Goup Selected"
End Sub

Private Sub cmdCmParseNDecode_Click()
frmPostNDecode.Show vbModal
End Sub
