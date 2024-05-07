#include "PreCompile.h"
#include "SoundManager.h"

USoundManager::USoundManager()
{
}

USoundManager::~USoundManager()
{
}

UEngineSoundPlayer USoundManager::SoundPlay_PlayerRun()
{
    UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 4);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::player_run_1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::player_run_2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::player_run_3);
		break;
	case 4:
		Result = UEngineSound::SoundPlay(SoundRes::player_run_4);
		break;
	}

	Result.SetVolume(0.5f);
	return Result;
}
