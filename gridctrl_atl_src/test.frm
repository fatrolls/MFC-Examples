VERSION 5.00
Object = "{1A6B8660-58C4-11D3-B221-006097FEBF00}#1.0#0"; "ATLNewGrid.dll"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "Tabctl32.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "Comdlg32.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   9390
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   10890
   LinkTopic       =   "Form1"
   ScaleHeight     =   9390
   ScaleWidth      =   10890
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   9720
      Top             =   2760
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   9375
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   10815
      _ExtentX        =   19076
      _ExtentY        =   16536
      _Version        =   393216
      Tabs            =   4
      TabsPerRow      =   6
      TabHeight       =   520
      TabCaption(0)   =   "Standard"
      TabPicture(0)   =   "test.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label1"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Label7"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Label8"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "ucFixedCols"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "ucFixedRows"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "ucCols"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "ucRows"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "chkShowVerticalLines"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "chkShowHorzLine"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "chkAllowRowRes"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "chkAllowColRes"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "chkEditable"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).Control(12)=   "chkAllowSelection"
      Tab(0).Control(12).Enabled=   0   'False
      Tab(0).Control(13)=   "chkListMode"
      Tab(0).Control(13).Enabled=   0   'False
      Tab(0).Control(14)=   "chkSortOnHeaderClick"
      Tab(0).Control(14).Enabled=   0   'False
      Tab(0).Control(15)=   "chkSingleSelectionMode"
      Tab(0).Control(15).Enabled=   0   'False
      Tab(0).Control(16)=   "chkCell11RO"
      Tab(0).Control(16).Enabled=   0   'False
      Tab(0).Control(17)=   "chkFixedCellItalic"
      Tab(0).Control(17).Enabled=   0   'False
      Tab(0).Control(18)=   "btnChangeFont"
      Tab(0).Control(18).Enabled=   0   'False
      Tab(0).Control(19)=   "btnPrint"
      Tab(0).Control(19).Enabled=   0   'False
      Tab(0).Control(20)=   "btnCancel"
      Tab(0).Control(20).Enabled=   0   'False
      Tab(0).Control(21)=   "btninsertRow"
      Tab(0).Control(21).Enabled=   0   'False
      Tab(0).Control(22)=   "btnDeleteRow"
      Tab(0).Control(22).Enabled=   0   'False
      Tab(0).Control(23)=   "chkEnableToolTips"
      Tab(0).Control(23).Enabled=   0   'False
      Tab(0).Control(24)=   "Grid2"
      Tab(0).Control(24).Enabled=   0   'False
      Tab(0).ControlCount=   25
      TabCaption(1)   =   "Test"
      TabPicture(1)   =   "test.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Grid1"
      Tab(1).Control(1)=   "Frame4"
      Tab(1).Control(2)=   "Frame3"
      Tab(1).Control(3)=   "Frame2"
      Tab(1).Control(4)=   "Frame1"
      Tab(1).ControlCount=   5
      TabCaption(2)   =   "Stress"
      TabPicture(2)   =   "test.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "chkPicture"
      Tab(2).Control(1)=   "Command31"
      Tab(2).Control(2)=   "txtFixedColsToAdd"
      Tab(2).Control(3)=   "txtFixedRowsToAdd"
      Tab(2).Control(4)=   "Picture3"
      Tab(2).Control(5)=   "txtCell"
      Tab(2).Control(6)=   "txtRowCaption"
      Tab(2).Control(7)=   "cmdContinue"
      Tab(2).Control(8)=   "chkBreak"
      Tab(2).Control(9)=   "txtColsToAdd"
      Tab(2).Control(10)=   "txtRowsToAdd"
      Tab(2).Control(11)=   "txtLoopNumber"
      Tab(2).Control(12)=   "Command28"
      Tab(2).Control(13)=   "Command27"
      Tab(2).Control(14)=   "Grid3"
      Tab(2).Control(15)=   "lblCellFont"
      Tab(2).Control(16)=   "Label25"
      Tab(2).Control(17)=   "Label24"
      Tab(2).Control(18)=   "lblMeter"
      Tab(2).Control(19)=   "Label22"
      Tab(2).Control(20)=   "Label21"
      Tab(2).Control(21)=   "Label20"
      Tab(2).Control(22)=   "Label19"
      Tab(2).Control(23)=   "Label18"
      Tab(2).Control(24)=   "Label17"
      Tab(2).Control(25)=   "Label16"
      Tab(2).Control(26)=   "Label15"
      Tab(2).ControlCount=   27
      TabCaption(3)   =   "ConnectionPoint"
      TabPicture(3)   =   "test.frx":0054
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "Command30"
      Tab(3).Control(1)=   "List1"
      Tab(3).Control(2)=   "chkTrue"
      Tab(3).Control(3)=   "Grid4"
      Tab(3).Control(4)=   "Label23"
      Tab(3).Control(5)=   "Line1"
      Tab(3).ControlCount=   6
      Begin VB.CheckBox chkPicture 
         Caption         =   "Cell with picture"
         Height          =   255
         Left            =   -68160
         TabIndex        =   133
         Top             =   4320
         Width           =   1815
      End
      Begin VB.CommandButton Command31 
         Caption         =   "Change Font"
         Height          =   255
         Left            =   -68280
         TabIndex        =   132
         Top             =   3840
         Width           =   1695
      End
      Begin VB.CommandButton Command30 
         Caption         =   "Clear the events list"
         Height          =   255
         Left            =   -70080
         TabIndex        =   130
         Top             =   6360
         Width           =   2295
      End
      Begin VB.ListBox List1 
         Height          =   2205
         ItemData        =   "test.frx":0070
         Left            =   -74160
         List            =   "test.frx":0072
         TabIndex        =   128
         Top             =   5640
         Width           =   3855
      End
      Begin VB.CheckBox chkTrue 
         Caption         =   "Return true for cancel on events"
         Height          =   255
         Left            =   -70080
         TabIndex        =   127
         Top             =   5760
         Width           =   2655
      End
      Begin ATLNEWGRIDLibCtl.Grid Grid4 
         Height          =   3855
         Left            =   -74160
         TabIndex        =   126
         Top             =   1080
         Width           =   7335
         _cx             =   12938
         _cy             =   6800
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         RowCount        =   10
         ColumnCount     =   10
         ColumnResizing  =   -1  'True
         RowResizing     =   -1  'True
         GridLines       =   3
         Editable        =   -1  'True
         FixedRows       =   1
         FixedCols       =   1
         AllowSelection  =   -1  'True
         ListMode        =   0   'False
         HeaderSort      =   -1  'True
         SingleRowSelection=   0   'False
         BackColor       =   8421504
         FixedBackColor  =   12632256
         TextColor       =   0
         TextBackColor   =   16777215
         Color           =   12632256
         FixedTextColor  =   0
         ToolTip         =   -1  'True
         KeepTab         =   0   'False
      End
      Begin VB.TextBox txtFixedColsToAdd 
         Height          =   285
         Left            =   -71400
         TabIndex        =   124
         Text            =   "1"
         Top             =   3084
         Width           =   2055
      End
      Begin VB.TextBox txtFixedRowsToAdd 
         Height          =   285
         Left            =   -71400
         TabIndex        =   122
         Text            =   "1"
         Top             =   2836
         Width           =   2055
      End
      Begin VB.PictureBox Picture3 
         Height          =   615
         Left            =   -71400
         Picture         =   "test.frx":0074
         ScaleHeight     =   555
         ScaleWidth      =   1995
         TabIndex        =   120
         Top             =   3900
         Width           =   2055
      End
      Begin VB.TextBox txtCell 
         Height          =   285
         Left            =   -71400
         TabIndex        =   119
         Text            =   "Cell"
         Top             =   3580
         Width           =   2055
      End
      Begin VB.TextBox txtRowCaption 
         Height          =   285
         Left            =   -71400
         TabIndex        =   118
         Text            =   "Row Caption"
         Top             =   3332
         Width           =   2055
      End
      Begin VB.CommandButton cmdContinue 
         Caption         =   "Continue test"
         Enabled         =   0   'False
         Height          =   255
         Left            =   -67800
         TabIndex        =   117
         Top             =   2460
         Width           =   1695
      End
      Begin VB.CheckBox chkBreak 
         Caption         =   "Break for each loop"
         Height          =   255
         Left            =   -67800
         TabIndex        =   116
         Top             =   2100
         Width           =   1935
      End
      Begin VB.TextBox txtColsToAdd 
         Height          =   285
         Left            =   -71400
         TabIndex        =   115
         Text            =   "20"
         Top             =   2588
         Width           =   2055
      End
      Begin VB.TextBox txtRowsToAdd 
         Height          =   285
         Left            =   -71400
         TabIndex        =   114
         Text            =   "50"
         Top             =   2340
         Width           =   2055
      End
      Begin VB.TextBox txtLoopNumber 
         Height          =   285
         Left            =   -73200
         TabIndex        =   112
         Text            =   "150"
         Top             =   1980
         Width           =   1215
      End
      Begin VB.CommandButton Command28 
         Caption         =   "Stop Test"
         Height          =   255
         Left            =   -71160
         TabIndex        =   108
         Top             =   1620
         Width           =   1695
      End
      Begin VB.CommandButton Command27 
         Caption         =   "Start Stress Test"
         Height          =   255
         Left            =   -71160
         TabIndex        =   104
         Top             =   1260
         Width           =   1695
      End
      Begin ATLNEWGRIDLibCtl.Grid Grid3 
         Height          =   3855
         Left            =   -74640
         TabIndex        =   101
         Top             =   5100
         Width           =   9135
         _cx             =   16113
         _cy             =   6800
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Times New Roman"
            Size            =   14.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         RowCount        =   20
         ColumnCount     =   10
         ColumnResizing  =   -1  'True
         RowResizing     =   -1  'True
         GridLines       =   3
         Editable        =   -1  'True
         FixedRows       =   0
         FixedCols       =   0
         AllowSelection  =   -1  'True
         ListMode        =   0   'False
         HeaderSort      =   -1  'True
         SingleRowSelection=   0   'False
         BackColor       =   8421504
         FixedBackColor  =   12632256
         TextColor       =   0
         TextBackColor   =   12648447
         Color           =   12632256
         FixedTextColor  =   0
         ToolTip         =   -1  'True
         KeepTab         =   0   'False
      End
      Begin ATLNEWGRIDLibCtl.Grid Grid2 
         Height          =   4455
         Left            =   240
         TabIndex        =   1
         Top             =   900
         Width           =   7695
         _cx             =   5080
         _cy             =   5080
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         RowCount        =   50
         ColumnCount     =   10
         ColumnResizing  =   -1  'True
         RowResizing     =   -1  'True
         GridLines       =   3
         Editable        =   -1  'True
         FixedRows       =   1
         FixedCols       =   1
         AllowSelection  =   -1  'True
         ListMode        =   0   'False
         HeaderSort      =   -1  'True
         SingleRowSelection=   0   'False
         BackColor       =   12632256
         FixedBackColor  =   12632256
         TextColor       =   0
         TextBackColor   =   14811135
         Color           =   12632256
         FixedTextColor  =   0
         ToolTip         =   -1  'True
         KeepTab         =   0   'False
      End
      Begin ATLNEWGRIDLibCtl.Grid Grid1 
         Height          =   2655
         Left            =   -74880
         TabIndex        =   7
         Top             =   660
         Width           =   9015
         _cx             =   5080
         _cy             =   5080
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         RowCount        =   50
         ColumnCount     =   10
         ColumnResizing  =   -1  'True
         RowResizing     =   -1  'True
         GridLines       =   3
         Editable        =   -1  'True
         FixedRows       =   1
         FixedCols       =   1
         AllowSelection  =   -1  'True
         ListMode        =   0   'False
         HeaderSort      =   -1  'True
         SingleRowSelection=   0   'False
         BackColor       =   8421504
         FixedBackColor  =   12632256
         TextColor       =   0
         TextBackColor   =   14811135
         Color           =   12632256
         FixedTextColor  =   0
         ToolTip         =   -1  'True
         KeepTab         =   0   'False
      End
      Begin VB.Frame Frame4 
         Caption         =   "Cell Operations"
         Height          =   3015
         Left            =   -74880
         TabIndex        =   65
         Top             =   3420
         Width           =   5775
         Begin VB.CommandButton Command34 
            Caption         =   "EndEllipsis"
            Height          =   255
            Index           =   2
            Left            =   1920
            TabIndex        =   142
            ToolTipText     =   "Set Vertical Cell Align to Center"
            Top             =   2400
            Width           =   975
         End
         Begin VB.CommandButton Command34 
            Caption         =   "WordBreak"
            Height          =   255
            Index           =   1
            Left            =   960
            TabIndex        =   141
            ToolTipText     =   "Set Vertical Cell Align to Bottom"
            Top             =   2400
            Width           =   975
         End
         Begin VB.CommandButton Command34 
            Caption         =   "Normal"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   140
            ToolTipText     =   "Set Vertical Cell Align to Top"
            Top             =   2400
            Width           =   855
         End
         Begin VB.CommandButton Command33 
            Caption         =   "Vert.Top"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   139
            ToolTipText     =   "Set Vertical Cell Align to Top"
            Top             =   2160
            Width           =   855
         End
         Begin VB.CommandButton Command33 
            Caption         =   "Vert.Bottom"
            Height          =   255
            Index           =   1
            Left            =   960
            TabIndex        =   138
            ToolTipText     =   "Set Vertical Cell Align to Bottom"
            Top             =   2160
            Width           =   975
         End
         Begin VB.CommandButton Command33 
            Caption         =   "Vert.Center"
            Height          =   255
            Index           =   2
            Left            =   1920
            TabIndex        =   137
            ToolTipText     =   "Set Vertical Cell Align to Center"
            Top             =   2160
            Width           =   975
         End
         Begin VB.CommandButton Command32 
            Caption         =   "Horz.Center"
            Height          =   255
            Index           =   2
            Left            =   1920
            TabIndex        =   136
            ToolTipText     =   "Set Horizontal Cell Align toCenter"
            Top             =   1920
            Width           =   975
         End
         Begin VB.CommandButton Command32 
            Caption         =   "Horz.Right"
            Height          =   255
            Index           =   1
            Left            =   960
            TabIndex        =   135
            ToolTipText     =   "Set Horizontal Cell Align to Right"
            Top             =   1920
            Width           =   975
         End
         Begin VB.CommandButton Command32 
            Caption         =   "Horz.Left"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   134
            ToolTipText     =   "Set Horizontal Cell Align to Left"
            Top             =   1920
            Width           =   855
         End
         Begin VB.CommandButton Command29 
            Caption         =   "SetCurrentCell"
            Height          =   255
            Left            =   3720
            TabIndex        =   125
            Top             =   240
            Width           =   1335
         End
         Begin VB.ComboBox Combo1 
            Height          =   315
            Left            =   4320
            Style           =   2  'Dropdown List
            TabIndex        =   99
            Top             =   2640
            Width           =   1335
         End
         Begin VB.CommandButton Command26 
            Caption         =   "Clear Cell Pic"
            Height          =   255
            Left            =   3120
            TabIndex        =   98
            Top             =   2760
            Width           =   1095
         End
         Begin VB.PictureBox Picture2 
            Height          =   375
            Left            =   5160
            ScaleHeight     =   315
            ScaleWidth      =   435
            TabIndex        =   97
            Top             =   1440
            Width           =   495
         End
         Begin VB.CommandButton Command25 
            Caption         =   "GET:Cell->Image"
            Height          =   255
            Left            =   1560
            TabIndex        =   96
            Top             =   2760
            Width           =   1575
         End
         Begin VB.PictureBox Picture1 
            Height          =   375
            Left            =   4440
            Picture         =   "test.frx":0146
            ScaleHeight     =   315
            ScaleWidth      =   435
            TabIndex        =   95
            Top             =   1440
            Width           =   495
         End
         Begin VB.CommandButton Command24 
            Caption         =   "PUT:Cell->Image"
            Height          =   255
            Left            =   120
            TabIndex        =   94
            Top             =   2760
            Width           =   1455
         End
         Begin VB.CommandButton Command23 
            Caption         =   "Cell->Font"
            Height          =   255
            Left            =   2040
            TabIndex        =   93
            Top             =   1440
            Width           =   1095
         End
         Begin VB.CommandButton Command22 
            Caption         =   "Cell->Text"
            Height          =   255
            Left            =   3720
            TabIndex        =   92
            Top             =   1080
            Width           =   1215
         End
         Begin VB.CommandButton Command21 
            Caption         =   "Get Cell Font"
            Height          =   255
            Left            =   120
            TabIndex        =   91
            Top             =   1680
            Width           =   1455
         End
         Begin VB.CheckBox Check8 
            Caption         =   "Cell Enabled"
            Height          =   255
            Left            =   2040
            TabIndex        =   79
            Top             =   1680
            Value           =   1  'Checked
            Width           =   1455
         End
         Begin VB.CommandButton Command16 
            Caption         =   "SetCellFont"
            Height          =   255
            Left            =   120
            TabIndex        =   73
            Top             =   1440
            Width           =   1455
         End
         Begin VB.CommandButton Command2 
            Caption         =   "GetText"
            Height          =   255
            Left            =   120
            TabIndex        =   72
            Top             =   495
            Width           =   975
         End
         Begin VB.CommandButton Command1 
            Caption         =   "Set Text"
            Height          =   255
            Left            =   120
            TabIndex        =   71
            Top             =   240
            Width           =   975
         End
         Begin VB.TextBox txtCellCol 
            Height          =   285
            Left            =   1920
            TabIndex        =   70
            Text            =   "2"
            Top             =   480
            Width           =   975
         End
         Begin VB.TextBox txtCellRow 
            Height          =   285
            Left            =   1920
            TabIndex        =   69
            Text            =   "2"
            Top             =   240
            Width           =   975
         End
         Begin VB.TextBox txtVal 
            Height          =   285
            Left            =   1920
            TabIndex        =   68
            Text            =   "Text1"
            Top             =   1080
            Width           =   1695
         End
         Begin VB.CommandButton Command3 
            Caption         =   "SetImage"
            Height          =   255
            Left            =   120
            TabIndex        =   67
            Top             =   855
            Width           =   975
         End
         Begin VB.CommandButton Command4 
            Caption         =   "GetImage"
            Height          =   255
            Left            =   120
            TabIndex        =   66
            Top             =   1110
            Width           =   975
         End
         Begin VB.Label Label26 
            Caption         =   "Label26"
            Height          =   255
            Left            =   4560
            TabIndex        =   145
            Top             =   600
            Width           =   855
         End
         Begin VB.Label Label6 
            Caption         =   "Label6"
            Height          =   255
            Left            =   3480
            TabIndex        =   144
            Top             =   600
            Width           =   615
         End
         Begin VB.Label Label5 
            Caption         =   "Col"
            Height          =   255
            Left            =   1440
            TabIndex        =   78
            Top             =   480
            Width           =   495
         End
         Begin VB.Label Label4 
            Caption         =   "Row"
            Height          =   255
            Left            =   1440
            TabIndex        =   77
            Top             =   240
            Width           =   855
         End
         Begin VB.Label Label3 
            Caption         =   "Result"
            Height          =   255
            Left            =   4800
            TabIndex        =   76
            Top             =   2040
            Width           =   615
         End
         Begin VB.Label Label2 
            Caption         =   "Value"
            Height          =   255
            Left            =   1320
            TabIndex        =   75
            Top             =   1080
            Width           =   495
         End
         Begin VB.Label lblRes 
            Caption         =   "Label1"
            Height          =   375
            Left            =   3120
            TabIndex        =   74
            Top             =   1920
            Width           =   735
         End
      End
      Begin VB.Frame Frame3 
         Caption         =   "Grid Operations"
         ForeColor       =   &H00000000&
         Height          =   2655
         Left            =   -74880
         TabIndex        =   50
         Top             =   6480
         Width           =   5775
         Begin VB.CheckBox Check13 
            Caption         =   "Keep Tab"
            Height          =   255
            Left            =   3480
            TabIndex        =   143
            Top             =   1680
            Width           =   2055
         End
         Begin VB.CheckBox Check12 
            Caption         =   "Enable ToolTips"
            Height          =   255
            Left            =   120
            TabIndex        =   100
            Top             =   2080
            Value           =   1  'Checked
            Width           =   1575
         End
         Begin VB.CheckBox Check11 
            Caption         =   "List mode ?"
            Height          =   255
            Left            =   120
            TabIndex        =   90
            Top             =   1880
            Width           =   1815
         End
         Begin VB.CheckBox Check10 
            Caption         =   "Sort on header click ?"
            Enabled         =   0   'False
            Height          =   255
            Left            =   120
            TabIndex        =   89
            Top             =   2300
            Value           =   1  'Checked
            Width           =   2055
         End
         Begin VB.CheckBox Check9 
            Caption         =   "Single Selection mode ?"
            Enabled         =   0   'False
            Height          =   255
            Left            =   0
            TabIndex        =   88
            Top             =   2640
            Width           =   2535
         End
         Begin VB.CommandButton Command20 
            Caption         =   "SetFixedCols"
            Height          =   255
            Left            =   2160
            TabIndex        =   87
            Top             =   1440
            Width           =   1215
         End
         Begin VB.CommandButton Command19 
            Caption         =   "SetFixedRow"
            Height          =   255
            Left            =   2160
            TabIndex        =   85
            Top             =   1200
            Width           =   1215
         End
         Begin VB.TextBox Text1 
            Height          =   285
            Left            =   3480
            TabIndex        =   84
            Text            =   "1"
            Top             =   1200
            Width           =   495
         End
         Begin VB.CommandButton Command14 
            Caption         =   "AutosizeRows"
            Height          =   255
            Left            =   2160
            TabIndex        =   61
            Top             =   840
            Width           =   1215
         End
         Begin VB.CommandButton Command7 
            Caption         =   "AutosizeCols"
            Height          =   255
            Left            =   2160
            TabIndex        =   60
            Top             =   600
            Width           =   1215
         End
         Begin VB.CheckBox Check7 
            Caption         =   "Grid Editable"
            Height          =   255
            Left            =   120
            TabIndex        =   57
            Top             =   1680
            Value           =   1  'Checked
            Width           =   1215
         End
         Begin VB.CheckBox Check6 
            Caption         =   "Show Horizontal lines"
            Height          =   255
            Left            =   120
            TabIndex        =   54
            Top             =   1080
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CheckBox Check5 
            Caption         =   "Show Vertical Line"
            Height          =   255
            Left            =   120
            TabIndex        =   53
            Top             =   840
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CommandButton Command17 
            Caption         =   "Autosize"
            Height          =   255
            Left            =   120
            TabIndex        =   52
            Top             =   480
            Width           =   975
         End
         Begin VB.CommandButton Command15 
            Caption         =   "SetFont"
            Height          =   255
            Left            =   120
            TabIndex        =   51
            Top             =   240
            Width           =   975
         End
         Begin VB.Label Label9 
            Caption         =   "Label9"
            Height          =   255
            Left            =   4080
            TabIndex        =   86
            Top             =   1200
            Width           =   1095
         End
         Begin VB.Label Label13 
            Caption         =   "TRUE"
            Height          =   255
            Left            =   1440
            TabIndex        =   58
            Top             =   1920
            Width           =   735
         End
         Begin VB.Label Label12 
            Caption         =   "Lines showed"
            Height          =   255
            Left            =   120
            TabIndex        =   56
            Top             =   1320
            Width           =   1095
         End
         Begin VB.Label Label11 
            Caption         =   "3"
            Height          =   255
            Left            =   1440
            TabIndex        =   55
            Top             =   1320
            Width           =   495
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "Column Operations"
         Height          =   2835
         Left            =   -69000
         TabIndex        =   32
         Top             =   6300
         Width           =   4575
         Begin VB.CommandButton DeleteColumn 
            Caption         =   "Delete Column"
            Height          =   255
            Left            =   1920
            TabIndex        =   83
            Top             =   1080
            Width           =   1335
         End
         Begin VB.CommandButton getCurrentCol 
            Caption         =   "GetCurrentCol"
            Height          =   255
            Left            =   120
            TabIndex        =   81
            Top             =   720
            Width           =   1335
         End
         Begin VB.TextBox txtCol 
            Height          =   285
            Left            =   2160
            TabIndex        =   63
            Text            =   "1"
            Top             =   780
            Width           =   1935
         End
         Begin VB.CommandButton Command18 
            Caption         =   "AutosizeColumn"
            Height          =   255
            Left            =   120
            TabIndex        =   62
            Top             =   1680
            Width           =   1335
         End
         Begin VB.TextBox txtColVal 
            Height          =   285
            Left            =   2160
            TabIndex        =   46
            Text            =   "10"
            Top             =   180
            Width           =   1935
         End
         Begin VB.CheckBox Check2 
            Caption         =   "Result"
            Enabled         =   0   'False
            Height          =   255
            Left            =   2280
            TabIndex        =   38
            Top             =   1920
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CheckBox Check1 
            Caption         =   "Allow col resizing ?"
            Height          =   255
            Left            =   120
            TabIndex        =   37
            Top             =   1920
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CommandButton Command13 
            Caption         =   "SetColumnWidth"
            Height          =   255
            Left            =   120
            TabIndex        =   36
            Top             =   1080
            Width           =   1335
         End
         Begin VB.CommandButton Command12 
            Caption         =   "GetColumWidth"
            Height          =   255
            Left            =   120
            TabIndex        =   35
            Top             =   1320
            Width           =   1335
         End
         Begin VB.CommandButton Command9 
            Caption         =   "SetColumnCount"
            Height          =   255
            Left            =   120
            TabIndex        =   34
            Top             =   180
            Width           =   1335
         End
         Begin VB.CommandButton Command8 
            Caption         =   "GetColumnCount"
            Height          =   255
            Left            =   120
            TabIndex        =   33
            Top             =   480
            Width           =   1335
         End
         Begin VB.Label Label14 
            Caption         =   "Col"
            Height          =   255
            Left            =   1680
            TabIndex        =   64
            Top             =   780
            Width           =   495
         End
         Begin VB.Label lblColRes 
            Caption         =   "Label9"
            Height          =   255
            Left            =   2160
            TabIndex        =   47
            Top             =   520
            Width           =   1935
         End
      End
      Begin VB.CheckBox chkEnableToolTips 
         Caption         =   "Enable Titletips"
         Height          =   255
         Left            =   5040
         TabIndex        =   31
         Top             =   5580
         Value           =   1  'Checked
         Width           =   1695
      End
      Begin VB.CommandButton btnDeleteRow 
         Caption         =   "Delete Row"
         Height          =   255
         Left            =   2880
         TabIndex        =   30
         Top             =   5580
         Width           =   1215
      End
      Begin VB.CommandButton btninsertRow 
         Caption         =   "Insert Row"
         Height          =   255
         Left            =   1440
         TabIndex        =   29
         Top             =   5580
         Width           =   1215
      End
      Begin VB.CommandButton btnCancel 
         Cancel          =   -1  'True
         Caption         =   "Cancel"
         Height          =   375
         Left            =   8640
         TabIndex        =   25
         Top             =   7200
         Width           =   1455
      End
      Begin VB.CommandButton btnPrint 
         Caption         =   "Print..."
         Enabled         =   0   'False
         Height          =   375
         Left            =   8640
         TabIndex        =   24
         Top             =   6600
         Width           =   1455
      End
      Begin VB.CommandButton btnChangeFont 
         Caption         =   "Change Font..."
         Height          =   375
         Left            =   8640
         TabIndex        =   23
         Top             =   6120
         Width           =   1455
      End
      Begin VB.CheckBox chkFixedCellItalic 
         Caption         =   "Fixed cells italic ?"
         Height          =   255
         Left            =   8280
         TabIndex        =   22
         Top             =   5580
         Width           =   1815
      End
      Begin VB.CheckBox chkCell11RO 
         Caption         =   "Cell (1,1) Read-only ?"
         Height          =   255
         Left            =   8280
         TabIndex        =   21
         Top             =   5220
         Width           =   2055
      End
      Begin VB.CheckBox chkSingleSelectionMode 
         Caption         =   "Single Selection mode ?"
         Enabled         =   0   'False
         Height          =   255
         Left            =   8280
         TabIndex        =   20
         Top             =   4860
         Width           =   2055
      End
      Begin VB.CheckBox chkSortOnHeaderClick 
         Caption         =   "Sort on header click ?"
         Enabled         =   0   'False
         Height          =   255
         Left            =   8280
         TabIndex        =   19
         Top             =   4620
         Value           =   1  'Checked
         Width           =   2055
      End
      Begin VB.CheckBox chkListMode 
         Caption         =   "List mode ?"
         Height          =   255
         Left            =   8280
         TabIndex        =   18
         Top             =   4380
         Width           =   1815
      End
      Begin VB.CheckBox chkAllowSelection 
         Caption         =   "Allow selection ?"
         Height          =   255
         Left            =   8280
         TabIndex        =   17
         Top             =   4020
         Value           =   1  'Checked
         Width           =   2055
      End
      Begin VB.CheckBox chkEditable 
         Caption         =   "Editable ?"
         Height          =   195
         Left            =   8280
         TabIndex        =   16
         Top             =   3780
         Value           =   1  'Checked
         Width           =   1575
      End
      Begin VB.CheckBox chkAllowColRes 
         Caption         =   "Allow Column resizing"
         Height          =   195
         Left            =   8280
         TabIndex        =   15
         Top             =   3420
         Value           =   1  'Checked
         Width           =   1935
      End
      Begin VB.CheckBox chkAllowRowRes 
         Caption         =   "Allow Row resizing"
         Height          =   255
         Left            =   8280
         TabIndex        =   14
         Top             =   3180
         Value           =   1  'Checked
         Width           =   2055
      End
      Begin VB.CheckBox chkShowHorzLine 
         Caption         =   "Show Horz. lines"
         Height          =   195
         Left            =   8280
         TabIndex        =   13
         Top             =   2820
         Value           =   1  'Checked
         Width           =   2055
      End
      Begin VB.CheckBox chkShowVerticalLines 
         Caption         =   "Show Vertical lines"
         Height          =   255
         Left            =   8280
         TabIndex        =   12
         Top             =   2580
         Value           =   1  'Checked
         Width           =   1935
      End
      Begin Project1.UserControl1 ucRows 
         Height          =   255
         Left            =   8280
         TabIndex        =   8
         Top             =   1140
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   450
         Caption         =   "Rows"
         Value           =   "50"
      End
      Begin VB.Frame Frame1 
         Caption         =   "Row Operations"
         Height          =   2655
         Left            =   -69000
         TabIndex        =   2
         Top             =   3660
         Width           =   4575
         Begin VB.CommandButton DeleteRow 
            Caption         =   "Delete row"
            Height          =   255
            Left            =   1800
            TabIndex        =   82
            Top             =   1080
            Width           =   1335
         End
         Begin VB.CommandButton getCurrentRow 
            Caption         =   "GetCurrentRow"
            Height          =   255
            Left            =   120
            TabIndex        =   80
            Top             =   720
            Width           =   1335
         End
         Begin VB.CommandButton Command6 
            Caption         =   "AutosizeRow"
            Height          =   255
            Left            =   120
            TabIndex        =   59
            Top             =   1680
            Width           =   1335
         End
         Begin VB.TextBox txtRow 
            Height          =   285
            Left            =   2160
            TabIndex        =   48
            Text            =   "1"
            Top             =   780
            Width           =   1935
         End
         Begin VB.TextBox Text2 
            Height          =   285
            Left            =   1560
            TabIndex        =   45
            Text            =   "1"
            Top             =   2280
            Width           =   735
         End
         Begin VB.CommandButton Command5 
            Caption         =   "Insert ROW at"
            Height          =   255
            Left            =   120
            TabIndex        =   44
            Top             =   2280
            Width           =   1215
         End
         Begin VB.TextBox Text3 
            Height          =   285
            Left            =   2400
            TabIndex        =   43
            Text            =   "Caption"
            Top             =   2280
            Width           =   2055
         End
         Begin VB.TextBox txtRowVal 
            Height          =   285
            Left            =   2160
            TabIndex        =   41
            Text            =   "50"
            Top             =   180
            Width           =   1935
         End
         Begin VB.CheckBox Check4 
            Caption         =   "Allow Row resizing ?"
            Height          =   255
            Left            =   120
            TabIndex        =   40
            Top             =   1920
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CheckBox Check3 
            Caption         =   "Result"
            Enabled         =   0   'False
            Height          =   255
            Left            =   2280
            TabIndex        =   39
            Top             =   1920
            Value           =   1  'Checked
            Width           =   1815
         End
         Begin VB.CommandButton GetRowCount 
            Caption         =   "GetRowCount"
            Height          =   255
            Left            =   120
            TabIndex        =   6
            Top             =   480
            Width           =   1335
         End
         Begin VB.CommandButton Command10 
            Caption         =   "SetRowHeight"
            Height          =   255
            Left            =   120
            TabIndex        =   5
            Top             =   1080
            Width           =   1335
         End
         Begin VB.CommandButton Command11 
            Caption         =   "GetRowHeight"
            Height          =   255
            Left            =   120
            TabIndex        =   4
            Top             =   1320
            Width           =   1335
         End
         Begin VB.CommandButton SetRowCount 
            Caption         =   "SetRowCount"
            Height          =   255
            Left            =   120
            TabIndex        =   3
            Top             =   180
            Width           =   1335
         End
         Begin VB.Label Label10 
            Caption         =   "Row"
            Height          =   255
            Left            =   1680
            TabIndex        =   49
            Top             =   780
            Width           =   495
         End
         Begin VB.Label lblRowRes 
            Caption         =   "Label9"
            Height          =   255
            Left            =   2160
            TabIndex        =   42
            Top             =   520
            Width           =   1935
         End
      End
      Begin Project1.UserControl1 ucCols 
         Height          =   255
         Left            =   8280
         TabIndex        =   9
         Top             =   1500
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   450
         Caption         =   "Cols"
         Value           =   "10"
      End
      Begin Project1.UserControl1 ucFixedRows 
         Height          =   255
         Left            =   8280
         TabIndex        =   10
         Top             =   1980
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   450
         Caption         =   "Fixed Rows"
         Value           =   "1"
      End
      Begin Project1.UserControl1 ucFixedCols 
         Height          =   255
         Left            =   8280
         TabIndex        =   11
         Top             =   2220
         Width           =   1935
         _ExtentX        =   3413
         _ExtentY        =   450
         Caption         =   "Fixed Cols"
         Value           =   "1"
      End
      Begin VB.Label lblCellFont 
         Caption         =   "Cell's font"
         Height          =   375
         Left            =   -68880
         TabIndex        =   131
         Top             =   3000
         Width           =   3255
      End
      Begin VB.Label Label23 
         Caption         =   "Label23"
         Height          =   255
         Left            =   -74160
         TabIndex        =   129
         Top             =   5160
         Width           =   2535
      End
      Begin VB.Line Line1 
         X1              =   -74160
         X2              =   -69720
         Y1              =   5520
         Y2              =   5520
      End
      Begin VB.Label Label25 
         Caption         =   "Fixed Cols for each loop"
         Height          =   255
         Left            =   -74040
         TabIndex        =   123
         Top             =   3180
         Width           =   2055
      End
      Begin VB.Label Label24 
         Caption         =   "Fixed Rows for each loop"
         Height          =   255
         Left            =   -74040
         TabIndex        =   121
         Top             =   2940
         Width           =   2055
      End
      Begin VB.Label lblMeter 
         Alignment       =   1  'Right Justify
         Caption         =   "1"
         Height          =   255
         Left            =   -71640
         TabIndex        =   113
         Top             =   1980
         Width           =   2295
      End
      Begin VB.Label Label22 
         Caption         =   "Cell Picture"
         Height          =   255
         Left            =   -74040
         TabIndex        =   111
         Top             =   3900
         Width           =   1455
      End
      Begin VB.Label Label21 
         Caption         =   "Cell Text"
         Height          =   255
         Left            =   -74040
         TabIndex        =   110
         Top             =   3660
         Width           =   2415
      End
      Begin VB.Label Label20 
         Caption         =   "Caption of the row"
         Height          =   255
         Left            =   -74040
         TabIndex        =   109
         Top             =   3420
         Width           =   2175
      End
      Begin VB.Label Label19 
         Caption         =   "Column to insert for each loop"
         Height          =   255
         Left            =   -74040
         TabIndex        =   107
         Top             =   2700
         Width           =   2295
      End
      Begin VB.Label Label18 
         Caption         =   "Row to insert for each loop"
         Height          =   255
         Left            =   -74040
         TabIndex        =   106
         Top             =   2460
         Width           =   1935
      End
      Begin VB.Label Label17 
         Caption         =   "Loop Number"
         Height          =   255
         Left            =   -74520
         TabIndex        =   105
         Top             =   1980
         Width           =   2055
      End
      Begin VB.Label Label16 
         Caption         =   "Good Luck !"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   18
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   -69000
         TabIndex        =   103
         Top             =   1380
         Width           =   3375
      End
      Begin VB.Label Label15 
         Caption         =   $"test.frx":0248
         Height          =   615
         Left            =   -74640
         TabIndex        =   102
         Top             =   900
         Width           =   8895
      End
      Begin VB.Label Label8 
         Caption         =   $"test.frx":02F4
         Height          =   615
         Left            =   360
         TabIndex        =   28
         Top             =   7140
         Width           =   7335
      End
      Begin VB.Label Label7 
         Caption         =   $"test.frx":03F3
         Height          =   615
         Left            =   360
         TabIndex        =   27
         Top             =   6420
         Width           =   7215
      End
      Begin VB.Label Label1 
         Caption         =   "Features:"
         Height          =   255
         Left            =   360
         TabIndex        =   26
         Top             =   6180
         Width           =   735
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim m_conn As New ADODB.Connection
Dim m_rds As New ADODB.Recordset
Dim contLoop As Boolean
Private Sub TheLoop()
On Error Resume Next

