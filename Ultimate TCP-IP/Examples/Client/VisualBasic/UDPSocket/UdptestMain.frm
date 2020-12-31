VERSION 5.00
Object = "{D23EA52C-0D35-11D3-A46D-0080C858F182}#1.4#0"; "UTSocket.dll"
Begin VB.Form frmMain 
   Caption         =   "Dundas TCP/IP 4.0 Socket ActiveX Client Control - Demo Program"
   ClientHeight    =   7524
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   6852
   ClipControls    =   0   'False
   Icon            =   "UdptestMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7524
   ScaleWidth      =   6852
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame fraSocket 
      Caption         =   "&Socket Options"
      Height          =   1875
      Left            =   60
      TabIndex        =   9
      Top             =   720
      Width           =   6675
      Begin VB.CommandButton cmdSetOptions 
         Caption         =   "&Set Options"
         Enabled         =   0   'False
         Height          =   375
         Left            =   5340
         TabIndex        =   18
         ToolTipText     =   "Closes the current socket connection and re-establishes a connection based on the new socket settings."
         Top             =   495
         Width           =   1195
      End
      Begin VB.TextBox txtRemoteAddress 
         Height          =   285
         Left            =   3240
         TabIndex        =   17
         Top             =   1320
         Width           =   1335
      End
      Begin VB.TextBox txtRemotePort 
         Height          =   285
         Left            =   3240
         TabIndex        =   16
         Top             =   540
         Width           =   1335
      End
      Begin VB.TextBox txtLAddress 
         Height          =   285
         Left            =   840
         TabIndex        =   15
         Top             =   1320
         Width           =   1335
      End
      Begin VB.TextBox txtLPort 
         Height          =   285
         Left            =   840
         TabIndex        =   14
         Top             =   540
         Width           =   1335
      End
      Begin VB.Label lblRemotePort 
         Caption         =   "Remote &Port:"
         Height          =   195
         Left            =   3240
         TabIndex        =   13
         ToolTipText     =   "The port being used by the other instance of this application."
         Top             =   300
         Width           =   975
      End
      Begin VB.Label lblRemoteAddress 
         Caption         =   "&Remote IP Address:"
         Height          =   195
         Left            =   3240
         TabIndex        =   12
         ToolTipText     =   "The IP address of the machine where the other instance is running."
         Top             =   1020
         Width           =   1515
      End
      Begin VB.Label lblLocalAddress 
         Caption         =   "Local &IP Address:"
         Height          =   195
         Left            =   840
         TabIndex        =   11
         ToolTipText     =   "The IP address of the machine where this instance is running."
         Top             =   1020
         Width           =   1335
      End
      Begin VB.Label lblLocalPort 
         Caption         =   "&Local Port:"
         Height          =   195
         Left            =   840
         TabIndex        =   10
         ToolTipText     =   "The port used for this instance."
         Top             =   300
         Width           =   855
      End
   End
   Begin VB.Timer tmrTimTimer 
      Interval        =   500
      Left            =   4380
      Top             =   4020
   End
   Begin VB.CommandButton cmdSendData 
      Caption         =   "&Send Data"
      Height          =   375
      Left            =   5520
      TabIndex        =   7
      ToolTipText     =   "Send the data to the other instance of this application."
      Top             =   4200
      Width           =   1195
   End
   Begin VB.TextBox txtReceived 
      Height          =   1215
      Left            =   60
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   2
      ToolTipText     =   "Data retrieved from the other running instance of this application."
      Top             =   4920
      Width           =   6675
   End
   Begin VB.TextBox txtLocal 
      Height          =   1095
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Text            =   "UdptestMain.frx":030A
      ToolTipText     =   $"UdptestMain.frx":0318
      Top             =   3000
      Width           =   6675
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "E&xit"
      Height          =   375
      Left            =   5520
      TabIndex        =   0
      ToolTipText     =   "Exit the demo application."
      Top             =   7080
      Width           =   1195
   End
   Begin VB.TextBox txtStatus 
      BackColor       =   &H80000004&
      Height          =   375
      Left            =   60
      Locked          =   -1  'True
      TabIndex        =   3
      ToolTipText     =   "Any relevant status messages are displayed here."
      Top             =   6600
      Width           =   6675
   End
   Begin UTSOCKETLibCtl.Socket utaxSocket1 
      Left            =   1560
      Top             =   4200
      ConnectTimeOut  =   5
      ReceiveTimeOut  =   30
      BlockingMode    =   0   'False
      SocketType      =   1
      SocketProtocol  =   0
      SocketFamily    =   2
   End
   Begin VB.Label lblHelp 
      Caption         =   $"UdptestMain.frx":03A4
      ForeColor       =   &H00FF0000&
      Height          =   675
      Left            =   60
      TabIndex        =   8
      Top             =   60
      Width           =   6555
   End
   Begin VB.Label lblRetrieved 
      AutoSize        =   -1  'True
      Caption         =   "Retrieved data:"
      Height          =   195
      Left            =   60
      TabIndex        =   6
      Top             =   4620
      Width           =   1095
   End
   Begin VB.Label lblStatus 
      AutoSize        =   -1  'True
      Caption         =   "Status Messages:"
      Height          =   195
      Left            =   60
      TabIndex        =   5
      Top             =   6300
      Width           =   1260
   End
   Begin VB.Label lblLocal 
      AutoSize        =   -1  'True
      Caption         =   "&Data to be sent::"
      Height          =   195
      Index           =   4
      Left            =   60
      TabIndex        =   4
      Top             =   2700
      Width           =   1185
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
' This is a simple chat program that will emulate a one to one chat session by using
'  2 instances of this application.
'
' We have hardcoded ports (20000 and 20001) and are also using the local loopback address
'  for the local IP addresses, so if both instances are on the same machine the demo will
'  function properly immediately upon execution.
'
'To run the 2 instances on different machines the user must set the remote IP addresses and
'  the ports used for both instances so that the RemotePort for one instance matches the Local Port
'  of the other instance, etc...
'
'Dundas Software Contact Information:
'   Email:  sales@dundas.com
'   Phone:  (800) 463-1492
'           (416) 467-5100
'   Fax:    (416) 422-4801
' ===================================================================

