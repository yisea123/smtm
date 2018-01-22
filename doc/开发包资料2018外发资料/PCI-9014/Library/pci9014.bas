Attribute VB_Name = "PCI9014"
Option Explicit

'Initialization
Declare Function p9014_initial Lib "pci9014.dll" (pCard_count As Long, pBoard_id As Long) As Long
Declare Function p9014_close Lib "pci9014.dll" () As Long

'Pulse Input/Output Configuration
Declare Function p9014_set_pls_outmode Lib "pci9014.dll" (ByVal axis As Long, ByVal pls_outmode As Long) As Long
Declare Function p9014_set_pls_iptmode Lib "pci9014.dll" (ByVal axis As Long, ByVal pls_iptmode As Long) As Long

'parameter setting
Declare Function p9014_set_t_profile Lib "pci9014.dll" (ByVal axis As Long, ByVal start_vel As Double, ByVal max_vel As Double, ByVal acc As Double, ByVal dec As Double) As Long
Declare Function p9014_set_s_profile Lib "pci9014.dll" (ByVal axis As Long, ByVal start_vel As Double, ByVal max_vel As Double, ByVal acc As Double, ByVal dec As Double, ByVal jerk_percent As Double) As Long

'single axis driving functions
'dist_mode:  0  incremental coordinate; 1 - absolute coordinate
'vel_mode:   0  low speed mode without acc/dec;
'                         1 high speed mode without acc/dec;
'                         2 high speed mode with acc/dec
Declare Function p9014_pmove Lib "pci9014.dll" (ByVal axis As Long, ByVal dist As Long, ByVal dist_mode As Long, ByVal vel_mode As Long) As Long
Declare Function p9014_vmove Lib "pci9014.dll" (ByVal axis As Long, ByVal plus_dir As Long, ByVal vel_mode As Long) As Long
Declare Function p9014_stop Lib "pci9014.dll" (ByVal axis As Long, ByVal emg_stop As Long) As Long

'home return
'mode:          0       - low speed, ORG only;
'                       2   - low speed,  ORG + EZ;
Declare Function p9014_home_config Lib "pci9014.dll" (ByVal axis As Long, ByVal mode As Long, ByVal org_level As Long, ByVal ez_level As Long) As Long
Declare Function p9014_home_move Lib "pci9014.dll" (ByVal axis As Long, ByVal plus_dir As Long) As Long

'position counter control
Declare Function p9014_set_pos Lib "pci9014.dll" (ByVal axis As Long, ByVal cntr_no As Long, ByVal pos As Long) As Long
Declare Function p9014_get_pos Lib "pci9014.dll" (ByVal axis As Long, ByVal cntr_no As Long, pos As Long) As Long

'I/O control
Declare Function p9014_set_do Lib "pci9014.dll" (ByVal card_no As Long, ByVal data As Long) As Long
Declare Function p9014_set_do_bit Lib "pci9014.dll" (ByVal card_no As Long, ByVal bit_no As Long, ByVal data As Long) As Long
Declare Function p9014_get_do Lib "pci9014.dll" (ByVal card_no As Long, pData As Long) As Long
Declare Function p9014_get_di Lib "pci9014.dll" (ByVal card_no As Long, pData As Long) As Long
Declare Function p9014_get_di_bit Lib "pci9014.dll" (ByVal card_no As Long, ByVal bit_no As Long, pData As Long) As Long

'mechanical switch status
Declare Function p9014_get_io_status Lib "pci9014.dll" (ByVal card_no As Long, pStatus As Long) As Long

'motion status
Declare Function p9014_get_motion_status Lib "pci9014.dll" (ByVal axis As Long, pStatus As Long) As Long
Declare Function p9014_get_current_speed Lib "pci9014.dll" (ByVal axis As Long, pSpeed As Double) As Long

'soft limit
Declare Function p9014_set_soft_limit Lib "pci9014.dll" (ByVal axis As Long, ByVal enable As Long, ByVal pl As Long, ByVal ml As Long) As Long

'version
Declare Function p9014_get_version Lib "pci9014.dll" (ByVal card_no As Long, pApi_ver As Long, pDriver_ver As Long, pLogic_ver As Long) As Long

'V1.11
'set End Limit Input active level
Declare Function p9014_set_el_level Lib "pci9014.dll" (ByVal axis As Long, ByVal active_level As Long) As Long

