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

	Sound(char* _path, float _volume, bool _isLoop = false);

	void printVolume(int x, int y);

	void SoundEnable();

	void PlayAudio(bool _isFadeIn = false, int _fadeFrame = -1);
	void StopAudio(bool _isFadeOut = false, int _fadeFrame = -1);
};