Dim iStart, iStop, iRows, iCols, iFixedRows, iFixedCols, indexLoop, indexRow, indexCol As Long
Dim bPic As Boolean
iRows = CLng(txtRowsToAdd.Text)
iCols = CLng(txtColsToAdd.Text)
iFixedRows = CLng(txtFixedRowsToAdd.Text)
iFixedCols = CLng(txtFixedColsToAdd)
iStart = CLng(lblMeter.Caption)
iStop = CLng(txtLoopNumber.Text)
Dim font As New StdFont
Set font = lblCellFont.font
bPic = chkPicture.Value
For indexLoop = iStart To iStop
    ' Clear the grid
    Grid3.ColumnCount = iCols
    Grid3.RowCount = iRows
    Grid3.FixedCols = iFixedCols
    Grid3.FixedRows = iFixedRows
    
    For indexRow = 0 To iRows - 1
        ' We add the row
        'Grid3.InsertRow indexRow, txtRowCaption.Text
        For indexCol = 0 To iCols - 1
            ' We add the column
            'Grid3.Text(indexRow, indexCol) = txtCell.Text
            Grid3.Cell(indexRow, indexCol).Text = txtCell.Text
            'Grid3.CellFont(indexRow, indexCol) = lblCellFont.font
            Grid3.Cell(indexRow, indexCol).font = lblCellFont.font
            If bPic Then
                Grid3.Cell(indexRow, indexCol).Picture = Picture3.Picture
            End If
        Next indexCol
    Next indexRow
    ' For each loop we resize the grid
    Grid3.AutoSize
    ' End of the loop see chkbreak
    lblMeter.Caption = CStr(indexLoop)
    If chkBreak.Value Then
        lblMeter.Caption = CStr(indexLoop + 1)
        Exit Sub
    End If
    DoEvents
    If contLoop = False Then
        lblMeter.Caption = CStr(indexLoop + 1)
        Exit Sub
    End If
