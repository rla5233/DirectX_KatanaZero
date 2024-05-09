#pragma once

// Ό³Έν :
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
	static USoundManager* GetInst()
	{
		if (nullptr == Inst)
		{
			Inst = new USoundManager();
		}

		return Inst;
	}

	static void DestoryInstance()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

	UEngineSoundPlayer GetFactoryBGM()
	{
		return FactoryBGM;
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

private:
	void FactoryBGMInit();
	void SlomoSoundInit();
	void ReplaySoundInit();
	void PlayerSoundInit();
	void HeadHunterSoundInit();

private:
	static USoundManager* Inst;

	UEngineSoundPlayer FactoryBGM;
	UEngineSoundPlayer SlomoStart;
	UEngineSoundPlayer SlomoEnd;
	UEngineSoundPlayer Replay_Play;
	UEngineSoundPlayer Replay_FastPlay;
	UEngineSoundPlayer Player_WallSlide;
	UEngineSoundPlayer HeadHunterBGM1;
};

