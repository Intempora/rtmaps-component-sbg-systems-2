////////////////////////////////
// RTMaps SDK Component
////////////////////////////////

////////////////////////////////
// Purpose of this module :
////////////////////////////////

#include "maps_ellipse_decoder.h"	// Includes the header of this component
#include "maps_sbg_ecom_output_types.h"

// Use the macros to declare the inputs
MAPS_BEGIN_INPUTS_DEFINITION(MAPSellipse_decoder)
    MAPS_INPUT("sbg_ecom_data_in",MAPSFilterSbgEComData,MAPS::FifoReader)
MAPS_END_INPUTS_DEFINITION

// Use the macros to declare the outputs
MAPS_BEGIN_OUTPUTS_DEFINITION(MAPSellipse_decoder)
    MAPS_OUTPUT("status",MAPS::Integer32,NULL,NULL,6)
    MAPS_OUTPUT("utc_time",MAPS::Integer32,NULL,NULL,9)
    MAPS_OUTPUT("utc_time_us",MAPS::Integer64,NULL,NULL,1)
	MAPS_OUTPUT("imu_acceleration",MAPS::Float32,NULL,NULL,4)
	MAPS_OUTPUT("imu_gyros",MAPS::Float32,NULL,NULL,4)
	MAPS_OUTPUT("imu_other",MAPS::Float32,NULL,NULL,8)
	MAPS_OUTPUT("mag",MAPS::Float32,NULL,NULL,7)
	MAPS_OUTPUT("mag_calib",MAPS::Integer32,NULL,NULL,17)
	MAPS_OUTPUT("ekf_euler",MAPS::Float32,NULL,NULL,7)
	MAPS_OUTPUT("ekf_quat",MAPS::Float32,NULL,NULL,8)
	MAPS_OUTPUT("ekf_nav_pos",MAPS::Float64,NULL,NULL,8)
	MAPS_OUTPUT("ekf_nav_vel",MAPS::Float32,NULL,NULL,7)
	MAPS_OUTPUT("ship_motion_0",MAPS::Float32,NULL,NULL,11)
	MAPS_OUTPUT("gps_1_vel",MAPS::Float32,NULL,NULL,10)
	MAPS_OUTPUT("gps_1_pos",MAPS::Float64,NULL,NULL,9)
	MAPS_OUTPUT("gps_1_hdt",MAPS::Float32,NULL,NULL,6)
	MAPS_OUTPUT("gps_1_raw",MAPS::Stream8,NULL,NULL,SBG_ECOM_RAW_DATA_MAX_BUFFER_SIZE)
	MAPS_OUTPUT("gps_2_vel",MAPS::Float32,NULL,NULL,10)
	MAPS_OUTPUT("gps_2_pos",MAPS::Float64,NULL,NULL,9)
	MAPS_OUTPUT("gps_2_hdt",MAPS::Float32,NULL,NULL,6)
	MAPS_OUTPUT("odo_vel",MAPS::Float32,NULL,NULL,2)
	MAPS_OUTPUT("event_A",MAPS::Integer32,NULL,NULL,5)
	MAPS_OUTPUT("event_B",MAPS::Integer32,NULL,NULL,5)
	MAPS_OUTPUT("event_C",MAPS::Integer32,NULL,NULL,5)
	MAPS_OUTPUT("event_D",MAPS::Integer32,NULL,NULL,5)
	MAPS_OUTPUT("event_E",MAPS::Integer32,NULL,NULL,5)
	MAPS_OUTPUT("dvl_bottom_track",MAPS::Float32,NULL,NULL,7)
	MAPS_OUTPUT("ship_motion_hp_0",MAPS::Float32,NULL,NULL,11)
	MAPS_OUTPUT("pressure",MAPS::Float32,NULL,NULL,3)
	MAPS_OUTPUT("usbl",MAPS::Float64,NULL,NULL,7)
	MAPS_OUTPUT_FIFOSIZE("sbg_timestamp",MAPS::Integer64,NULL,NULL,1,256)
MAPS_END_OUTPUTS_DEFINITION

