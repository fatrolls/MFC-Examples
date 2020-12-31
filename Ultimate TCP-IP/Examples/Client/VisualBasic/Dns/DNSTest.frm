VERSION 5.00
Object = "{86E5D740-02EB-11D3-A464-0080C858F182}#1.4#0"; "UTDns.dll"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmMain 
   Caption         =   "Dundas TCP/IP DNS Client Control 4.0 - Demo Program"
   ClientHeight    =   5616
   ClientLeft      =   2736
   ClientTop       =   2016
   ClientWidth     =   6936
   ClipControls    =   0   'False
   LinkTopic       =   "Form1"
   ScaleHeight     =   5616
   ScaleWidth      =   6936
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdAbout 
      Caption         =   "About"
      Height          =   375
      Left            =   5775
      TabIndex        =   7
      Top             =   525
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5775
      TabIndex        =   5
      ToolTipText     =   "Exit the Demo Application"
      Top             =   105
      Width           =   1095
   End
   Begin MSFlexGridLib.MSFlexGrid flexMsgDNS 
      Height          =   3135
      Left            =   0
      TabIndex        =   9
      Top             =   1200
      Width           =   6855
      _ExtentX        =   12086
      _ExtentY        =   5525
      _Version        =   393216
      Cols            =   14
      BackColorBkg    =   -2147483643
      AllowBigSelection=   0   'False
      AllowUserResizing=   1
   End
   Begin VB.TextBox txtResults 
      Enabled         =   0   'False
      Height          =   1095
      Left            =   105
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   8
      Top             =   4440
      Width           =   6735
   End
   Begin VB.CommandButton cmdAuthLookUp 
      Caption         =   "&Au. Lookup"
      Height          =   375
      Left            =   4515
      TabIndex        =   4
      ToolTipText     =   "Perform Authoritative Lookup Operation"
      Top             =   525
      Width           =   1095
   End
   Begin VB.CommandButton cmdLookUp 
      Caption         =   "&Lookup"
      Height          =   375
      Left            =   4515
      TabIndex        =   3
      ToolTipText     =   "Perform Lookup Operation"
      Top             =   105
      Width           =   1095
   End
   Begin VB.TextBox txtLookUp 
      Height          =   320
      Left            =   1080
      TabIndex        =   2
      Text            =   "Dundas.com"
      ToolTipText     =   "Lookup Name"
      Top             =   600
      Width           =   3015
   End
   Begin VB.TextBox txtServerName 
      Height          =   320
      Left            =   1080
      TabIndex        =   1
      Text            =   "A.ROOT-SERVERS.NET"
      Top             =   120
      Width           =   3015
   End
   Begin UTDNSLibCtl.DNS utaxDNSControl 
      Left            =   4080
      Top             =   840
      LookupTimeOut   =   20
      IncludeDefMX    =   0   'False
      BlockingMode    =   0   'False
      Protocol        =   0
   End
   Begin VB.Label lblLookUp 
      Caption         =   "Lookup:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      ToolTipText     =   "Valid Domain Name"
      Top             =   648
      Width           =   615
   End
   Begin VB.Label lblDNSServ 
      Caption         =   "DNS Server:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      ToolTipText     =   "DNS Server"
      Top             =   168
      Width           =   975
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
'
' ===================================================================
'
Option Explicit

Dim rt As Long 'return value of LookUp(), AuthLookUp()
Dim strResults As String 'results of lookup variable

'declare module object variables
Dim DisplyGrid As MSFlexGrid
Dim MyDnsControl As DNS 'DNS Control Class

Private Sub cmdAbout_Click()
MyDnsControl.AboutBox
End Sub

Private Sub cmdAuthLookUp_Click()
        
    ' Execute an authoritative lookup on the specified host
    txtResults = "Waiting for result ..."
    rt = MyDnsControl.AuthoritativeLookup(txtServerName, txtLookUp, 255)
    
End Sub

Private Sub cmdExit_Click()
    
    'unload the form
    Unload Me

End Sub

