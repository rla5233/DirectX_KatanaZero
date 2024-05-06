#include "PreCompile.h"
#include "HeadHunterPhase1.h"

#include "HeadHunterLevel.h"
#include "MainCamera.h"

void AHeadHunterPhase1::CreateRollCroudEffect(float _DeltaTime)
{
	if (0.0f < CroudTimeCount)
	{
		CroudTimeCount -= _DeltaTime;
		return;
	}

	if (true == Cloud[CloudIdx].Renderer->IsActive())
	{
		return;
	}

	Cloud[CloudIdx].Renderer->AnimationReset();
	Cloud[CloudIdx].Renderer->ChangeAnimation(Anim::effect_player_dustcloud);
	Cloud[CloudIdx].Renderer->SetAutoSize(2.0f, true);
	Cloud[CloudIdx].Renderer->SetActive(true);

	float Deg = UEngineRandom::MainRandom.RandomFloat(5.0f, 35.0f);
	Deg *= UEngineMath::DToR;
	FVector VelDir = { cosf(Deg), sinf(Deg), 0.0f };

	float Speed = UEngineRandom::MainRandom.RandomFloat(100.0f, 250.0f);

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(20.0f, 5.0f, 0.0f));
		break;
	case EEngineDir::Right:
		Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(-20.0f, 5.0f, 0.0f));
		VelDir.X *= -1;
		break;
	}

	Cloud[CloudIdx].Velocity = VelDir * Speed;

	++CloudIdx;
	if (CloudSize <= CloudIdx)
	{
		CloudIdx = 0;
	}

	CroudTimeCount = Const::effect_roll_cloud_delay;
}

void AHeadHunterPhase1::CroudEffectUpdate(float _DeltaTime)
{
	for (size_t i = 0; i < Cloud.size(); i++)
	{
		if (false == Cloud[i].Renderer->IsActive())
		{
			continue;
		}

		Cloud[i].Renderer->AddPosition(Cloud[i].Velocity * _DeltaTime);
	}
}

void AHeadHunterPhase1::SetRifle1LaserEffect()
{
	LaserEffect->SetSprite(ImgRes::compo_bullet);
	LaserEffect->SetScale({ 0.0f, 2.0f, 1.0f });

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		LaserEffect->SetPosition({ -41.0f, 56.0f ,0.0f });
		break;
	case EEngineDir::Right:
		LaserEffect->SetPosition({ 41.0f, 56.0f ,0.0f });
		break;
	}

	LaserEffect->SetActive(true);
	PatternOrder = 1;

	DelayCallBack(0.5f, [=] { PatternOrder = 2; });
}

void AHeadHunterPhase1::Rifle1LaserEffectUpdate1(float _DeltaTime)
{
	FVector CurScale = LaserEffect->GetLocalScale();
	if (1280.0f < CurScale.X)
	{
		return;
	}

	float AddScaleX = 5000.0f * _DeltaTime;
	LaserEffect->AddScale({ AddScaleX, 0.0f, 0.0f });
	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		LaserEffect->AddPosition({ -AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	case EEngineDir::Right:
		LaserEffect->AddPosition({ AddScaleX * 0.5f, 0.0f ,0.0f });
		break;
	}
}

void AHeadHunterPhase1::Rifle1LaserEffectUpdate2(float _DeltaTime)
{
	LaserAlpha -= 9.0f * _DeltaTime;

	if (0.0f > LaserAlpha)
	{
		LaserAlpha = 0.0f;
		PatternOrder = -1;
		LaserEffect->SetActive(false);
		DelayCallBack(0.04f, [=]
			{
				LaserAlpha = 1.0f;
				LaserEffect->SetActive(true);
				LaserEffect->ChangeAnimation(Anim::effect_laser);
				LaserEffect->AddScale({ 0.0f, 14.0f, 0.0f });
				LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
				switch (Body->GetDir())
				{
				case EEngineDir::Left:
					LaserEffect->SetRotationDeg({ 0.0f, 180.0f, 0.0f });
					break;
				case EEngineDir::Right:
					LaserEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
					break;
				}

				LaserCol->SetActive(true);

				AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
				PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

				DelayCallBack(0.1f, [=]
					{
						PatternOrder = 3;
					}
				);
			}
		);
	}

	LaserEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, LaserAlpha });
}

void AHeadHunterPhase1::Rifle1LaserEffectUpdate3(float _DeltaTime)
{
	if (false == LaserEffect->IsActive())
	{
		return;
	}

	float AddScaleY = -100.0f * _DeltaTime;
	LaserEffect->AddScale({ 0.0f, AddScaleY, 0.0f });

	FVector CurScale = LaserEffect->GetLocalScale();
	if (0.0f > CurScale.Y)
	{
		LaserCol->SetActive(false);
		LaserEffect->SetActive(false);

		// 3회 발사후 돌아가기
		if (0 == Pattern1Count)
		{
			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
			PatternOrder = -1;
			return;
		}

		AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
		FVector PlayerPos = PlayLevel->GetPlayerLocation();
		FVector CurPos = GetActorLocation();
		if (350.0f < abs(CurPos.X - PlayerPos.X))
		{
			DelayCallBack(0.06f, [=] { PatternOrder = 0; });
		}
		else
		{
			// 패턴 추가
			Body->ChangeAnimation(Anim::headhunter_putback_rifle);
			PatternOrder = -1;
			return;
		}
	}
}