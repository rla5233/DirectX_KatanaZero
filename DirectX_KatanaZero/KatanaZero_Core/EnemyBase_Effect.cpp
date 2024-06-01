#include "PreCompile.h"
#include "EnemyBase.h"

void AEnemyBase::EffectInit()
{
	for (size_t i = 0; i < Blood.size(); i++)
	{
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter1, ImgRes::effect_blood_splatter1, 0.06f, true);
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter2, ImgRes::effect_blood_splatter2, 0.06f, true);
		Blood[i].Renderer->CreateAnimation(Anim::effect_blood_splatter3, ImgRes::effect_blood_splatter3, 0.06f, true);
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter1, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter2, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetLastFrameCallback(Anim::effect_blood_splatter3, [=] { Blood[i].Renderer->SetActive(false); });
		Blood[i].Renderer->SetOrder(ERenderOrder::EffectBack);
		Blood[i].Renderer->SetAutoSize(2.5f, true);
		Blood[i].Renderer->SetActive(false);
	}
}

void AEnemyBase::BloodVecIdxUpdate()
{
	++BloodIdx;

	if (BloodSize <= BloodIdx)
	{
		BloodIdx = 0;
	}
}

void AEnemyBase::CreateBloodEffect(float _DeltaTime)
{
	if (0.0f < BloodTimeCount || true == Blood[BloodIdx].Renderer->IsActive())
	{
		BloodTimeCount -= _DeltaTime;
		return;
	}

	Blood[BloodIdx].Renderer->AnimationReset();
	Blood[BloodIdx].Renderer->SetActive(true);

	int RandomValue = UEngineRandom::MainRandom.RandomInt(1, 3);
	switch (RandomValue)
	{
	case 1:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter1);
		break;
	case 2:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter2);
		break;
	case 3:
		Blood[BloodIdx].Renderer->ChangeAnimation(Anim::effect_blood_splatter3);
		break;
	}

	FVector VelDir = -UPhysicsObject::Velocity.Normalize2DReturn();
	float Deg = UContentsMath::GetAngleToAxisX2D(VelDir);
	Deg += UEngineRandom::MainRandom.RandomFloat(-35.0f, 35.0f);
	Blood[BloodIdx].Renderer->SetRotationDeg({ 0.0f, 0.0f, Deg });

	float Rad = Deg * UEngineMath::DToR;
	VelDir = { cosf(Rad), sinf(Rad), 0.0f };
	Blood[BloodIdx].UBloodEffect::Velocity = VelDir * 150.0f;
	Blood[BloodIdx].Renderer->SetPosition(GetActorLocation() + FVector(0.0f, 50.0f, 0.0f));
	Blood[BloodIdx].Renderer->AddPosition(VelDir * 40.0f);

	BloodVecIdxUpdate();
	BloodTimeCount = Const::effect_blood_splatter_delay;
}

void AEnemyBase::BloodEffectUpdate(float _DeltaTime)
{
	for (size_t i = 0; i < Blood.size(); i++)
	{
		if (false == Blood[i].Renderer->IsActive())
		{
			continue;
		}

		Blood[i].Renderer->AddPosition(Blood[i].Velocity * _DeltaTime);
	}
}