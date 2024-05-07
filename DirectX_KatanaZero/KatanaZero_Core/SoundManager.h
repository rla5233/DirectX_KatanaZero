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
	
	static UEngineSoundPlayer SoundPlay_PlayerRun();

	UEngineSoundPlayer GetFactoryBGM()
	{
		return FactoryBGM;
	}

private:
	void SetFactoryBGM();

private:
	static USoundManager* Inst;

	UEngineSoundPlayer FactoryBGM;
};

