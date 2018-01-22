VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form1"
   ClientHeight    =   7365
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7275
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7365
   ScaleWidth      =   7275
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame5 
      Caption         =   "Distance"
      Height          =   735
      Left            =   120
      TabIndex        =   31
      ToolTipText     =   "Driving distance in positioning drive"
      Top             =   3240
      Width           =   3375
      Begin VB.TextBox TextDist 
         Height          =   375
         Left            =   1440
         TabIndex        =   32
         Text            =   "Text1"
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.Timer Timer1 
      Interval        =   50
      Left            =   6840
      Top             =   240
   End
   Begin VB.Frame Frame3 
      Caption         =   "Command"
      Height          =   2415
      Left            =   120
      TabIndex        =   17
      Top             =   4680
      Width           =   6615
      Begin VB.CommandButton CommandEmgStop 
         Caption         =   "Emg. Stop"
         Height          =   615
         Left            =   3840
         TabIndex        =   24
         Top             =   1560
         Width           =   1935
      End
      Begin VB.CommandButton CommandSdStop 
         Caption         =   "SD Stop"
         Height          =   615
         Left            =   3840
         TabIndex        =   23
         Top             =   840
         Width           =   1935
      End
      Begin VB.CommandButton CommandRun 
         Caption         =   "Run"
         Height          =   375
         Left            =   3840
         TabIndex        =   22
         Top             =   240
         Width           =   1935
      End
      Begin VB.Frame Frame4 
         Height          =   1935
         Left            =   240
         TabIndex        =   18
         Top             =   240
         Width           =   2895
         Begin VB.OptionButton Option3 
            Caption         =   "Velecity Mode Drive(-)"
            Height          =   255
            Left            =   240
            TabIndex        =   21
            Top             =   1200
            Width           =   2175
         End
         Begin VB.OptionButton Option2 
            Caption         =   "Velecity Mode Drive(+)"
            Height          =   375
            Left            =   240
            TabIndex        =   20
            Top             =   660
            Width           =   2415
         End
         Begin VB.OptionButton Option1 
            Caption         =   "Incr. Positioning Drive"
            Height          =   255
            Left            =   240
            TabIndex        =   19
            Top             =   240
            Width           =   2175
         End
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Motion Status"
      Height          =   4215
      Left            =   3720
      TabIndex        =   1
      Top             =   360
      Width           =   3015
      Begin VB.TextBox TextEmg 
         Height          =   285
         Left            =   1200
         TabIndex        =   36
         Text            =   "Text3"
         Top             =   3840
         Width           =   1695
      End
      Begin VB.TextBox TextEz 
         Height          =   285
         Left            =   1200
         TabIndex        =   35
         Text            =   "Text2"
         Top             =   3405
         Width           =   1695
      End
      Begin VB.TextBox TextOrg 
         Height          =   285
         Left            =   1200
         TabIndex        =   34
         Text            =   "Text1"
         Top             =   2970
         Width           =   1695
      End
      Begin VB.TextBox TextMel 
         Height          =   285
         Left            =   1200
         TabIndex        =   33
         Text            =   "Text1"
         Top             =   2535
         Width           =   1695
      End
      Begin VB.TextBox TextPel 
         Height          =   285
         Left            =   1200
         TabIndex        =   11
         Text            =   "Text9"
         Top             =   2100
         Width           =   1695
      End
      Begin VB.TextBox TextEncPos 
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   10
         Text            =   "Text8"
         Top             =   1665
         Width           =   1695
      End
      Begin VB.TextBox TextCmdPos 
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   9
         Text            =   "Text7"
         Top             =   1230
         Width           =   1695
      End
      Begin VB.TextBox TextStatus 
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   8
         Text            =   "Text6"
         Top             =   795
         Width           =   1695
      End
      Begin VB.TextBox TextCurVel 
         Height          =   285
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   7
         Text            =   "Text5"
         Top             =   360
         Width           =   1695
      End
      Begin VB.Label Label14 
         Caption         =   "EMG:"
         Height          =   255
         Left            =   240
         TabIndex        =   39
         Top             =   3840
         Width           =   495
      End
      Begin VB.Label Label13 
         Caption         =   "EZ:"
         Height          =   255
         Left            =   240
         TabIndex        =   38
         Top             =   3450
         Width           =   615
      End
      Begin VB.Label Label12 
         Caption         =   "ORG:"
         Height          =   255
         Left            =   240
         TabIndex        =   37
         Top             =   3000
         Width           =   615
      End
      Begin VB.Label Label11 
         Caption         =   "MEL:"
         Height          =   255
         Left            =   240
         TabIndex        =   30
         Top             =   2520
         Width           =   495
      End
      Begin VB.Label Label10 
         Caption         =   "PEL:"
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   2160
         Width           =   495
      End
      Begin VB.Label Label9 
         Caption         =   "Enc. Pos.:"
         Height          =   255
         Left            =   240
         TabIndex        =   28
         Top             =   1680
         Width           =   855
      End
      Begin VB.Label Label8 
         Caption         =   "Cmd. Pos.:"
         Height          =   375
         Left            =   240
         TabIndex        =   27
         Top             =   1200
         Width           =   855
      End
      Begin VB.Label Label7 
         Caption         =   "Status:"
         Height          =   375
         Left            =   240
         TabIndex        =   26
         Top             =   840
         Width           =   495
      End
      Begin VB.Label Label6 
         Caption         =   "Cur. Vel.:"
         Height          =   375
         Left            =   240
         TabIndex        =   25
         Top             =   360
         Width           =   855
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Parameter"
      Height          =   2775
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   3375
      Begin VB.TextBox TextDec 
         Height          =   375
         Left            =   1440
         TabIndex        =   6
         Text            =   "Text4"
         Top             =   2160
         Width           =   1575
      End
      Begin VB.TextBox TextAcc 
         Height          =   375
         Left            =   1440
         TabIndex        =   5
         Text            =   "Text3"
         Top             =   1680
         Width           =   1575
      End
      Begin VB.TextBox TextMaxVel 
         Height          =   375
         Left            =   1440
         TabIndex        =   4
         Text            =   "Text2"
         Top             =   1200
         Width           =   1575
      End
      Begin VB.TextBox TextStartVel 
         Height          =   375
         Left            =   1440
         TabIndex        =   3
         Text            =   "Text1"
         Top             =   720
         Width           =   1575
      End
      Begin VB.ComboBox ComboAxisSel 
         Height          =   315
         Left            =   1440
         TabIndex        =   2
         Text            =   "Combo1"
         Top             =   240
         Width           =   1575
      End
      Begin VB.Label Label5 
         Caption         =   "Deceleration:"
         Height          =   375
         Left            =   240
         TabIndex        =   16
         Top             =   2280
         Width           =   975
      End
      Begin VB.Label Label4 
         Caption         =   "acceleration:"
         Height          =   375
         Left            =   240
         TabIndex        =   15
         Top             =   1800
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "max. vel.:"
         Height          =   375
         Left            =   360
         TabIndex        =   14
         Top             =   1200
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "start vel.:"
         Height          =   375
         Left            =   360
         TabIndex        =   13
         Top             =   720
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "Axis:"
         Height          =   375
         Left            =   480
         TabIndex        =   12
         Top             =   360
         Width           =   975
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit     'check syntax strictly

