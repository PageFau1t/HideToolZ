#include "stdafx.h"
#include "VolumeCtrl.h"

VolumeCtrl::VolumeCtrl(void)
:m_pEndptVolCtrl(NULL),
m_pEnumerator(NULL),
m_pSpeaker(NULL),
m_guidMyContext(GUID_NULL)
{
	InitCOM();
}

VolumeCtrl::~VolumeCtrl(void)
{
	UninitCOM();
}

BOOL VolumeCtrl::InitCOM()
{
	CoInitialize(NULL);
	CoCreateGuid(&m_guidMyContext);   //=========================???

	// Get enumerator for audio endpoint devices.
	CoCreateInstance(__uuidof(MMDeviceEnumerator),	NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),	(void**)&m_pEnumerator);

	return TRUE;
}


BOOL VolumeCtrl::UninitCOM()
{
	SAFE_RELEASE(m_pEnumerator);
	//SAFE_RELEASE(m_pSpeaker);
	//SAFE_RELEASE(m_pEndptVolCtrl);
	//SAFE_RELEASE(m_pSessionManager);
	CoUninitialize();
	return TRUE;
}


void VolumeCtrl::InitController()
{
	// Get default audio-rendering device.
	m_pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pSpeaker);

	// get endpoint(for speaker volume) and sessionmanager2(session volume)
	m_pSpeaker->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&m_pEndptVolCtrl);
	m_pSpeaker->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&m_pSessionManager);
}

void VolumeCtrl::ReleaseController()
{
	SAFE_RELEASE(m_pSpeaker);
	SAFE_RELEASE(m_pEndptVolCtrl);
	SAFE_RELEASE(m_pSessionManager);
}

int VolumeCtrl::GetVolume()
{
	InitController();
	float fVolume;
	int iVolume;
	if (m_pEndptVolCtrl)
	{
		m_pEndptVolCtrl->GetMasterVolumeLevelScalar(&fVolume);
		iVolume = (int)(MAX_VOL * fVolume + 0.5);
	}

	ReleaseController();
	return iVolume;
}

BOOL VolumeCtrl::GetMute()
{
	InitController();
	BOOL bMute = FALSE;
	if (m_pEndptVolCtrl)
		m_pEndptVolCtrl->GetMute(&bMute);

	ReleaseController();
	return bMute;
}


BOOL VolumeCtrl::SetVolume(int nVol)
{
	InitController();
	if (nVol < 0)
		nVol = 0;
	if (nVol > MAX_VOL)
		nVol = MAX_VOL;
	if (m_pEndptVolCtrl)
	{
		HRESULT hr = m_pEndptVolCtrl->SetMasterVolumeLevelScalar((float)nVol / MAX_VOL, &m_guidMyContext);
		return SUCCEEDED(hr) ? TRUE : FALSE;
	}

	ReleaseController();
	return FALSE;
}

BOOL VolumeCtrl::SetMute(BOOL bMute)
{
	InitController();
	if (m_pEndptVolCtrl)
		m_pEndptVolCtrl->SetMute(bMute, &m_guidMyContext);

	ReleaseController();
	return TRUE;
}

int VolumeCtrl::SetSessionMute(int PID, BOOL bMute)
{
	InitController();
	// enumerate sessions on this device
	IAudioSessionEnumerator *sessionEnumerator;
	m_pSessionManager->GetSessionEnumerator(&sessionEnumerator);
	int count = 0;
	sessionEnumerator->GetCount(&count);
	
	for (int i = 0; i < count; ++i)
	{
		IAudioSessionControl2 *sessionCtrl;
		sessionEnumerator->GetSession(i, (IAudioSessionControl**)&sessionCtrl);
		DWORD processID;
		sessionCtrl->GetProcessId(&processID);
		if (PID==processID) //session属于目标进程
		{
			ISimpleAudioVolume *pAudioVolume;
			sessionCtrl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pAudioVolume);
			pAudioVolume->SetMute(bMute, &m_guidMyContext);
			SAFE_RELEASE(pAudioVolume);
		}
		SAFE_RELEASE(sessionCtrl);
	}
	SAFE_RELEASE(sessionEnumerator);
	ReleaseController();
	return 0;
}