Next indexLoop
End Sub
Public Function getFont() As StdFont
    CommonDialog1.CancelError = True
    On Error GoTo errHandler
    CommonDialog1.Flags = cdlCFScreenFonts
    CommonDialog1.ShowFont
    Dim X As New StdFont
    X.Bold = CommonDialog1.FontBold
    X.Name = CommonDialog1.FontName
    X.Italic = CommonDialog1.FontItalic
    X.Size = CommonDialog1.FontSize
    X.Strikethrough = CommonDialog1.FontStrikethru
    X.Underline = CommonDialog1.FontUnderline
    Set getFont = X
    Exit Function
errHandler:
    Set getFont = Me.font
End Function

Private Sub btnChangeFont_Click()
    Grid1.font = getFont()
End Sub

Private Sub btnDeleteRow_Click()
    Dim Row As Integer
    Row = Grid2.CurrentRow
    If Row > 0 Then
        Grid2.DeleteRow Row
    End If

End Sub

Private Sub btninsertRow_Click()
    Dim Row As Integer
    Row = Grid2.CurrentRow
    Grid2.InsertRow Row, "Newest row"
        
End Sub

Private Sub Check1_Click()
On Error Resume Next
    If Check1.Value = vbChecked Then
        Grid1.ColumnResizing = True
    Else
        Grid1.ColumnResizing = False
    End If
    If Grid1.ColumnResizing Then
        Check2.Value = 1
    Else
        Check2.Value = 0
    End If
    
