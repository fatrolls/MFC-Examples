VERSION 5.00
Begin VB.Form frmAdmin 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Mail Server"
   ClientHeight    =   6120
   ClientLeft      =   2850
   ClientTop       =   825
   ClientWidth     =   5940
   ClipControls    =   0   'False
   Icon            =   "AdministratorForm.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   6120
   ScaleWidth      =   5940
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Height          =   375
      Left            =   4725
      TabIndex        =   19
      ToolTipText     =   "Close this Window"
      Top             =   5625
      Width           =   1095
   End
   Begin VB.Frame fraLocalNames 
      Caption         =   "&Local Names"
      ClipControls    =   0   'False
      Height          =   2640
      Left            =   3060
      TabIndex        =   11
      Top             =   2880
      Width           =   2775
      Begin VB.CommandButton cmdAddLocal 
         Caption         =   "&Add"
         Height          =   375
         Left            =   135
         TabIndex        =   21
         ToolTipText     =   "Add Specified Local Name"
         Top             =   720
         Width           =   1095
      End
      Begin VB.CommandButton cmdDeleteLocal 
         Caption         =   "&Delete"
         Height          =   375
         Left            =   1545
         TabIndex        =   18
         ToolTipText     =   "Delete Specified Local Name"
         Top             =   720
         Width           =   1095
      End
      Begin VB.TextBox txtLocalName 
         Height          =   300
         Left            =   765
         TabIndex        =   16
         Top             =   247
         Width           =   1875
      End
      Begin VB.ListBox lstLocalNames 
         Height          =   1035
         Left            =   135
         TabIndex        =   13
         ToolTipText     =   "Select Entry by Double-clicking"
         Top             =   1305
         Width           =   2505
      End
      Begin VB.Label lblLocalName 
         Caption         =   "&Name:"
         Height          =   255
         Left            =   135
         TabIndex        =   17
         ToolTipText     =   "Local Name to Add or Delete"
         Top             =   270
         Width           =   495
      End
   End
   Begin VB.Frame fraDnsNames 
      Caption         =   "&DNS Names"
      ClipControls    =   0   'False
      Height          =   2640
      Left            =   3060
      TabIndex        =   10
      Top             =   45
      Width           =   2775
      Begin VB.CommandButton cmdDnsDelete 
         Caption         =   "&Delete"
         Height          =   375
         Left            =   1440
         TabIndex        =   22
         ToolTipText     =   "Delete Dns Name"
         Top             =   675
         Width           =   1095
      End
      Begin VB.CommandButton cmdDnsAdd 
         Caption         =   "&Add"
         Default         =   -1  'True
         Height          =   375
         Left            =   135
         TabIndex        =   20
         ToolTipText     =   "Add a New Dns Name"
         Top             =   675
         Width           =   1095
      End
      Begin VB.TextBox txtDnsName 
         Height          =   300
         Left            =   765
         TabIndex        =   15
         Top             =   217
         Width           =   1860
      End
      Begin VB.ListBox lstDnsNames 
         Height          =   1230
         Left            =   135
         TabIndex        =   12
         ToolTipText     =   "Select Entry by Double-clicking"
         Top             =   1260
         Width           =   2490
      End
      Begin VB.Label lblDnsName 
         Caption         =   "&Name:"
         Height          =   255
         Left            =   135
         TabIndex        =   14
         ToolTipText     =   "DNS Name to Add or Delete"
         Top             =   240
         Width           =   975
      End
   End
   Begin VB.Frame fraUsers 
      Caption         =   "&Users"
      ClipControls    =   0   'False
      Height          =   5460
      Left            =   90
      TabIndex        =   0
      Top             =   45
      Width           =   2775
      Begin VB.CommandButton cmdUserDelete 
         Caption         =   "&Delete"
         Height          =   375
         Left            =   1515
         TabIndex        =   9
         ToolTipText     =   "Delete Specified User"
         Top             =   1395
         Width           =   1095
      End
      Begin VB.CommandButton cmdUserAdd 
         Caption         =   "&Add"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         ToolTipText     =   "Add the Specified User Account"
         Top             =   1395
         Width           =   1095
      End
      Begin VB.TextBox txtUserEmail 
         Height          =   300
         Left            =   1080
         TabIndex        =   4
         Top             =   937
         Width           =   1530
      End
      Begin VB.TextBox txtPassword 
         Height          =   300
         Left            =   1080
         TabIndex        =   3
         Top             =   577
         Width           =   1530
      End
      Begin VB.TextBox txtUserName 
         Height          =   300
         Left            =   1080
         TabIndex        =   2
         Top             =   217
         Width           =   1530
      End
      Begin VB.ListBox lstUsers 
         Height          =   3180
         Left            =   120
         TabIndex        =   1
         ToolTipText     =   "Select Entry by Double-clicking"
         Top             =   1980
         Width           =   2490
      End
      Begin VB.Label lblEMail 
         Caption         =   "&EMails:"
         Height          =   255
         Left            =   120
         TabIndex        =   7
         ToolTipText     =   "EMail Account of User"
         Top             =   960
         Width           =   975
      End
      Begin VB.Label lblPassword 
         Caption         =   "&Password:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         ToolTipText     =   "User Password"
         Top             =   600
         Width           =   975
      End
      Begin VB.Label lblUserName 
         Caption         =   "U&ser Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         ToolTipText     =   "Name of User"
         Top             =   240
         Width           =   975
      End
   End