Private intInstance As Integer    'this is 1 if it the first instance running, otherwise it is 2

Option Explicit

Private Sub cmdExit_Click()
'exit the demo application

    Unload Me
    
End Sub

Private Sub cmdSendData_Click()
'Send the contents of the text box to the connected chat partner using the SendTo method
'note that this routine is also invoked if the user presses the <Return> key while
'  entering text into the txtLocal textbox
    
    Dim ret                     'stores returned error code
    Dim strTemp As String
    Dim ln As Long              'length of the string of data to be sent
    
    Dim i, BytesSent As Long
    Dim x() As Byte             'stores data as an array of bytes
    
    'text from user input
    strTemp = txtLocal.Text
    
    'find the size required for the string passed
    ln = Len(strTemp)
    ReDim x(ln)
    
    x = StrConv(strTemp, vbFromUnicode)  ' Convert string to array of bytes
    
    'send data to chat partner.  bu not specifying port and remote address we use
    '  the values which were specififed in the CreateUDPSocket call
    ret = utaxSocket1.SendTo(x)
        
    'trap for errors in initiating the request
    If ret <> ecSuccess Then
        txtStatus.Text = "Error: " & utaxSocket1.GetErrorText(ret)
    End If
   
End Sub

Private Sub cmdSetOptions_Click()
'closes the current socket connection (if open) and establishes a new connection using
'  the new socket settings
    
    Dim ret As Long     'used to store function return value (an errorcode)
    
    If utaxSocket1.IsConnected Then utaxSocket1.CloseConnection
    
    'attempt to establish a new connection with the new socket settings
    ret = utaxSocket1.CreateUDPSocket(CLng(Trim(txtLPort)), CLng(Trim(txtRemotePort)), Trim(txtRemoteAddress), Trim(txtLAddress))

    'output error message if initiating the request at the server has failed
    If ret <> ecSuccess Then
        txtStatus = utaxSocket1.GetErrorText(ret)
    End If

