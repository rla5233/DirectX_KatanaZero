#include "PreCompile.h"
#include "SoundManager.h"

USoundManager* USoundManager::Inst = nullptr;

USoundManager::USoundManager()
{
	FactoryBGMInit();
	SlomoSoundInit();
	ReplaySoundInit();
}

USoundManager::~USoundManager()
{
}

void USoundManager::FactoryBGMInit()
{
	FactoryBGM = UEngineSound::SoundPlay(SoundRes::bgm_factory);
	FactoryBGM.SetVolume(0.6f);
	FactoryBGM.Loop();
	FactoryBGM.Off();
}

void USoundManager::SlomoSoundInit()
{
	SlomoStart = UEngineSound::SoundPlay(SoundRes::slomo_start);
	SlomoStart.SetVolume(0.6f);
	SlomoStart.Off();

	SlomoEnd = UEngineSound::SoundPlay(SoundRes::slomo_end);
	SlomoEnd.Off();
}

void USoundManager::ReplaySoundInit()
{
	Replay_Play = UEngineSound::SoundPlay(SoundRes::replay_play);
	Replay_Play.SetVolume(1.0f);
	Replay_Play.Loop();
	Replay_Play.Off();

	Replay_FastPlay = UEngineSound::SoundPlay(SoundRes::replay_fastplay);
	Replay_FastPlay.SetVolume(1.0f);
	Replay_FastPlay.Loop();
	Replay_FastPlay.Off();

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

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_EnemyDeadSword()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_dead_sword1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_dead_sword2);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_EnemyBloodSplat()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 4);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_bloodsplat1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_bloodsplat2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_bloodsplat3);
		break;
	case 4:
		Result = UEngineSound::SoundPlay(SoundRes::enemy_bloodsplat4);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_GunFire()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 2);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::gun_fire1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::gun_fire1);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}