End Sub

Private Sub Check10_Click()
On Error Resume Next
    If Check10.Value = vbChecked Then
        Grid1.HeaderSort = True
    Else
        Grid1.HeaderSort = False
    End If
    ShowLblRes Grid1.HeaderSort
End Sub

Private Sub Check11_Click()
On Error Resume Next
    Check10.Enabled = Check11.Value
    Check9.Enabled = Check11.Value
    If chkListMode.Value = vbChecked Then
        Grid1.ListMode = True
    Else
        Grid1.ListMode = False
    End If
    ShowLblRes Grid1.ListMode
End Sub

Private Sub Check12_Click()
On Error Resume Next
    If Check11.Value = vbChecked Then
        Grid1.ToolTip = True
    Else
        Grid1.ToolTip = False
    End If
    ShowLblRes Grid1.ToolTip
End Sub

Private Sub Check13_Click()
On Error Resume Next
If Check13.Value = vbChecked Then
    Grid1.KeepTab = True
Else
    Grid1.KeepTab = False
End If
End Sub

Private Sub Check4_Click()
If Check4.Value = vbChecked Then
    Grid1.RowResizing = True
Else
    Grid1.RowResizing = False
End If
    If Grid1.RowResizing Then
        Check3.Value = 1
    Else
        Check3.Value = 0
    End If