// Use the macros to declare the properties
MAPS_BEGIN_PROPERTIES_DEFINITION(MAPSellipse_decoder)
    MAPS_PROPERTY("output_status",true,false,false)
    MAPS_PROPERTY("output_utc_time",true,false,false)
	MAPS_PROPERTY("output_imu_data",true,false,false)
	MAPS_PROPERTY("output_mag",false,false,false)
	MAPS_PROPERTY("output_mag_calib",false,false,false)
	MAPS_PROPERTY("output_ekf_euler",true,false,false)
	MAPS_PROPERTY("output_ekf_quat",false,false,false)
	MAPS_PROPERTY("output_ekf_nav",true,false,false)
	MAPS_PROPERTY("output_ship_motion_0",false,false,false)
	MAPS_PROPERTY("output_gps_1_vel",false,false,false)
	MAPS_PROPERTY("output_gps_2_vel",false,false,false)
	MAPS_PROPERTY("output_gps_1_pos",false,false,false)
	MAPS_PROPERTY("output_gps_2_pos",false,false,false)
	MAPS_PROPERTY("output_gps_1_hdt",false,false,false)
	MAPS_PROPERTY("output_gps_2_hdt",false,false,false)
	MAPS_PROPERTY("output_gps_1_raw",false,false,false)
	MAPS_PROPERTY("output_odo_vel",false,false,false)
	MAPS_PROPERTY("output_event_A",false,false,false)
	MAPS_PROPERTY("output_event_B",false,false,false)
	MAPS_PROPERTY("output_event_C",false,false,false)
	MAPS_PROPERTY("output_event_D",false,false,false)
	MAPS_PROPERTY("output_event_E",false,false,false)
	MAPS_PROPERTY("output_dvl_bottom_track",false,false,false)
	MAPS_PROPERTY("output_ship_motion_hp_0",false,false,false)
	MAPS_PROPERTY("output_pressure",false,false,false)
	MAPS_PROPERTY("output_usbl",false,false,false)
MAPS_END_PROPERTIES_DEFINITION

// Use the macros to declare the actions
MAPS_BEGIN_ACTIONS_DEFINITION(MAPSellipse_decoder)
    //MAPS_ACTION("aName",MAPSellipse_decoder::ActionName)
MAPS_END_ACTIONS_DEFINITION

//V1.1: added implementation for decoding a few additional fields.
//V1.2: 2017-07-26: fix output_ship_motion_hp_* properties handling (outputs were bound on output_ship_motion_* instead for index 1 through 3)
//V1.3: 2018-06-20: use AbsoluteTimeUTC2Timestamp instead of AbsoluteTime2Integer

// Use the macros to declare this component (ellipse_decoder) behaviour
MAPS_COMPONENT_DEFINITION(MAPSellipse_decoder,"ellipse_decoder","2.0.0",128,
			  MAPS::Threaded,MAPS::Threaded,
			  -1, // Nb of inputs. Leave -1 to use the number of declared input definitions
			  0, // Nb of outputs. Leave -1 to use the number of declared output definitions
			  -1, // Nb of properties. Leave -1 to use the number of declared property definitions
			  -1) // Nb of actions. Leave -1 to use the number of declared action definitions


