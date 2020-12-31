VERSION 5.00
Object = "{8FAB3686-0EBF-11D3-A46F-0080C858F182}#1.4#0"; "UTHistory.dll"
Object = "{7C303390-06E5-11D3-A467-0080C858F182}#1.4#0"; "UTFtp.dll"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmForm1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Dundas TCP/IP v4.0 ActiveX FTP Client Demo"
   ClientHeight    =   7272
   ClientLeft      =   2280
   ClientTop       =   576
   ClientWidth     =   7008
   FillColor       =   &H00FF0000&
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   7272
   ScaleWidth      =   7008
   Begin UTHISTORYLibCtl.History utaxHistory1 
      Height          =   1452
      Left            =   120
      OleObjectBlob   =   "FtpTest.frx":0000
      TabIndex        =   25
      Top             =   5040
      Width           =   6732
   End
   Begin VB.CommandButton cmdCdUp 
      Caption         =   "CDUP"
      DisabledPicture =   "FtpTest.frx":0086
      DownPicture     =   "FtpTest.frx":0190
      Height          =   315
      Left            =   5340
      Picture         =   "FtpTest.frx":029A
      TabIndex        =   22
      Top             =   2280
      Width           =   1575
   End
   Begin VB.CommandButton cmdCancelFiletransferCmd 
      Caption         =   "&Cancel Transfer"
      Height          =   315
      Left            =   5340
      TabIndex        =   12
      Top             =   4320
      Width           =   1575
   End
   Begin VB.CommandButton cmdCommand1 
      Caption         =   "E&xit"
      Height          =   315
      Left            =   5340
      TabIndex        =   13
      Top             =   4680
      Width           =   1575
   End
   Begin VB.TextBox txtHelpFor 
      Height          =   330
      Left            =   1080
      TabIndex        =   5
      Text            =   "HELP"
      Top             =   1212
      Width           =   3960
   End
   Begin VB.CommandButton cmdHelp 
      Caption         =   "<-Get cmdHelp for"
      Height          =   315
      Left            =   5340
      TabIndex        =   6
      Top             =   1200
      Width           =   1575
   End
   Begin VB.TextBox txtTextQuoteLine 
      Height          =   330
      Left            =   1080
      TabIndex        =   7
      Text            =   "NOOP"
      Top             =   1680
      Width           =   3912
   End
   Begin VB.TextBox txtHost 
      Height          =   330
      Left            =   1080
      TabIndex        =   0
      Text            =   "ftp.microsoft.com"
      Top             =   180
      Width           =   3912
   End
   Begin VB.CommandButton cmdSndQuote 
      Caption         =   "Snd. Quote"
      Height          =   315
      Left            =   5340
      TabIndex        =   8
      Top             =   1680
      Width           =   1575
   End
   Begin VB.TextBox txtPassword 
      Height          =   330
      Left            =   3840
      TabIndex        =   2
      Text            =   "yourEmail@yourEmail.com"
      Top             =   600
      Width           =   1188
   End
   Begin VB.TextBox txtText2 
      Height          =   330
      Left            =   1080
      TabIndex        =   1
      Text            =   "anonymous"
      Top             =   600
      Width           =   1188
   End
   Begin VB.CommandButton cmdMKDIR 
      Caption         =   "Make Dir"
      DownPicture     =   "FtpTest.frx":03F6
      DragIcon        =   "FtpTest.frx":0552
      Height          =   315
      Left            =   5340
      Picture         =   "FtpTest.frx":0994
      TabIndex        =   10
      Top             =   3000
      Width           =   1575
   End
   Begin ComctlLib.ProgressBar pbrProg1 
      Height          =   252
      Left            =   1080
      TabIndex        =   15
      Top             =   4320
      Width           =   4092
      _ExtentX        =   7218
      _ExtentY        =   445
      _Version        =   327682
      Appearance      =   1
   End
   Begin MSComDlg.CommonDialog dlgComDlg 
      Left            =   0
      Top             =   4440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "*.*"
      DialogTitle     =   "Down Load /Upload file"
      MaxFileSize     =   9999
   End
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send File..."
      Height          =   315
      Left            =   5340
      TabIndex        =   9
      Top             =   2640
      Width           =   1575
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   315
      Left            =   5340
      TabIndex        =   4
      Top             =   600
      Width           =   1575
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   315
      Left            =   5340
      TabIndex        =   3
      Top             =   195
      Width           =   1575
   End
   Begin ComctlLib.TreeView tvwTreeV 
      Height          =   1860
      Left            =   1080
      TabIndex        =   11
      Top             =   2280
      Width           =   4092
      _ExtentX        =   7218
      _ExtentY        =   3281
      _Version        =   327682
      HideSelection   =   0   'False
      Indentation     =   0
      LabelEdit       =   1
      LineStyle       =   1
      Style           =   7
      Appearance      =   1
   End
   Begin VB.Label Label1 
      Caption         =   "Server Response"
      Height          =   372
      Left            =   0
      TabIndex        =   26
      Top             =   4560
      Width           =   852
   End
   Begin UTFTPLibCtl.Ftp utaxControl 
      Left            =   5280
      Top             =   3480
      ConnectTimeOut  =   5
      BlockingMode    =   0   'False
      FireWallMode    =   0   'False
      HostName        =   ""
      UserName        =   "anonymous"
      Password        =   "anonymous@anonymous.com"
      Account         =   ""
   End
   Begin VB.Label lblLabel8 
      Caption         =   "File Info :"
      Height          =   372
      Left            =   360
      TabIndex        =   24
      Top             =   6600
      Width           =   732
   End
   Begin VB.Label lblStatus 
      BackColor       =   &H80000013&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00FF0000&
      Height          =   612
      Left            =   1200
      TabIndex        =   23
      Top             =   6600
      Width           =   5652
   End
   Begin VB.Label lblLabel5 
      AutoSize        =   -1  'True
      Caption         =   "Help:"
      Height          =   192
      Left            =   600
      TabIndex        =   21
      Top             =   1236
      Width           =   372
   End
   Begin VB.Label lblLabel2 
      Caption         =   "Quote Command"
      Height          =   372
      Left            =   120
      TabIndex        =   20
      Top             =   1680
      Width           =   732
   End
   Begin VB.Label lblLabel7 
      AutoSize        =   -1  'True
      Caption         =   "User"
      Height          =   195
      Left            =   600
      TabIndex        =   19
      Top             =   600
      Width           =   330
   End
   Begin VB.Label lblLabel6 
      AutoSize        =   -1  'True
      Caption         =   "Password:"
      Height          =   195
      Left            =   3000
      TabIndex        =   18
      Top             =   600
      Width           =   735
   End
   Begin VB.Label lblLabel4 
      Caption         =   "To Download a file simply double click on it's icon and select where to save to!"
      ForeColor       =   &H00FF0000&
      Height          =   2100
      Left            =   120
      TabIndex        =   17
      Top             =   2400
      Width           =   852
   End
   Begin VB.Label lblLabel3 
      ForeColor       =   &H000000FF&
      Height          =   312
      Left            =   1080
      TabIndex        =   16
      Top             =   4680
      Width           =   4092
   End
   Begin VB.Label lblLabel1 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Server txtHost"
      Height          =   195
      Left            =   120
      TabIndex        =   14
      Top             =   240
      Width           =   840
   End
   Begin ComctlLib.ImageList imlImageList1 
      Left            =   0
      Top             =   3720
      _ExtentX        =   995
      _ExtentY        =   995
      BackColor       =   -2147483643
      ImageWidth      =   18
      ImageHeight     =   14
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "FtpTest.frx":0A9E
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "FtpTest.frx":0BD8
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "FtpTest.frx":0D36
            Key             =   ""
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmForm1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' =================================================================
'  Dundas TCP/IP FTP ActiveX Control Demo
'
' ===================================================================
' Dundas TCP/IP v4.0
' Copyright © Dundas Software 1995-2001, all rights reserved
' ===================================================================
Dim DipsBytes As Long
Dim CancelFiletransfer As Long