End Sub

Private Sub Check5_Click()
    ShowLines1
End Sub

Private Sub Check6_Click()
    ShowLines1
End Sub

Private Sub Check7_Click()
On Error Resume Next
If Check7.Value = vbChecked Then
    Grid1.Editable = True
Else
    Grid1.Editable = False
End If
    ShowLblRes Grid1.Editable
End Sub
Private Sub ShowLblRes(val As Boolean)
    If (val) Then
        Label13 = "TRUE"
    Else
        Label13 = "FALSE"
    End If

End Sub

Private Sub Check8_Click()
On Error Resume Next
If Check8.Value = vbChecked Then
    Grid1.CellEnabled(CLng(txtCellRow), CLng(txtCellCol)) = True
Else
    Grid1.CellEnabled(CLng(txtCellRow), CLng(txtCellCol)) = False
End If
End Sub

Private Sub Check9_Click()
    Grid1.SingleRowSelection = Check9.Value
    ShowLblRes Grid1.SingleRowSelection
End Sub

Private Sub chkAllowColRes_Click()
    Grid2.ColumnResizing = chkAllowColRes.Value
End Sub

Private Sub chkAllowRowRes_Click()
     If chkAllowRowRes.Value = vbChecked Then
        Grid2.RowResizing = True
    Else
        Grid2.RowResizing = False
    End If
