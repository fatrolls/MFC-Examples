VERSION 4.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "VB OLE Automation Controller"
   ClientHeight    =   2490
   ClientLeft      =   2805
   ClientTop       =   3435
   ClientWidth     =   5760
   Height          =   2895
   Left            =   2745
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2490
   ScaleWidth      =   5760
   ShowInTaskbar   =   0   'False
   Top             =   3090
   Width           =   5880
   Begin VB.TextBox txtHourlywage 
      Height          =   375
      Left            =   1440
      TabIndex        =   1
      Top             =   1440
      Width           =   1695
   End
   Begin VB.CommandButton cmdClose 
      Cancel          =   -1  'True
      Caption         =   "Close"
      Height          =   375
      Left            =   3480
      TabIndex        =   3
      Top             =   1440
      Width           =   2055
   End
   Begin VB.TextBox txtHoursWorked 
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   960
      Width           =   1695
   End
   Begin VB.CommandButton cmdCalcGrossPay 
      Caption         =   "&Calculate Gross Pay"
      Default         =   -1  'True
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   960
      Width           =   2055
   End
   Begin VB.Label Label4 
      Caption         =   $"AUTOCTL1.frx":0000
      Height          =   735
      Left            =   120
      TabIndex        =   8
      Top             =   120
      Width           =   5415
   End
   Begin VB.Label lblGrossPay 
      Height          =   255
      Left            =   1440
      TabIndex        =   7
      Top             =   2040
      Width           =   1695
   End
   Begin VB.Label Label3 
      Caption         =   "Gross Pay:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Hourly Wage:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1560
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Hours Worked:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   1335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub cmdCalcGrossPay_Click()
   Dim sTitle As String
   sTitle = "VB OLE Automation Controller"
   
   ' Get outta here if a text box is empty
   If ((txtHoursWorked = "") Or (Val(txtHoursWorked.Text) = 0)) Then
      MsgBox "You must enter the hours worked first!", 48, sTitle
      txtHoursWorked.SetFocus
      Exit Sub
   End If
      
   If ((txtHourlywage = "") Or (Val(txtHourlywage.Text) = 0)) Then
      MsgBox "You must enter the hourly wage first!", 48, sTitle
      txtHourlywage.SetFocus
      Exit Sub
   End If
      
   ' Handle errors
   On Error GoTo CalcGrossPayErr
   
   ' Create some local variables
   Dim fHoursWorked  As Single
   Dim fHourlyWage   As Single
   Dim fResult       As Single
   
   fHoursWorked = CSng(Val(txtHoursWorked.Text))
   fHourlyWage = CSng(Val(txtHourlywage.Text))
   
   ' Create an object
   Dim objAutoController As Object
   
   ' Assign the objAutoController object to the AutoSrv1.Auto1 class
   Set objAutoController = CreateObject("AutoSrv1.Auto1")
   
   ' Call the OLE Automation method from AutoSrv1
   fResult = objAutoController.CalcGrossPay(fHoursWorked, fHourlyWage)
   
   ' Format and display the result
   lblGrossPay.Caption = Format$(CStr(fResult), "Currency")
   
   ' Clean up
   Set objAutoMsg = Nothing
   
   Exit Sub
   
CalcGrossPayErr:
   ' Display error message and exit
   MsgBox Error(Err), 16

   ' Clean up
   Set objAutoMsg = Nothing
   
   Exit Sub
   
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub


Private Sub Form_Load()
   ' Center the form
   Move (Screen.Width - Me.Width) \ 2, (Screen.Height - Me.Height) \ 2
   
   Me.Show
   txtHoursWorked.SetFocus
End Sub


