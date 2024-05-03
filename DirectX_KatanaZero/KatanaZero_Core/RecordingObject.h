#pragma once

class URecordingObject;

struct FSpriteRendererInfo
{
public:
	FSpriteInfo SpriteInfo;
	FVector Position = FVector::Zero;
	FVector Rotation = FVector::Zero;
	EEngineDir Dir = EEngineDir::MAX;
	bool IsActive = false;
};

class URecordInfo
{
	friend URecordingObject;
private:
	std::map<std::shared_ptr<USpriteRenderer>, FSpriteRendererInfo> SpriteRendererData;
	FVector Position;
};

// 설명 : 리플레이 기능 오브젝트
class URecordingObject
{
public:
	// constrcuter destructer
	URecordingObject();
	~URecordingObject();

	// delete Function
	URecordingObject(const URecordingObject& _Other) = delete;
	URecordingObject(URecordingObject&& _Other) noexcept = delete;
	URecordingObject& operator=(const URecordingObject& _Other) = delete;
	URecordingObject& operator=(URecordingObject&& _Other) noexcept = delete;

	void SetRecordingSize();
	void SetReplayStart();
	void SetRewindStart();

	void Recording(float _DeltaTime);
	void Replaying(float _DeltaTime);

	inline void SetReplayMode(EReplayMode _Mode)
	{
		Mode = _Mode;
	}

	inline void SetRecordingActive(bool _Active)
	{
		IsRecordingValue = _Active;
	}

	inline bool IsRecording() const 
	{
		return IsRecordingValue;
	}

	inline void SetReplaySpeed(int _Speed)
	{
		ReplaySpeed = _Speed;
	}

	void IncreaseReplaySpeed();

	inline bool IsReplayEnd() const
	{
		bool Result = false;

		if (AllRecordInfo.size() - 1 <= CurIndex)
		{
			Result = true;
		}
		
		return Result;
	}

	inline bool IsRewindEnd() const
	{
		bool Result = false;

		if (0 >= CurIndex)
		{
			Result = true;
		}

		return Result;
	}

	// 수정 
	int GetReplaySpeed()
	{
		return ReplaySpeed;
	}


protected:
	void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
	}

private:
	void DecreaseIndex();
	void IncreaseIndex();

private:
	AActor* Actor = nullptr;

	EReplayMode Mode = EReplayMode::Play;
	int ReplaySpeed = 1;
	
	bool IsRecordingValue = false;
	int MaxSize = 0;
	int CurIndex = 0;
	float TimeCount = Const::recording_delay;

	std::vector<URecordInfo> AllRecordInfo;
};

