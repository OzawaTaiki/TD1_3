#include "sound.h"
#include <Novice.h>
#include <cassert>

Sound::Sound(const char* _path, float _volume, bool _isLoop)
{
	soundHandle = Novice::LoadAudio(_path);

	voiceHandle = -1;
	isSound = false;
	isLoop = _isLoop;
	isPlaying = false;
	isFade = true;
	volume = _volume;
	currentVolume = 0;
	frameCnt = 0;
}

Sound::Sound(int _handle, float _volume, bool _isLoop)
{
	soundHandle = _handle;

	voiceHandle = -1;
	isSound = false;
	isLoop = _isLoop;
	isPlaying = false;
	isFade = true;
	volume = _volume;
	currentVolume = 0;
	frameCnt = 0;
}

#ifdef _DEBUG
void Sound::printVolume(int x, int y)
{
	Novice::ScreenPrintf(x, y, "%.1f", currentVolume);
}
#endif // _DEBUG

void Sound::SoundEnable()
{
	isSound = true;
}

void Sound::PlayAudio(bool _isFadeIn, int _fadeFrame)
{
	float val = 0;
	if (_isFadeIn && isPlaying && isFade)
	{
		assert(_fadeFrame != -1);

		frameCnt++;
		val = (float)frameCnt / (float)_fadeFrame;
		if (val >= 1.0f)
		{
			val = 1.0f;
			isFade = false;
		}
		currentVolume = val * volume;
		Novice::SetAudioVolume(voiceHandle, currentVolume);
	}

	if (isLoop)
	{
		if ((!Novice::IsPlayingAudio(voiceHandle) || voiceHandle == -1) && isSound)
		{
			voiceHandle = Novice::PlayAudio(soundHandle, isLoop, currentVolume);
			isSound = false;
			isPlaying = true;
		}
	}
	else
	{
		if (/*(!Novice::IsPlayingAudio(voiceHandle) || voiceHandle == -1) && */isSound)
		{
			voiceHandle = Novice::PlayAudio(soundHandle, isLoop, volume);
			isSound = false;
		}
	}


}

void Sound::StopAudio(bool _isFadeOut, int _fadeFrame)
{
	if (_isFadeOut && isPlaying && isFade)
	{
		assert(_fadeFrame != -1);

		frameCnt++;
		float val = float(_fadeFrame - frameCnt) / (float)_fadeFrame;

		if (val <= 0)
		{
			val = 0;
			isPlaying = false;
			isFade = false;
			isSound = false;
		}

		Novice::SetAudioVolume(voiceHandle, val * volume);
	}

	else if (Novice::IsPlayingAudio(voiceHandle))
	{
		Novice::StopAudio(voiceHandle);
		isPlaying = false;
	}
}
