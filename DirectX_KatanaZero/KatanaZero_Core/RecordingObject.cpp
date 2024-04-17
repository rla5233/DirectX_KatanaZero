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

void URecordingObject::Recording(float _DeltaTime)
{
#ifdef _DEBUG
	if (nullptr == Actor)
	{
		MsgBoxAssert("��ȭ ����� �������� �ʾҽ��ϴ�.");
		return;
	}

	if (MaxSize < CurIndex)
	{
		MsgBoxAssert("��ȭ �뷮�� �ʰ��߽��ϴ�.");
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
		NewRecInfo.SpriteRendererData[AllRenderer[i]].Dir = AllRenderer[i]->GetDir();
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

	if (AllRecordInfo.size() <= CurIndex)
	{
		int a = 0;
		return;
	}

	Actor->SetActorLocation(AllRecordInfo[CurIndex].Position);

	std::vector<std::shared_ptr<USpriteRenderer>> AllRenderer = Actor->GetComponentToClass<USpriteRenderer>();

	for (size_t i = 0; i < AllRenderer.size(); i++)
	{
		USpriteRendererInfo CurSpriteInfo = AllRecordInfo[CurIndex].SpriteRendererData[AllRenderer[i]];

		if (nullptr == CurSpriteInfo.SpriteInfo.Texture)
		{
			continue;
		}

		AllRenderer[i]->SetCurInfo(CurSpriteInfo.SpriteInfo);
		AllRenderer[i]->SetDir(CurSpriteInfo.Dir);
	}

	CurIndex++;

	TimeCount = Const::recording_delay;
}
