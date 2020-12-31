VERSION 5.00
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.UserControl UserControl1 
   ClientHeight    =   825
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   4800
   ScaleHeight     =   825
   ScaleWidth      =   4800
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   960
      TabIndex        =   1
      Text            =   "0"
      Top             =   240
      Width           =   615
   End
   Begin MSComCtl2.UpDown UpDown1 
      Height          =   285
      Left            =   1560
      TabIndex        =   0
      Top             =   240
      Width           =   240
      _ExtentX        =   423
      _ExtentY        =   503
      _Version        =   393216
      AutoBuddy       =   -1  'True
      BuddyControl    =   "Text1"
      BuddyDispid     =   196610
      OrigLeft        =   2520
      OrigTop         =   240
      OrigRight       =   2760
      OrigBottom      =   525
      Max             =   10000
      SyncBuddy       =   -1  'True
      BuddyProperty   =   65547
      Enabled         =   -1  'True
   End
   Begin VB.Label Label1 
      BorderStyle     =   1  'Fixed Single
      Height          =   285
      Left            =   0
      TabIndex        =   2
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "UserControl1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'Event Declarations:
Event Change(newVal As Integer) 'MappingInfo=Text1,Text1,-1,Change

Private Sub UserControl_Resize()
    Label1.Move 0, 0, Label1.Width, UserControl.Height
    Text1.Move Text1.Left, 0, Text1.Width, UserControl.Height
    UpDown1.Move UpDown1.Left, 0, UpDown1.Width, UserControl.Height
End Sub
'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=Label1,Label1,-1,Caption
Public Property Get Caption() As String
Attribute Caption.VB_Description = "Returns/sets the text displayed in an object's title bar or below an object's icon."
    Caption = Label1.Caption
End Property

Public Property Let Caption(ByVal New_Caption As String)
    Label1.Caption() = New_Caption
    PropertyChanged "Caption"
End Property

'WARNING! DO NOT REMOVE OR MODIFY THE FOLLOWING COMMENTED LINES!
'MappingInfo=Text1,Text1,-1,Text
Public Property Get Value() As String
Attribute Value.VB_Description = "Returns/sets the text contained in the control."
    Value = Text1.Text
End Property

Public Property Let Value(ByVal New_Value As String)
    Text1.Text() = New_Value
    PropertyChanged "Value"
End Property

Private Sub Text1_Change()
    RaiseEvent Change(CInt(Text1.Text))
End Sub

'Load property values from storage
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)

    Label1.Caption = PropBag.ReadProperty("Caption", "Label1")
    Text1.Text = PropBag.ReadProperty("Value", "Text1")
End Sub

'Write property values to storage
Private Sub UserControl_WriteProperties(PropBag As PropertyBag)

    Call PropBag.WriteProperty("Caption", Label1.Caption, "Label1")
    Call PropBag.WriteProperty("Value", Text1.Text, "Text1")
End Sub

