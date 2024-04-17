#include "PreComPile.h"
#include "RecordingObject.h"

URecordingObject::URecordingObject()
{
}

URecordingObject::~URecordingObject()
{
}

void URecordingObject::SetRecordingSize(float _RecTime)
{
	//TransInfo.reserve(static_cast<size_t>(_RecTime));

	AllRecordInfo.reserve(MaxSize);
}

void URecordingObject::Recording(AActor* _Actor, float _DeltaTime)
{
	if (0.0f < TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	if (MaxSize < CurIndex)
	{
		MsgBoxAssert("녹화 용량을 초과했습니다.");
		return;
	}

	AActor* Actor = _Actor;

	URecordInfo NewRecInfo = URecordInfo();
	NewRecInfo.Position = _Actor->GetActorLocation();
	
	AllRecordInfo.push_back(NewRecInfo);

	CurIndex++;

	TimeCount = Const::recording_delay;
}

void URecordingObject::SetReplayStart()
{
	CurIndex = 0;
}

void URecordingObject::Replaying(AActor* _Actor, float _DeltaTime)
{
	if (0.0f < TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	if (AllRecordInfo.size() <= CurIndex)
	{
		int a = 0;
		return;
	}

	_Actor->SetActorLocation(AllRecordInfo[CurIndex].Position);

	CurIndex++;

	TimeCount = Const::recording_delay;
}
