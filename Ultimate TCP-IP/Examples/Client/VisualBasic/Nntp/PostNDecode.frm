VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{663A8A50-6792-11D3-A4E3-0080C858F182}#1.4#0"; "UTMsg.dll"
Begin VB.Form frmPostNDecode
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Decode and Parse News Article"
   ClientHeight    =   7368
   ClientLeft      =   4596
   ClientTop       =   2844
   ClientWidth     =   6684
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7368
   ScaleWidth      =   6684
   Begin MSComDlg.CommonDialog dlgComDlg
      Left            =   5160
      Top             =   120
      _ExtentX        =   677
      _ExtentY        =   677
      _Version        =   393216
   End
   Begin VB.TextBox txtNewsGroup
      Height          =   372
      Left            =   960
      TabIndex        =   8
      ToolTipText     =   "The news group to which this message was posted"
      Top             =   1560
      Width           =   2412
   End
   Begin VB.TextBox txtDate
      Height          =   372
      Left            =   960
      TabIndex        =   6
      ToolTipText     =   "A string containing the time stamp of the message"
      Top             =   1080
      Width           =   2412
   End
   Begin VB.TextBox txtSubject
      Height          =   372
      Left            =   960
      TabIndex        =   4
      ToolTipText     =   "The subject of the article as parsed by Dundas Message object"
      Top             =   600
      Width           =   2412
   End
   Begin VB.TextBox txtFrom
      Height          =   372
      Left            =   960
      TabIndex        =   2
      ToolTipText     =   "The name of the author of this article"
      Top             =   120
      Width           =   2412
   End
   Begin VB.TextBox txtDecodedMsgBody
      Height          =   4812
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   1
      ToolTipText     =   "The body of the message after decoding it"
      Top             =   2400
      Width           =   6372
   End
   Begin VB.ListBox lstAttachment
      Height          =   1392
      Left            =   3600
      TabIndex        =   0
      ToolTipText     =   "List of the attached files included in the message , to decode each message simply double click on the name of each file"
      Top             =   480
      Width           =   2892
   End
   Begin UTMSGLibCtl.Message utaxMsgObj
      Left            =   4800
      Top             =   2040
   End
   Begin VB.Label lblLabel6
      Caption         =   "Text  Body"
      Height          =   252
      Left            =   240
      TabIndex        =   11
      Top             =   2040
      Width           =   1452
   End
   Begin VB.Label lblLabel5
      Alignment       =   1  'Right Justify
      Caption         =   "Attachments"
      Height          =   252
      Left            =   3600
      TabIndex        =   10
      Top             =   120
      Width           =   972
   End
   Begin VB.Label lblLabel4
      Alignment       =   1  'Right Justify
      Caption         =   "News Group"
      Height          =   372
      Left            =   120
      TabIndex        =   9
      Top             =   1560
      Width           =   732
   End
   Begin VB.Label lblLabel3
      Alignment       =   1  'Right Justify
      Caption         =   "Date"
      Height          =   372
      Left            =   120
      TabIndex        =   7
      Top             =   1080
      Width           =   732
   End
   Begin VB.Label lblLabel2
      Alignment       =   1  'Right Justify
      Caption         =   "Subject"
      Height          =   252
      Left            =   240
      TabIndex        =   5
      Top             =   600
      Width           =   612
   End
   Begin VB.Label lblLabel1
      Alignment       =   1  'Right Justify
      Caption         =   "From"
      Height          =   252
      Left            =   240
      TabIndex        =   3
      Top             =   120
      Width           =   612
   End
End
Attribute VB_Name = "frmPostNDecode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' In this form we will attempt to read the file that we have saved the
' article to
' after we load the message which is to be RFC822, 850, 1036  format
' then we will display the headers and any available attchments

Private Sub Form_Load()
utaxMsgObj.AboutBox

Dim errcode As Long
Dim Response

On Error GoTo errhandler

If utaxMsgObj.Load(frmMain.txtTempDirTxt) <> ecSuccess Then
Response = MsgBox("Unable to find the file you have specified as Temp file, Do you like to locate it ? ", vbYesNo + vbCritical + vbDefaultButton2)
If Response <> vbYes Then
GoTo errhandler
End If
    'comDlg
    dlgComDlg.CancelError = True
    On Error GoTo errhandler
    
    dlgComDlg.ShowOpen
    Exit Sub
   errcode = utaxMsgObj.Load(dlgComDlg.fileName)
    If errcode <> ecSuccess Then
    MsgBox utaxMsgObj.GetErrorText(errcode)
    
    End If
    
End If
    
    utaxMsgObj.GetAttachmentNumber

For Counter = 0 To utaxMsgObj.GetAttachmentNumber + 1
lstAttachment.AddItem utaxMsgObj.GetAttachmentName(Counter)
Next Counter
txtFrom = utaxMsgObj.GetHeaderByType(ftFrom)
txtSubject = utaxMsgObj.GetHeaderByType(ftSubject)
txtDate = utaxMsgObj.GetHeaderByType(ftDate)
txtNewsGroup = utaxMsgObj.GetHeaderByType(ftNewsGroups)
txtDecodedMsgBody = utaxMsgObj.GetMessageBody
Exit Sub
errhandler:
End Sub

' The use Double cliks on the attachment
' looking for decoding it to file
' we will invoke the common control dialog prombting him/her to enter a name to save it to
Private Sub lstAttachment_DblClick()
Dim fileName As String
Dim errcode As Long
errcode = 0

If utaxMsgObj.GetAttachmentNumber > 0 Then
    Response = MsgBox("WARNING: WebPages, executables, and other attachments may contain viruses or scripts that can be harmful to your computer. It is very important to be certain that this file is from a trustworthy source. Are you sure you want to decode and save this file to your computer? ", vbYesNo + vbExclamation + vbDefaultButton2, "Decoding attachment!, NNTP DEMO")
    If Response <> vbYes Then
    GoTo UserCancel
    End If

    dlgComDlg.CancelError = True
    On Error GoTo UserCancel
       dlgComDlg.ShowSave
       fileName = dlgComDlg.fileName
       errcode = utaxMsgObj.DecodeAttachment(lstAttachment.ListIndex, Trim$(fileName))
       MsgBox utaxMsgObj.GetErrorText(errcode)
 End If
 
UserCancel:
End Sub
