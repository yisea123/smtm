#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

typedef struct __AXIS_PARAM_T{
	int output_pulse_mode;
	int	input_pulse_mode;
	int	home_mode;
	int	org_level;
	int	ez_level;
	int el_level;
	
	int vel_profile;
	int vel_mode;
	double start_vel;
	double max_vel;
	double accel;
	double decel;
	double jp;
}AXIS_PARAM_T;

#endif