End Sub

Private Sub chkAllowSelection_Click()
If chkAllowSelection.Value = vbChecked Then
    Grid2.AllowSelection = True
Else
    Grid2.AllowSelection = False
End If

End Sub

Private Sub chkBreak_Click()
    cmdContinue.Enabled = chkBreak.Value
End Sub

Private Sub chkCell11RO_Click()
    If chkCell11RO.Value = vbChecked Then
        Grid2.CellEnabled(1, 1) = False
    Else
        Grid2.CellEnabled(1, 1) = True
    End If
End Sub

Private Sub chkEditable_Click()
If chkEditable.Value = vbChecked Then
    Grid2.Editable = True
Else
    Grid2.Editable = False
End If
End Sub

Private Sub chkEnableToolTips_Click()
    Grid2.ToolTip = chkEnableToolTips.Value
End Sub

Private Sub chkListMode_Click()
    chkSortOnHeaderClick.Enabled = chkListMode.Value
    chkSingleSelectionMode.Enabled = chkListMode.Value
    If chkListMode.Value = vbChecked Then
        Grid2.ListMode = True
    Else
        Grid2.ListMode = False
    End If
End Sub


Private Sub chkShowHorzLine_Click()
    ShowLines
End Sub

Private Sub chkShowVerticalLines_Click()
    ShowLines