End Sub

Private Sub Form_Load()
utaxSocket1.AboutBox
'opens the UDP socket and enables the timer so that this instance immediately
'  starts checking for incoming data
  
   'first see if previous instance is already running
   If App.PrevInstance Then
        intInstance = 2
   Else
        intInstance = 1
   End If
   
   'set socket defaults (set to work with both instances on the same machine)
   Call SetSocketDefaults
   
   'create socket
   Call CreateSocket
   
   'set up the timer so we check for waiting data to be retrieved
   tmrTimTimer.Enabled = True
   
End Sub

Private Sub Form_Resize()
'This resize roution simply re-positions and/or adjusts the size of all controls
'   when user resize the Form
        
    On Error Resume Next
    
    If Me.WindowState <> vbMinimized Then
        
        'First, limit the minimum size of the Form
        If Me.Height < 7935 Then Me.Height = 7935
        If Me.Width < 6975 Then Me.Width = 6975
            
        txtStatus.Height = Me.ScaleHeight - txtStatus.Top - 600
        cmdExit.Top = Me.ScaleHeight - 500
        
        cmdExit.Left = Me.ScaleWidth - 1300
        cmdSendData.Left = cmdExit.Left
        
        fraSocket.Width = Me.ScaleWidth - 200
        txtLocal.Width = fraSocket.Width
        txtReceived.Width = fraSocket.Width
        txtStatus.Width = fraSocket.Width
        lblHelp.Width = fraSocket.Width
        
        cmdSetOptions.Left = fraSocket.Width - 1400
                            
    End If

End Sub

Private Sub Form_Unload(Cancel As Integer)
'unload the form

    Set frmMain = Nothing

End Sub

Private Sub CreateSocket()
'creates the UDP socket.  Note that ports are hardcoded.  If the user changes the socket
'  settings then this method IS NOT used to recreate the socket connection with the new settings
'notice that the Remote IP address is set to the IP address of the machine the app is running on
'this means that initially this sample will only work if both instances are on the same machine.
'  To work on different machines the user will need to specify the Remote addresses for both instances

    Dim sResult As String       'stores function return value
    
    MousePointer = vbHourglass
    
    'attempt to create socket.  Note that if this is the first running instance we will
    '  set the local port to 20000, if it is the second running instance set the
    '  local port to be 20001
    If intInstance = 2 Then
        sResult = utaxSocket1.CreateUDPSocket(20001, 20000, utaxSocket1.GetHostAddress)
    Else
        sResult = utaxSocket1.CreateUDPSocket(20000, 20001, utaxSocket1.GetHostAddress)
    End If
        
    If sResult <> ecSuccess Then
        txtStatus.Text = "Error: " & utaxSocket1.GetErrorText(sResult)
    End If
            
End Sub

Private Sub UpdateStatus()
'updates the status textbox with port and IP information for the socket
    
    Dim strStatus As String     'stores status information
    
    strStatus = "Local Port: " & Str(utaxSocket1.LocalPort) & _
              "   Remote Port: " & Str(utaxSocket1.RemotePort) & _
              "   Remote Address: " & utaxSocket1.RemoteHostIPAddress
    
    txtStatus = strStatus
    
End Sub

Private Sub utaxSocket1_OnCloseConnection(ByVal Result As Long)
'outputs status of connection to the status textbox

    txtStatus = utaxSocket1.GetErrorText(Result)

End Sub