Private Sub CommandEmgStop_Click()
'stop axis without deceleration
Dim axis As Long
Dim rc As Long
rc = 0
axis = Int(ComboAxisSel.Text)
rc = p9014_stop(axis, 0)

'check return code
If rc <> 0 Then
    MsgBox ("Stop axis fail, return code: " + Str(rc))
End If

End Sub

Private Sub CommandRun_Click()
'start to drive axis
Dim axis As Long
Dim rc As Long
Dim mode As Long

mode = 0
rc = 0

If Option1.Value = True Then
    mode = 0
End If

If Option2.Value = True Then
    mode = 1
End If

If Option3.Value = True Then
    mode = 2
End If
    
axis = Int(ComboAxisSel.Text)
rc = p9014_set_t_profile(axis, _
        Int(TextStartVel.Text), _
        Int(TextMaxVel.Text), _
        Int(TextAcc.Text), _
        Int(TextDec.Text))


Select Case mode
Case 0  'positioning driving
    rc = p9014_pmove(axis, Int(TextDist.Text), 0, 2)
Case 1  'forward driving
    rc = p9014_vmove(axis, 1, 2)
Case 2  'backward driving
    rc = p9014_vmove(axis, 0, 2)
End Select

'check return code
If rc <> 0 Then
    MsgBox ("Drive axis fail, return code: " + Str(rc))
