#include "PreCompile.h"
#include "EnemyBase.h"

#include "PlayLevelBase.h"
#include "UpMark.h"

void AEnemyBase::StateInit()
{
	// State 생성
	State.CreateState(EnemyState::idle);
	State.CreateState(EnemyState::run);
	State.CreateState(EnemyState::hitfall);
	State.CreateState(EnemyState::dead);
	State.CreateState(EnemyState::patrol_walk);
	State.CreateState(EnemyState::patrol_turn);
	State.CreateState(EnemyState::patrol_stop);
	State.CreateState(EnemyState::chase);

	State.CreateState(EnemyState::replay);
	State.CreateState(EnemyState::restart);

	// etc.
	State.CreateState(EnemyState::turn);

	// State Start 함수 세팅
	State.SetStartFunction(EnemyState::idle,			std::bind(&AEnemyBase::IdleStart, this));
	State.SetStartFunction(EnemyState::run,				std::bind(&AEnemyBase::RunStart, this));
	State.SetStartFunction(EnemyState::hitfall,			std::bind(&AEnemyBase::HitFallStart, this));
	State.SetStartFunction(EnemyState::dead,			std::bind(&AEnemyBase::DeadStart, this));
	State.SetStartFunction(EnemyState::patrol_walk,		std::bind(&AEnemyBase::PatrolWalkStart, this));
	State.SetStartFunction(EnemyState::patrol_turn,		std::bind(&AEnemyBase::PatrolTurnStart, this));
	State.SetStartFunction(EnemyState::patrol_stop,		std::bind(&AEnemyBase::PatrolStopStart, this));
	State.SetStartFunction(EnemyState::chase,			std::bind(&AEnemyBase::ChaseStart, this));

	// Sub
	State.SetStartFunction(EnemyState::replay, [=]
		{
			SetRecordingActive(false);
			SetReplayStart();
		}
	);

	State.SetStartFunction(EnemyState::restart, [=]
		{
			SetRewindStart();
		}
	);

	State.SetStartFunction(EnemyState::turn,			std::bind(&AEnemyBase::TurnStart, this));

	// State Update 함수 세팅
	State.SetUpdateFunction(EnemyState::idle,			std::bind(&AEnemyBase::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::run,			std::bind(&AEnemyBase::Run, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::hitfall,		std::bind(&AEnemyBase::HitFall, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::dead,			std::bind(&AEnemyBase::Dead, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_walk,	std::bind(&AEnemyBase::PatrolWalk, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_turn,	std::bind(&AEnemyBase::PatrolTurn, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::patrol_stop,	std::bind(&AEnemyBase::PatrolStop, this, std::placeholders::_1));
	State.SetUpdateFunction(EnemyState::chase,			std::bind(&AEnemyBase::Chase, this, std::placeholders::_1));

	State.SetUpdateFunction(EnemyState::replay, [=](float _DeltaTime) 
		{ 
			Replaying(_DeltaTime); 
		}
	);

	State.SetUpdateFunction(EnemyState::restart, [=](float _DeltaTime) 
		{ 
			Replaying(_DeltaTime); 
		}
	);


	State.SetUpdateFunction(EnemyState::turn,			std::bind(&AEnemyBase::Turn, this, std::placeholders::_1));

	// State End 함수 세팅
	State.SetEndFunction(EnemyState::patrol_turn,		std::bind(&AEnemyBase::PatrolTurnEnd, this));

	State.SetEndFunction(EnemyState::turn, [=] { DirChange(); });
}

void AEnemyBase::Idle(float _DeltaTime)
{
	Recording(_DeltaTime);
}

void AEnemyBase::Run(float _DeltaTime)
{
	Recording(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);
}

void AEnemyBase::HitFallStart()
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	PlayLevel->EnemyDeadUpdate();

	if (0.0f > HitDir.X)
	{
		Body->SetDir(EEngineDir::Left);
	}
	else
	{
		Body->SetDir(EEngineDir::Right);
	}

	SetVelocity(HitDir * 1000.0f);
	BodyCol->SetActive(false);

	DeadCol->SetPosition(BodyCol->GetLocalPosition());
	DeadCol->SetScale(BodyCol->GetLocalScale());
	DeadCol->SetActive(true);
}

void AEnemyBase::HitFall(float _DeltaTime)
{
	EEngineDir Dir = Body->GetDir();
	Recording(_DeltaTime);

	// 충돌 체크
	DeadCol->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other) {	Velocity.X *= -1.0f; });

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

	// Effect
	CreateBloodEffect(_DeltaTime);
	BloodEffectUpdate(_DeltaTime);

	// State Change Check
	if (true == IsOnGround(Dir) || true == IsOnPlatForm(Dir)
		|| true == IsOnGP_Boundary(Dir) || true == IsOnStairs(Dir))
	{
		State.ChangeState(EnemyState::dead);
		return;
	}
}

void AEnemyBase::DeadStart()
{
	DeadCol->SetActive(false);
}

void AEnemyBase::Dead(float _DeltaTime)
{
	Recording(_DeltaTime);
	BloodEffectUpdate(_DeltaTime);
}

void AEnemyBase::PatrolWalkStart()
{
	DelayCallBack(PatrolWalkTime, [=] 
		{ 
			std::string CurState = State.GetCurStateName();
			if (EnemyState::patrol_walk == CurState)
			{
				State.ChangeState(EnemyState::patrol_turn);
			}			
		}
	);
}

void AEnemyBase::PatrolWalk(float _DeltaTime)
{
	Recording(_DeltaTime);

	// 위치 업데이트
	PosUpdate(_DeltaTime);
}

void AEnemyBase::PatrolTurnStart()
{
	SetVelocityByDir(FVector::Zero);
}

void AEnemyBase::PatrolTurn(float _DeltaTime)
{
	Recording(_DeltaTime);

	// State Change Check
	if (true == Body->IsCurAnimationEnd())
	{
		State.ChangeState(EnemyState::patrol_stop);
		return;
	}
}

void AEnemyBase::PatrolTurnEnd()
{
	DirChange();
}

void AEnemyBase::PatrolStopStart()
{
	SetVelocityByDir(FVector::Zero);
	DelayCallBack(PatrolStopTime, [=] 
		{ 
			std::string CurState = State.GetCurStateName();
			if (EnemyState::patrol_stop == CurState)
			{
				State.ChangeState(EnemyState::patrol_walk);
			}			
		}
	);
}

void AEnemyBase::PatrolStop(float _DeltaTime)
{
	Recording(_DeltaTime);
}


void AEnemyBase::Turn(float _DeltaTime)
{
	Recording(_DeltaTime);

	if (Body->IsCurAnimationEnd())
	{
		State.ChangeState(EnemyState::idle);
		return;
	}
}

void AEnemyBase::ChaseStart()
{
	ChaseMark = GetWorld()->SpawnActor<AUpMark>("ChaseMark");
	 
}

void AEnemyBase::Chase(float _DeltaTime)
{
	ChaseMark->SetActorLocation(GetActorLocation() + FVector(0.0f, 100.0f, 0.0f));
}

void AEnemyBase::TurnStart()
{
	SetVelocityByDir({ 0.0f, 0.0f, 0.0f });
}



