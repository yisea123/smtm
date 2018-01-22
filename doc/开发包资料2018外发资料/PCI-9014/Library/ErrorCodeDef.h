#ifndef	__ERRORCODEDEF_H__
#define __ERRORCODEDEF_H__

//return code definition
#define RC_SUCCESS	0
#define RC_NO_ERROR	0

//general error code
#define	RC_INVALID_PARAM				1	//invalid parameter
#define RC_ALLOCATE_MEMORY_FAIL  		2	//allocate memory fail
#define RC_QUE_FULL					    3
#define RC_QUE_EMPTY					4
#define RC_DEVICE_DETACH				5	//device detached, cannot detect device
#define RC_ERROR			            6	//unkown error
#define RC_COMM_FAIL					7	//
#define RC_MEMORY_TOOL_SMALL			8	//
#define RC_INVALID_DRIVER				9
#define RC_INSUFFICIENT_RESOURCE		10	//insufficient system resource, create system object fail
#define RC_INVALID_HARDWARE				11
#define RC_DEVICE_ALREADY_OPEN			12

//peripheral error
#define RC_PCI_ACCESS_ERROR		(100 + 0)
#define RC_PCI_CONFIG_ERROR		(100 + 1)
#define RC_PCI_ACCESS_TIMEOUT	(100 + 3)

//MOTION control error
#define RC_MOV_ERR				(200 + 1)		//unknow motion error
#define RC_AXIS_BUSY			(200 + 2)		//the axis is busy
#define RC_INTERP_BUSY			(200 + 3)		//the axis is busy interplating
#define RC_FAIL_SEARCH_HOME		(200 + 4)		//fail to search home
#define RC_EL_ACTIVE			(200 + 5)		//limit switch is active while driving
#define RC_CI_MODE_DISABLED		(200 + 6)		//continuous interpolation mode is disable
#define RC_CI_MODE_ENABLED		(200 + 7)		//continuous interplation mode is enabled
#define RC_DIST_LARGE			(200 + 8)		//distance too large for positioning drive or linear interpolation
#define RC_ARC_LEN_LARGE		(200 + 9)		//arc length too large for circular interpolation
#define RC_DIST_SMALL			(200 + 10)

#endif