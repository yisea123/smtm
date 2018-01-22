Module Pci9014
    Declare Function p9014_initial Lib "Pci9014.dll" (ByRef pCard_count As Integer, ByRef pBoard_id As Integer) As Integer
    Declare Function p9014_close Lib "Pci9014.dll" () As Integer
    
    Declare Function p9014_set_pls_outmode Lib "Pci9014.dll" (ByVal axis As Integer, ByVal pls_outmode As Integer) As Integer
    Declare Function p9014_set_pls_iptmode Lib "Pci9014.dll" (ByVal axis As Integer, ByVal pls_iptmode As Integer) As Integer
    
    Declare Function p9014_set_t_profile Lib "Pci9014.dll" (ByVal axis As Integer, ByVal start_vel As Double, ByVal max_vel As Double, ByVal acc As Double, ByVal dec As Double) As Integer
    
    Declare Function p9014_pmove Lib "Pci9014.dll" (ByVal axis As Integer, ByVal dist As Integer, ByVal dist_mode As Integer, ByVal vel_mode As Integer) As Integer
    Declare Function p9014_vmove Lib "Pci9014.dll" (ByVal axis As Integer, ByVal plus_dir As Integer, ByVal vel_mode As Integer) As Integer
    Declare Function p9014_stop Lib "Pci9014.dll" (ByVal axis As Integer, ByVal EmgStop As Integer) As Integer
    
    Declare Function p9014_home_config Lib "Pci9014.dll" (ByVal axis As Integer, ByVal mode As Integer, ByVal org_level As Integer, ByVal ez_level As Integer) As Integer
    Declare Function p9014_home_move Lib "Pci9014.dll" (ByVal axis As Integer, ByVal plus_dir As Integer) As Integer

    Declare Function p9014_get_pos Lib "Pci9014.dll" (ByVal axis As Integer, ByVal cntr_no As Integer, ByRef Pos As Integer) As Integer
    Declare Function p9014_set_pos Lib "Pci9014.dll" (ByVal axis As Integer, ByVal cntr_no As Integer, ByVal pos As Integer) As Integer

    Declare Function p9014_set_do Lib "pci9014.dll" (ByVal card_no As Integer, ByVal data As UInteger) As Integer
    Declare Function p9014_set_do_bit Lib "pci9014.dll" (ByVal card_no As Integer, ByVal bit_no As UInteger, ByVal data As UInteger) As Integer
    Declare Function p9014_get_do Lib "pci9014.dll" (ByVal card_no As Integer, ByRef data As UInteger) As Integer
    Declare Function p9014_get_di Lib "pci9014.dll" (ByVal card_no As Integer, ByRef data As UInteger) As Integer
    Declare Function p9014_get_di_bit Lib "pci9014.dll" (ByVal card_no As Integer, ByVal bit_no As UInteger, ByRef data As UInteger) As Integer


    Declare Function p9014_get_io_status Lib "Pci9014.dll" (ByVal axis As Integer, ByRef status As UInteger) As Integer
    Declare Function p9014_get_motion_status Lib "Pci9014.dll" (ByVal axis As Integer, ByRef status As UInteger) As Integer
    Declare Function p9014_get_current_speed Lib "Pci9014.dll" (ByVal axis As Integer, ByRef pspeed As Double) As Integer

    Declare Function p9014_get_version Lib "Pci9014.dll" (ByVal card_no As Integer, ByRef Api_ver As UInteger, ByRef Driver_ver As UInteger, ByRef Logic_ver As UInteger) As Integer

    'V1.11
    Declare Function p9014_set_el_level Lib "Pci9014.dll" (ByVal axis As Integer, ByVal active_level As Integer) As Integer


End Module