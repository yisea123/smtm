///
///	Description:
///			C# class for PCI-9014
///	Author:
///			yuanxiaowei
///	History:
///			2012-9-12  Create, part of APIs implemented
///			2014-4-11  update, all APIs implemented
///
using System;
using System.Runtime.InteropServices;

namespace Pci9014
{
    public class CPci9014
    {      
		//open/close
        [DllImport("Pci9014.dll")] public static extern int p9014_initial( ref int pCardCount, int[] pBoardId);         
        [DllImport("Pci9014.dll")] public static extern int p9014_close();
		
		//pulse input/output configuration
		[DllImport("Pci9014.dll")] public static extern int p9014_set_pls_outmode(int axis, int pls_outmode);
		[DllImport("Pci9014.dll")] public static extern int p9014_set_pls_iptmode(int axis, int pls_iptmode);
		
        [DllImport("Pci9014.dll")] public static extern int p9014_set_t_profile(int axis, double start_vel, double max_vel, double acc, double dec);
		[DllImport("Pci9014.dll")] public static extern int p9014_set_s_profile(int axis, double start_vel, double max_vel, double acc, double dec, double jerk_percent);
		
		//single axis driving functions
		//dist_mode:  0  incremental coordinate; 1 - absolute coordinate
		//vel_mode:   0  low speed mode without acc/dec;
		//			  1 high speed mode without acc/dec;
		//			  2 high speed mode with acc/dec
        [DllImport("Pci9014.dll")] public static extern int p9014_pmove(int axis, int dist, int dist_mode, int vel_mode);
        [DllImport("Pci9014.dll")] public static extern int p9014_vmove(int axis, int plus_dir, int vel_mode);
        [DllImport("Pci9014.dll")] public static extern int p9014_stop(int axis, int emg_stop);
		
		//home return
		//mode:		0	- low speed, ORG only;
		//			2   - low speed,  ORG + EZ;
        [DllImport("Pci9014.dll")] public static extern int p9014_home_config(int axis, int mode, int org_level, int ez_level);
        [DllImport("Pci9014.dll")] public static extern int p9014_home_move(int axis, int plus_dir);
		
		//position counter control
        [DllImport("Pci9014.dll")] public static extern int p9014_set_pos(int axis, int cntr_no,  int pos); 
        [DllImport("Pci9014.dll")] public static extern int p9014_get_pos(int axis, int cntr_no, ref int pPos );
		
		//I/O control
		[DllImport("Pci9014.dll")] public static extern int p9014_set_do(int card_no, uint data);
		[DllImport("Pci9014.dll")] public static extern int p9014_set_do_bit(int card_no, uint bit_no, uint data);
		[DllImport("Pci9014.dll")] public static extern int p9014_get_do(int card_no, ref uint pData);
		[DllImport("Pci9014.dll")] public static extern int p9014_get_di(int card_no, ref uint pData);
        [DllImport("Pci9014.dll")] public static extern int p9014_get_di_bit(int card_no , uint bit_no, ref uint pData);
		
        //axis switch input
        [DllImport("Pci9014.dll")] public static extern int p9014_get_io_status(int axis, ref uint pStatus);
		
		//axis's motion status
		[DllImport("Pci9014.dll")] public static extern int p9014_get_motion_status(int axis, ref uint pStatus);
		[DllImport("Pci9014.dll")] public static extern int p9014_get_current_speed(int axis, ref double pSpeed);
		
		//version information
		[DllImport("Pci9014.dll")] public static extern int p9014_get_version(int axis, ref uint pApi_ver, ref uint pDriver_ver, ref uint pLogic_ver);
		//[DllImport("Pci9014.dll")] public static extern int p9014_get_revision(int card_no, int *pLogic_revision);
		
		//set End Limit Input active level
		[DllImport("Pci9014.dll")] public static extern int p9014_set_el_level(int axis, int active_level);
		
		//set stop mode(decelerate to stop, suddenly stop) on error
		[DllImport("Pci9014.dll")] public static extern int p9014_set_error_stop_mode(int axis, int stop_mode);
		
		//config alarm input
		[DllImport("Pci9014.dll")] public static extern int p9014_set_alarm(int axis, int enable, int active_level); 		
    }
}
