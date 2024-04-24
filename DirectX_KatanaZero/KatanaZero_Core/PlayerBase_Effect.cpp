#include "PreCompile.h"
#include "PlayerBase.h"

void APlayerBase::EffectInit()
{
	AttackEffect->CreateAnimation(Anim::effect_player_slash, ImgRes::effect_player_slash, 0.04f, false);
	AttackEffect->SetFrameCallback(Anim::effect_player_slash, 4, [=] { AttackEffect->SetActive(false); });
	AttackEffect->SetOrder(ERenderOrder::EffectFront);
	AttackEffect->SetActive(false);

	JumpLandEffect->CreateAnimation(Anim::effect_player_jumpcloud, ImgRes::effect_player_jumpcloud, 0.08f, false);
	JumpLandEffect->CreateAnimation(Anim::effect_player_landcloud, ImgRes::effect_player_landcloud, 0.06f, false);
	JumpLandEffect->SetFrameCallback(Anim::effect_player_jumpcloud, 3, [=] { JumpLandEffect->SetActive(false); });
	JumpLandEffect->SetFrameCallback(Anim::effect_player_landcloud, 6, [=] { JumpLandEffect->SetActive(false); });
	JumpLandEffect->SetOrder(ERenderOrder::EffectBack);
	JumpLandEffect->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });
	JumpLandEffect->SetAutoSize(2.0f, true);
	JumpLandEffect->SetActive(false);

	for (size_t i = 0; i < Cloud.size(); i++)
	{
		Cloud[i].Renderer->CreateAnimation(
			Anim::effect_player_dustcloud,
			ImgRes::effect_player_dustcloud,
			{ 0.08f, 0.08f, 0.08f, 0.08f, 0.06f, 0.06f, 0.06f },
			{ 0, 1, 2, 3, 4, 5, 6 },
			false);
		Cloud[i].Renderer->SetFrameCallback(Anim::effect_player_dustcloud, 6, [=] { Cloud[i].Renderer->SetActive(false); });
		Cloud[i].Renderer->SetOrder(ERenderOrder::EffectBack);
		Cloud[i].Renderer->SetActive(false);
	}
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
	AttackEffect->AnimationReset();
	AttackEffect->ChangeAnimation(Anim::effect_player_slash);
	AttackEffect->SetAutoSize(2.0f, true);
	AttackEffect->SetPosition({ 0.0f, 30.0f, 0.0f });
	AttackEffect->SetRotationDeg({ 0.0f, 0.0f, _Deg });
	AttackEffect->SetActive(true);
}

void APlayerBase::SetJumpEffect()
{
	JumpLandEffect->AnimationReset();
	JumpLandEffect->ChangeAnimation(Anim::effect_player_jumpcloud);
	JumpLandEffect->SetPosition(GetActorLocation() + FVector(0.0f, 52.0f, 0.0f));
	JumpLandEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
	JumpLandEffect->SetActive(true);
}

void APlayerBase::SetLandEffect()
{
	JumpLandEffect->AnimationReset();
	JumpLandEffect->ChangeAnimation(Anim::effect_player_landcloud);
	JumpLandEffect->SetPosition(GetActorLocation() + FVector(0.0f, 15.0f, 0.0f));
	JumpLandEffect->SetRotationDeg({ 0.0f, 0.0f, 0.0f });
	JumpLandEffect->SetActive(true);
}

void APlayerBase::SetWallJumpEffet()
{
	JumpLandEffect->AnimationReset();
	JumpLandEffect->ChangeAnimation(Anim::effect_player_jumpcloud);
	JumpLandEffect->SetActive(true);
}

void APlayerBase::SetCroudEffect(int _Num)
{
	EEngineDir Dir = Body->GetDir();

	for (int i = 0; i < _Num; i++)
	{
		if (true == Cloud[CloudIdx].Renderer->IsActive())
		{
			continue;
		}

		Cloud[CloudIdx].Renderer->AnimationReset();
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

void APlayerBase::SetWallSlideCroudEffect(int _Num)
{
	EEngineDir Dir = Body->GetDir();

	for (int i = 0; i < _Num; i++)
	{
		if (true == Cloud[CloudIdx].Renderer->IsActive())
		{
			continue;
		}

		Cloud[CloudIdx].Renderer->AnimationReset();
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
			Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(-25.0f, 0.0f, 0.0f));
			break;
		case EEngineDir::Right:
			Cloud[CloudIdx].Renderer->SetPosition(GetActorLocation() + FVector(25.0f, 0.0f, 0.0f));
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
	CroudTimeCount = Const::effect_roll_cloud_delay;
}

void APlayerBase::CreateWallSlideCroudEffect(float _DeltaTime)
{
	if (0.0f < CroudTimeCount)
	{
		CroudTimeCount -= _DeltaTime;
		return;
	}

	SetWallSlideCroudEffect(1);

	CroudTimeCount = Const::effect_wallslide_cloud_delay;
}