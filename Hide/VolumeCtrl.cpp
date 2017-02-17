#include "stdafx.h"
#include "VolumeCtrl.h"

VolumeCtrl::VolumeCtrl(void)
:m_pEndptVolCtrl(NULL),
m_pEnumerator(NULL),
m_pSpeaker(NULL),
m_guidMyContext(GUID_NULL)
{
	InitEndPoint();
}

VolumeCtrl::~VolumeCtrl(void)
{
	UninitEndPoint();
}

BOOL VolumeCtrl::InitEndPoint()
{
	CoInitialize(NULL);
	CoCreateGuid(&m_guidMyContext);   //=========================???

	// Get enumerator for audio endpoint devices.
	CoCreateInstance(__uuidof(MMDeviceEnumerator),	NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),	(void**)&m_pEnumerator);

	// Get default audio-rendering device.
	m_pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pSpeaker);

	// get endpoint(for speaker volume) and sessionmanager2(session volume)
	m_pSpeaker->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL, NULL, (void**)&m_pEndptVolCtrl);
	m_pSpeaker->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&m_pSessionManager);
	return TRUE;
}

BOOL VolumeCtrl::UninitEndPoint()
{
	SAFE_RELEASE(m_pEnumerator);
	SAFE_RELEASE(m_pSpeaker);
	SAFE_RELEASE(m_pEndptVolCtrl);
	SAFE_RELEASE(m_pSessionManager);
	CoUninitialize();
	return TRUE;
}

int VolumeCtrl::GetVolume()
{
	float fVolume;
	int iVolume;
	if (m_pEndptVolCtrl)
	{
		m_pEndptVolCtrl->GetMasterVolumeLevelScalar(&fVolume);
		iVolume = (int)(MAX_VOL * fVolume + 0.5);
	}
	return iVolume;
}

BOOL VolumeCtrl::GetMute()
{
	BOOL bMute = FALSE;
	if (m_pEndptVolCtrl)
		m_pEndptVolCtrl->GetMute(&bMute);
	return bMute;
}

BOOL VolumeCtrl::SetVolume(int nVol)
{
	if (nVol < 0)
		nVol = 0;
	if (nVol > MAX_VOL)
		nVol = MAX_VOL;
	if (m_pEndptVolCtrl)
	{
		HRESULT hr = m_pEndptVolCtrl->SetMasterVolumeLevelScalar((float)nVol / MAX_VOL, &m_guidMyContext);
		return SUCCEEDED(hr) ? TRUE : FALSE;
	}
	return FALSE;
}

BOOL VolumeCtrl::SetMute(BOOL bMute)
{
	if (m_pEndptVolCtrl)
		m_pEndptVolCtrl->SetMute(bMute, &m_guidMyContext);
	return TRUE;
}

int VolumeCtrl::SetSessionMute(int PID, BOOL bMute)
{
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
		if (PID==processID)
		{
			sessionCtrl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&m_pAudioVolume);
			m_pAudioVolume->SetMute(bMute, &m_guidMyContext);
		}		
	}

	return 0;
}
