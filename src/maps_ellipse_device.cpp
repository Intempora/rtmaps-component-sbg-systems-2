////////////////////////////////
// RTMaps SDK Component
////////////////////////////////
//TODO : Clock synch.
// widgets.
// units conversions (degrees / radians, km/h, etc.)
////////////////////////////////
// Purpose of this module :
////////////////////////////////

#ifdef __linux__
extern "C"
{
# include <sys/time.h>
}
#endif
#include "maps_ellipse_device.h"	// Includes the header of this component
#include "maps_sbg_ecom_output_types.h"

// Use the macros to declare the inputs
MAPS_BEGIN_INPUTS_DEFINITION(MAPSellipse_device)
MAPS_END_INPUTS_DEFINITION

// Use the macros to declare the outputs
MAPS_BEGIN_OUTPUTS_DEFINITION(MAPSellipse_device)
	{"sbg_ecomdata_out",0,{MAPS::Structure,new MAPSString((const char*)"SbgEComData"),new MAPSString((const char*)NULL)},int(sizeof(SbgEComData)),200,1,1}, //User structure, with default fifosize = 200.
MAPS_END_OUTPUTS_DEFINITION

// Use the macros to declare the properties
MAPS_BEGIN_PROPERTIES_DEFINITION(MAPSellipse_device)
	MAPS_PROPERTY("port_name","COM1",false,false)
	MAPS_PROPERTY("baudrate",115200,false,false)
	MAPS_PROPERTY("configure_device_at_startup",true,false,false)
	MAPS_PROPERTY_ENUM("status_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",8,false,false)
	MAPS_PROPERTY_ENUM("utc_time_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",10,false,false)
	MAPS_PROPERTY_ENUM("imu_data_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",3,false,false)
	MAPS_PROPERTY_ENUM("mag_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("mag_calib_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("EKF_euler_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",3,false,false)
	MAPS_PROPERTY_ENUM("EKF_quat_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("EKF_nav_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",3,false,false)
	MAPS_PROPERTY_ENUM("ship_motion_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_1_vel_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_1_pos_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_1_hdt_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_1_raw_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_2_vel_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_2_pos_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("gps_2_hdt_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("odo_vel_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
//	MAPS_PROPERTY_ENUM("user_heading_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
//	MAPS_PROPERTY_ENUM("user_vel_NED_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
//	MAPS_PROPERTY_ENUM("user_vel_XYZ_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
//	MAPS_PROPERTY_ENUM("user_pos_LLA_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("event_A_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("event_B_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("event_C_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("event_D_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("event_E_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("dvl_bottom_track_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	//MAPS_PROPERTY_ENUM("dvl_water_track_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("ship_motion_hp_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("pressure_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
	MAPS_PROPERTY_ENUM("usbl_output_mode","Disabled|200 Hz|100 Hz|50 Hz|25 Hz|20 Hz|10 Hz|5 Hz|1 Hz|On PPS|On New Data|On Sync A event|On Sync B event|On Sync C event|On Sync D event",0,false,false)
MAPS_END_PROPERTIES_DEFINITION

// Use the macros to declare the actions
MAPS_BEGIN_ACTIONS_DEFINITION(MAPSellipse_device)
MAPS_END_ACTIONS_DEFINITION

// Version 1.1: added configure_device_at_startup property, allows to work with monodirectional serial port.

// Use the macros to declare this component (ig_device) behaviour
MAPS_COMPONENT_DEFINITION(MAPSellipse_device,"ellipse_device","2.0.0",255,
			  MAPS::Threaded,MAPS::Threaded,
			  0, // Nb of inputs
			  -1, // Nb of outputs
			  -1, // Nb of properties
			  0) // Nb of actions

#define CHECK_AND_ERROR(res,msg) 	if (res != SBG_NO_ERROR) { \
		char err_msg[256]; \
		sbgEComErrorToString(res,err_msg); \
		MAPSStreamedString ss; \
		ss << msg << " " << err_msg; \
		Error(ss); \
	}

#define CHECK_AND_DO_AND_ERROR(res,action, msg) 	if (res != SBG_NO_ERROR) { \
        char err_msg[256]; \
        sbgEComErrorToString(res,err_msg); \
        MAPSStreamedString ss; \
        { action; } \
        ss << msg << " " << err_msg; \
        Error(ss); \
    }

#define CHECK_AND_REPORT_ERROR(res,msg) 	if (res != SBG_NO_ERROR) { \
		char err_msg[256]; \
		sbgEComErrorToString(res,err_msg); \
		MAPSStreamedString ss; \
		ss << msg << err_msg; \
		ReportError(ss); \
	}


SbgEComOutputMode GetSbgOutputMode(int prop_value)
{
	switch (prop_value) {
	case 0:
		return SBG_ECOM_OUTPUT_MODE_DISABLED;
	case 1:
		return SBG_ECOM_OUTPUT_MODE_MAIN_LOOP;
	case 2:
		return SBG_ECOM_OUTPUT_MODE_DIV_2;
	case 3:
		return SBG_ECOM_OUTPUT_MODE_DIV_4;
	case 4:
		return SBG_ECOM_OUTPUT_MODE_DIV_8;
	case 5:
		return SBG_ECOM_OUTPUT_MODE_DIV_10;
	case 6:
		return SBG_ECOM_OUTPUT_MODE_DIV_20;
	case 7:
		return SBG_ECOM_OUTPUT_MODE_DIV_40;
	case 8:
		return SBG_ECOM_OUTPUT_MODE_DIV_200;
	case 9:
		return SBG_ECOM_OUTPUT_MODE_PPS;
	case 10:
		return SBG_ECOM_OUTPUT_MODE_NEW_DATA;
	case 11:
		return SBG_ECOM_OUTPUT_MODE_EVENT_IN_A;
	case 12:
		return SBG_ECOM_OUTPUT_MODE_EVENT_IN_B;
	case 13:
		return SBG_ECOM_OUTPUT_MODE_EVENT_IN_C;
	case 14:
		return SBG_ECOM_OUTPUT_MODE_EVENT_IN_D;
	default:
		return SBG_ECOM_OUTPUT_MODE_DISABLED;
	}
}


void MAPSellipse_device::Birth()
{
    _sbgInterface.reset();
    _comHandle.reset();
    _deviceInfo.reset();

	_synch_count = 0;
	_synch_when = 2; //hard coded for now : see maps_gps_NMEA0183 -> 2 = synch every valid frame.
	MAPSString portname = GetStringProperty("port_name");
	int baudrate = (int)GetIntegerProperty("baudrate");

    _sbgInterface = std::make_unique<SbgInterface>();
	SbgErrorCode res = sbgInterfaceSerialCreate(_sbgInterface.get(), (const char*)portname, baudrate);								// Example for Windows serial communication
	CHECK_AND_DO_AND_ERROR(res, _sbgInterface.reset(), "Could not initialize COM port: ");

    _comHandle = std::make_unique<SbgEComHandle>();
	res = sbgEComInit(_comHandle.get(), _sbgInterface.get());
	CHECK_AND_DO_AND_ERROR(res, _comHandle.reset(), "Could not initialize the ECom library: ");

	bool configure_device = GetBoolProperty("configure_device_at_startup");

	if (true == configure_device) {
	    _deviceInfo = std::make_unique<SbgEComDeviceInfo>();
		res = sbgEComCmdGetInfo(_comHandle.get(), _deviceInfo.get());
		CHECK_AND_DO_AND_ERROR(res, _deviceInfo.reset(), "Could not get device information: ");
	}
	// Wait until the device has been initialised
	sbgSleep(50);

	if (true == configure_device) {
		int prop_val;
		prop_val = (int)GetIntegerProperty("status_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_STATUS, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("utc_time_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_UTC_TIME, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("imu_data_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_IMU_DATA, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("mag_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_MAG, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("mag_calib_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_MAG_CALIB, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("EKF_euler_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EKF_EULER, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("EKF_quat_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EKF_QUAT, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("EKF_nav_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EKF_NAV, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("ship_motion_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_SHIP_MOTION, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_1_vel_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS1_VEL, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_1_pos_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS1_POS, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_1_hdt_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS1_HDT, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_1_raw_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS1_RAW, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_2_vel_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS2_VEL, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_2_pos_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS2_POS, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("gps_2_hdt_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_GPS2_HDT, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("odo_vel_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_ODO_VEL, GetSbgOutputMode(prop_val));
		/*
		prop_val = (int)GetIntegerProperty("user_heading_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_USER_HEADING, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("user_vel_NED_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_USER_VEL_NED, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("user_vel_XYZ_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_USER_VEL_XYZ, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("user_pos_LLA_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_USER_POS_LLA, GetSbgOutputMode(prop_val));
		*/
		prop_val = (int)GetIntegerProperty("event_A_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EVENT_A, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("event_B_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EVENT_B, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("event_C_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EVENT_C, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("event_D_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EVENT_D, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("event_E_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_EVENT_E, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("dvl_bottom_track_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_DVL_BOTTOM_TRACK, GetSbgOutputMode(prop_val));
		//prop_val = (int)GetIntegerProperty("dvl_water_track_output_mode");
		//sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_DVL_WATER_TRACK, GetSbgOutputMode(prop_val));
		prop_val = (int)GetIntegerProperty("ship_motion_hp_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_SHIP_MOTION_HP, GetSbgOutputMode(prop_val));
	    sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_AIR_DATA, GetSbgOutputMode(prop_val));
	    prop_val = (int)GetIntegerProperty("pressure_output_mode");
		prop_val = (int)GetIntegerProperty("usbl_output_mode");
		sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_USBL, GetSbgOutputMode(prop_val));
		//prop_val = (int)GetIntegerProperty("num_messages_output_mode");
		//sbgEComCmdOutputSetConf(_comHandle.get(), SBG_ECOM_OUTPUT_PORT_A, SBG_ECOM_CLASS_LOG_ECOM_0, SBG_ECOM_LOG_ECOM_NUM_MESSAGES, GetSbgOutputMode(prop_val));
	}

	sbgEComSetReceiveLogCallback(_comHandle.get(), &MAPSellipse_device::continuousCallbackStatic, this);

}

void MAPSellipse_device::Core() 
{
	SbgErrorCode res = sbgEComHandle(_comHandle.get());

	//
	// Test if we have to release some CPU (no frame received)
	//
	if (res == SBG_NOT_READY)
	{
		//
		// Release CPU
		//
		sbgSleep(1);
	}
}

SbgErrorCode MAPSellipse_device::continuousCallbackStatic(SbgEComHandle* pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData* pLogData, void* pUserArg)
{
	MAPSellipse_device* c = (MAPSellipse_device*)pUserArg;
	return c->continuousCallback(pHandle, msgClass, msg, pLogData);
}

SbgErrorCode MAPSellipse_device::continuousCallback(SbgEComHandle* pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgBinaryLogData* pLogData)
{
	if (NULL == pHandle || pLogData == NULL) {
		return SBG_NULL_POINTER;
	}
	try {
	MAPSTimestamp t=  MAPS::CurrentTime();
	MAPSIOElt* ioeltout = StartWriting(Output(0));
	SbgEComData* ecomdata = (SbgEComData*)ioeltout->Data();
	ecomdata->cmd = msgClass;
	switch(msgClass) {
	case SBG_ECOM_LOG_STATUS:
		ecomdata->logdata.statusData = pLogData->statusData;
		break;
	case SBG_ECOM_LOG_UTC_TIME:
		ecomdata->logdata.utcData    = pLogData->utcData    ;
		break;
	case SBG_ECOM_LOG_IMU_DATA:
		ecomdata->logdata.imuData    = pLogData->imuData    ;
		break;
	case SBG_ECOM_LOG_MAG:
		ecomdata->logdata.magData    = pLogData->magData    ;
		break;
	case SBG_ECOM_LOG_MAG_CALIB:
		ecomdata->logdata.magCalibData    = pLogData->magCalibData    ;
		break;
	case SBG_ECOM_LOG_EKF_EULER:
		ecomdata->logdata.ekfEulerData    = pLogData->ekfEulerData    ;
		break;
	case SBG_ECOM_LOG_EKF_QUAT:
		ecomdata->logdata.ekfQuatData    = pLogData->ekfQuatData    ;
		break;
	case SBG_ECOM_LOG_EKF_NAV:
		ecomdata->logdata.ekfNavData    = pLogData->ekfNavData    ;
		break;
	case SBG_ECOM_LOG_SHIP_MOTION:
		ecomdata->logdata.shipMotionData    = pLogData->shipMotionData    ;
		break;
	case SBG_ECOM_LOG_GPS1_VEL:
	case SBG_ECOM_LOG_GPS2_VEL:
		ecomdata->logdata.gpsVelData    = pLogData->gpsVelData    ;
		break;
	case SBG_ECOM_LOG_GPS1_POS:
	case SBG_ECOM_LOG_GPS2_POS:
		ecomdata->logdata.gpsPosData    = pLogData->gpsPosData    ;
		break;
	case SBG_ECOM_LOG_GPS1_HDT:
	case SBG_ECOM_LOG_GPS2_HDT:
		ecomdata->logdata.gpsHdtData    = pLogData->gpsHdtData    ;
		break;
	case SBG_ECOM_LOG_GPS1_RAW:
		ecomdata->logdata.gpsRawData    = pLogData->gpsRawData    ;
		break;
	case SBG_ECOM_LOG_ODO_VEL:
		ecomdata->logdata.odometerData    = pLogData->odometerData    ;
		break;
		/*
	case SBG_ECOM_LOG_USER_HEADING:
		ecomdata->logdata    = pLogData-    ;
		break;
	case SBG_ECOM_LOG_USER_VEL_NED:
		ecomdata->logdata    = pLogData-    ;
		break;
	case SBG_ECOM_LOG_USER_VEL_XYZ:
		ecomdata->logdata    = pLogData-    ;
		break;
	case SBG_ECOM_LOG_USER_POS_LLA:
		ecomdata->logdata    = pLogData-    ;
		break;
		*/
	case SBG_ECOM_LOG_EVENT_A:
	case SBG_ECOM_LOG_EVENT_B:
	case SBG_ECOM_LOG_EVENT_C:
	case SBG_ECOM_LOG_EVENT_D:
	case SBG_ECOM_LOG_EVENT_E:
		ecomdata->logdata.eventMarker    = pLogData->eventMarker    ;
		break;
	case SBG_ECOM_LOG_DVL_BOTTOM_TRACK:
		ecomdata->logdata.dvlData    = pLogData->dvlData    ;
		break;
	//case SBG_ECOM_LOG_DVL_WATER_TRACK:
	//	ecomdata->logdata    = pLogData-    ;
	//	break;
	case SBG_ECOM_LOG_SHIP_MOTION_HP:
		ecomdata->logdata.shipMotionData    = pLogData->shipMotionData    ;
		break;
	case SBG_ECOM_LOG_AIR_DATA:
		ecomdata->logdata.airData    = pLogData->airData    ;
		break;
	case SBG_ECOM_LOG_USBL:
		ecomdata->logdata.usblData    = pLogData->usblData    ;
		break;
	}

	ioeltout->Timestamp() = t;
	StopWriting(ioeltout);

	int synch_status = 0;
	/*
	if (this->_synchOnGPS) {
		if ((pOutput->deviceStatus >> 18) & 0x1) { //flag UTC 0.25 sec accuracy is set.
			synch_status = 2;
			MAPSAbsoluteTime at;
			at.year = pOutput->utcYear+2000;
			at.month = pOutput->utcMonth;
			at.day = pOutput->utcDay;
			at.hour = pOutput->utcHour;
			at.minutes = pOutput->utcMin;
			at.seconds = pOutput->utcSec;
			at.milliseconds = pOutput->utcNano/1000000;
			at.microseconds = pOutput->utcNano/1000 - at.milliseconds*1000000;
			MAPSTimestamp offset = this->PerformSynchOperation(at);
			if (this->_outputAppliedOffset) {
				OutputOffset(synch_status,offset);
			}
		} else {
			synch_status = 1;
		}
	}
	*/
	} catch (int /*error*/) {
		return SBG_NO_ERROR;
	}
	return SBG_NO_ERROR;
}

void MAPSellipse_device::Death()
{
    if (_comHandle)
		sbgEComClose(_comHandle.get());
    if (_sbgInterface)
        sbgInterfaceDestroy(_sbgInterface.get());

}
/************************************
* RTMaps clock synch
*************************************/
/* This method is called when RTMaps needs to start its current clock. */
void MAPSellipse_device::RunClock()
{
    /*
    Use this function to declare the maximum "real" timespeed that your clock will impose.
    This value can be higher than the "real" timespeed but never lower.
    If this value is much higher than the "real" timespeed, this may result in more CPU consumption,
    whereas lower values result in unaccuracies for pausing functions such as Rest or Wait (so this may
    cause delays during replay for example.
    */
    SetAbsoluteTimeSpeed(1000);
	
	//RunClock is called, so the user is trying to synchronize on the GPS clock.
	_synchOnGPS = true;

	if (MAPS::GetFirstTimestamp() != 0 || MAPS::GetLastTimestamp() != 0) //We've got a Player in the diagram...
	{
		_synchOnGPS = false;
		ReportError("Trying to synchronize the RTMaps clock with the GPS UTC time is not allowed in replay mode.");
	}

	m_MyTimeMonitor.Lock();
	MAPSAbsoluteTime absTime; 
	MAPSellipse_device::GetSystemTime(&absTime);
	m_TimebaseX = MAPS::GetSystemAccurateTiming();

	m_Timebase = MAPSellipse_device::AbsTime2Timestamp(absTime);
    //Retrieve absolute PC clock value.
    m_MyTimeMonitor.Release();

}

void MAPSellipse_device::ShutdownClock()
{
	_synchOnGPS = false;
}

/* This method is called everytime someone in RTMaps asks for the current time*/
MAPSTimestamp MAPSellipse_device::CurrentTime() 
{
    m_MyTimeMonitor.Lock();
    MAPSTimestamp t = m_Timebase + (MAPS::GetSystemAccurateTiming() - m_TimebaseX);
    m_MyTimeMonitor.Release();
    return t;
}

MAPSTimestamp MAPSellipse_device::PerformSynchOperation(MAPSAbsoluteTime& at)
{
	if (false == _synchOnGPS) //Clock is not active.
		return 0;

	if (_synch_when == 0 && _synch_count > 0) //Once at start
		return 0;
	MAPSTimestamp ct = MAPS::CurrentTime();
	if (_synch_count > 0 && _synch_when == 1 && ct < _nextSynchTime) //Every X seconds and new appointment not reached yet.
		return 0;

	if (_synch_count == 0 && _synchOnGPS) {
		MAPSellipse_device::SetSystemTime(at);
	}
	if (_synch_when == 0 && _synch_count > 0) //Once at start
		return 0;
	MAPSTimestamp t = MAPS::CurrentTime();
	if (_synch_when == 1 && t < _nextSynchTime) //Every X seconds and new appointment not reached yet.
		return 0;

	MAPSTimestamp absTimestamp;
	absTimestamp = MAPSellipse_device::AbsTime2Timestamp(at);
	MAPSTimestamp offset = absTimestamp - t;
	m_Timebase += offset;
	_synch_count++;
	if (_synch_when == 1) { //Every X seconds
		_nextSynchTime += GetIntegerProperty("synchronize_every_X_seconds")*1000000;
	}
	return offset;
}

void MAPSellipse_device::OutputOffset(int status, MAPSTimestamp offset)
{
	MAPSIOElt* ioElt = StartWriting(Output("synch_info"));
	ioElt->Integer64(0) = status;
	ioElt->Integer64(1) = offset;
	StopWriting(ioElt);
}

/************************************
* TIME UTILS *
************************************/
void MAPSellipse_device::Timestamp2AbsTime(MAPSTimestamp t,MAPSAbsoluteTime* absTime)
{
#ifdef WIN32
	MAPSTimestamp tsecs = t/1000000;
	tm tmTime = *(_gmtime64(&tsecs));
	MAPSellipse_device::tm2AbsTime(tmTime,absTime);
	MAPSTimestamp microsecsLeft = t - tsecs*1000000;
	absTime->milliseconds = (int)microsecsLeft/1000;
	absTime->microseconds = (int)(microsecsLeft - absTime->milliseconds*1000);
#else
	time_t tsecs = t/1000000;
	tm tmTime;
	if(NULL==gmtime_r(&tsecs,&tmTime))
	  MAPS::ReportError("Error in call to gmtime_r.");

	MAPSellipse_device::tm2AbsTime(tmTime,absTime);
	MAPSTimestamp microsecsLeft = t - tsecs*1000000;
	absTime->milliseconds = (int)microsecsLeft/1000;
	absTime->microseconds = (int)(microsecsLeft - absTime->milliseconds*1000);
#endif
}

MAPSTimestamp MAPSellipse_device::AbsTime2Timestamp(const MAPSAbsoluteTime& absTime)
{
#ifdef WIN32
	SYSTEMTIME st;
	MAPSellipse_device::AbsTime2SystemTime(absTime,&st);
	FILETIME ft;
	SystemTimeToFileTime(&st,&ft);
	ULARGE_INTEGER ftULInt;
	memcpy(&ftULInt,&ft,sizeof(ft));
	SYSTEMTIME storigin;
	storigin.wDay = 1;
	storigin.wHour = 0;
	storigin.wMilliseconds = 0;
	storigin.wMinute = 0;
	storigin.wMonth = 1;
	storigin.wSecond = 0;
	storigin.wYear = 1970;
	FILETIME ftOrigin;
	SystemTimeToFileTime(&storigin,&ftOrigin);
	ULARGE_INTEGER ftULIntOrigin;
	memcpy(&ftULIntOrigin,&ftOrigin, sizeof(ftOrigin));
	MAPSTimestamp t = (ftULInt.QuadPart - ftULIntOrigin.QuadPart)/10;
	return t;
#else
	MAPSTimestamp t;
	tm ansiDateStruct;
	MAPSDelay d = MAPSellipse_device::AbsTime2tm(absTime,&ansiDateStruct);

	time_t secs = timegm(&ansiDateStruct);
	if (secs == -1)
	  MAPS::ReportError("Error in call to timegm.");
	t = ((MAPSInt64)secs)*1000000 + d;
	return t;
#endif
}

void MAPSellipse_device::GetSystemTime(MAPSAbsoluteTime* absTime)
{
#ifdef WIN32
	SYSTEMTIME st;
	::GetSystemTime(&st);
	absTime->day = st.wDay;
	absTime->hour = st.wHour;
	absTime->microseconds = 0;
	absTime->milliseconds = st.wMilliseconds;
	absTime->minutes = st.wMinute;
	absTime->month = st.wMonth;
	absTime->seconds = st.wSecond;
	absTime->year = st.wYear;
#else
	struct tm tmTime;
	timeval currentTime;
	int res = gettimeofday(&currentTime,NULL);
	if (res != 0)
	  MAPS::ReportError("Error in call to gettimeofday.");

	if(NULL == gmtime_r(&(currentTime.tv_sec),&tmTime))
	  MAPS::ReportError("Error in call to gmtime_r.");

	absTime->day = tmTime.tm_mday;
	absTime->hour = tmTime.tm_hour;
	absTime->microseconds = 0;
	absTime->milliseconds = currentTime.tv_usec/1000;
	absTime->minutes = tmTime.tm_min;
	absTime->month = tmTime.tm_mon+1;
	absTime->seconds = tmTime.tm_sec;
	absTime->year = tmTime.tm_year+1900;
#endif
}

bool MAPSellipse_device::SetSystemTime(const MAPSAbsoluteTime& absTime)
{
#ifdef WIN32
	SYSTEMTIME st;
	st.wDay = absTime.day;
	st.wHour = absTime.hour;
	st.wMilliseconds = absTime.milliseconds;
	st.wMinute = absTime.minutes;
	st.wMonth = absTime.month;
	st.wSecond = absTime.seconds;
	st.wYear = absTime.year;
	if (FALSE == ::SetSystemTime(&st)) {
		MAPS::ReportWarning("Could not set the System Time. Administrator privileges are required.");
		return false;
	} else {
		return true;
	}
#else
	timeval newtime;
	newtime.tv_usec = absTime.milliseconds*1000;
	newtime.tv_sec = (MAPSInt64)(AbsTime2Timestamp(absTime)/1000000);
	int res = settimeofday(&newtime,NULL);
	if (res == -1) {
	  MAPS::ReportWarning("Could not set the System Time. Superuser access rights are required.");
	  return false;
	} else {
	  return true;
	}
#endif
}

MAPSDelay MAPSellipse_device::AbsTime2tm(const MAPSAbsoluteTime& absTime,tm* tmTime)
{
	tmTime->tm_hour = absTime.hour;
	tmTime->tm_mday = absTime.day;
	tmTime->tm_min = absTime.minutes;
	tmTime->tm_mon = absTime.month - 1;
	tmTime->tm_sec = absTime.seconds;
	tmTime->tm_year = absTime.year - 1900;
	tmTime->tm_isdst = -1; //The C-runtime libraries will determine automatically
	return absTime.milliseconds*1000 + absTime.microseconds;
}

#ifdef WIN32
MAPSDelay MAPSellipse_device::AbsTime2SystemTime(const MAPSAbsoluteTime& absTime,SYSTEMTIME* st)
{
	st->wHour = absTime.hour;
	st->wDay = absTime.day;
	st->wMinute = absTime.minutes;
	st->wMonth = absTime.month;
	st->wMilliseconds = absTime.milliseconds;
	st->wSecond = absTime.seconds;
	st->wYear = absTime.year;
	return absTime.microseconds;
}
#endif

void MAPSellipse_device::tm2AbsTime(const tm& tmTime, MAPSAbsoluteTime* absTime)
{
	absTime->day = tmTime.tm_mday;
	absTime->hour = tmTime.tm_hour;
	absTime->microseconds = 0;
	absTime->milliseconds = 0;
	absTime->minutes = tmTime.tm_min;
	absTime->month = tmTime.tm_mon + 1;
	absTime->seconds = tmTime.tm_sec;
	absTime->year = tmTime.tm_year + 1900;
}

MAPSString MAPSellipse_device::AbsTime2String(MAPSAbsoluteTime absTime)
{
  MAPSStreamedString sx;
  sx<<absTime.year<<" "<<absTime.month<<" "<<absTime.day<<" "<<absTime.hour<<":"<<absTime.minutes<<":"<<absTime.seconds<<"."<<absTime.milliseconds<<"."<<absTime.microseconds;
  return sx;
}