Private Sub utaxSocket1_OnCreateUDPSocket(ByVal Result As Long)
'this callback event is raised when either the server has finished processing the CreatUDPSocket request or
'  when the user cancels the operation

    txtStatus = ""
    
    If Result <> ecSuccess Then
        txtStatus.Text = "Error: " & utaxSocket1.GetErrorText(Result)
    Else
        Call UpdateStatus
    End If
    
    cmdSetOptions.Enabled = False
    
    MousePointer = vbDefault

End Sub

Private Sub utaxSocket1_OnReceiveFrom(ByVal Data As Variant, ByVal IPAddress As String, ByVal Result As Long)
'this callback event is raised when the server has either processed the ReceiveFrom() operation
'  or the user cancelled the operation
'the Data parameter is used to pass the returned data (passed as an array of bytes)
'the IPAddress parameter is the IP address of the data source
'the Result parameter indicates the success or failure of the operation, and can be used
'  in conjunction with the GetErrorText method to retrieve error strings

    Dim sData As String     'stores the transferred data (converted to a string representation)
    Dim i As Long           'counter variable
   
    'if successful output the data to a textbox, otherwise we display the relevant error string
    If Result = ecSuccess Then
        
        txtStatus = ""
        txtStatus = Str(UBound(Data) + 1) & " bytes of data received from " & IPAddress
        For i = LBound(Data) To UBound(Data)
                sData = sData & Chr(Data(i))    'we use the Chr() method to convert each character from a byte to a string
        Next i
        
        'display the transferred data
        txtReceived = ""
        txtReceived.Text = txtReceived & sData
        
    Else
        
        txtStatus = ""
        txtStatus = utaxSocket1.GetErrorText(Result)
                
    End If

End Sub

Private Sub utaxSocket1_OnSendTo(ByVal BytesSent As Long)
'updates status box with number of bytes successfully transferred
'this callback event is raised when the server has either finished processing the SendTo
'  request or the user cancels the operation
'the Result parameter returns an error code, indicating the overall success/failure of the
'  SendTo operation (zero = success).  If operation is unsuccessful use this errorcode with
'  the GetErrorText method to retrieve a relevant error string

    txtStatus = ""
    txtStatus = "Number of bytes successfully sent: " & CStr(BytesSent)

End Sub

Private Sub tmrTimTimer_Timer()
'this timer first checks to see if there is any data to be retrieved, if there is we retrieve it
'  by calling the ReceiveFrom method, otherwise we output a message indicating there is no data

    If utaxSocket1.IsDataWaiting <> 0 Then
    'there is data to be retrieved
    
        utaxSocket1.ReceiveTimeOut = 2
        utaxSocket1.ReceiveFrom (1024)      'retrieves data, which is displayed by the
                                        '  OnReceiveFrom callback event
    End If

End Sub

Private Sub txtLAddress_Change()

    cmdSetOptions.Enabled = True

End Sub

Private Sub txtLocal_KeyUp(KeyCode As Integer, Shift As Integer)
'when the user presses the enter key we want to send the
'  contents of the text box to the connected chat partner using the SendTo method
    
    If KeyCode = 13 Or KeyCode = 10 Then  ' enter key
    
        Call cmdSendData_Click
        
   End If
   
End Sub

Private Sub txtLPort_Change()

    cmdSetOptions.Enabled = True

End Sub

Private Sub txtRemoteAddress_Change()

    cmdSetOptions.Enabled = True

End Sub

Private Sub txtRemotePort_Change()

    cmdSetOptions.Enabled = True

End Sub

Private Sub SetSocketDefaults()
'sets the defaul remote and local IP addresses and ports.  Note that by default
'  the ports are hardcoded and the IP addresses are assumed to be the local loopback address, so
'  in order for this demo to work with instances on different machines the user will have
'  to specify the Remote IP addresses for both instances.

    If intInstance = 1 Then
        txtLPort = 20000
        txtRemotePort = 20001
    Else
        txtLPort = 20001
        txtRemotePort = 20000
    End If
    
    txtRemoteAddress = utaxSocket1.GetHostAddress
    txtLAddress = txtRemoteAddress

End Sub