Private Sub cmdCancelFiletransferCmd_Click()
    ' User clicked the cancel button; close the Current connnection.
    ' To cancel any in progress operation we set the cancel flag to 0
    ' this flag is checked by the on SendFileProgress and OnReceiveFile
    ' progress events of the control
    CancelFiletransfer = 0
End Sub

Private Sub cmdCdUp_Click()
    ' Change directory to the parent directory
    tvwTreeV.Nodes.Clear
    lblStatus.Caption = " "
          
    utaxControl.CdUp
   
End Sub

Private Sub cmdClose_Click()
    ' close the Current connnection
    utaxControl.Close
    tvwTreeV.Nodes.Clear
    lblLabel3 = "Connection was closed"
    lblStatus.Caption = " "
     cmdHelp.Enabled = False
     Me.cmdCdUp.Enabled = False
     Me.cmdMKDIR.Enabled = False
     Me.cmdSndQuote.Enabled = False
     Me.cmdCommand1.Enabled = False
     cmdCancelFiletransferCmd.Enabled = False
    Me.cmdSend.Enabled = False
    End Sub
     
Private Sub cmdSndQuote_Click()
utaxControl.Quote txtTextQuoteLine

End Sub

Private Sub cmdCommand1_Click()
    ' User clicked the Exit button. Close any active connection
    ' then terminate the program
    utaxControl.Close
    End
