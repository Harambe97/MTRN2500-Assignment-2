#ifndef XINPUT_WRAPPER_H
#define XINPUT_WRAPPER_H

#include <XInput.h>
#include <errno.h>

/*
* The wrapper intercepts inputs from the controller functions to allow automarking of the assignment files, it works
* independently of the functions and does not affect the functionality of the controller. The wrapper needs to be
* called in controller functions that require access to the 'XInput' library using syntax that mimics the following
* example:
*
* this->xinput = xinput;
* xinput->XInputGetState(ControllerID, &State); (or any other 'XInput' function that needs to be accessed)
*/

class XInputWrapper {
public:
	XInputWrapper() = default;
	~XInputWrapper() = default;

	virtual DWORD XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState) {
#ifdef _WIN32
		return ::XInputGetState(dwUserIndex, pState);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration) {
#ifdef _WIN32
		return ::XInputSetState(dwUserIndex, pVibration);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities) {
#ifdef _WIN32
		return ::XInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION* pBatteryInformation) {
#ifdef _WIN32
		return ::XInputGetBatteryInformation(dwUserIndex, devType, pBatteryInformation);
#else
		return EPERM;
#endif
	}

	virtual DWORD XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeyStroke) {
#ifdef _WIN32
		return ::XInputGetKeystroke(dwUserIndex, dwReserved, pKeyStroke);
#else
		return EPERM;
#endif
	}
};

#endif // XINPUT_WRAPPER_H