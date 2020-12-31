VERSION 5.00
Object = "{741EFDCF-03DE-11D3-A465-0080C858F182}#1.4#0"; "UTPing.dll"
Begin VB.Form frmMain
   Caption         =   "Dundas TCP/IP 4.0 Ping Client ActiveX Control - Demo Program"
   ClientHeight    =   4515
   ClientLeft      =   3315
   ClientTop       =   2175
   ClientWidth     =   6630
   ClipControls    =   0   'False
   Icon            =   "PingTest.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   4515
   ScaleWidth      =   6630
   StartUpPosition =   2  'CenterScreen
   Begin VB.CheckBox chkCheck2
      Caption         =   "Blocking Mode"
      Height          =   255
      Left            =   3300
      TabIndex        =   8
      ToolTipText     =   "Call Methods in Synchronous Mode"
      Top             =   90
      Width           =   1455
   End
   Begin VB.CheckBox chkCheck1
      Caption         =   "Do Lookup"
      Height          =   195
      Left            =   4860
      TabIndex        =   7
      ToolTipText     =   "Perform Domain Name Resolution"
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton cmdExit
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5400
      TabIndex        =   6
      ToolTipText     =   "Exit the Demo Application"
      Top             =   4020
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   4200
      TabIndex        =   5
      ToolTipText     =   "Cancel the Operation (when BlockingMode is False) "
      Top             =   4020
      Width           =   1095
   End
   Begin VB.TextBox txtResults
      Height          =   3315
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Top             =   540
      Width           =   6450
   End
   Begin VB.CommandButton cmdTraceOut
      Caption         =   "&Trace Route"
      Height          =   375
      Left            =   3000
      TabIndex        =   3
      ToolTipText     =   "Trace Route of Specified Address"
      Top             =   4020
      Width           =   1095
   End
   Begin VB.CommandButton cmdPing
      Caption         =   "&Ping"
      Default         =   -1  'True
      Height          =   375
      Left            =   1800
      TabIndex        =   2
      ToolTipText     =   "Ping the Specified Address"
      Top             =   4020
      Width           =   1095
   End
   Begin VB.TextBox txtAddress
      Height          =   320
      Left            =   780
      TabIndex        =   1
      Text            =   "dundas.com"
      Top             =   57
      Width           =   2205
   End
   Begin UTPINGLibCtl.Ping utaxPingControl
      Left            =   120
      Top             =   3840
      BlockingMode    =   0   'False
      DoLookup        =   0   'False
      MaxTimeOuts     =   5
   End
   Begin VB.Label lblAddress
      AutoSize        =   -1  'True
      Caption         =   "&Address:"
      Height          =   195
      Left            =   45
      TabIndex        =   0
      ToolTipText     =   "Address to Ping"
      Top             =   120
      Width           =   615
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' =================================================================
' Dundas TCP/IP v4.0 Ping ActiveX Control Demo
'
' ===================================================================
' Dundas TCP/IP v4.0
' Copyright © Dundas Software 1995-2001, all rights reserved
'
' Contact Information:
'   Email:  sales@dundas.com
'   Phone:  (800) 463-1492
'           (416) 467-5100
'   Fax:    (416) 422-4801
'
' ===================================================================
'
Option Explicit

Private Sub cmdCancel_Click()
'Cancels any pending ping operation

    utaxPingControl.CancelPing
    MousePointer = vbNormal
    
End Sub

Private Sub cmdExit_Click()
        
    'exit the app
    Unload Me
 
End Sub

Private Sub cmdPing_Click()
    
    On Error Resume Next  'enable inline error trapping
    
    Dim lngRt As Long  'return variable, indicates success/filure
  
    Me.MousePointer = vbHourglass
    
    txtResults = ""
    txtResults.Refresh
        
    CheckOptions
         
    ' Ping the specified address
    lngRt = utaxPingControl.Ping(Trim(txtAddress), , 20)
    
    ' Check the result code, error indicate to user
    If lngRt <> 0 Then
        txtResults = utaxPingControl.GetErrorText(lngRt)
    End If
    
End Sub

Private Sub Form_Load()
utaxPingControl.AboutBox
End Sub

