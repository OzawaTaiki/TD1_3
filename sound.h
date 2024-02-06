#pragma once

class Sound
{
private:
	int soundHandle;
	int voiceHandle;
	bool isSound;
	bool isLoop;
	bool isPlaying;
	bool isFade;
	float volume;
	float currentVolume;
	int frameCnt;
public:

	Sound(const char* _path, float _volume, bool _isLoop = false);
	Sound(int _handle, float _volume, bool _isLoop = false);

#ifdef _DEBUG
	void printVolume(int x, int y);
#endif // _DEBUG

	void SoundEnable();

	void PlayAudio(bool _isFadeIn = false, int _fadeFrame = -1);
	void StopAudio(bool _isFadeOut = false, int _fadeFrame = -1);
};