End Sub
Private Sub ShowLines1()
' Show grid lines
    If (Check5 And Check6) Then
        Grid1.GridLines = GVL_BOTH
    ElseIf (Check5 And Not Check6) Then
        Grid1.GridLines = GVL_VERT
    ElseIf (Not Check5 And Check6) Then
        Grid1.GridLines = GVL_HORZ
    Else
        Grid1.GridLines = GVL_NONE
    End If
    Label11 = CStr(Grid1.GridLines)
End Sub
Private Sub ShowLines()
' Show grid lines
    If (chkShowVerticalLines And chkShowHorzLine) Then
        Grid2.GridLines = GVL_BOTH
    ElseIf (chkShowVerticalLines And Not chkShowHorzLine) Then
        Grid2.GridLines = GVL_VERT
    ElseIf (Not chkShowVerticalLines And chkShowHorzLine) Then
        Grid2.GridLines = GVL_HORZ
    Else
        Grid2.GridLines = GVL_NONE
    End If
End Sub

Private Sub chkSingleSelectionMode_Click()
If chkSingleSelectionMode.Value = vbChecked Then
    Grid2.SingleRowSelection = True
Else
    Grid2.SingleRowSelection = False
End If
End Sub

Private Sub chkSortOnHeaderClick_Click()
    Grid2.HeaderSort = chkSortOnHeaderClick.Value
End Sub

Private Sub cmdContinue_Click()
contLoop = True
Call TheLoop
End Sub

Private Sub Combo1_Click()
    If Combo1.ListIndex = 0 Then
        Grid1.Cell(txtCellRow, txtCellCol).PictureOrientation = grPictOrientationLeft
    ElseIf Combo1.ListIndex = 1 Then
        Grid1.Cell(txtCellRow, txtCellCol).PictureOrientation = grPictOrientationCenter
    Else
        Grid1.Cell(txtCellRow, txtCellCol).PictureOrientation = grPictOrientationRight
   
    End If
End Sub

Private Sub Command1_Click()
On Error Resume Next
Grid1.Text(CInt(txtCellRow), CInt(txtCellCol)) = txtVal.Text
End Sub

Private Sub Command10_Click()
On Error Resume Next
    Grid1.RowHeight(CInt(txtRow)) = CInt(txtRowVal)
End Sub

Private Sub Command11_Click()
On Error Resume Next
    lblRowRes = Grid1.RowHeight(CInt(txtRow))
End Sub

Private Sub Command12_Click()
On Error Resume Next
    lblRes = Grid1.ColumnWidth(CInt(txtCol))
End Sub

Private Sub Command13_Click()
On Error Resume Next
Grid1.ColumnWidth(CInt(txtCol)) = CInt(txtColVal)
End Sub

Private Sub Command14_Click()
On Error Resume Next
    Grid1.AutosizeRow (-1)
End Sub

Private Sub Command15_Click()
On Error Resume Next

    Grid1.font = getFont()

End Sub

Private Sub Command16_Click()
On Error Resume Next
    Grid1.CellFont(txtCellRow, txtCellCol) = getFont()
End Sub

Private Sub Command17_Click()
On Error Resume Next
    Grid1.AutoSize
End Sub

Private Sub Command18_Click()
On Error Resume Next
    Grid1.AutosizeColumn (CLng(txtCol))
End Sub

Private Sub Command19_Click()
On Error Resume Next
    Grid1.FixedRows = CLng(Text1.Text)
    Label9.Caption = CStr(Grid1.FixedRows)

End Sub

Private Sub Command2_Click()
On Error Resume Next
    lblRes.Caption = Grid1.Text(CLng(txtCellRow), CLng(txtCellCol))
End Sub

Private Sub Command20_Click()
On Error Resume Next
    Grid1.FixedCols = CLng(Text1)
    Label9.Caption = CStr(Grid1.FixedCols)
End Sub

Private Sub Command21_Click()
On Error Resume Next
    Dim X As New StdFont
    Dim msg As String
    Set X = Grid1.CellFont(CLng(txtCellRow.Text), CLng(txtCellCol.Text))
    msg = "The font is " + X.Name + " Dimension is=" + CStr(X.Size)
    msg = msg + " Bold = "
    If X.Bold = True Then
        msg = msg + " TRUE"
    Else
        msg = msg + " FALSE"
    End If
    msg = msg + " Italic = "
    If X.Italic = True Then
        msg = msg + " TRUE"
    Else
        msg = msg + " FALSE"
    End If
    MsgBox msg
    Grid1.CellFont(CLng(txtCellRow.Text), CLng(txtCellCol.Text)) = X
End Sub

Private Sub Command22_Click()
On Error Resume Next
    Grid1.Cell(CInt(txtCellRow), CInt(txtCellCol)).Text = txtVal.Text
End Sub

Private Sub Command23_Click()
On Error Resume Next
    Grid1.Cell(txtCellRow, txtCellCol).font = getFont()
End Sub

Private Sub Command24_Click()
On Error Resume Next
    Grid1.Cell(txtCellRow, txtCellCol).Picture = Picture1.Picture
End Sub

Private Sub Command25_Click()
On Error Resume Next
    Picture2.Picture = Grid1.Cell(txtCellRow, txtCellCol).Picture
End Sub

Private Sub Command26_Click()
On Error Resume Next
    Grid1.Cell(txtCellRow, txtCellCol).Picture = Nothing

End Sub

Private Sub Command27_Click()
' Start the loop
contLoop = True
Call TheLoop
End Sub

Private Sub Command28_Click()
' Stop the loop
contLoop = False
lblMeter.Caption = "1"
End Sub

Private Sub Command29_Click()
On Error Resume Next
    Grid1.CurrentCol = CLng(txtCellCol.Text)
    Grid1.CurrentRow = CLng(txtCellRow.Text)
    Label6.Caption = CStr(Grid1.CurrentRow)
    Label26.Caption = CStr(Grid1.CurrentCol)
End Sub

Private Sub Command3_Click()
On Error Resume Next
    Grid1.Image(CLng(txtCellRow), CLng(txtCellCol)) = CInt(txtVal.Text)
End Sub


Private Sub Command30_Click()
List1.Clear
End Sub

Private Sub Command31_Click()
lblCellFont.font = getFont()
End Sub


Private Sub Command32_Click(Index As Integer)
On Error Resume Next
If Index = 0 Then
   Grid1.Cell(txtCellRow, txtCellCol).HorizontalAlignment = grOrizAlignLeft
