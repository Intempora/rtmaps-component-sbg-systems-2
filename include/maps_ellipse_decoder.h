////////////////////////////////
// RTMaps SDK Component header
////////////////////////////////

#ifndef _Maps_ellipse_decoder_H
#define _Maps_ellipse_decoder_H

// Includes maps sdk library header
#include "maps.hpp"

// Declares a new MAPSComponent child class
class MAPSellipse_decoder : public MAPSComponent 
{
	// Use standard header definition macro
	MAPS_COMPONENT_STANDARD_HEADER_CODE(MAPSellipse_decoder)
	void Dynamic();
private :
	// Place here your specific methods and attributes
	bool m_output_status;
	bool m_output_utc_time;
	bool m_output_imu_data;
	bool m_output_mag;
	bool m_output_mag_calib;
	bool m_output_ekf_euler;
	bool m_output_ekf_quat;
	bool m_output_ekf_nav;
	bool m_output_ship_motion;
	bool m_output_gps_1_vel;
	bool m_output_gps_2_vel;
	bool m_output_gps_1_pos;
	bool m_output_gps_2_pos;
	bool m_output_gps_1_hdt;
	bool m_output_gps_2_hdt;
	bool m_output_gps_1_raw;
	bool m_output_odo_vel;
	bool m_output_event_A;
	bool m_output_event_B;
	bool m_output_event_C;
	bool m_output_event_D;
	bool m_output_event_E;
	bool m_output_dvl_bottom_track;
	bool m_output_ship_motion_hp;
	bool m_output_pressure;
	bool m_output_usbl;
};

#endif
