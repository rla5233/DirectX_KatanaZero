#include "PreCompile.h"
#include "HeadHunterBase.h"

#include "HeadHunterLevel.h"
#include "PlayLevelBase.h"
#include "MainCamera.h"

void AHeadHunterBase::StateInit()
{
	// State Create
	State.CreateState(HeadHunterState::none);
	State.CreateState(HeadHunterState::idle);
	State.CreateState(HeadHunterState::hitfly);
	State.CreateState(HeadHunterState::recover);

	// State Start
	State.SetStartFunction(HeadHunterState::none,				[=] {});
	State.SetStartFunction(HeadHunterState::idle,				std::bind(&AHeadHunterBase::IdleStart, this));
	State.SetStartFunction(HeadHunterState::hitfly,				std::bind(&AHeadHunterBase::HitFlyStart, this));
	State.SetStartFunction(HeadHunterState::recover,			std::bind(&AHeadHunterBase::RecoverStart, this));

	// State Update
	State.SetUpdateFunction(HeadHunterState::none,				[=](float _DeltaTime) {});
	State.SetUpdateFunction(HeadHunterState::idle,				std::bind(&AHeadHunterBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::hitfly,			std::bind(&AHeadHunterBase::HitFly, this, std::placeholders::_1));
	State.SetUpdateFunction(HeadHunterState::recover,			std::bind(&AHeadHunterBase::Recover, this, std::placeholders::_1));

	// State End
	State.SetEndFunction(HeadHunterState::recover,				[=] { Body->SetPosition(FVector::Zero); });

}

void AHeadHunterBase::IdleStart()
{
	Body->ChangeAnimation(Anim::headhunter_idle);
	BodyCol->SetActive(true);
}

void AHeadHunterBase::Idle(float _DeltaTime)
{
	// 충돌 체크
	ColCheckUpdate();

	// 방향 체크
	AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
	FVector PlayerPos = PlayLevel->GetPlayerLocation();
	FVector CurPos = GetActorLocation();

	if (PlayerPos.X < CurPos.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}
}

void AHeadHunterBase::HitFlyStart()
{
	if (0.0f < HitDir.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}

	EEngineDir Dir = Body->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Body->SetPosition({ -50.0f, 0.0f ,0.0f });
		break;
	case EEngineDir::Right:
		Body->SetPosition({ 50.0f, 0.0f ,0.0f });
		break;
	}

	SetVelocity(HitDir * 800.0f);
	BodyCol->SetActive(false);

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	PlayLevel->GetKZMainCamera()->StateChange(MainCameraState::ret_shaking);

	LaserEffect->SetActive(false);
	Body->ChangeAnimation(Anim::headhunter_hitfly);
}

void AHeadHunterBase::HitFly(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();

	// 속도 업데이트
	ApplyGravity(_DeltaTime);

	if (true == IsColHeadToCeil(Dir))
	{
		Velocity.Y = 0.0f;
		AddActorLocation({ 0.0f, -10.0f, 0.0f });
	}

	if (true == IsColWall(Dir) 
		|| true == IsColHeadToWall(Dir) 
		|| true == IsColBackToWall(Dir))
	{

		bool a = IsColBackToWall(Dir);
		Velocity.X = 0.0f;
	}

	// 위치 업데이트
	PosUpdate(_DeltaTime);

	// 충돌 체크
	ColCheckUpdate();

	// State Change Check
	if (true == IsOnGround(Dir))
	{
		State.ChangeState(HeadHunterState::recover);
		return;
	}
}

void AHeadHunterBase::RecoverStart()
{
	DelayCallBack(1.0f, [=] 
		{
			Body->ChangeAnimation(Anim::headhunter_recover);
			SetRecoverEffect();
		}
	);
}

void AHeadHunterBase::Recover(float _DletaTime)
{
}