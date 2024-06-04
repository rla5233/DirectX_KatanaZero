#include "PreCompile.h"
#include "SoundManager.h"

USoundManager::USoundManager()
{
	FactoryBGMInit();
	SlomoSoundInit();
	ReplaySoundInit();
	PlayerSoundInit();
	HeadHunterSoundInit();
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

void USoundManager::PlayerSoundInit()
{
	Player_WallSlide = UEngineSound::SoundPlay(SoundRes::player_wall_slide);
	Player_WallSlide.SetVolume(0.5f);
	Player_WallSlide.Loop();
	Player_WallSlide.Off();
}

void USoundManager::HeadHunterSoundInit()
{
	HeadHunterBGM1 = UEngineSound::SoundPlay(SoundRes::bgm_headhunter1);
	HeadHunterBGM1.SetVolume(0.6f);
	HeadHunterBGM1.Loop();
	HeadHunterBGM1.Off();

	HeadHunterBGM2 = UEngineSound::SoundPlay(SoundRes::bgm_headhunter2);
	HeadHunterBGM2.SetVolume(0.6f);
	HeadHunterBGM2.Loop();
	HeadHunterBGM2.Off();
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

UEngineSoundPlayer USoundManager::SoundPlay_WallKick()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::player_wall_kick1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::player_wall_kick1);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::player_wall_kick1);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_HH_LaserShot()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_shoot1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_shoot2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_shoot3);
		break;
	}

	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_HH_Voice_WallJump()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_walljump1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_walljump2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_walljump3);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_HH_Voice_Hurt()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_hurt1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_hurt2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::hh_voice_hurt3);
		break;
	}

	Result.SetVolume(0.75f);
	return Result;
}

UEngineSoundPlayer USoundManager::SoundPlay_HH_Laser_Vertical()
{
	UEngineSoundPlayer Result = UEngineSoundPlayer();

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_vertical1);
		break;
	case 2:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_vertical2);
		break;
	case 3:
		Result = UEngineSound::SoundPlay(SoundRes::hh_laser_vertical3);
		break;
	}

	return Result;
}


