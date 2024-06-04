#pragma once

// ���� :
class USoundManager
{
private:
	// constrcuter destructer
	USoundManager();
	~USoundManager();

	// delete Function
	USoundManager(const USoundManager& _Other) = delete;
	USoundManager(USoundManager&& _Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& _Other) = delete;
	USoundManager& operator=(USoundManager&& _Other) noexcept = delete;

public:
	static USoundManager& GetInst()
	{
		static USoundManager Inst;
		return Inst;
	}

	UEngineSoundPlayer GetFactoryBGM()
	{
		return FactoryBGM;
	}

	void ResetFactoryBGM()
	{
		FactoryBGM = FactoryBGM.Replay();
		FactoryBGM.SetVolume(0.6f);
		FactoryBGM.Loop();
		FactoryBGM.Off();
	}

	UEngineSoundPlayer GetSlomoStart()
	{
		return SlomoStart;
	}

	void SetSlomoStart(UEngineSoundPlayer _Sound)
	{
		SlomoStart = _Sound;
	}

	UEngineSoundPlayer GetSlomoEnd()
	{
		return SlomoEnd;
	}

	void SetSlomoEnd(UEngineSoundPlayer _Sound)
	{
		SlomoEnd = _Sound;
	}

	UEngineSoundPlayer GetReplayPlay()
	{
		return Replay_Play;
	}
	
	UEngineSoundPlayer GetReplayFastPlay()
	{
		return Replay_FastPlay;
	}

	UEngineSoundPlayer GetPlayerWallSlide()
	{
		return Player_WallSlide;
	}

	UEngineSoundPlayer GetHeadHunterBGM1()
	{
		return HeadHunterBGM1;
	}

	UEngineSoundPlayer GetHeadHunterBGM2()
	{
		return HeadHunterBGM2;
	}

	void ResetHeadHunterBGM1()
	{
		HeadHunterBGM1 = HeadHunterBGM1.Replay();
		HeadHunterBGM1.SetVolume(0.6f);
		HeadHunterBGM1.Loop();
		HeadHunterBGM1.Off();
	}

	void ResetHeadHunterBGM2()
	{
		HeadHunterBGM2 = HeadHunterBGM2.Replay();
		HeadHunterBGM2.SetVolume(0.6f);
		HeadHunterBGM2.Loop();
		HeadHunterBGM2.Off();
	}

public:
	static UEngineSoundPlayer SoundPlay_PlayerRun();
	static UEngineSoundPlayer SoundPlay_PlayerSlash();
	static UEngineSoundPlayer SoundPlay_EnemyDeadSword();
	static UEngineSoundPlayer SoundPlay_EnemyBloodSplat();
	static UEngineSoundPlayer SoundPlay_GunFire();
	static UEngineSoundPlayer SoundPlay_WallKick();
	static UEngineSoundPlayer SoundPlay_HH_LaserShot();
	static UEngineSoundPlayer SoundPlay_HH_Voice_WallJump();
	static UEngineSoundPlayer SoundPlay_HH_Voice_Hurt();
	static UEngineSoundPlayer SoundPlay_HH_Laser_Vertical();

private:
	void FactoryBGMInit();
	void SlomoSoundInit();
	void ReplaySoundInit();
	void PlayerSoundInit();
	void HeadHunterSoundInit();

private:
	UEngineSoundPlayer FactoryBGM;
	UEngineSoundPlayer SlomoStart;
	UEngineSoundPlayer SlomoEnd;
	UEngineSoundPlayer Replay_Play;
	UEngineSoundPlayer Replay_FastPlay;
	UEngineSoundPlayer Player_WallSlide;
	UEngineSoundPlayer HeadHunterBGM1;
	UEngineSoundPlayer HeadHunterBGM2;
};

