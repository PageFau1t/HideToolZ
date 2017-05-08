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
	BOOL InitCOM();
	BOOL UninitCOM();
	void InitController(); //获取默认输出设备、终结点、session管理
	void ReleaseController();

	IMMDeviceEnumerator *m_pEnumerator; //枚举音频设备
	IMMDevice *m_pSpeaker; 
	IAudioEndpointVolume *m_pEndptVolCtrl; //音频终结点
	IAudioSessionManager2 *m_pSessionManager; //音频session管理	
	GUID m_guidMyContext; //GUID? 不知何用
};