End Sub

Private Sub txtHost_Change()
If txtHost.Text = "" Then
    cmdConnect.Enabled = False
    Else
    cmdConnect.Enabled = True
    End If
    
End Sub

Private Sub utaxControl_OnCdUp(ByVal Result As Long)
 
 ShowServerResponse
 If Result = ecSuccess Then
        lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(Result)
        DirList
    Else
         Beep
        lblLabel3.Caption = "Error: " + utaxControl.GetErrorText(Result)
        Beep
    End If
End Sub

Private Sub utaxControl_OnChDir(ByVal Result As Long)
    DirList
    ShowServerResponse
    lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(retcode)
End Sub

Private Sub utaxControl_OnConnect(ByVal Result As Long)
    ' This event is firted upon returning from the connect attempt
    ' Return code of 0 is successful otherwise use the GetErrorText
    ' method to report errors
    ShowServerResponse
    frmForm1.MousePointer = vbDefault
    If (Result = ecSuccess) Then
          cmdHelp.Enabled = True
          Me.cmdCdUp.Enabled = True
          Me.cmdMKDIR.Enabled = True
          Me.cmdSndQuote.Enabled = True
          Me.cmdCommand1.Enabled = True
          Me.cmdSend.Enabled = True
          cmdCancelFiletransferCmd.Enabled = True
        lblLabel3.Caption = "Result: Connected Receiving Directory Listing "
        DirList
        Else
        lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(Result)
          cmdHelp.Enabled = False
          Me.cmdCdUp.Enabled = False
          Me.cmdMKDIR.Enabled = False
          Me.cmdSndQuote.Enabled = False
          Me.cmdCommand1.Enabled = False
          Me.cmdSend.Enabled = False
          cmdCancelFiletransferCmd.Enabled = False
  End If
  
    
    
    Beep
End Sub

Private Sub utaxControl_OnGetCurDir(ByVal Result As Long, ByVal Directory As String)
 '   Label9.Caption = "Current Directory:" + Directory + Chr$(13) + Chr$(10)
    lblLabel3.Caption = "Result: retrieving Directory Listing"
    utaxControl.GetDirInfo
    ShowServerResponse
End Sub

Private Sub utaxControl_OnGetDirInfo(ByVal Result As Long)
    ' add each directory to the tree control
    utaxControl.ResetDirEntryEnum
    While (utaxControl.EnumDirEntry = ecSuccess)
        If utaxControl.DirEntryIsDir Then
            tvwTreeV.Nodes.Add , , , utaxControl.DirEntryName, 1, 1
        Else
            tvwTreeV.Nodes.Add , , , utaxControl.DirEntryName, 2, 2
        End If
    Wend
        
    frmForm1.MousePointer = vbDefault
    lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(Result)
End Sub

Private Sub utaxControl_OnGetHelp(ByVal Result As Long)
     ShowServerResponse
End Sub

Private Sub utaxControl_OnMkDir(ByVal Result As Long)
 If Result = ecSuccess Then
            MsgBox ("The directory was successfully created")
        Else
            Beep
            lblLabel3.Caption = "Error " + utaxControl.GetErrorText(Result)
            Beep
       
        End If
        ShowServerResponse
        frmForm1.MousePointer = vbDefault
End Sub

Private Sub utaxControl_OnQuote(ByVal Result As Long)
ShowServerResponse
End Sub

Private Sub utaxControl_OnReceiveFile(ByVal Result As Long)
    ' this event is fired upon returning from a receive attempt
    ' Return code of 0 is successful otherwise use GetErrorText
    ' method to report errors
      ShowServerResponse
      If Result = ecSuccess Then
      pbrProg1.Value = pbrProg1.Max
        MsgBox "Download Completed"
        lblLabel3.Caption = "Successfully downloaded " + Str(DipsBytes) + " bytes"
        Else
        MsgBox utaxControl.GetErrorText(Result)
    End If
    Beep
    lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(Result)
    Beep
    CancelFiletransfer = 0
 
