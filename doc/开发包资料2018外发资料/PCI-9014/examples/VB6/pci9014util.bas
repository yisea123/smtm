Attribute VB_Name = "Module1"
Option Explicit     'check syntax strictly

'query PEL input is active or not
Function p9014_get_pel(ByVal axis As Long, ByRef pel As Long) As Long
    Dim status As Long
    Dim rc As Long
    
    rc = p9014_get_io_status(axis, status)
    If status And &H1 Then
        pel = 1
    Else
        pel = 0
    End If
    p9014_get_pel = rc
End Function

'query MEL input  is active or not
Function p9014_get_mel(ByVal axis As Long, ByRef mel As Long) As Long
    Dim status As Long
    Dim rc As Long
    
    rc = p9014_get_io_status(axis, status)
    If status And &H2 Then
        mel = 1
    Else
        mel = 0
    End If
    p9014_get_mel = rc
End Function

'query state of ORG input
Function p9014_get_org(ByVal axis As Long, ByRef org As Long) As Long
    Dim status As Long
    Dim rc As Long
    
    rc = p9014_get_io_status(axis, status)
    If status And &H4 Then
        org = 1
    Else
        org = 0
    End If
    p9014_get_org = rc
End Function

'query state of ez input
Function p9014_get_ez(ByVal axis As Long, ByRef ez As Long) As Long
    Dim status As Long
    Dim rc As Long
    
    rc = p9014_get_io_status(axis, status)
    If status And &H8 Then
        ez = 1
    Else
        ez = 0
    End If
    p9014_get_ez = rc
End Function

'query state of EMG input(low active)
Function p9014_get_emg(ByVal axis As Long, ByRef emg As Long) As Long
    Dim status As Long
    Dim rc As Long
    
    rc = p9014_get_io_status(axis, status)
    If status And &H10 Then
        emg = 1
    Else
        emg = 0
    End If
    p9014_get_emg = rc
End Function

