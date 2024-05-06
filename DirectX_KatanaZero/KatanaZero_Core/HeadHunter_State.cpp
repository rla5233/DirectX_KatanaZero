#include "PreCompile.h"
#include "HeadHunter.h"

#include "PlayLevelBase.h"
#include "MainCamera.h"

void AHeadHunter::StateInit()
{
	// State Create
	State.CreateState(HeadHunterState::none);
	State.CreateState(HeadHunterState::idle);
	State.CreateState(HeadHunterState::hitfly);

	State.CreateState(HeadHunterState::pattern_rifle1);

	// State Start
	State.SetStartFunction(HeadHunterState::none, [=] {});
	State.SetStartFunction(HeadHunterState::idle,				std::bind(&AHeadHunter::IdleStart, this));
	State.SetStartFunction(HeadHunterState::hitfly,				std::bind(&AHeadHunter::HitFlyStart, this));
	State.SetStartFunction(HeadHunterState::pattern_rifle1,		std::bind(&AHeadHunter::PatternRifle1Start, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(HeadHunterState::idle,				std::bind(&AHeadHunter::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::hitfly,			std::bind(&AHeadHunter::HitFly, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::pattern_rifle1,	std::bind(&AHeadHunter::PatternRifle1, this, std::placeholders::_1));

	// State End
	State.SetEndFunction(HeadHunterState::pattern_rifle1, [=] { Body->SetPosition(FVector::Zero); });
}

void AHeadHunter::IdleStart()
{
	Body->ChangeAnimation(Anim::headhunter_idle);
	BodyCol->SetActive(true);
}

void AHeadHunter::Idle(float _DeltaTime)
{
}

void AHeadHunter::HitFlyStart()
{
	if (0.0f < HitDir.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}

	SetVelocity(HitDir * 800.0f);
	BodyCol->SetActive(false);

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

	Body->ChangeAnimation(Anim::headhunter_hitfly);
}

void AHeadHunter::HitFly(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();

	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	if (true == IsColHeadToCeil(Dir))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}

	if (true == IsColWall(Dir) || true == IsColHeadToWall(Dir))
	{
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// State Change Check
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir)
		|| true == IsOnGP_Boundary(Dir) || true == IsOnStairs(Dir))
	{
		State.ChangeState(HeadHunterState::idle);
		return;
	}
}

void AHeadHunter::PatternRifle1Start()
{
	Body->ChangeAnimation(Anim::headhunter_takeup_rifle);

	switch (Body->GetDir())
	{
	case EEngineDir::Left:
		Body->AddPosition({ -6.0f, 0.0f, 0.0f });
		break;
	case EEngineDir::Right:
		Body->AddPosition({ 6.0f, 0.0f, 0.0f });
		break;
	}

	PatternOrder = 0;
}

void AHeadHunter::PatternRifle1(float _DeltaTime)
{
	switch (PatternOrder)
	{
	case 0:
		break;
	case 1:
		Rifle1LaserEffectUpdate1(_DeltaTime);
		break;
	case 2:
		Rifle1LaserEffectUpdate2(_DeltaTime);
		break;
	case 3:
		Rifle1LaserEffectUpdate3(_DeltaTime);
		LaserColCheck();
		break;
	default:
		break;
	}
}