End Sub

Private Sub utaxControl_OnReceiveStatus(ByVal BytesReceived As Long)
 pbrProg1.Min = 0 ' set the minimum size of the progress bar
    pbrProg1.Max = 100
    
    If pbrProg1.Value >= 99 Then
        pbrProg1.Value = 0
    End If
    ' this event is fired for each block of bytes received to
    ' check if the user is asking us to cancel
    
    ' To cancel the receive set the cancel parameter to 0
    Cancel = CancelFiletransfer
    If CancelFiletransfer <> 0 Then
        lblLabel3.Caption = "Received " + Str(BytesReceived) + " bytes"
    End If
    pbrProg1.Value = pbrProg1.Value + 1 '
End Sub

Private Sub utaxControl_OnSendFile(ByVal Result As Long)
    
    ' this event is fired upon returning from a send attempt
    ' Return code of 0 is successful otherwise use GetErrorText
    ' method to report errors
    ShowServerResponse
    If (Result = ecSuccess) Then
        
    
        MsgBox "Send Completed"
            lblLabel3.Caption = "Successfully uploaded " + Str(DipsBytes) + " bytes"
            Else
            MsgBox utaxControl.GetErrorText(Result)
    End If
    Beep
    lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(Result)
    Beep
    CancelFiletransfer = 0
    utaxHistory1.AddLine "Send finished " & utaxControl.GetErrorText(Result)

End Sub

Private Sub utaxControl_OnSendStatus(ByVal BytesSend As Long)
    ' this event is fired upon for each bloack of bytes Sent to
    ' check if the user is asking us to cancel
    ' To cancel the send attempt set the cancel parameter to 0
    inprogress = True
    pbrProg1.Min = 0 ' set the minimum size of the progress bar
    pbrProg1.Max = 100
    
    If pbrProg1.Value >= 99 Then
        pbrProg1.Value = 0
    End If
    
    pbrProg1.Value = pbrProg1.Value + 1 ' Update the progress bar value
    Cancel = CancelFiletransfer
    DipsBytes = DipsBytes + bytesSent
    lblLabel3.Caption = "Sent " + Str(DipsBytes) + "bytes"
End Sub




Private Sub cmdMKDIR_Click()
    ' Prompt the user for the name of a new directory and
    ' attempt to create it on the remote host. Display
    ' any error(s) that may occur.
    newdir = InputBox("Specify the name of the directory to create:", "Please choose a new directory name")
    
    If (newdir <> "") Then
        frmForm1.MousePointer = vbHourglass
        utaxControl.MkDir (newdir)
       
    End If
    
    
     
End Sub

Private Sub cmdConnect_Click()
    ' Setup the user interface components (tree, list box)
    ' and initialize the FTP control.
    tvwTreeV.Nodes.Clear
    utaxControl.UserName = txtText2.Text
    utaxControl.UserPassword = txtPassword.Text
    utaxControl.HostName = txtHost.Text
    lblStatus.Caption = " "
    lblLabel3.Caption = "Result: connecting to server"
    utaxControl.Connect ' Connect to the remote host
    DipsBytes = 0
    frmForm1.MousePointer = vbHourglass
End Sub

Private Sub Form_Load()
utaxControl.AboutBox
    ' initialize
    tvwTreeV.ImageList = imlImageList1
    DipsBytes = 0
    
    'we will set the default as to go in passive mode
    ' so we will set the Firewall maode to true
    utaxControl.FireWallMode = True
    cmdHelp.Enabled = False
    Me.cmdCdUp.Enabled = False
    Me.cmdMKDIR.Enabled = False
    Me.cmdSndQuote.Enabled = False
    Me.cmdCommand1.Enabled = False
    Me.cmdSend.Enabled = False
    cmdCancelFiletransferCmd.Enabled = False
End Sub

Private Sub DirList()
    ' List the directory information of the current directory
    frmForm1.MousePointer = vbHourglass
    tvwTreeV.Nodes.Clear
    utaxControl.GetCurDir
End Sub

Private Sub cmdHelp_Click()
     ' You may select a help string to get the syntax for
    ' This may not be implemnet by all FTP serevrs
     retcode = utaxControl.GetHelp(txtHelpFor.Text)
    If retcode = ecSuccess Then
        pbrProg1.Value = 0
    
    End If
    Beep
    lblLabel3.Caption = "Result: " + utaxControl.GetErrorText(retcode)
    Beep
