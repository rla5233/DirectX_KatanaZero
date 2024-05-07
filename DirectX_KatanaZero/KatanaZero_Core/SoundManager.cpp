#include "PreCompile.h"
#include "SoundManager.h"

USoundManager* USoundManager::Inst = nullptr;

USoundManager::USoundManager()
{
	SetFactoryBGM();

}

USoundManager::~USoundManager()
{
	delete Inst;
}

void USoundManager::SetFactoryBGM()
{
	FactoryBGM = UEngineSound::SoundPlay(SoundRes::bgm_factory);
	FactoryBGM.SetVolume(0.6f);
	FactoryBGM.Loop();
	FactoryBGM.Off();
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

UEngineSoundPlayer USoundManager::SoundPlay_PlayerSlash()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::player_slash_1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::player_slash_2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::player_slash_3);
		break;
	}

	Result.SetVolume(0.5f);
	return Result;
}