Private Sub Form_Resize()
    'write resizing routine
    
    On Error Resume Next
    
    Dim lngFormWidth  'form's scalewidth
    Dim lngFormHeight  'form's scaleheight
    
    lngFormWidth = Me.ScaleWidth
    lngFormHeight = Me.ScaleHeight
    
    'first,align leftmost controls
    lblAddress.Left = 100
    txtResults.Left = 100
    
    'next, adjust widths of controls
    txtResults.Width = lngFormWidth - 170
        
    'adjust command buttons to right justify to form
    cmdExit.Left = lngFormWidth - cmdExit.Width - 80
    cmdCancel.Left = cmdExit.Left - 1095 - 95
    cmdTraceOut.Left = cmdCancel.Left - 1095 - 95
    cmdPing.Left = cmdTraceOut.Left - 1095 - 95
        
    'adjust height of txtResults
    txtResults.Height = lngFormHeight - txtResults.Top - 600

    cmdExit.Top = txtResults.Top + txtResults.Height + 80
    cmdCancel.Top = cmdExit.Top
    cmdTraceOut.Top = cmdExit.Top
    cmdPing.Top = cmdExit.Top
    
    'lastly, do not let user undersize form
    If Me.Width < 6700 Then Me.Width = 6700
    If Me.Height < 4920 Then Me.Height = 4920
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    
    'release form variable
    Set frmMain = Nothing
    
End Sub

Private Sub cmdTraceOut_Click()
'performs a trace route operation on specified address
    
    Dim rt As Long  'return variable, indicates success/failure
    
    Me.MousePointer = vbHourglass
    
    txtResults = ""
    txtResults.Refresh
    
    CheckOptions
    
    'Execute a trace route operation on the address
    rt = utaxPingControl.TraceRoute(txtAddress)
    
    ' Check the result from the server
    If rt <> 0 Then
        txtResults = utaxPingControl.GetErrorText(rt)
    End If
    
    'reset textbox cursor
    txtResults.SelStart = 30000
    
End Sub

Private Sub utaxPingControl_OnPing(ByVal Result As Long)
'this callback is raised when the ping operation is either complete or has been cancelled
    
    txtResults = txtResults & vbCrLf & utaxPingControl.GetErrorText(Result)
    
    'retrieve response duration results of ping or trace route operation
    Call GetStats
        
    txtResults.SelStart = 5000
    
    'make sure icon is no longer an hourglass
    Me.MousePointer = vbNormal
        
End Sub

Private Sub utaxPingControl_OnReceiveICMP()
'Callback which is raised when data is ready to be read from server
    
    txtResults = txtResults & vbCrLf + "Msg: " & utaxPingControl.GetResponseMessage & vbTab
    txtResults = txtResults & "Seq: " & Str(utaxPingControl.GetResponseSequence) & vbTab
    txtResults = txtResults & "Time: " & Str(utaxPingControl.GetResponseDuration) & vbCrLf
    txtResults = txtResults & "From: " & utaxPingControl.GetResponseAddress & vbTab
    txtResults = txtResults & "Name: " & utaxPingControl.GetResponseName & vbCrLf
                
End Sub

Private Sub utaxPingControl_OnTraceRoute(ByVal Result As Long)
'this callback is raised when the trace route operation is either complete or has been cancelled

    txtResults = txtResults & vbCrLf & utaxPingControl.GetErrorText(Result)
    
    'retrieve response duration results of ping or trace route operation
    Call GetStats

    txtResults.SelStart = 30000
    
    'make sure icon is no longer an hourglass
    Me.MousePointer = vbNormal
    
End Sub

Private Sub CheckOptions()
'checks options available to user, and sets the control's properties accordingly

    'check 'do lookup' checkbox...
    If chkCheck1.Value = 0 Then
        utaxPingControl.DoLookup = 0
    Else
        utaxPingControl.DoLookup = 1
    End If
    
    'check 'blocking mode' checkbox...
    If chkCheck2.Value = 0 Then
        utaxPingControl.BlockingMode = 0
    Else
        utaxPingControl.BlockingMode = 1
    End If
    
End Sub

Private Sub GetStats()
'retrieves response duration results of ping or trace route operation
    
    Dim i, count, intSum, intAvg As Integer
    
    On Error Resume Next
    
    utaxPingControl.GetResponseDuration (i)
    For i = 0 To utaxPingControl.GetResponseSize - 1
        If utaxPingControl.GetResponseType(i) <> 255 Then
            count = count + 1
            intSum = intSum + utaxPingControl.GetResponseDuration(i)
        End If
    Next
    
    intAvg = intSum / count
    
    txtResults = txtResults & vbCrLf + "Average response duration:" & Str$(intAvg)
        
End Sub