End Sub


Private Sub cmdSend_Click()
    ' The user clicked  the send button
    ' This sub will call open dialog to allow the
    ' user to select a file to send
    ' I have not set the progress bar to the size
    ' of the file if you like you can do that and set
    ' its value to the bytes sent in OnSendFileProgress
    pbrProg1.Value = 0
    DipsBytes = 0
    CancelFiletransfer = 1
    dlgComDlg.CancelError = True
    On Error GoTo errhandler
    
    dlgComDlg.ShowOpen
    
    pbrProg1.Value = 0
    pbrProg1.Min = 0 ' set the minimum size of the progress bar
    
    Open dlgComDlg.FileName For Input As #1 ' Close before reopening in another mode.
        pbrProg1.Max = LOF(1) ' get the length of the file
    Close #1
    
    utaxControl.SendFile dlgComDlg.FileName, dlgComDlg.FileTitle
    Exit Sub
errhandler:
End Sub

Private Sub tvwTreeV_DblClick()
    ' Change directory or Download file
    Dim selectedItem As Node
    pbrProg1.Value = 0
    DipsBytes = 0
    CancelFiletransfer = 1
    If tvwTreeV.Nodes.Count > 0 Then
        ' enumerate through the list of all files until the
        ' selected file (or directory) is reached
        utaxControl.ResetDirEntryEnum
        Set selectedItem = tvwTreeV.selectedItem
        ' in case the user just clicks on a space which is not trapped as selection
        
        On Error GoTo errhandler
        
        For j = 0 To tvwTreeV.selectedItem.Index - 1
              utaxControl.EnumDirEntry
        Next j

          If utaxControl.DirEntryIsDir Then
            
            ' This item is a directory. Change into the directory and
            ' list all the files
            res = utaxControl.ChDir(tvwTreeV.selectedItem.Text)
        Else
            ' user wants to download a file
            dlgComDlg.CancelError = True
            On Error GoTo errhandler
            pbrProg1.Value = 0
            pbrProg1.Min = 0 ' set the minimum size of the progress bar
            pbrProg1.Max = utaxControl.DirEntrySize
            ' set the default name of the new file to the file being downloaded
            dlgComDlg.FileName = tvwTreeV.selectedItem.Text
            dlgComDlg.ShowSave
            
            ' save the selected file to the name entered by the user
            utaxControl.ReceiveFile tvwTreeV.selectedItem.Text, dlgComDlg.FileName
        End If
    End If
    Exit Sub
errhandler:
End Sub


' Update The history control with the server response
Sub ShowServerResponse()
Counter = 0
 While utaxControl.GetMultilineResponse(Counter) <> ""
    utaxHistory1.AddLine utaxControl.GetMultilineResponse(Counter)
    Counter = Counter + 1
    Wend
End Sub

' When the user selects a node lets diplay the information for that file
'
Private Sub tvwTreeV_NodeClick(ByVal Node As ComctlLib.Node)
  ' reset the counter
   utaxControl.ResetDirEntryEnum
   ' lets fast forward the index to the one selected by the user
   For j = 0 To tvwTreeV.selectedItem.Index - 1
              utaxControl.EnumDirEntry
   Next j
   ' now display the information
   lblStatus.Caption = "Name " & utaxControl.DirEntryName & Chr(10)
   
   ' if the selected node is a directory then
   ' let's tell the user it is a directory otherwise
   ' lets display the size
   If utaxControl.DirEntryIsDir Then
  lblStatus.Caption = lblStatus.Caption & "Directory" & Chr(10)
  Else
  lblStatus.Caption = lblStatus.Caption & "Size " & utaxControl.DirEntrySize & " Bytes" & Chr(10)
  End If
  ' let's display the date and time of the file or directory
  lblStatus.Caption = lblStatus.Caption & "Date: " & utaxControl.DirEntryYear & "/" & utaxControl.DirEntryMonth & "/" & utaxControl.DirEntryDay & _
    "    Time: " & utaxControl.DirEntryHour & ":"
    If utaxControl.DirEntryMinute > 9 Then
    lblStatus.Caption = lblStatus.Caption & utaxControl.DirEntryMinute
    Else
     lblStatus.Caption = lblStatus.Caption & "0" & utaxControl.DirEntryMinute
    
    End If
    
    

End Sub
' End  of Demo Program
'///////////////////////////////////////////GW