void MAPSellipse_decoder::Dynamic()
{
    m_output_status = GetBoolProperty("output_status");
    m_output_utc_time = GetBoolProperty("output_utc_time");
	m_output_imu_data = GetBoolProperty("output_imu_data");
	m_output_mag = GetBoolProperty("output_mag");
	m_output_mag_calib = GetBoolProperty("output_mag_calib");
	m_output_ekf_euler = GetBoolProperty("output_ekf_euler");
	m_output_ekf_quat = GetBoolProperty("output_ekf_quat");
	m_output_ekf_nav = GetBoolProperty("output_ekf_nav");
	m_output_ship_motion = GetBoolProperty("output_ship_motion_0");
	m_output_gps_1_vel = GetBoolProperty("output_gps_1_vel");
	m_output_gps_2_vel = GetBoolProperty("output_gps_2_vel");
	m_output_gps_1_pos = GetBoolProperty("output_gps_1_pos");
	m_output_gps_2_pos = GetBoolProperty("output_gps_2_pos");
	m_output_gps_1_hdt = GetBoolProperty("output_gps_1_hdt");
	m_output_gps_2_hdt = GetBoolProperty("output_gps_2_hdt");
	m_output_gps_1_raw = GetBoolProperty("output_gps_1_raw");
	m_output_odo_vel = GetBoolProperty("output_odo_vel");
	m_output_event_A = GetBoolProperty("output_event_A");
	m_output_event_B = GetBoolProperty("output_event_B");
	m_output_event_C = GetBoolProperty("output_event_C");
	m_output_event_D = GetBoolProperty("output_event_D");
	m_output_event_E = GetBoolProperty("output_event_E");
	m_output_dvl_bottom_track = GetBoolProperty("output_dvl_bottom_track");
	m_output_ship_motion_hp = GetBoolProperty("output_ship_motion_hp_0");
	m_output_pressure = GetBoolProperty("output_pressure");
	m_output_usbl = GetBoolProperty("output_usbl");


	if (this->m_output_status) NewOutput("status");
	if (this->m_output_utc_time) NewOutput("utc_time");
	if (this->m_output_utc_time) NewOutput("utc_time_us");
	if (this->m_output_imu_data) NewOutput("imu_acceleration");
	if (this->m_output_imu_data) NewOutput("imu_gyros");
	if (this->m_output_imu_data) NewOutput("imu_other");
	if (this->m_output_mag) NewOutput("mag");
	if (this->m_output_mag_calib) NewOutput("mag_calib");
	if (this->m_output_ekf_euler) NewOutput("ekf_euler");
	if (this->m_output_ekf_quat) NewOutput("ekf_quat");
	if (this->m_output_ekf_nav) NewOutput("ekf_nav_pos");
	if (this->m_output_ekf_nav) NewOutput("ekf_nav_vel");
	if (this->m_output_ship_motion) NewOutput("ship_motion_0");
	if (this->m_output_gps_1_vel) NewOutput("gps_1_vel");
	if (this->m_output_gps_1_pos) NewOutput("gps_1_pos");
	if (this->m_output_gps_1_hdt) NewOutput("gps_1_hdt");
	if (this->m_output_gps_1_raw) NewOutput("gps_1_raw");
	if (this->m_output_gps_2_vel) NewOutput("gps_2_vel");
	if (this->m_output_gps_2_pos) NewOutput("gps_2_pos");
	if (this->m_output_gps_2_hdt) NewOutput("gps_2_hdt");
	if (this->m_output_odo_vel) NewOutput("odo_vel");
	if (this->m_output_event_A) NewOutput("event_A");
	if (this->m_output_event_B) NewOutput("event_B");
	if (this->m_output_event_C) NewOutput("event_C");
	if (this->m_output_event_D) NewOutput("event_D");
	if (this->m_output_event_E) NewOutput("event_E");
	if (this->m_output_dvl_bottom_track) NewOutput("dvl_bottom_track");
	if (this->m_output_ship_motion_hp) NewOutput("ship_motion_hp_0");
	if (this->m_output_pressure) NewOutput("pressure");
	if (this->m_output_usbl) NewOutput("usbl");
	NewOutput("sbg_timestamp");

}
//Initialization: Birth() will be called once at diagram execution startup.			  
void MAPSellipse_decoder::Birth()
{
}