End
Attribute VB_Name = "frmAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ===================================================================
' Ultimate TCP/IP v3.0
' Copyright © Dundas Software 1995-1999, all rights reserved
' ===================================================================
'
Option Explicit

Private Sub cmdClose_Click()
    'unload form
    Unload Me
    
End Sub

Private Sub cmdDnsAdd_Click()
    ' add a new DNS name
    
    If txtDnsName = "" Then Exit Sub
    
    Call frmMain.MailServ.DNS_Add(txtDnsName)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub


Private Sub cmdDnsDelete_Click()
    ' delete the selected DNS entry
    
    frmMain.MailServ.DNS_Delete (lstDnsNames.ListIndex)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'release hidden form var
    Set frmAdmin = Nothing
    
End Sub

Private Sub lstDnsNames_Click()
    
    ' get information from mail server
    txtDnsName = frmMain.MailServ.DNS_Get(lstDnsNames.ListIndex)
    
End Sub

Private Sub Form_Load()
    
    'intiialize listboxes
    Call InitBoxes
        
End Sub

Private Sub cmdAddLocal_Click()
    
    If txtLocalName = "" Then Exit Sub
    
    Call frmMain.MailServ.LocalName_Add(txtLocalName)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub

Private Sub cmdDeleteLocal_Click()

    frmMain.MailServ.LocalName_Delete (lstLocalNames.ListIndex)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub

Private Sub lstLocalNames_Click()
    
    txtLocalName = frmMain.MailServ.LocalName_Get(lstLocalNames.ListIndex)
    
End Sub

Private Sub cmdUserAdd_Click()
    
    If txtUserName = "" Or txtPassword = "" Or txtUserEmail = "" Then Exit Sub
    
    Call frmMain.MailServ.User_Add(txtUserName, txtPassword, txtUserEmail)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub

Private Sub cmdUserDelete_Click()
    'delete user account from server
    
    frmMain.MailServ.User_Delete (lstUsers.Text)
    Call InitBoxes ' reinitialize the list boxes
    
End Sub

Private Sub lstUsers_Click()
    
    txtUserName = frmMain.MailServ.User_GetName(lstUsers.ListIndex)
    txtPassword = frmMain.MailServ.User_GetPassword(lstUsers.ListIndex)
    txtUserEmail = frmMain.MailServ.User_GetAddress(lstUsers.ListIndex)

End Sub

Private Sub InitBoxes()
'initialize listboxes

    Dim Index As Long  'while loop variable
    
    ' Initialize all the list boxes
    lstUsers.Clear
    lstDnsNames.Clear
    lstLocalNames.Clear
    
    Index = 0
    While Index < frmMain.MailServ.User_GetCount
        lstUsers.AddItem (frmMain.MailServ.User_GetName(Index))
        Index = Index + 1
    Wend
    
    Index = 0
    While Index < frmMain.MailServ.DNS_GetCount
        lstDnsNames.AddItem (frmMain.MailServ.DNS_Get(Index))
        Index = Index + 1
    Wend
    
    Index = 0
    While Index < frmMain.MailServ.LocalName_GetCount
        lstLocalNames.AddItem (frmMain.MailServ.LocalName_Get(Index))
        Index = Index + 1
    Wend
     
End Sub
