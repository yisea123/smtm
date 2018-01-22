Public Class Form1
    Dim AxisNoArray(64) As Integer
    Private Sub ButtonRun_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonRun.Click
        Dim axis As Integer
        Dim pos As Double
        Dim start_vel, max_vel, accel, decel As Double
        Dim type As Integer
        Dim rc As Integer

        If (ComboBoxAxis.SelectedIndex < 0) Then
            axis = 0
        Else
            axis = AxisNoArray(ComboBoxAxis.SelectedIndex)
        End If

        If (ComboBoxMotionType.SelectedIndex < 0) Then
            type = 0
        Else
            type = ComboBoxMotionType.SelectedIndex
        End If

        pos = CDbl(TextBoxTargetPos.Text)
        start_vel = CDbl(TextBoxStartVel.Text)
        max_vel = CDbl(TextBoxMaxVel.Text)
        accel = CDbl(TextBoxAccel.Text)
        decel = CDbl(TextBoxDecel.Text)

        Pci9014.p9014_set_t_profile(axis, start_vel, max_vel, accel, decel)

        Select Case type
            Case 0
                'abs move
                rc = Pci9014.p9014_pmove(axis, pos, 1, 2)
            Case 1
                'incr move
                rc = Pci9014.p9014_pmove(axis, pos, 0, 2)
            Case 2
                'cont move +
                rc = Pci9014.p9014_vmove(axis, 1, 2)
            Case 3
                'cont move -
                rc = Pci9014.p9014_vmove(axis, 0, 2)
            Case 4
                'home search+
                rc = Pci9014.p9014_home_config(axis, 0, 0, 1)
                rc = Pci9014.p9014_home_move(axis, 1)
            Case 5
                'home search -
                rc = Pci9014.p9014_home_config(axis, 0, 0, 1)
                rc = Pci9014.p9014_home_move(axis, 0)
            Case 6
                'clear pos.
                rc = Pci9014.p9014_set_pos(axis, 0, 0)
                rc = Pci9014.p9014_set_pos(axis, 1, 0)
        End Select

        If rc <> 0 Then
            MsgBox("Drive axis fail, return code: " + rc.ToString())
        End If
    End Sub

    Private Sub ButtonStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonStop.Click
        Dim axis As Integer
        Dim rc As Integer

        If (ComboBoxAxis.SelectedIndex < 0) Then
            axis = 0
        Else
            axis = AxisNoArray(ComboBoxAxis.SelectedIndex)
        End If

        rc = Pci9014.p9014_stop(axis, 0)
        If rc <> 0 Then
            MsgBox("Stop axis fail, return code: " + rc.ToString())
        End If
    End Sub

    Public Sub New()

        ' This call is required by the Windows Form Designer.
        InitializeComponent()

        ' Add any initialization after the InitializeComponent() call.
        Dim card_count As Integer
        Dim card_id_array(16) As Integer
        Dim rc As Integer
        Dim i, j As Integer
        Dim axis As Integer

        rc = Pci9014.p9014_initial(card_count, card_id_array(0))
        If rc <> 0 Then
            MsgBox("Init fail")
        End If
        If card_count < 1 Then
            MsgBox("Find no card")
        End If

        For i = 0 To card_count - 1
            For j = 0 To 3
                axis = card_id_array(i) * 4 + j
                ComboBoxAxis.Items.Add(axis.ToString())
                AxisNoArray(i * 4 + j) = axis
            Next
        Next

        ComboBoxAxis.SelectedIndex = 0  'select first axis

        ComboBoxMotionType.SelectedIndex = 0
        TextBoxStartVel.Text = "1000"
        TextBoxMaxVel.Text = "10000"
        TextBoxAccel.Text = "500000"
        TextBoxDecel.Text = "500000"
        TextBoxTargetPos.Text = "5000"
    End Sub

    Protected Overrides Sub Finalize()
        MyBase.Finalize()

        Pci9014.p9014_close()
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        Dim axis, cmd_pos, enc_pos As Integer
        Dim vel As Double
        Dim status, pel, mel, org, ez, emg As Integer
        Dim util As New PCI9014Util

        If (ComboBoxAxis.SelectedIndex < 0) Then
            axis = 0
        Else
            axis = AxisNoArray(ComboBoxAxis.SelectedIndex)
        End If

        'hear we do not check return value
        Pci9014.p9014_get_pos(axis, 0, cmd_pos)
        Pci9014.p9014_get_pos(axis, 1, enc_pos)
        Pci9014.p9014_get_current_speed(axis, vel)
        Pci9014.p9014_get_motion_status(axis, status)

        util.p9014_get_axis_pel(axis, pel)
        util.p9014_get_axis_mel(axis, mel)
        util.p9014_get_axis_org(axis, org)
        util.p9014_get_axis_ez(axis, ez)
        util.p9014_get_axis_emg(axis, emg)

        TextBoxCurVel.Text = vel.ToString("f2")
        TextBoxCmdPos.Text = cmd_pos.ToString()
        TextBoxEncPos.Text = enc_pos.ToString()
        TextBoxStatus.Text = status.ToString()

        If pel <> 0 Then
            TextBoxPel.Text = "ON"
        Else
            TextBoxPel.Text = "OFF"
        End If

        If mel <> 0 Then
            TextBoxMel.Text = "ON"
        Else
            TextBoxMel.Text = "OFF"
        End If

        If org <> 0 Then
            TextBoxOrg.Text = "ON"
        Else
            TextBoxOrg.Text = "OFF"
        End If

        TextBoxEz.Text = ez.ToString()
        TextBoxEmg.Text = emg.ToString()

    End Sub
End Class
