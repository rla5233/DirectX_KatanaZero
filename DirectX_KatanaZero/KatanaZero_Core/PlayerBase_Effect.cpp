#include "PreCompile.h"
#include "PlayerBase.h"

void APlayerBase::EffectInit()
{
	AttackEffect->CreateAnimation(Anim::effect_player_slash, ImgRes::effect_player_slash, 0.04f, false);
	AttackEffect->SetFrameCallback(Anim::effect_player_slash, 4, [=] { AttackEffect->SetActive(false); });

	for (size_t i = 0; i < Cloud.size(); i++)
	{
		Cloud[i].Renderer->CreateAnimation(
			Anim::effect_player_dustcloud,
			ImgRes::effect_player_dustcloud,
			{ 0.08f, 0.08f, 0.08f, 0.08f, 0.06f, 0.06f, 0.06f },
			{ 0, 1, 2, 3, 4, 5, 6 },
			false);
		Cloud[i].Renderer->SetFrameCallback(Anim::effect_player_dustcloud, 6, [=] { Cloud[i].Renderer->SetActive(false); });

		Cloud[i].Renderer->SetOrder(ERenderOrder::Effect);
		Cloud[i].Renderer->SetActive(false);
	}

	AttackEffect->SetOrder(ERenderOrder::Effect);
	AttackEffect->SetActive(false);
}

void APlayerBase::EffectVecIdxUpdate()
{
	++CloudIdx;

	if (CloudSize <= CloudIdx)
	{
		CloudIdx = 0;
	}
}

void APlayerBase::SetAttackEffect(float _Deg)
{
	AttackEffect->ChangeAnimation(Anim::effect_player_slash);
	AttackEffect->SetAutoSize(2.0f, true);
	AttackEffect->SetPosition({ 0.0f, 30.0f, 0.0f });
	AttackEffect->SetRotationDeg({ 0.0f, 0.0f, _Deg });
	AttackEffect->SetActive(true);
}

void APlayerBase::SetCroudEffect(int _Num)
{
	EEngineDir Dir = Renderer->GetDir();

	for (int i = 0; i < _Num; i++)
	{
		if (true == Cloud[CloudIdx].Renderer->IsActive())
		{
			continue;
		}

		Cloud[CloudIdx].Renderer->ChangeAnimation(Anim::effect_player_dustcloud);
		Cloud[CloudIdx].Renderer->SetAutoSize(2.0f, true);
		Cloud[CloudIdx].Renderer->SetActive(true);
		
		float Deg = UEngineRandom::MainRandom.RandomFloat(5.0f, 35.0f);
		Deg *= UEngineMath::DToR;
		FVector VelDir = { cosf(Deg), sinf(Deg), 0.0f };

		float Speed = UEngineRandom::MainRandom.RandomFloat(100.0f, 250.0f);

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

		EffectVecIdxUpdate();
	}
}

void APlayerBase::SetCroudEffectUpdate(float _DeltaTime)
{
	if (false == IsPlayValue)
	{
		return;
	}

	for (size_t i = 0; i < Cloud.size(); i++)
	{
		if (false == Cloud[i].Renderer->IsActive())
		{
			continue;
		}

		Cloud[i].Renderer->AddPosition(Cloud[i].Velocity * _DeltaTime);
	}
}

void APlayerBase::CreateRollCroudEffect(float _DeltaTime)
{
	if (0.0f < CroudTimeCount)
	{
		CroudTimeCount -= _DeltaTime;
		return;
	}

	SetCroudEffect(1);
	CroudTimeCount = Const::effect_cloud_delay;
}