ElseIf Index = 1 Then
   Grid1.Cell(txtCellRow, txtCellCol).HorizontalAlignment = grOrizAlignRight
Else
   Grid1.Cell(txtCellRow, txtCellCol).HorizontalAlignment = grOrizAlignCenter
End If
End Sub

Private Sub Command33_Click(Index As Integer)
On Error Resume Next
If Index = 0 Then
   Grid1.Cell(txtCellRow, txtCellCol).VerticalAlignment = grVertAlignTop
ElseIf Index = 1 Then
   Grid1.Cell(txtCellRow, txtCellCol).VerticalAlignment = grVertAlignBottom
Else
   Grid1.Cell(txtCellRow, txtCellCol).VerticalAlignment = grVertAlignCenter
End If

End Sub

Private Sub Command34_Click(Index As Integer)
On Error Resume Next
If Index = 0 Then
   Grid1.Cell(txtCellRow, txtCellCol).BreakingTextWords = grBreakingTWNormal
ElseIf Index = 1 Then
   Grid1.Cell(txtCellRow, txtCellCol).BreakingTextWords = grBreakingTWWordBreak
Else
   Grid1.Cell(txtCellRow, txtCellCol).BreakingTextWords = grBreakingTWEndEllipsis
End If

End Sub

Private Sub Command4_Click()
On Error Resume Next
    lblRes.Caption = CStr(Grid1.Image(CInt(txtRow), CInt(txtCol)))
End Sub

Private Sub Command5_Click()
On Error Resume Next
Grid1.InsertRow CInt(Text2), Text3
End Sub

Private Sub Command6_Click()
On Error Resume Next
    Grid1.AutosizeRow (CLng(txtRow))
End Sub

Private Sub Command7_Click()
On Error Resume Next
    Grid1.AutosizeColumn (-1)
End Sub

Private Sub Command8_Click()
On Error Resume Next
    lblColRes.Caption = CStr(Grid1.ColumnCount)
End Sub

Private Sub Command9_Click()
On Error Resume Next
Grid1.ColumnCount = CInt(txtColVal.Text)
End Sub

Private Sub DeleteColumn_Click()
On Error Resume Next
    Grid1.DeleteColumn CLng(txtCol.Text)
    lblColRes.Caption = CStr(Grid2.ColumnCount)
End Sub

Private Sub DeleteRow_Click()
On Error Resume Next
    Grid1.DeleteRow CLng(txtRow.Text)
    lblRowRes.Caption = CStr(Grid1.RowCount)
End Sub

Private Sub Form_Load()
'    m_conn.Open "dsn=pOracle", "WINRAP", "WINRAP"
'    m_rds.ActiveConnection = m_conn
'    m_rds.CursorLocation = adUseClient
'    m_rds.CursorType = adOpenStatic
'    m_rds.LockType = adLockBatchOptimistic
'Grid2.SimpleConf
contLoop = True
Dim X As New StdFont
Dim Row, Col, res As Integer
For Row = 0 To Grid2.RowCount - 1
    For Col = 0 To Grid1.ColumnCount - 1
        If Row < 1 Then
            Grid2.Text(Row, Col) = "Column " + CStr(Col)
            Grid1.Text(Row, Col) = "Column " + CStr(Col)
        ElseIf Col < 1 Then
            Grid2.Image(Row, Col) = 3
            Grid2.Text(Row, Col) = "Row " + CStr(Row)
            Grid1.Text(Row, Col) = "Row " + CStr(Row)
        Else
            Grid2.Text(Row, Col) = CStr(Row * Col)
            Grid1.Text(Row, Col) = CStr(Row * Col)
        End If
        res = (Row * Col) Mod 15
        If res = 0 And Row > 0 Then
            Grid2.CellBgColor(Row, Col) = RGB(colorRnd, colorRnd, colorRnd)
            Grid1.CellBgColor(Row, Col) = RGB(colorRnd, colorRnd, colorRnd)
            Grid2.CellFgColor(Row, Col) = RGB(255, 0, 0)
            Grid1.CellFgColor(Row, Col) = RGB(255, 0, 0)
        End If
    Next Col
Next Row
'x.Size = 8
'x.Weight = 400
'x.Italic = False
'x.Name = "MS Sans Serif"
'x.Bold = False
'Grid1.Font = x
Grid2.AutoSize
Grid1.AutoSize
Grid2.RowHeight(0) = Grid2.RowHeight(0) * 3 / 2
Grid2.RowHeight(0) = Grid2.RowHeight(0) * 3 / 2
Combo1.Clear
Combo1.AddItem "left"
Combo1.AddItem "center"
Combo1.AddItem "right"
Combo1.ListIndex = 0
End Sub

Private Sub getCurrentCol_Click()
On Error Resume Next
    lblColRes.Caption = CStr(Grid1.CurrentCol)
End Sub

Private Sub getCurrentRow_Click()
On Error Resume Next
    lblRowRes.Caption = CStr(Grid1.CurrentRow)
End Sub

Private Sub GetRowCount_Click()
On Error Resume Next
    lblRowRes.Caption = CStr(Grid1.RowCount)
End Sub

Private Sub Grid4_AfterEdit(ByVal Row As Long, ByVal Col As Long)
    List1.AddItem "AfterEdit Row=" & CStr(Row) & " Col=" & CStr(Col)
    
End Sub

Private Sub Grid4_BeforeEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)
    List1.AddItem "BeforeEdit Row=" & CStr(Row) & " Col=" & CStr(Col)
    Cancel = chkTrue.Value

End Sub

Private Sub Grid4_ColumnClick(ByVal Col As Long)
    List1.AddItem "AfterEdit Col=" & CStr(Col)
End Sub

Private Sub Grid4_EnterCell(ByVal Row As Long, ByVal Col As Long)
    List1.AddItem "EnterCell Row=" & CStr(Row) & " Col=" & CStr(Col)
End Sub

Private Sub Grid4_LeaveCell(ByVal Row As Long, ByVal Col As Long)
    List1.AddItem "LeaveCell Row=" & CStr(Row) & " Col=" & CStr(Col)
End Sub

Private Sub Grid4_RowClick(ByVal Row As Long)
    List1.AddItem "RowClick Row=" & CStr(Row)
End Sub

Private Sub Grid4_SelChanged()
    List1.AddItem "SelChanged"
End Sub

Private Sub Grid4_SelChanging()
    List1.AddItem "SelChanging"
End Sub

Private Sub Grid5_BeforeEdit(ByVal Row As Long, ByVal Col As Long, Cancel As Boolean)

End Sub

Private Sub SetRowCount_Click()
On Error Resume Next
    Grid1.RowCount = CInt(txtRowVal.Text)
End Sub

Private Sub ucCols_Change(newVal As Integer)
    Grid2.ColumnCount = newVal
End Sub

Private Sub ucFixedCols_Change(newVal As Integer)
    If newVal >= 0 Then
        Grid2.FixedCols = newVal
    Else
        ucFixedCols.Value = 0
    End If
End Sub

Private Sub ucFixedRows_Change(newVal As Integer)
    If newVal >= 0 Then
        Grid2.FixedRows = newVal
    Else
        ucFixedRows.Value = 0
    End If
End Sub

Private Sub ucRows_Change(newVal As Integer)
    Grid2.RowCount = newVal
End Sub
Public Function colorRnd()
    Dim X As Integer
    X = 128 + Int(128 * Rnd)
    colorRnd = X
End Function
