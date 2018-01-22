<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label6 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.ComboBoxAxis = New System.Windows.Forms.ComboBox
        Me.TextBoxDecel = New System.Windows.Forms.TextBox
        Me.TextBoxAccel = New System.Windows.Forms.TextBox
        Me.TextBoxMaxVel = New System.Windows.Forms.TextBox
        Me.TextBoxStartVel = New System.Windows.Forms.TextBox
        Me.TextBoxTargetPos = New System.Windows.Forms.TextBox
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.Label16 = New System.Windows.Forms.Label
        Me.TextBoxEmg = New System.Windows.Forms.TextBox
        Me.Label15 = New System.Windows.Forms.Label
        Me.Label14 = New System.Windows.Forms.Label
        Me.Label13 = New System.Windows.Forms.Label
        Me.Label12 = New System.Windows.Forms.Label
        Me.Label11 = New System.Windows.Forms.Label
        Me.Label10 = New System.Windows.Forms.Label
        Me.Label9 = New System.Windows.Forms.Label
        Me.Label8 = New System.Windows.Forms.Label
        Me.TextBoxEz = New System.Windows.Forms.TextBox
        Me.TextBoxOrg = New System.Windows.Forms.TextBox
        Me.TextBoxMel = New System.Windows.Forms.TextBox
        Me.TextBoxPel = New System.Windows.Forms.TextBox
        Me.TextBoxEncPos = New System.Windows.Forms.TextBox
        Me.TextBoxCmdPos = New System.Windows.Forms.TextBox
        Me.TextBoxStatus = New System.Windows.Forms.TextBox
        Me.TextBoxCurVel = New System.Windows.Forms.TextBox
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.Label7 = New System.Windows.Forms.Label
        Me.ButtonStop = New System.Windows.Forms.Button
        Me.ButtonRun = New System.Windows.Forms.Button
        Me.ComboBoxMotionType = New System.Windows.Forms.ComboBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.Label6)
        Me.GroupBox1.Controls.Add(Me.Label5)
        Me.GroupBox1.Controls.Add(Me.Label4)
        Me.GroupBox1.Controls.Add(Me.Label3)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Controls.Add(Me.ComboBoxAxis)
        Me.GroupBox1.Controls.Add(Me.TextBoxDecel)
        Me.GroupBox1.Controls.Add(Me.TextBoxAccel)
        Me.GroupBox1.Controls.Add(Me.TextBoxMaxVel)
        Me.GroupBox1.Controls.Add(Me.TextBoxStartVel)
        Me.GroupBox1.Controls.Add(Me.TextBoxTargetPos)
        Me.GroupBox1.Location = New System.Drawing.Point(12, 21)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(268, 232)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Parameters"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(3, 193)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(125, 12)
        Me.Label6.TabIndex = 11
        Me.Label6.Text = "Deceleration(PPS/s):"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(3, 159)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(125, 12)
        Me.Label5.TabIndex = 10
        Me.Label5.Text = "Acceleration(PPS/s):"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(45, 125)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(83, 12)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "Max Vel(PPS):"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(27, 91)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(101, 12)
        Me.Label3.TabIndex = 8
        Me.Label3.Text = "start Vel.(PPS):"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(51, 57)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(77, 12)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "Target Pos.:"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(93, 23)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(35, 12)
        Me.Label1.TabIndex = 6
        Me.Label1.Text = "Axis:"
        '
        'ComboBoxAxis
        '
        Me.ComboBoxAxis.FormattingEnabled = True
        Me.ComboBoxAxis.Location = New System.Drawing.Point(143, 20)
        Me.ComboBoxAxis.Name = "ComboBoxAxis"
        Me.ComboBoxAxis.Size = New System.Drawing.Size(105, 20)
        Me.ComboBoxAxis.TabIndex = 5
        '
        'TextBoxDecel
        '
        Me.TextBoxDecel.Location = New System.Drawing.Point(143, 194)
        Me.TextBoxDecel.Name = "TextBoxDecel"
        Me.TextBoxDecel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxDecel.TabIndex = 4
        '
        'TextBoxAccel
        '
        Me.TextBoxAccel.Location = New System.Drawing.Point(143, 159)
        Me.TextBoxAccel.Name = "TextBoxAccel"
        Me.TextBoxAccel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxAccel.TabIndex = 3
        '
        'TextBoxMaxVel
        '
        Me.TextBoxMaxVel.Location = New System.Drawing.Point(143, 124)
        Me.TextBoxMaxVel.Name = "TextBoxMaxVel"
        Me.TextBoxMaxVel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxMaxVel.TabIndex = 2
        '
        'TextBoxStartVel
        '
        Me.TextBoxStartVel.Location = New System.Drawing.Point(143, 89)
        Me.TextBoxStartVel.Name = "TextBoxStartVel"
        Me.TextBoxStartVel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxStartVel.TabIndex = 1
        '
        'TextBoxTargetPos
        '
        Me.TextBoxTargetPos.Location = New System.Drawing.Point(143, 54)
        Me.TextBoxTargetPos.Name = "TextBoxTargetPos"
        Me.TextBoxTargetPos.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxTargetPos.TabIndex = 0
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label16)
        Me.GroupBox2.Controls.Add(Me.TextBoxEmg)
        Me.GroupBox2.Controls.Add(Me.Label15)
        Me.GroupBox2.Controls.Add(Me.Label14)
        Me.GroupBox2.Controls.Add(Me.Label13)
        Me.GroupBox2.Controls.Add(Me.Label12)
        Me.GroupBox2.Controls.Add(Me.Label11)
        Me.GroupBox2.Controls.Add(Me.Label10)
        Me.GroupBox2.Controls.Add(Me.Label9)
        Me.GroupBox2.Controls.Add(Me.Label8)
        Me.GroupBox2.Controls.Add(Me.TextBoxEz)
        Me.GroupBox2.Controls.Add(Me.TextBoxOrg)
        Me.GroupBox2.Controls.Add(Me.TextBoxMel)
        Me.GroupBox2.Controls.Add(Me.TextBoxPel)
        Me.GroupBox2.Controls.Add(Me.TextBoxEncPos)
        Me.GroupBox2.Controls.Add(Me.TextBoxCmdPos)
        Me.GroupBox2.Controls.Add(Me.TextBoxStatus)
        Me.GroupBox2.Controls.Add(Me.TextBoxCurVel)
        Me.GroupBox2.Location = New System.Drawing.Point(303, 21)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(262, 268)
        Me.GroupBox2.TabIndex = 1
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Status"
        '
        'Label16
        '
        Me.Label16.AutoSize = True
        Me.Label16.Location = New System.Drawing.Point(90, 229)
        Me.Label16.Name = "Label16"
        Me.Label16.Size = New System.Drawing.Size(29, 12)
        Me.Label16.TabIndex = 17
        Me.Label16.Text = "EMG:"
        '
        'TextBoxEmg
        '
        Me.TextBoxEmg.Location = New System.Drawing.Point(126, 230)
        Me.TextBoxEmg.Name = "TextBoxEmg"
        Me.TextBoxEmg.ReadOnly = True
        Me.TextBoxEmg.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxEmg.TabIndex = 16
        '
        'Label15
        '
        Me.Label15.AutoSize = True
        Me.Label15.Location = New System.Drawing.Point(96, 204)
        Me.Label15.Name = "Label15"
        Me.Label15.Size = New System.Drawing.Size(23, 12)
        Me.Label15.TabIndex = 15
        Me.Label15.Text = "EZ:"
        '
        'Label14
        '
        Me.Label14.AutoSize = True
        Me.Label14.Location = New System.Drawing.Point(90, 179)
        Me.Label14.Name = "Label14"
        Me.Label14.Size = New System.Drawing.Size(29, 12)
        Me.Label14.TabIndex = 14
        Me.Label14.Text = "ORG:"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(90, 154)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(29, 12)
        Me.Label13.TabIndex = 13
        Me.Label13.Text = "MEL:"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(90, 129)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(29, 12)
        Me.Label12.TabIndex = 12
        Me.Label12.Text = "PEL:"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(60, 104)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(59, 12)
        Me.Label11.TabIndex = 11
        Me.Label11.Text = "Enc.Pos.:"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(54, 79)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(65, 12)
        Me.Label10.TabIndex = 10
        Me.Label10.Text = "Cmd. Pos.:"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(84, 54)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(35, 12)
        Me.Label9.TabIndex = 9
        Me.Label9.Text = "Busy:"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(6, 29)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(113, 12)
        Me.Label8.TabIndex = 8
        Me.Label8.Text = "Current Vel.(PPS):"
        '
        'TextBoxEz
        '
        Me.TextBoxEz.Location = New System.Drawing.Point(126, 204)
        Me.TextBoxEz.Name = "TextBoxEz"
        Me.TextBoxEz.ReadOnly = True
        Me.TextBoxEz.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxEz.TabIndex = 7
        '
        'TextBoxOrg
        '
        Me.TextBoxOrg.Location = New System.Drawing.Point(126, 178)
        Me.TextBoxOrg.Name = "TextBoxOrg"
        Me.TextBoxOrg.ReadOnly = True
        Me.TextBoxOrg.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxOrg.TabIndex = 6
        '
        'TextBoxMel
        '
        Me.TextBoxMel.Location = New System.Drawing.Point(126, 152)
        Me.TextBoxMel.Name = "TextBoxMel"
        Me.TextBoxMel.ReadOnly = True
        Me.TextBoxMel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxMel.TabIndex = 5
        '
        'TextBoxPel
        '
        Me.TextBoxPel.Location = New System.Drawing.Point(126, 126)
        Me.TextBoxPel.Name = "TextBoxPel"
        Me.TextBoxPel.ReadOnly = True
        Me.TextBoxPel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxPel.TabIndex = 4
        '
        'TextBoxEncPos
        '
        Me.TextBoxEncPos.Location = New System.Drawing.Point(126, 100)
        Me.TextBoxEncPos.Name = "TextBoxEncPos"
        Me.TextBoxEncPos.ReadOnly = True
        Me.TextBoxEncPos.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxEncPos.TabIndex = 3
        '
        'TextBoxCmdPos
        '
        Me.TextBoxCmdPos.Location = New System.Drawing.Point(126, 74)
        Me.TextBoxCmdPos.Name = "TextBoxCmdPos"
        Me.TextBoxCmdPos.ReadOnly = True
        Me.TextBoxCmdPos.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxCmdPos.TabIndex = 2
        '
        'TextBoxStatus
        '
        Me.TextBoxStatus.Location = New System.Drawing.Point(126, 48)
        Me.TextBoxStatus.Name = "TextBoxStatus"
        Me.TextBoxStatus.ReadOnly = True
        Me.TextBoxStatus.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxStatus.TabIndex = 1
        '
        'TextBoxCurVel
        '
        Me.TextBoxCurVel.Location = New System.Drawing.Point(126, 22)
        Me.TextBoxCurVel.Name = "TextBoxCurVel"
        Me.TextBoxCurVel.ReadOnly = True
        Me.TextBoxCurVel.Size = New System.Drawing.Size(105, 21)
        Me.TextBoxCurVel.TabIndex = 0
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.Label7)
        Me.GroupBox3.Controls.Add(Me.ButtonStop)
        Me.GroupBox3.Controls.Add(Me.ButtonRun)
        Me.GroupBox3.Controls.Add(Me.ComboBoxMotionType)
        Me.GroupBox3.Location = New System.Drawing.Point(12, 295)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(553, 124)
        Me.GroupBox3.TabIndex = 2
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "Command"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(20, 50)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(35, 12)
        Me.Label7.TabIndex = 9
        Me.Label7.Text = "Type:"
        '
        'ButtonStop
        '
        Me.ButtonStop.Location = New System.Drawing.Point(366, 23)
        Me.ButtonStop.Name = "ButtonStop"
        Me.ButtonStop.Size = New System.Drawing.Size(171, 85)
        Me.ButtonStop.TabIndex = 8
        Me.ButtonStop.Text = "STOP"
        Me.ButtonStop.UseVisualStyleBackColor = True
        '
        'ButtonRun
        '
        Me.ButtonRun.Location = New System.Drawing.Point(197, 23)
        Me.ButtonRun.Name = "ButtonRun"
        Me.ButtonRun.Size = New System.Drawing.Size(120, 85)
        Me.ButtonRun.TabIndex = 7
        Me.ButtonRun.Text = "RUN"
        Me.ButtonRun.UseVisualStyleBackColor = True
        '
        'ComboBoxMotionType
        '
        Me.ComboBoxMotionType.FormattingEnabled = True
        Me.ComboBoxMotionType.Items.AddRange(New Object() {"Abs. Move", "Incr. Move", "Cont. Move(+)", "Cont. Move(-)", "Home Search(+)", "Home Search(-)", "Clear Position"})
        Me.ComboBoxMotionType.Location = New System.Drawing.Point(61, 47)
        Me.ComboBoxMotionType.Name = "ComboBoxMotionType"
        Me.ComboBoxMotionType.Size = New System.Drawing.Size(116, 20)
        Me.ComboBoxMotionType.TabIndex = 6
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        Me.Timer1.Interval = 50
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(592, 431)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents TextBoxDecel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxAccel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxMaxVel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxStartVel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxTargetPos As System.Windows.Forms.TextBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents TextBoxEz As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxOrg As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxMel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxPel As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxEncPos As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxCmdPos As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxStatus As System.Windows.Forms.TextBox
    Friend WithEvents TextBoxCurVel As System.Windows.Forms.TextBox
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents ComboBoxAxis As System.Windows.Forms.ComboBox
    Friend WithEvents ButtonStop As System.Windows.Forms.Button
    Friend WithEvents ButtonRun As System.Windows.Forms.Button
    Friend WithEvents ComboBoxMotionType As System.Windows.Forms.ComboBox
    Friend WithEvents Label16 As System.Windows.Forms.Label
    Friend WithEvents TextBoxEmg As System.Windows.Forms.TextBox
    Friend WithEvents Label15 As System.Windows.Forms.Label
    Friend WithEvents Label14 As System.Windows.Forms.Label
    Friend WithEvents Label13 As System.Windows.Forms.Label
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Timer1 As System.Windows.Forms.Timer

End Class
