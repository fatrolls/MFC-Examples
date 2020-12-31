VERSION 5.00
Begin VB.Form Ping 
   Caption         =   "VBPing"
   ClientHeight    =   5085
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8370
   LinkTopic       =   "Form1"
   ScaleHeight     =   5085
   ScaleWidth      =   8370
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox timeout 
      Height          =   375
      Left            =   4440
      TabIndex        =   25
      Top             =   4440
      Width           =   975
   End
   Begin VB.TextBox tos 
      Height          =   375
      Left            =   6720
      TabIndex        =   23
      Top             =   4080
      Width           =   975
   End
   Begin VB.TextBox timestamp 
      Height          =   375
      Left            =   6720
      TabIndex        =   22
      Top             =   3720
      Width           =   975
   End
   Begin VB.TextBox rroute 
      Height          =   375
      Left            =   6720
      TabIndex        =   21
      Top             =   3360
      Width           =   975
   End
   Begin VB.CheckBox tracert 
      Caption         =   "TraceRT"
      Height          =   375
      Left            =   1680
      TabIndex        =   17
      Top             =   3720
      Width           =   1335
   End
   Begin VB.CheckBox interrupt 
      Caption         =   "Interrupt"
      Height          =   375
      Left            =   240
      TabIndex        =   16
      Top             =   4440
      Width           =   1335
   End
   Begin VB.CheckBox nofrag 
      Caption         =   "No Fragment"
      Height          =   375
      Left            =   240
      TabIndex        =   15
      Top             =   4080
      Width           =   1335
   End
   Begin VB.CheckBox resolve 
      Caption         =   "Resolve Name"
      Height          =   375
      Left            =   240
      TabIndex        =   14
      Top             =   3720
      Width           =   1335
   End
   Begin VB.TextBox numpack 
      Height          =   375
      Left            =   4440
      TabIndex        =   13
      Top             =   4080
      Width           =   975
   End
   Begin VB.TextBox packlen 
      Height          =   375
      Left            =   4440
      TabIndex        =   12
      Top             =   3720
      Width           =   975
   End
   Begin VB.TextBox ttl 
      Height          =   375
      Left            =   4440
      TabIndex        =   11
      Top             =   3360
      Width           =   975
   End
   Begin VB.TextBox hostname 
      Height          =   375
      Left            =   1080
      TabIndex        =   6
      Top             =   2880
      Width           =   5175
   End
   Begin VB.CommandButton Command5 
      Caption         =   "StopICMP"
      Height          =   495
      Left            =   4920
      TabIndex        =   5
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton Command4 
      Caption         =   "StopPing"
      Height          =   495
      Left            =   3720
      TabIndex        =   4
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "RunPing"
      Height          =   495
      Left            =   2520
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.ListBox list1 
      Height          =   1425
      ItemData        =   "atlrun.frx":0000
      Left            =   120
      List            =   "atlrun.frx":0007
      TabIndex        =   2
      Top             =   1320
      Width           =   8055
   End
   Begin VB.CommandButton Command2 
      Caption         =   "SetVars"
      Height          =   495
      Left            =   1320
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "StartICMP"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label8 
      Caption         =   "Timeout"
      Height          =   255
      Left            =   3120
      TabIndex        =   24
      Top             =   4560
      Width           =   1215
   End
   Begin VB.Label Label7 
      Caption         =   "TOS"
      Height          =   255
      Left            =   5640
      TabIndex        =   20
      Top             =   4200
      Width           =   855
   End
   Begin VB.Label Label6 
      Caption         =   "# Timestamps"
      Height          =   255
      Left            =   5640
      TabIndex        =   19
      Top             =   3720
      Width           =   1095
   End
   Begin VB.Label Label5 
      Caption         =   "RRoute Num"
      Height          =   255
      Left            =   5640
      TabIndex        =   18
      Top             =   3360
      Width           =   1095
   End
   Begin VB.Label Label4 
      Caption         =   "NumPackets"
      Height          =   255
      Left            =   3120
      TabIndex        =   10
      Top             =   4200
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "Packet Length"
      Height          =   255
      Left            =   3120
      TabIndex        =   9
      Top             =   3720
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "TTL"
      Height          =   255
      Left            =   3960
      TabIndex        =   8
      Top             =   3360
      Width           =   375
   End
   Begin VB.Label Label1 
      Caption         =   "Hostname"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2880
      Width           =   855
   End
End
Attribute VB_Name = "ping"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim mhostname As String
Dim optresolve As Long
Dim optnofrag As Long
Dim optruntointerupt As Long
Dim optttl As Long
Dim optpacketlen As Long
Dim optrroutenum As Long
Dim opttimestamp As Long
Dim opttos As Long
Dim opttimeout As Long
Dim opttrcrt As Long
Dim optnumpackets As Long
Dim optinterrupt As Long

Dim WithEvents ICMP As CICMPCom
Attribute ICMP.VB_VarHelpID = -1








Private Sub Command1_Click()
Rem start ping button

Dim mstring As String
Call ICMP.StartICMP

End Sub

Private Sub Command2_Click()
Rem setvars button

Rem hostname = "127.0.0.1"
Rem optresolve = 1
Rem optnofrag = 1
Rem optpacketlen = 256
Rem opttimeout = 5
Rem optttl = 0
Rem optpacketlen = 128
Rem optrroutenum = 0
Rem opttimestamp = 0
Rem opttos = 0
Rem opttimeout = 5
Rem opttrcrt = 0 ' no trace rt.
Rem optnumpackets = 5


Call ICMP.SetPingVariables(hostname, opttrcrt, optresolve, optnofrag, optruntointerupt, optttl, optpacketlen, optnumpackets, optrroutenum, opttimestamp, opttos, opttimeout)
End Sub

Private Sub Command3_Click()
Call ICMP.RunPing

End Sub

Private Sub Command4_Click()
Call ICMP.StopPing

End Sub

Private Sub Command5_Click()
Call ICMP.StopICMP

End Sub

Private Sub Form_Load()

Set ICMP = New CICMPCom

                                             
End Sub




Private Sub hostname_LostFocus()
mhostname = hostname.Text

End Sub

Private Sub ICMP_PingDoneEvent()
list1.AddItem ("Ping Done!")
   
    
End Sub

Private Sub ICMP_PingMsgEvent(ByVal PingMsg As String)
Dim mystring As String

list1.AddItem (PingMsg)


End Sub

Private Sub MaskEdBox1_Change()

End Sub



Private Sub ICMP_PingTerminated()
list1.AddItem ("Ping Terminated!")
End Sub

Private Sub interrupt_Click()
optinterrupt = interrupt.Value


End Sub

Private Sub nofrag_Click()
optnofrag = nofrag.Value


End Sub

Private Sub numpack_LostFocus()
optnumpackets = numpack.Text
End Sub



Private Sub packlen_LostFocus()
optpacketlen = packlen.Text

End Sub

Private Sub resolve_Click()
 optresolve = resolve.Value
 

End Sub

Private Sub rroute_LostFocus()
optrroutenum = rroute.Text

End Sub



Private Sub timeout_LostFocus()
opttimeout = timeout.Text

End Sub

Private Sub timestamp_LostFocus()
opttimestamp = timestamp.Text


End Sub

Private Sub tos_LostFocus()
opttos = tos.Text

End Sub

Private Sub tracert_Click()
opttrcrt = tracert.Value


End Sub

Private Sub ttl_LostFocus()
optttl = ttl.Text

End Sub
