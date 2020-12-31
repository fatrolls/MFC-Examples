VERSION 5.00
Object = "{E1F1FA1C-047D-11D3-A466-0080C858F182}#1.4#0"; "UTHttp.dll"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Dundas TCP/IP  HTTP Client ActiveX Control 4.0 -  Demo Program"
   ClientHeight    =   7248
   ClientLeft      =   1080
   ClientTop       =   5568
   ClientWidth     =   9696
   ClipControls    =   0   'False
   Icon            =   "HttpTest.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7248
   ScaleWidth      =   9696
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtHeaders 
      Height          =   1452
      Left            =   4560
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   19
      Top             =   1680
      Width           =   4332
   End
   Begin VB.ListBox lstLinkTags 
      Height          =   1200
      Left            =   1200
      TabIndex        =   15
      Top             =   1740
      Width           =   3132
   End
   Begin VB.CommandButton cmdGet 
      Caption         =   "&GET"
      Height          =   375
      Left            =   7245
      TabIndex        =   10
      ToolTipText     =   "Retrieve Specified Web Page "
      Top             =   592
      Width           =   1095
   End
   Begin VB.CommandButton cmdHead 
      Caption         =   "&HEAD"
      Default         =   -1  'True
      Height          =   375
      Left            =   7245
      TabIndex        =   9
      ToolTipText     =   "Retrieve Headers from Web Page"
      Top             =   105
      Width           =   1095
   End
   Begin VB.CommandButton cmdPut 
      Caption         =   "&PUT"
      Height          =   375
      Left            =   7245
      TabIndex        =   11
      ToolTipText     =   "Send File Specified by File Name Textbox to Web Server"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   8520
      TabIndex        =   14
      ToolTipText     =   "Exit Demo Application"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.TextBox txtFileName 
      Height          =   320
      Left            =   1080
      TabIndex        =   7
      Top             =   1080
      Width           =   5370
   End
   Begin VB.CommandButton cmdDeleteFile 
      Caption         =   "&Delete File"
      Height          =   375
      Left            =   8550
      TabIndex        =   12
      ToolTipText     =   "Delete File From Server"
      Top             =   105
      Width           =   1095
   End
   Begin VB.TextBox txtCustom 
      Height          =   320
      Left            =   1050
      TabIndex        =   3
      Text            =   "OPTIONS"
      Top             =   660
      Width           =   1095
   End
   Begin VB.CommandButton cmdCustom 
      Caption         =   "Com&mand"
      Height          =   375
      Left            =   8550
      TabIndex        =   13
      ToolTipText     =   "Execute Custom Command (in Command textbox)"
      Top             =   592
      Width           =   1095
   End
   Begin VB.TextBox txtData 
      Height          =   320
      Left            =   3195
      TabIndex        =   5
      Top             =   660
      Width           =   3255
   End
   Begin VB.TextBox txtResults 
      Height          =   3816
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   8
      Top             =   3360
      Width           =   9492
   End
   Begin VB.TextBox txtUrl 
      Height          =   320
      Left            =   1065
      TabIndex        =   1
      Text            =   "http://www.w3.org/"
      Top             =   135
      Width           =   5385
   End
   Begin UTHTTPLibCtl.Http ctrlHttp1 
      Left            =   6600
      Top             =   1080
      ConnectTimeOut  =   5
      MaxLinesToStore =   16000
      BlockingMode    =   0   'False
      ProxyServer     =   ""
   End
   Begin VB.Label lblLabel3 
      Caption         =   "Headers"
      ForeColor       =   &H00FF0000&
      Height          =   252
      Left            =   4560
      TabIndex        =   18
      Top             =   1440
      Width           =   732
   End
   Begin VB.Label lblLabel2 
      Caption         =   "Body"
      ForeColor       =   &H00FF0000&
      Height          =   252
      Left            =   120
      TabIndex        =   17
      Top             =   3000
      Width           =   852
   End
   Begin VB.Label lblLabel1 
      Caption         =   "Page Links"
      ForeColor       =   &H00FF0000&
      Height          =   252
      Left            =   1200
      TabIndex        =   16
      Top             =   1440
      Width           =   852
   End
   Begin VB.Label lblFileName 
      Caption         =   "&File Name:"
      Height          =   252
      Left            =   108
      TabIndex        =   6
      ToolTipText     =   "File to be Sent to Server with PUT Command"
      Top             =   1080
      Width           =   900
   End
   Begin VB.Label lblCustom 
      Caption         =   "&Command:"
      Height          =   255
      Left            =   105
      TabIndex        =   2
      ToolTipText     =   "Any Valid Command Not Included with TCP/IP 3.0"
      Top             =   690
      Width           =   870
   End
   Begin VB.Label lblData 
      Alignment       =   1  'Right Justify
      Caption         =   "Data:"
      Height          =   255
      Left            =   2520
      TabIndex        =   4
      ToolTipText     =   "Any Data Which Might be Needed for Custom Command"
      Top             =   690
      Width           =   420
   End
   Begin VB.Label lblUrl 
      Caption         =   "&URL:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      ToolTipText     =   "Target Url"
      Top             =   165
      Width           =   540
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
    ' Updated:
    '       Monday, May 7th 2001
    ' ===================================================================
    '
    Option Explicit
    
    Private Sub cmdCustom_Click()
        
        Dim rt As Long  'return variable
         txtHeaders.Text = ""
        txtResults = "Waiting for result ..."
         txtHeaders.Text = ""
        ' Clear received data and send header tags before executing
        ' next command
        ctrlHttp1.ClearReceivedData
        ctrlHttp1.ClearSendHeaderTags
        rt = ctrlHttp1.AddSendHeaderTag("Content-Length: " & Str(Len(txtData)))
        rt = ctrlHttp1.AddSendHeaderTag("Content-Type: Application/x-www-form-urlencoded")
            
        ' Execute the command
        rt = ctrlHttp1.CommandLine(txtCustom, txtUrl, txtData)
        
        ' Check result
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & ctrlHttp1.GetErrorText(rt)
        End If
    
    End Sub
    
    Private Sub cmdDeleteFile_Click()
        Dim rt As Long  'return variable
        
        txtResults = "Deleting file ..."
         txtHeaders.Text = ""
        ' Delete the file from the server
        rt = ctrlHttp1.DeleteFile(txtUrl)
        
        ' Check result
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & ctrlHttp1.GetErrorText(rt)
        End If
        
    End Sub
    
    Private Sub cmdExit_Click()
        
        'exit app
        Unload Me
        
    End Sub
    
    Private Sub cmdGet_Click()
         Me.cmdCustom.Enabled = False
        Me.cmdDeleteFile.Enabled = False
        Me.cmdGet.Enabled = False
        Me.cmdHead.Enabled = False
        Me.cmdPut.Enabled = False
        Dim rt As Long  'return variable
         txtHeaders.Text = ""
        txtResults = "Waiting for result ..."
        
        ' "GET" the specified web page
        rt = ctrlHttp1.GET(txtUrl)
        ' Check the result
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & ctrlHttp1.GetErrorText(rt)
        End If
        
    End Sub
    
    Private Sub cmdHead_Click()
        
        Dim rt As Long  'return variable
        txtHeaders.Text = ""
        txtResults = "Waiting for result ..."
        
        
        Me.cmdCustom.Enabled = False
        Me.cmdDeleteFile.Enabled = False
        Me.cmdGet.Enabled = False
        Me.cmdHead.Enabled = False
        Me.cmdPut.Enabled = False
        
        ' "HEAD" the specified web page -- get the headers
        rt = ctrlHttp1.HEAD(txtUrl)
        
        ' Check the result
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & ctrlHttp1.GetErrorText(rt)
        End If
        
    End Sub
    
