#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Audioclient.h>
#include <audiopolicy.h>

#define SAFE_RELEASE(punk)  \
if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }

#define MAX_VOL 100
class VolumeCtrl
{
public:
	VolumeCtrl(void);
	~VolumeCtrl(void);
	int GetVolume();
	BOOL GetMute();
	BOOL SetVolume(int nVol);
	BOOL SetMute(BOOL bMute);
	int SetSessionMute(int PID,BOOL bMute);

protected:
	BOOL InitEndPoint();
	BOOL UninitEndPoint();	

	IMMDeviceEnumerator *m_pEnumerator;
	IMMDevice *m_pSpeaker;
	IAudioEndpointVolume *m_pEndptVolCtrl;
	IAudioSessionManager2 *m_pSessionManager;
	ISimpleAudioVolume *m_pAudioVolume;
	GUID m_guidMyContext;	
};