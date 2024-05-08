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

	UEngineSoundPlayer GetSlomoEnd()
	{
		return SlomoEnd;
	}

	UEngineSoundPlayer GetReplayPlay()
	{
		return Replay_Play;
	}
	
	UEngineSoundPlayer GetReplayFastPlay()
	{
		return Replay_FastPlay;
	}

public:
	static UEngineSoundPlayer SoundPlay_PlayerRun();
	static UEngineSoundPlayer SoundPlay_PlayerSlash();
	static UEngineSoundPlayer SoundPlay_EnemyDeadSword();
	static UEngineSoundPlayer SoundPlay_EnemyBloodSplat();

private:
	void FactoryBGMInit();
	void SlomoSoundInit();
	void ReplaySoundInit();

private:
	static USoundManager* Inst;

	UEngineSoundPlayer FactoryBGM;
	UEngineSoundPlayer SlomoStart;
	UEngineSoundPlayer SlomoEnd;
	UEngineSoundPlayer Replay_Play;
	UEngineSoundPlayer Replay_FastPlay;
	//UEngineSoundPlayer SlomoEnd;
};

