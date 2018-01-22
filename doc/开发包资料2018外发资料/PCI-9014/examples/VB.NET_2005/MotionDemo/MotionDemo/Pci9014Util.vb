Public Class PCI9014Util
    Public Function p9014_get_axis_pel(ByVal axis As Integer, ByRef pel As Integer) As Integer
        Dim rc As Integer
        Dim status As UInteger
        rc = p9014_get_io_status(axis, status)

        pel = 0
        If status And &H1 Then
            pel = 1
        End If
        p9014_get_axis_pel = rc
    End Function
    Public Function p9014_get_axis_mel(ByVal axis As Integer, ByRef mel As Integer) As Integer
        Dim rc As Integer
        Dim status As UInteger
        rc = p9014_get_io_status(axis, status)

        mel = 0
        If status And &H2 Then
            mel = 1
        End If
        p9014_get_axis_mel = rc
    End Function
    Public Function p9014_get_axis_org(ByVal axis As Integer, ByRef org As Integer) As Integer
        Dim rc As Integer
        Dim status As UInteger
        rc = p9014_get_io_status(axis, status)

        org = 0
        If status And &H4 Then
            org = 1
        End If
        p9014_get_axis_org = rc
    End Function
    Public Function p9014_get_axis_ez(ByVal axis As Integer, ByRef ez As Integer) As Integer
        Dim rc As Integer
        Dim status As UInteger
        rc = p9014_get_io_status(axis, status)

        ez = 0
        If status And &H8 Then
            ez = 1
        End If
        p9014_get_axis_ez = rc
    End Function
    Public Function p9014_get_axis_emg(ByVal axis As Integer, ByRef emg As Integer) As Integer
        Dim rc As Integer
        Dim status As UInteger
        rc = p9014_get_io_status(axis, status)

        emg = 0
        If status And &H10 Then
            emg = 1
        End If
        p9014_get_axis_emg = rc
    End Function
End Class