Private Sub utaxDNSControl_OnLookup(ByVal Result As Long)
    ' This callback is received when the lookup is
    ' complete.
    
    Dim x As Long  ' counter variable
        
    ' Enumerate the list of servers and add their information
    '   fields to the result text window
          
    strResults = MyDnsControl.GetErrorText(Result) & vbCrLf
    MyDnsControl.ResetEnumeration
    x = 0
    While (MyDnsControl.EnumDNSEntry() = 0)
         x = x + 1
    Wend
    strResults = strResults & "Number of records found is " & Str(x) & vbCrLf
    txtResults = strResults
    
    'turn off redraw until all values have been set
    DisplyGrid.Redraw = False
    
    MyDnsControl.ResetEnumeration
    DisplyGrid.Rows = x + 1
    x = 1
     While (MyDnsControl.EnumDNSEntry() = 0)
          DisplyGrid.Row = x ' // set the number of rows to the number of entries
          DisplyGrid.Col = 0
          DisplyGrid.Text = Str(x)
          DisplyGrid.Col = 1
          DisplyGrid.Text = MyDnsControl.EntryHostName
          DisplyGrid.Col = 2
          DisplyGrid.Text = MyDnsControl.EntryData
          DisplyGrid.Col = 3
          DisplyGrid.Text = MyDnsControl.GetEntryShortName(MyDnsControl.EntryType)
          DisplyGrid.Col = 4
          DisplyGrid.Text = MyDnsControl.GetEntryLongName(MyDnsControl.EntryType)
          DisplyGrid.Col = 5
          DisplyGrid.Text = Str(MyDnsControl.EntryType)
          DisplyGrid.Col = 6
          DisplyGrid.Text = Str(MyDnsControl.EntryMX_Preference)
          DisplyGrid.Col = 7
          DisplyGrid.Text = Str(MyDnsControl.EntrySOA_Refresh)
          DisplyGrid.Col = 8
          DisplyGrid.Text = Str(MyDnsControl.EntrySOA_Expire)
          DisplyGrid.Col = 9
          DisplyGrid.Text = Str(MyDnsControl.EntrySOA_Retry)
          DisplyGrid.Col = 10
          DisplyGrid.Text = Str(MyDnsControl.EntrySOA_Serial)
          DisplyGrid.Col = 11
          DisplyGrid.Text = Str(MyDnsControl.EntryTimeToLive)
          DisplyGrid.Col = 12
          DisplyGrid.Text = Str(MyDnsControl.EntrySOA_Minimum)
          DisplyGrid.Col = 13
          DisplyGrid.Text = MyDnsControl.EntryData2
          x = x + 1
     Wend
     'cause flexgrid to paint now that values have been set
     DisplyGrid.Redraw = True

End Sub

Private Sub DNS1_OnLookup(ByVal Result As Long)

End Sub

Private Sub Form_Load()
        
    Dim strTemp As String  'temp string variable
    
    'set object variables to current instances of
    '   MSFlexGrid, DNS controls
    Set DisplyGrid = flexMsgDNS
    Set MyDnsControl = utaxDNSControl
    
    'turn autoredraw off to avoid screen falsh
    DisplyGrid.Redraw = False
    DisplyGrid.Clear
    'DisplyGrid.Rows = 1
        
    strTemp = "      |<Host                |<Data                 |<Short Name |<Long Name                 |^Type"
    strTemp = strTemp & " |<mx_preference   |<soa_refresh    |<soa_expire   |"
    strTemp = strTemp & "<soa_retry   |<soa_serial    |<Time to Live |"
    strTemp = strTemp & "<soa_minimum   |<Data2         "
    
    'assign headings for msflexgrid control
    flexMsgDNS.FormatString = strTemp
        
    'force paint of msflexgrid
    DisplyGrid.Redraw = True
    
End Sub

Private Sub cmdLookUp_Click()
    ' Execute a lookup the specified server
    
    txtResults = "Waiting for result ..."
    rt = MyDnsControl.Lookup(txtServerName, txtLookUp, 255)
    
End Sub

Private Sub Form_Resize()
    'need resizing routine for the controls on the form
    
    On Error Resume Next 'handles resizing error which occurs when it is too small
    
    'if form is being minimized then exit this function
    If frmMain.WindowState = vbMinimized Then Exit Sub
    
    'redo the leftmost controls so they all line up with their left borders
    lblDNSServ.Left = 80
    lblLookUp.Left = 80
    flexMsgDNS.Left = 80
    txtResults.Left = 80
    
    'next adjust width of msflexgrid and txtResults to match form width
    flexMsgDNS.Width = Me.ScaleWidth - 160
    txtResults.Width = Me.ScaleWidth - 160
    
    'keep exit button to right edge of form
    cmdExit.Left = Me.ScaleWidth - 80 - cmdExit.Width
    
    'adjust height of msflexgrid
    flexMsgDNS.Height = Me.ScaleHeight - 1500 - txtResults.Height
        
    'next adjust top of txtResults to keep outer border to form at 80 twips
    txtResults.Top = flexMsgDNS.Top + flexMsgDNS.Height + 205
    
    'check to see if form is smaller than minimal size
    '   if it is resize to minimum
    If Me.Width < 7050 Then Me.Width = 7050
        
    If Me.Height < 6000 Then Me.Height = 6000
        
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next  'in case we try to release obj variable which  has no valid
                            ' object reference
    
    'release object variables
    Set DisplyGrid = Nothing
    Set MyDnsControl = Nothing
    
    'release hidden form variable
    Set frmMain = Nothing
        
End Sub

