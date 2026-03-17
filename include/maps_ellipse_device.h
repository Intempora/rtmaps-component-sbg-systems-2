////////////////////////////////
// RTMaps SDK Component header
////////////////////////////////

#ifndef _Maps_ig_device_H
#define _Maps_ig_device_H

// Includes maps sdk library header
#include <memory>
#include <sbgEComLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maps.hpp"
#include "maps_baseclock.h"

// Declares a new MAPSComponent child class
class MAPSellipse_device : public MAPSComponent, public MAPSBaseClock 
{
	// Use standard header definition macro
	MAPS_COMPONENT_HEADER_CODE_WITHOUT_CONSTRUCTOR(MAPSellipse_device)
	MAPSellipse_device(const char *componentName, MAPSComponentDefinition& md):MAPSComponent(componentName, md), MAPSBaseClock(componentName) {_synchOnGPS = false;}
private :
	// Place here your specific methods and attributes
	std::unique_ptr<SbgEComHandle> _comHandle = nullptr;
	std::unique_ptr<SbgInterface> _sbgInterface = nullptr;
	std::unique_ptr<SbgEComDeviceInfo> _deviceInfo = nullptr;


	static SbgErrorCode continuousCallbackStatic(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgEComLogUnion *pLogData, void *pUserArg);
	SbgErrorCode continuousCallback(SbgEComHandle *pHandle, SbgEComClass msgClass, SbgEComMsgId msg, const SbgEComLogUnion *pLogData);
	
    //Implement those 4 methods, inherited from the MAPSBaseClock class.
    void InitClock() {}		    //Nothing special here. Initialization of the clock when RTMaps is launched.
    void RunClock();		    //Implemented in .cpp. Called when RTMaps needs to start the clock.
    void ShutdownClock();	    //Nothing special here. Called when RTMaps stops the current clock.
    MAPSTimestamp CurrentTime();    //Implemented in .cpp. Called every time someone in RTMaps needs the current time.
    MAPSMutex		m_MyTimeMonitor;
    MAPSTimestamp	m_Timebase;
    MAPSTimestamp	m_TimebaseX;
	bool _synchOnGPS;
	int _synch_count;
	bool _outputAppliedOffset;
	int _synch_when;
	MAPSTimestamp _nextSynchTime;

	MAPSTimestamp PerformSynchOperation(MAPSAbsoluteTime& at);
	void OutputOffset(int status, MAPSTimestamp offset);

	//Time utils
	static MAPSString AbsTime2String(MAPSAbsoluteTime absTime);

	static void Timestamp2AbsTime(MAPSTimestamp t, MAPSAbsoluteTime* absTime);
	static MAPSTimestamp AbsTime2Timestamp(const MAPSAbsoluteTime& absTime);

	static void GetSystemTime(MAPSAbsoluteTime* absTime);
	static bool SetSystemTime(const MAPSAbsoluteTime& absTime);

	/*	Converts a MAPSAbsoluteTime value into a tm ANSI struct
		Since tm has a resolution of only a second, this function return the number of microsecondes left
		in the MAPSAbsoluteTime after conversion.*/
	static MAPSDelay AbsTime2tm(const MAPSAbsoluteTime& absTime, tm* tmTime);
	static void tm2AbsTime(const tm& tmTime, MAPSAbsoluteTime* absTime);
#ifdef WIN32
	static MAPSDelay AbsTime2SystemTime(const MAPSAbsoluteTime& absTime, SYSTEMTIME* st);
#endif

};

#endif
