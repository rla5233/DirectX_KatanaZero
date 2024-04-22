#include "PreComPile.h"
#include "RecordingObject.h"

#include "PlayLevelBase.h"

URecordingObject::URecordingObject()
{
}

URecordingObject::~URecordingObject()
{
}

void URecordingObject::SetRecordingSize()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(Actor->GetWorld()->GetGameMode().get());
	
#ifdef _DEBUG
	if (nullptr == PlayLevel)
	{
		MsgBoxAssert("레벨이 설정되지 않았거나 잘못된 레벨입니다.")
	}
#endif // _DEBUG
	
	float TotalPlayTime = PlayLevel->GetTotalPlayTime();
	MaxSize = static_cast<int>(TotalPlayTime * (1 / Const::recording_delay)) + 10;
	AllRecordInfo.reserve(MaxSize);
}

void URecordingObject::Recording(float _DeltaTime)
{
	if (false == IsRecordingValue)
	{
		return;
	}

#ifdef _DEBUG
	if (nullptr == Actor)
	{
		MsgBoxAssert("녹화 대상이 설정되지 않았습니다.");
		return;
	}

	if (MaxSize < CurIndex)
	{
		MsgBoxAssert("녹화 용량을 초과했습니다.");
		return;
	}
#endif // _DEBUG

	if (0.0f < TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	URecordInfo NewRecInfo = URecordInfo();
	NewRecInfo.Position = Actor->GetActorLocation();
	
	std::vector<std::shared_ptr<USpriteRenderer>> AllRenderer = Actor->GetComponentToClass<USpriteRenderer>();
	for (size_t i = 0; i < AllRenderer.size(); i++)
	{
		NewRecInfo.SpriteRendererData[AllRenderer[i]].SpriteInfo = AllRenderer[i]->GetCurInfo();
		NewRecInfo.SpriteRendererData[AllRenderer[i]].Position = AllRenderer[i]->GetLocalPosition();
		NewRecInfo.SpriteRendererData[AllRenderer[i]].Rocation = AllRenderer[i]->GetLocalRotation();
		NewRecInfo.SpriteRendererData[AllRenderer[i]].Dir = AllRenderer[i]->GetDir();
		NewRecInfo.SpriteRendererData[AllRenderer[i]].IsActive = AllRenderer[i]->IsActive();
	}
	
	AllRecordInfo.push_back(NewRecInfo);

	CurIndex++;

	TimeCount = Const::recording_delay;
}

void URecordingObject::SetReplayStart()
{
	CurIndex = 0;
}

void URecordingObject::Replaying(float _DeltaTime)
{
	if (0.0f < TimeCount)
	{
		TimeCount -= _DeltaTime;
		return;
	}

	Actor->SetActorLocation(AllRecordInfo[CurIndex].Position);

	std::vector<std::shared_ptr<USpriteRenderer>> AllRenderer = Actor->GetComponentToClass<USpriteRenderer>();

	for (size_t i = 0; i < AllRenderer.size(); i++)
	{
		FSpriteRendererInfo CurSpriteInfo = AllRecordInfo[CurIndex].SpriteRendererData[AllRenderer[i]];

		if (false == CurSpriteInfo.IsActive || nullptr == CurSpriteInfo.SpriteInfo.Texture)
		{
			AllRenderer[i]->SetActive(false);
			continue;
		}

		AllRenderer[i]->SetCurInfo(CurSpriteInfo.SpriteInfo);
		AllRenderer[i]->SetPosition(CurSpriteInfo.Position);
		AllRenderer[i]->SetRotationDeg(CurSpriteInfo.Rocation);
		AllRenderer[i]->SetDir(CurSpriteInfo.Dir);
		AllRenderer[i]->SetActive(true);
	}

	switch (Mode)
	{
	case EReplayMode::Rewind:
		DecreaseIndex();
		break;
	case EReplayMode::Stop:
		break;
	case EReplayMode::Play:
		IncreaseIndex();
		break;
	}
	
	TimeCount = Const::recording_delay;
}

void URecordingObject::IncreaseReplaySpeed()
{
	if (16 <= ReplaySpeed)
	{
		return;
	}

	ReplaySpeed *= 2;
}

void URecordingObject::DecreaseIndex()
{
	CurIndex -= ReplaySpeed;

	if (0 > CurIndex)
	{
		CurIndex = 0;
	}
}

void URecordingObject::IncreaseIndex()
{
	CurIndex += ReplaySpeed;

	if (static_cast<int>(AllRecordInfo.size()) <= CurIndex)
	{
		CurIndex = static_cast<int>(AllRecordInfo.size()) - 1;
	}
}
