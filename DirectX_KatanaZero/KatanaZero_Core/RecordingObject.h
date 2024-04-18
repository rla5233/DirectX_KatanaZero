#pragma once

class URecordingObject;

struct USpriteRendererInfo
{
public:
	FSpriteInfo SpriteInfo;
	FVector Position = FVector::Zero;
	FVector Rocation = FVector::Zero;
	EEngineDir Dir = EEngineDir::MAX;
	bool IsActive = false;
};

class URecordInfo
{
	friend URecordingObject;
private:
	std::map<std::shared_ptr<USpriteRenderer>, USpriteRendererInfo> SpriteRendererData;
	FVector Position;
};

// ���� : ���÷��� ��� ������Ʈ
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

	void SetRecordingSize(float _RecTime);
	void Recording(float _DeltaTime);

	void SetReplayStart();
	void Replaying(float _DeltaTime);

protected:
	void SetRecordActor(AActor* _Actor)
	{
		Actor = _Actor;
	}

private:
	AActor* Actor = nullptr;
	
	int MaxSize = 10000;
	int CurIndex = 0;
	float TimeCount = Const::recording_delay;

	std::vector<URecordInfo> AllRecordInfo;
};
