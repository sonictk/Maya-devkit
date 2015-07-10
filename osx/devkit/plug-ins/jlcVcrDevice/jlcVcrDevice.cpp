//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

//////////////////////////////////////////////////////////////////
//
//  JLCVCRdevice
//
//	Description:
//			The jlcVcr class is an interface to the
//          JLCooper midi VCR control box.
//
//////////////////////////////////////////////////////////////////

#if defined (LINUX) || defined (SGI)
#include <dmedia/midi.h>
#endif

#include <maya/MIOStream.h>

#include <maya/MPxMidiInputDevice.h>
#include <maya/MDeviceState.h>
#include <maya/MDeviceChannel.h>
#include <maya/MString.h>
#include <maya/MFnPlugin.h>
#include <maya/MObject.h>

#define kVCRRewindButtonName "rewind"
#define kVCRRewindButtonIndex 0
#define kVCRForwardButtonName "forward"
#define kVCRForwardButtonIndex 1
#define kVCRStopButtonName "stop"
#define kVCRStopButtonIndex 2
#define kVCRPlayButtonName "play"
#define kVCRPlayButtonIndex 3
#define kVCRRecordButtonName "record"
#define kVCRRecordButtonIndex 4
#define kVCRLastButtonIndex 5

#define kVCRScrubWheelName "scrub"
#define kVCRScrubWheelIndex 0
#define kVCRLastAxisIndex 1

#define kVCRRewindUp    0x07
#define kVCRRewindDown  0x47
#define kVCRForwardUp   0x06
#define kVCRForwardDown 0x46
#define kVCRStopUp      0x05
#define kVCRStopDown    0x45
#define kVCRPlayUp      0x04
#define kVCRPlayDown    0x44
#define kVCRRecordUp    0x00
#define kVCRRecordDown  0x40

class jlcVcr : public MPxMidiInputDevice {

public:
								jlcVcr();
    virtual						~jlcVcr();

	virtual void		 		nameAxes();
	virtual void		 		nameButtons();

	static void*				creator();

protected:
	virtual MDeviceState*		deviceState();
#if defined (LINUX) || defined (SGI)
	virtual MDeviceState*		deviceState(MDevent&);
#endif
};

jlcVcr::jlcVcr()
{
	setDegreesOfFreedom( kVCRLastAxisIndex );
	setNumberOfButtons( kVCRLastButtonIndex );
}

jlcVcr::~jlcVcr() {}

void* jlcVcr::creator()
{
	return new jlcVcr();
}



// Name the buttons of this device
void jlcVcr::nameButtons()
{
	MString name;

	name.set(kVCRRewindButtonName);
	setNamedButton(name, kVCRRewindButtonIndex);

	name.set(kVCRForwardButtonName);
	setNamedButton(name, kVCRForwardButtonIndex);

	name.set(kVCRStopButtonName);
	setNamedButton(name, kVCRStopButtonIndex);

	name.set(kVCRPlayButtonName);
	setNamedButton(name, kVCRPlayButtonIndex);

	name.set(kVCRRecordButtonName);
	setNamedButton(name, kVCRRecordButtonIndex);
}

// Name the axes of this device
void jlcVcr::nameAxes()
{
	MString name(kVCRScrubWheelName);

	MDeviceChannel* scrubChannel =
		new MDeviceChannel(name, NULL, kVCRScrubWheelIndex);

	addChannel( *scrubChannel );
}

MDeviceState* jlcVcr::deviceState()
{
	return MPxMidiInputDevice::deviceState();
}

// If this midi event belongs to this device then turn it
// into a MDeviceState.  Otherwise return NULL.
#if defined (LINUX) || defined (SGI)
MDeviceState* jlcVcr::deviceState(MDevent& mde)
{
	MDeviceState * device_state = deviceState();

	if ( !device_state->isNull() &&
		(mde.msglen == 6) &&
		(mde.sysexmsg[1] == 0x15) &&
		(mde.sysexmsg[2] == 0x10)) {
		if (mde.sysexmsg[3] == 0) {
			// Button Event
			switch (mde.sysexmsg[4]) {
				case kVCRRewindUp:
					device_state->setButtonState(false, kVCRRewindButtonIndex);
					break;
				case kVCRRewindDown:
					device_state->setButtonState(true, kVCRRewindButtonIndex);
					break;
				case kVCRForwardUp:
					device_state->setButtonState(false, kVCRForwardButtonIndex);
					break;
				case kVCRForwardDown:
					device_state->setButtonState(true, kVCRForwardButtonIndex);
					break;
				case kVCRStopUp:
					device_state->setButtonState(false, kVCRStopButtonIndex);
					break;
				case kVCRStopDown:
					device_state->setButtonState(true, kVCRStopButtonIndex);
					break;
				case kVCRPlayUp:
					device_state->setButtonState(false, kVCRPlayButtonIndex);
					break;
				case kVCRPlayDown:
					device_state->setButtonState(true, kVCRPlayButtonIndex);
					break;
				case kVCRRecordUp:
					device_state->setButtonState(false, kVCRRecordButtonIndex);
					break;
				case kVCRRecordDown:
					device_state->setButtonState(true, kVCRRecordButtonIndex);
					break;
			}
			device_state->setDevicePosition(0.0, kVCRScrubWheelIndex);
		} else {
			// The scrub wheel moved
			int c = mde.sysexmsg[4];
			if (c & 0x40) { // Check the sign bit
				c = c - 128;
			}
			device_state->setDevicePosition(c, kVCRScrubWheelIndex);
		}
		return device_state;
	} else {
		return NULL;
	}
}
#endif


/////////////////////////////////////////////////////////
//
// Register the device
//
/////////////////////////////////////////////////////////
MStatus initializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj, PLUGIN_COMPANY, "3.0", "Any");

	status = plugin.registerDevice("jlcVcr", jlcVcr::creator );
	if (!status) {
		status.perror("registerDevice");
		return status;
	}

	return status;
}

MStatus uninitializePlugin( MObject obj )
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status =  plugin.deregisterDevice( "jlcVcr" );
	if (!status) {
		status.perror("deregisterDevice");
		return status;
	}

	return status;
}