//ATTENTION: 
//	Make sure there is ONE and ONLY ONE blocking function inside this Core method.
//	Consider that Core() will be called inside an infinite loop while the diagram is executing.
//	Something similar to: 
//		while (componentIsRunning) {Core();}
//
//	Usually, the one and only blocking function is one of the following:
//		* StartReading(MAPSInput& input); //Data request on a single BLOCKING input. A "blocking input" is an input declared as FifoReader, LastOrNextReader, Wait4NextReader or NeverskippingReader (declaration happens in MAPS_INPUT: see the beginning of this file). A SamplingReader input is non-blocking: StartReading will not block with a SamplingReader input.
//		* StartReading(int nCount, MAPSInput* inputs[], int* inputThatAnswered, int nCountEvents = 0, MAPSEvent* events[] = NULL); //Data request on several BLOCKING inputs.
//		* SynchroStartReading(int nb, MAPSInput** inputs, MAPSIOElt** IOElts, MAPSInt64 synchroTolerance = 0, MAPSEvent* abortEvent = NULL); // Synchronized reading - waiting for samples with same or nearly same timestamps on several BLOCKING inputs.
//		* Wait(MAPSTimestamp t); or Rest(MAPSDelay d); or MAPS::Sleep(MAPSDelay d); //Pauses the current thread for some time. Can be used for instance in conjunction with StartReading on a SamplingReader input (in which case StartReading is not blocking).
//		* Any blocking grabbing function or other data reception function from another API (device driver,etc.). In such case, make sure this function cannot block forever otherwise it could freeze RTMaps when shutting down diagram.
//**************************************************************************/
//	In case of no blocking function inside the Core, your component will consume 100% of a CPU.
//  Remember that the StartReading function used with an input declared as a SamplingReader is not blocking.
//	In case of two or more blocking functions inside the Core, this is likely to induce synchronization issues and data loss. (Ex: don't call two successive StartReading on FifoReader inputs.)
/***************************************************************************/
void MAPSellipse_decoder::Core() 
{
	MAPSIOElt* ioeltin = StartReading(Input(0));
	if (ioeltin == NULL)
		return;
	SbgEComData* datain = (SbgEComData*)ioeltin->Data();
	switch(datain->cmd) {
	case SBG_ECOM_LOG_STATUS:
		{
			if (this->m_output_status == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("status"));
			MAPSUInt32* values = (MAPSUInt32*)&ioeltout->Integer32();
			*(values++) = datain->logdata.statusData.generalStatus;
			*(values++) = datain->logdata.statusData.comStatus;
			*(values++) = datain->logdata.statusData.aidingStatus;
			ioeltout->VectorSize() = 3;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.statusData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_UTC_TIME:
		{
			if (this->m_output_utc_time == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("utc_time"));
			MAPSInt32* values = &ioeltout->Integer32();
			*(values++) = datain->logdata.utcData.year;
			*(values++) = datain->logdata.utcData.month;
			*(values++) = datain->logdata.utcData.day;
			*(values++) = datain->logdata.utcData.hour;
			*(values++) = datain->logdata.utcData.minute;
			*(values++) = datain->logdata.utcData.second;
			*(values++) = datain->logdata.utcData.nanoSecond;
			*(values++) = datain->logdata.utcData.gpsTimeOfWeek;
			*(values++) = datain->logdata.utcData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.utcData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);

			MAPSIOElt* ioeltout_time_us = StartWriting(Output("utc_time_us"));
			MAPSAbsoluteTime at;
			at.year = datain->logdata.utcData.year;
			at.month = datain->logdata.utcData.month;
			at.day = datain->logdata.utcData.day;
			at.hour = datain->logdata.utcData.hour;
			at.minutes = datain->logdata.utcData.minute;
			at.seconds = datain->logdata.utcData.second;
			at.milliseconds = datain->logdata.utcData.nanoSecond/1000000;
			at.microseconds = (datain->logdata.utcData.nanoSecond - at.milliseconds*1000000)/1000;
			ioeltout_time_us->Integer64() = MAPS::AbsoluteTimeUTC2Timestamp(&at);
			ioeltout_time_us->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_time_us);
		}
		break;
	case SBG_ECOM_LOG_IMU_DATA:
		{
			if (this->m_output_imu_data == false) return;
			MAPSIOElt* ioeltout_acc = StartWriting(Output("imu_acceleration"));
			MAPSIOElt* ioeltout_gyros = StartWriting(Output("imu_gyros"));
			MAPSIOElt* ioeltout_other = StartWriting(Output("imu_other"));
			MAPSFloat32* acc_values = &ioeltout_acc->Float32();
			*(acc_values++) = datain->logdata.imuData.accelerometers[0];
			*(acc_values++) = datain->logdata.imuData.accelerometers[1];
			*(acc_values++) = datain->logdata.imuData.accelerometers[2];
			*(acc_values++) = datain->logdata.imuData.status;

			MAPSFloat32* gyro_values = &ioeltout_gyros->Float32();
			*(gyro_values++) = datain->logdata.imuData.gyroscopes[0];
			*(gyro_values++) = datain->logdata.imuData.gyroscopes[1];
			*(gyro_values++) = datain->logdata.imuData.gyroscopes[2];
			*(gyro_values++) = datain->logdata.imuData.status;

			MAPSFloat32* other_values = &ioeltout_other->Float32();
			*(other_values++) = datain->logdata.imuData.deltaVelocity[0];
			*(other_values++) = datain->logdata.imuData.deltaVelocity[1];
			*(other_values++) = datain->logdata.imuData.deltaVelocity[2];
			*(other_values++) = datain->logdata.imuData.deltaAngle[0];
			*(other_values++) = datain->logdata.imuData.deltaAngle[1];
			*(other_values++) = datain->logdata.imuData.deltaAngle[2];
			*(other_values++) = datain->logdata.imuData.temperature;
			*(other_values++) = datain->logdata.imuData.status;


			ioeltout_acc->Timestamp() = ioeltin->Timestamp();
			ioeltout_gyros->Timestamp() = ioeltin->Timestamp();
			ioeltout_other->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_acc);
			StopWriting(ioeltout_gyros);
			StopWriting(ioeltout_other);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.imuData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_MAG:
		{
			if (this->m_output_mag == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("mag"));
			MAPSFloat32* values = &ioeltout->Float32();
			*(values++) = datain->logdata.magData.magnetometers[0];
			*(values++) = datain->logdata.magData.magnetometers[1];
			*(values++) = datain->logdata.magData.magnetometers[2];
			*(values++) = datain->logdata.magData.accelerometers[0];
			*(values++) = datain->logdata.magData.accelerometers[1];
			*(values++) = datain->logdata.magData.accelerometers[2];
			*(values++) = datain->logdata.magData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.magData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_MAG_CALIB:
		{
			if (this->m_output_mag_calib == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("mag_calib"));
			MAPSInt32* values = &ioeltout->Integer32();
			for (int i=0; i<16; i++) {
				*(values++) = datain->logdata.magCalibData.magData[i];
			}
			ioeltout->VectorSize() = 16;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.magCalibData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EKF_EULER:
		{
			if (this->m_output_ekf_euler == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("ekf_euler"));
			MAPSFloat32* values = &ioeltout->Float32();
			*(values++) = datain->logdata.ekfEulerData.euler[0];
			*(values++) = datain->logdata.ekfEulerData.euler[1];
			*(values++) = datain->logdata.ekfEulerData.euler[2];
			*(values++) = datain->logdata.ekfEulerData.eulerStdDev[0];
			*(values++) = datain->logdata.ekfEulerData.eulerStdDev[1];
			*(values++) = datain->logdata.ekfEulerData.eulerStdDev[02];
			*(values++) = (MAPSFloat32)(datain->logdata.ekfEulerData.status);
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.ekfEulerData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EKF_QUAT:
		{
			if (this->m_output_ekf_quat == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("ekf_quat"));
			MAPSFloat32* values = &ioeltout->Float32();
			*(values++) = datain->logdata.ekfQuatData.quaternion[0];
			*(values++) = datain->logdata.ekfQuatData.quaternion[1];
			*(values++) = datain->logdata.ekfQuatData.quaternion[2];
			*(values++) = datain->logdata.ekfQuatData.quaternion[3];
			*(values++) = datain->logdata.ekfQuatData.eulerStdDev[0];
			*(values++) = datain->logdata.ekfQuatData.eulerStdDev[1];
			*(values++) = datain->logdata.ekfQuatData.eulerStdDev[2];
			*(values++) = (MAPSFloat32)datain->logdata.ekfQuatData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.ekfQuatData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EKF_NAV:
		{
			if (this->m_output_ekf_nav == false) return; 
			MAPSIOElt* ioeltout_pos = StartWriting(Output("ekf_nav_pos"));
			MAPSIOElt* ioeltout_vel = StartWriting(Output("ekf_nav_vel"));
			MAPSFloat64* pos_out = &ioeltout_pos->Float64();
			MAPSFloat32* vel_out = &ioeltout_vel->Float32();
			*(pos_out++) = datain->logdata.ekfNavData.position[0];
			*(pos_out++) = datain->logdata.ekfNavData.position[1];
			*(pos_out++) = datain->logdata.ekfNavData.position[2];
			*(pos_out++) = datain->logdata.ekfNavData.positionStdDev[0];
			*(pos_out++) = datain->logdata.ekfNavData.positionStdDev[1];
			*(pos_out++) = datain->logdata.ekfNavData.positionStdDev[2];
			*(pos_out++) = datain->logdata.ekfNavData.undulation;
			*(pos_out++) = datain->logdata.ekfNavData.status;
			*(vel_out++) = datain->logdata.ekfNavData.velocity[0];
			*(vel_out++) = datain->logdata.ekfNavData.velocity[1];
			*(vel_out++) = datain->logdata.ekfNavData.velocity[2];
			*(vel_out++) = datain->logdata.ekfNavData.velocityStdDev[0];
			*(vel_out++) = datain->logdata.ekfNavData.velocityStdDev[1];
			*(vel_out++) = datain->logdata.ekfNavData.velocityStdDev[2];
			*(vel_out++) = (MAPSFloat32)datain->logdata.ekfNavData.status;
			ioeltout_pos->Timestamp() = ioeltin->Timestamp();
			ioeltout_vel->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_pos);
			StopWriting(ioeltout_vel);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.ekfNavData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_SHIP_MOTION:
		{
			if (this->m_output_ship_motion == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("ship_motion_0"));

			MAPSFloat32* dataout = &ioeltout->Float32();
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[0];
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[1];
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[2];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[0];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[1];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[2];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[0];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[1];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[2];
			*(dataout++) = datain->logdata.shipMotionData.mainHeavePeriod;
			*(dataout++) = datain->logdata.shipMotionData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = *(dataout++) = datain->logdata.shipMotionData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS1_VEL:
		{
			if(m_output_gps_1_vel == false) return;

			MAPSIOElt* ioeltout = StartWriting(Output("gps_1_vel"));
			ioeltout->Timestamp() = ioeltin->Timestamp();
			MAPSFloat32* float_data_out = &ioeltout->Float32();
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[0];
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[1];
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[2];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[0];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[1];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[2];
			*(float_data_out++) = datain->logdata.gpsVelData.course;
			*(float_data_out++) = datain->logdata.gpsVelData.courseAcc;
			*(float_data_out++) = datain->logdata.gpsVelData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsVelData.status;
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.gpsVelData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS1_POS:
		{
			if (this->m_output_gps_1_pos == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("gps_1_pos"));

			MAPSFloat64* float_data_out = &ioeltout->Float64();
			*(float_data_out++) = datain->logdata.gpsPosData.latitude;
			*(float_data_out++) = datain->logdata.gpsPosData.longitude;
			*(float_data_out++) = datain->logdata.gpsPosData.altitude;
			*(float_data_out++) = datain->logdata.gpsPosData.undulation;
			*(float_data_out++) = datain->logdata.gpsPosData.latitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.longitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.altitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsPosData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.gpsPosData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS1_HDT:
		{
			if (this->m_output_gps_1_hdt == false) return;   

			MAPSIOElt* ioeltout = StartWriting(Output("gps_1_hdt"));
			MAPSFloat32* float_data_out = &ioeltout->Float32();
			*(float_data_out++) = datain->logdata.gpsHdtData.heading;
			*(float_data_out++) = datain->logdata.gpsHdtData.pitch;
			*(float_data_out++) = datain->logdata.gpsHdtData.headingAccuracy;
			*(float_data_out++) = datain->logdata.gpsHdtData.pitchAccuracy;
			*(float_data_out++) = datain->logdata.gpsHdtData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsHdtData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = *(float_data_out++) = datain->logdata.gpsHdtData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS1_RAW:
		{
			if (this->m_output_gps_1_raw == false) return;   

			MAPSIOElt* ioeltout = StartWriting(Output("gps_1_raw"));
			char* data_out = (char*)ioeltout->Stream8();
			MAPS::Memcpy(data_out,datain->logdata.gpsRawData.rawBuffer,datain->logdata.gpsRawData.bufferSize);
			ioeltout->VectorSize() =datain->logdata.gpsRawData.bufferSize;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
		}
		break;
	case SBG_ECOM_LOG_GPS2_VEL:
		{
			if(m_output_gps_2_vel == false) return;

			MAPSIOElt* ioeltout = StartWriting(Output("gps_2_vel"));
			ioeltout->Timestamp() = ioeltin->Timestamp();
			MAPSFloat32* float_data_out = &ioeltout->Float32();
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[0];
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[1];
			*(float_data_out++) = datain->logdata.gpsVelData.velocity[2];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[0];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[1];
			*(float_data_out++) = datain->logdata.gpsVelData.velocityAcc[2];
			*(float_data_out++) = datain->logdata.gpsVelData.course;
			*(float_data_out++) = datain->logdata.gpsVelData.courseAcc;
			*(float_data_out++) = datain->logdata.gpsVelData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsVelData.status;
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.gpsVelData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS2_POS:
		{
			if (this->m_output_gps_2_pos == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("gps_2_pos"));

			MAPSFloat64* float_data_out = &ioeltout->Float64();
			*(float_data_out++) = datain->logdata.gpsPosData.latitude;
			*(float_data_out++) = datain->logdata.gpsPosData.longitude;
			*(float_data_out++) = datain->logdata.gpsPosData.altitude;
			*(float_data_out++) = datain->logdata.gpsPosData.undulation;
			*(float_data_out++) = datain->logdata.gpsPosData.latitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.longitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.altitudeAccuracy;
			*(float_data_out++) = datain->logdata.gpsPosData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsPosData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.gpsPosData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_GPS2_HDT:
		{
			if (this->m_output_gps_2_hdt == false) return;   

			MAPSIOElt* ioeltout = StartWriting(Output("gps_2_hdt"));
			MAPSFloat32* float_data_out = &ioeltout->Float32();
			*(float_data_out++) = datain->logdata.gpsHdtData.heading;
			*(float_data_out++) = datain->logdata.gpsHdtData.pitch;
			*(float_data_out++) = datain->logdata.gpsHdtData.headingAccuracy;
			*(float_data_out++) = datain->logdata.gpsHdtData.pitchAccuracy;
			*(float_data_out++) = datain->logdata.gpsHdtData.timeOfWeek;
			*(float_data_out++) = datain->logdata.gpsHdtData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = *(float_data_out++) = datain->logdata.gpsHdtData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_ODO_VEL:
		{
			if (m_output_odo_vel == false) return;

			MAPSIOElt* ioeltout = StartWriting(Output("odo_vel"));
			MAPSFloat32* float_data_out = &ioeltout->Float32();
			*(float_data_out++) = datain->logdata.odometerData.velocity;
			*(float_data_out++) = datain->logdata.odometerData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.odometerData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EVENT_A:
		{
			if (this->m_output_event_A == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("event_A"));
			MAPSInt32* dataout = &ioeltout->Integer32();
			*(dataout++) = datain->logdata.eventMarker.timeOffset0;
			*(dataout++) = datain->logdata.eventMarker.timeOffset1;
			*(dataout++) = datain->logdata.eventMarker.timeOffset2;
			*(dataout++) = datain->logdata.eventMarker.timeOffset3;
			*(dataout++) = datain->logdata.eventMarker.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.eventMarker.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EVENT_B:
		{
			if (this->m_output_event_B == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("event_B"));
			MAPSInt32* dataout = &ioeltout->Integer32();
			*(dataout++) = datain->logdata.eventMarker.timeOffset0;
			*(dataout++) = datain->logdata.eventMarker.timeOffset1;
			*(dataout++) = datain->logdata.eventMarker.timeOffset2;
			*(dataout++) = datain->logdata.eventMarker.timeOffset3;
			*(dataout++) = datain->logdata.eventMarker.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.eventMarker.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EVENT_C:
		{
			if (this->m_output_event_C == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("event_C"));
			MAPSInt32* dataout = &ioeltout->Integer32();
			*(dataout++) = datain->logdata.eventMarker.timeOffset0;
			*(dataout++) = datain->logdata.eventMarker.timeOffset1;
			*(dataout++) = datain->logdata.eventMarker.timeOffset2;
			*(dataout++) = datain->logdata.eventMarker.timeOffset3;
			*(dataout++) = datain->logdata.eventMarker.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.eventMarker.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EVENT_D:
		{
			if (this->m_output_event_D == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("event_D"));
			MAPSInt32* dataout = &ioeltout->Integer32();
			*(dataout++) = datain->logdata.eventMarker.timeOffset0;
			*(dataout++) = datain->logdata.eventMarker.timeOffset1;
			*(dataout++) = datain->logdata.eventMarker.timeOffset2;
			*(dataout++) = datain->logdata.eventMarker.timeOffset3;
			*(dataout++) = datain->logdata.eventMarker.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.eventMarker.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_EVENT_E:
		{
			if (this->m_output_event_E == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("event_E"));
			MAPSInt32* dataout = &ioeltout->Integer32();
			*(dataout++) = datain->logdata.eventMarker.timeOffset0;
			*(dataout++) = datain->logdata.eventMarker.timeOffset1;
			*(dataout++) = datain->logdata.eventMarker.timeOffset2;
			*(dataout++) = datain->logdata.eventMarker.timeOffset3;
			*(dataout++) = datain->logdata.eventMarker.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.eventMarker.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_DVL_BOTTOM_TRACK:
		{
			if (this->m_output_dvl_bottom_track == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("dvl_bottom_track"));
			MAPSFloat32* dataout = &ioeltout->Float32();
			*(dataout++) = datain->logdata.dvlData.velocity[0];
			*(dataout++) = datain->logdata.dvlData.velocity[1];
			*(dataout++) = datain->logdata.dvlData.velocity[2];
			// *(dataout++) = datain->logdata.dvlData.velocityStdDev[0];
			// *(dataout++) = datain->logdata.dvlData.velocityStdDev[1];
			// *(dataout++) = datain->logdata.dvlData.velocityStdDev[2];
			*(dataout++) = datain->logdata.dvlData.velocityQuality[0];
			*(dataout++) = datain->logdata.dvlData.velocityQuality[1];
			*(dataout++) = datain->logdata.dvlData.velocityQuality[2];
			*(dataout++) = datain->logdata.dvlData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);

			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.dvlData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_DVL_WATER_TRACK:
		{
			ReportError("Decoding for message SBG_ECOM_LOG_DVL_WATER_TRACK is not implemented yet. Please contact Intempora.");
		}
		break;
	case SBG_ECOM_LOG_SHIP_MOTION_HP:
		{
			if (this->m_output_ship_motion_hp == false) return;
			MAPSIOElt* ioeltout = StartWriting(Output("ship_motion_hp_0"));
			MAPSFloat32* dataout = &ioeltout->Float32();
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[0];
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[1];
			*(dataout++) = datain->logdata.shipMotionData.shipMotion[2];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[0];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[1];
			*(dataout++) = datain->logdata.shipMotionData.shipVel[2];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[0];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[1];
			*(dataout++) = datain->logdata.shipMotionData.shipAccel[2];
			*(dataout++) = datain->logdata.shipMotionData.mainHeavePeriod;
			*(dataout++) = datain->logdata.shipMotionData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.shipMotionData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_AIR_DATA:
		{
			if (this->m_output_pressure == false) return;  
			MAPSIOElt* ioeltout = StartWriting(Output("pressure"));
			MAPSFloat32* dataout = &ioeltout->Float32();
			*(dataout++) = datain->logdata.airData.pressureAbs;
			*(dataout++) = datain->logdata.airData.altitude;
			*(dataout++) = datain->logdata.airData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.airData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	case SBG_ECOM_LOG_USBL:
		{
			if (this->m_output_usbl == false) return;   
			MAPSIOElt* ioeltout = StartWriting(Output("usbl"));
			MAPSFloat64* dataout = &ioeltout->Float64();
			*(dataout++) = datain->logdata.usblData.latitude;
			*(dataout++) = datain->logdata.usblData.longitude;
			*(dataout++) = datain->logdata.usblData.depth;
			*(dataout++) = datain->logdata.usblData.latitudeAccuracy;
			*(dataout++) = datain->logdata.usblData.longitudeAccuracy;
			*(dataout++) = datain->logdata.usblData.depthAccuracy;
			*(dataout++) = datain->logdata.usblData.status;
			ioeltout->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout);
			MAPSIOElt* ioeltout_ts = StartWriting(Output("sbg_timestamp"));
			ioeltout_ts->Integer64() = datain->logdata.usblData.timeStamp;
			ioeltout_ts->Timestamp() = ioeltin->Timestamp();
			StopWriting(ioeltout_ts);
		}
		break;
	    default:
		    {
	            MAPSStreamedString ss;
	            ss << "Decoding of message type " << datain->cmd << "("
	                    << sbgEcomLogToString(datain->cmd) << ") is not implemented yet. Please "
	                    "contact Intempora.";
			    ReportError(ss);
		    }
	        break;
	}
}

//De-initialization: Death() will be called once at diagram execution shutdown.
void MAPSellipse_decoder::Death()
{
}
