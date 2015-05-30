// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VOLUMECTRL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VOLUMECTRL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VOLUMECTRL_EXPORTS
#define VOLUMECTRL_API  __declspec(dllexport)
#else
#define VOLUMECTRL_API __declspec(dllimport)
#endif

#pragma once
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <MMSystem.h>
#include <stdlib.h>
#include <commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#define SAFE_RELEASE(punk)  \
if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }
typedef enum WindowsType
{
	UnknownOS = 0,
	WindowsXP = 1,
	WindowsVista = 2,
	Windows7 = 3,
};
#define MAX_VOL 100

// This class is exported from the VolumeCtrl.dll
class VOLUMECTRL_API CVolumeCtrl 
{
public:
	CVolumeCtrl(void);
	~CVolumeCtrl(void);
	int GetMaxVol();
	int GetMinVol();
	int GetVolume();
	BOOL SetVolume(int nVol);
	BOOL SetMute(BOOL bMute);
	BOOL GetMute();
protected: //for xp
	unsigned int vGetVolume(int   dev);
	BOOL vSetVolume(long   dev, long   vol);
	BOOL vSetMute(long   dev, long   vol);
	BOOL vGetMute(long   dev);

	//
	BOOL   vGetVolumeControl(HMIXER   hmixer, long   componentType, long   ctrlType, MIXERCONTROL*   mxc);
	long   vGetMuteValue(HMIXER   hmixer, MIXERCONTROL   *mxc);
	unsigned int vGetVolumeValue(HMIXER   hmixer, MIXERCONTROL   *mxc);
	BOOL   vSetMuteValue(HMIXER   hmixer, MIXERCONTROL   *mxc, BOOL   mute);
	BOOL   vSetVolumeValue(HMIXER   hmixer, MIXERCONTROL   *mxc, long   volume);
protected://for vista and win7
	BOOL vInitEndPoint();
	BOOL vMuteSet(BOOL bMute);
	BOOL vMuteGet();
	BOOL vVolumeSet(DWORD dwVolume);
	BOOL vVolumeGet(DWORD* pdwVolume);
	BOOL vUninitEndPoint();
protected:
	WindowsType vGetWindowsType();
protected:
	WindowsType m_eWinType;
	IAudioEndpointVolume *m_pEndptVolCtrl;
	IMMDeviceEnumerator *m_pEnumerator;
	IMMDevice *m_pDevice;
	GUID m_guidMyContext;
};

extern VOLUMECTRL_API int nVolumeCtrl;

VOLUMECTRL_API int fnVolumeCtrl(void);