Private Sub Form_Load()
ctrlHttp1.AboutBox
End Sub

    Private Sub Form_Resize()
        'need resizing routine for controls
        
    '    ' lets not apply this routine if we are minimizing
    '    If Me.ScaleHeight = 0 Then Exit Sub
    '
    '    If Me.Height < 4000 Then
    '    Me.Height = 5000
    '    End If
    '    If Me.Width < 9000 Then
    '    Me.Width = 9000
    '    End If
    '
    '    Dim lngFormWidth As Long  'stores scalewidth of form
    '    lngFormWidth = Me.ScaleWidth
    '
    '    'first, align leftmost edges of left controls
    '    lblUrl.Left = 80
    '    lblCustom.Left = 80
    '    lblFileName.Left = 80
    '    txtResults.Left = 80
    '
    '    'next, align rightmost controls
    '    cmdDeleteFile.Left = lngFormWidth - 1175
    '    cmdCustom.Left = lngFormWidth - 1175
    '    cmdExit.Left = lngFormWidth - 1175
    '    cmdHead.Left = lngFormWidth - 2400
    '    cmdGet.Left = lngFormWidth - 2400
    '    cmdPut.Left = lngFormWidth - 2400
    '
    '    'next, adjust width of txtResults
    '    txtResults.Width = lngFormWidth - 160
    '    linkTags.Width = txtResults.Width
    '    'lastly, adjust height of txtResults
    '    txtResults.Height = Me.Height - 4000
           
        
    End Sub
    


    Private Sub ctrlHttp1_OnCommandLine(ByVal Result As Long)
        
        ' Call Http1_OnGet to display the output
        ' to the edit window
        ctrlHttp1_OnGET (Result)
        
    End Sub
    
    Private Sub ctrlHttp1_OnDeleteFile(ByVal Result As Long)
        
        ' Call Http1_OnGet to display the output
        ' to the edit window
        ctrlHttp1_OnGET (Result)
        
    End Sub
    
    Private Sub ctrlHttp1_OnGET(ByVal Result As Long)
        
        Dim Index As Long  'for loop counter
        
        txtResults = ""
            
        ' Clear the result text window and output the
        ' reponse from the server
        ctrlHttp1.ClearSendHeaderTags
        If Result = ecSuccess Then
            For Index = 0 To ctrlHttp1.BodyLineCount - 1
                txtResults = txtResults & vbCrLf & ctrlHttp1.GetBodyLine(Index)
            Next
        Else
            txtResults = txtResults & vbCrLf + "--- " & ctrlHttp1.GetErrorText(Result) & " ---"
        End If
        lstLinkTags.Clear
        txtHeaders = ""
         For Index = 0 To ctrlHttp1.HeaderLineCount - 1
                txtHeaders = txtHeaders & ctrlHttp1.GetHeaderLine(Index) & vbCrLf
            Next
        For Index = 0 To ctrlHttp1.LinkTagCount - 1
        lstLinkTags.AddItem ctrlHttp1.GetLinkTag(Index)
        Next Index
        
        '
           Me.cmdCustom.Enabled = True
        Me.cmdDeleteFile.Enabled = True
        Me.cmdGet.Enabled = True
        Me.cmdHead.Enabled = True
        Me.cmdPut.Enabled = True
        
    End Sub
    
    Private Sub ctrlHttp1_OnHEAD(ByVal Result As Long)
        
        Dim Index As Long  'for loop counter
        
        txtResults = ""
        
        ' Clear the result text window and output the
        ' reponse from the server
        ctrlHttp1.ClearSendHeaderTags
        If Result = ecSuccess Then
            For Index = 0 To ctrlHttp1.HeaderLineCount - 1
                txtHeaders = txtHeaders & ctrlHttp1.GetHeaderLine(Index) & vbCrLf
            Next
        Else
            txtResults = txtResults & vbCrLf & "--- " & ctrlHttp1.GetErrorText(Result) & " ---"
        End If
    Me.cmdCustom.Enabled = True
        Me.cmdDeleteFile.Enabled = True
        Me.cmdGet.Enabled = True
        Me.cmdHead.Enabled = True
        Me.cmdPut.Enabled = True
    
    End Sub
    
    Private Sub ctrlHttp1_OnPUT(ByVal Result As Long)
        
        ' Call Http1_OnGet to display the output
        ' to the edit window
         ctrlHttp1_OnGET (Result)
        
    End Sub
    
    Private Sub cmdPut_Click()
        
        Dim rt As Long  'return variable, idicates success/failure
         txtHeaders.Text = ""
        'first check to see if textbox indicates a file
        If txtFileName = "" Then
            MsgBox "Please type in name of file to PUT in File Name textbox", _
            vbOKOnly, "Missing Information"
            Exit Sub
        End If
            
        ' "PUT" the specified file to the HTTP server
        txtResults = "Putting ..."
        rt = ctrlHttp1.PUT(txtUrl, txtFileName)
        
        ' Check the result
        If (rt <> ecSuccess) Then
            txtResults = txtResults & vbCrLf & ctrlHttp1.GetErrorText(rt)
        End If
        
    End Sub
    

Private Sub Form_Unload(Cancel As Integer)
ctrlHttp1.CancelHttp
End Sub

    ' put the link the user double cliked on in the URL edit Box
    ' then
    Private Sub lstLinkTags_Click()
    Dim tagStr As String
    tagStr = lstLinkTags.Text
    If InStr(1, tagStr, "http:") Then
    txtUrl.Text = lstLinkTags.Text
    Else
    txtUrl.Text = txtUrl.Text & lstLinkTags.Text
    End If
    ' call the Get command to go to that url
    cmdGet_Click
    
    End Sub

Private Sub txtUrl_Change()
    If txtUrl.Text = "" Then
        Me.cmdCustom.Enabled = False
        Me.cmdDeleteFile.Enabled = False
        Me.cmdGet.Enabled = False
        Me.cmdHead.Enabled = False
        Me.cmdPut.Enabled = False
    Else
        Me.cmdCustom.Enabled = True
        Me.cmdDeleteFile.Enabled = True
        Me.cmdGet.Enabled = True
        Me.cmdHead.Enabled = True
        Me.cmdPut.Enabled = True
    End If
End Sub