End If
End Sub

Private Sub CommandSdStop_Click()
'stop axis with deceleration
Dim axis As Long
Dim rc As Long
rc = 0
axis = Int(ComboAxisSel.Text)
rc = p9014_stop(axis, 0)

'check return code
If rc <> 0 Then
    MsgBox ("Stop axis fail, return code: " + Str(rc))
End If

End Sub

Private Sub Form_Load()
Dim board_count As Long
Dim board_id(16) As Long
Dim rc As Long
Dim i As Integer
rc = 0

'initial motion controller
TextStartVel.Text = "1000"
TextMaxVel.Text = "10000"
TextAcc.Text = "100000"
TextDec.Text = "100000"
TextDist.Text = "50000"

TextCurVel.Text = "0"
TextStatus = "0"
TextCmdPos = "0"
TextEncPos = "0"
TextPel = "OFF"
TextMel = "OFF"

'positioning drive by default
Option1.Value = True

rc = p9014_initial(board_count, board_id(0))
If (0 <> rc) Then
    MsgBox ("Initialize PCI-9014 fail")
    End
End If

If (board_count < 1) Then
    MsgBox ("Find No PCI-9014")
    End
End If

For i = 0 To board_count - 1 Step 1
    ComboAxisSel.AddItem (Str(board_id(i) * 4))
    ComboAxisSel.AddItem (Str(board_id(i) * 4 + 1))
    ComboAxisSel.AddItem (Str(board_id(i) * 4 + 2))
    ComboAxisSel.AddItem (Str(board_id(i) * 4 + 3))
Next i

'set default select
ComboAxisSel.Text = ComboAxisSel.List(0)
End Sub

Private Sub Form_Unload(Cancel As Integer)
'close motion controller
Dim rc As Long
rc = 0
rc = p9014_close()
End Sub


Private Sub Timer1_Timer()

'display status in period
Dim speed As Double
Dim pos As Long
Dim status As Long
Dim rc As Long
Dim axis As Long
Dim pel As Long
Dim mel As Long
Dim org As Long
Dim ez As Long
Dim emg As Long

'current speed
axis = Int(ComboAxisSel.Text)
rc = p9014_get_current_speed(axis, speed)
TextCurVel.Text = Str(speed)

'current command pos.
rc = p9014_get_pos(axis, 0, pos)
TextCmdPos.Text = Str(pos)

'current encoder pos.
rc = p9014_get_pos(axis, 1, pos)
TextEncPos.Text = Str(pos)

'motion status
rc = p9014_get_motion_status(axis, status)
TextStatus.Text = Str(status)

'active state of pel input
rc = p9014_get_pel(axis, pel)
If pel <> 0 Then
    TextPel.Text = "ON"
Else
    TextPel.Text = "OFF"
End If

'active state of mel input
rc = p9014_get_mel(axis, mel)
If mel <> 0 Then
    TextMel.Text = "ON"
Else
    TextMel.Text = "OFF"
End If

'active state of org input
rc = p9014_get_org(axis, org)
If org <> 0 Then
    TextOrg.Text = "ON"
Else
    TextOrg.Text = "OFF"
End If

'active state of ez input
rc = p9014_get_ez(axis, ez)
If ez <> 0 Then
    TextEz.Text = "1"
Else
    TextEz.Text = "0"
End If

rc = p9014_get_emg(axis, emg)
If emg <> 0 Then
    TextEmg.Text = "1"
Else
    TextEmg.Text = "0"
End If

End Sub
