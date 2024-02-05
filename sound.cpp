#include "sound.h"
#include <Novice.h>
#include <cassert>

Sound::Sound(char* _path, float _volume, bool _isLoop)
{
	soundHandle = Novice::LoadAudio(_path);

	voiceHandle = -1;
	isSound = false;
	isLoop = _isLoop;
	isPlaying = false;
	isFade = true;
	volume = _volume;
	frameCnt = 0;
}

void Sound::PlayAudio(bool _isFadeIn, int _fadeFrame)
{
	if (_isFadeIn && isPlaying && isFade)
	{
		assert(_fadeFrame != -1);

		frameCnt++;
		float val = (float)frameCnt / (float)_fadeFrame;
		if (val >= 1.0f)
		{
			val = 1.0f;
			isFade = false;
		}

		Novice::SetAudioVolume(voiceHandle, val * volume);
	}

	if (isLoop)
	{
		if (Novice::IsPlayingAudio(voiceHandle) || voiceHandle == -1 && isSound)
		{
			voiceHandle = Novice::PlayAudio(soundHandle, isLoop, volume);
			isSound = false;
			isPlaying = true;
		}
	}
	else
	{
		if (isSound)
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
		}

		Novice::SetAudioVolume(voiceHandle, val * volume);
	}

	else if (Novice::IsPlayingAudio(voiceHandle))
	{
		Novice::StopAudio(voiceHandle);
		isPlaying = false;
	}
}
