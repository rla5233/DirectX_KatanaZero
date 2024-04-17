#pragma once

class URecordingObject;

class URecordInfo
{
	friend URecordingObject;
private:
	std::map<URenderer*, FSpriteInfo> RendererData;
	AActor* Actor;
	FVector Position;

public:
	void Revers()
	{
		/*for (std::pair<const URenderer*, FSpriteInfo>& Pair : RendererData)
		{

		}*/
		
		Actor->SetActorLocation(Position);
	}
	

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
	void Recording(AActor* _Actor, float _DeltaTime);

	void SetReplayStart();
	void Replaying(AActor* _Actor, float _DeltaTime);

protected:

private:
	int MaxSize = 10000;
	int CurIndex = 0;
	float TimeCount = 0.0f;

	std::vector<URecordInfo> AllRecordInfo;

};

