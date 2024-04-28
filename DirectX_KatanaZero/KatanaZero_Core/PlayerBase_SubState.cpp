#include "PrecomPile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"

void APlayerBase::SubStateInit()
{
	// State Create
	SubState.CreateState(PlayerSubState::none);
	SubState.CreateState(PlayerSubState::intro);
	SubState.CreateState(PlayerSubState::play);
	SubState.CreateState(PlayerSubState::replay);
	SubState.CreateState(PlayerSubState::outro);
	SubState.CreateState(PlayerSubState::restart);


	// State Start
	SubState.SetStartFunction(PlayerSubState::none,		[=] {});
	SubState.SetStartFunction(PlayerSubState::play,		std::bind(&APlayerBase::PlayStart, this));
	SubState.SetStartFunction(PlayerSubState::intro,	std::bind(&APlayerBase::IntroStart, this));
	SubState.SetStartFunction(PlayerSubState::replay,	std::bind(&APlayerBase::ReplayStart, this));
	SubState.SetStartFunction(PlayerSubState::outro,	std::bind(&APlayerBase::OutroStart, this));
	SubState.SetStartFunction(PlayerSubState::restart,	std::bind(&APlayerBase::ReStartStart, this));


	// State Update
	SubState.SetUpdateFunction(PlayerSubState::none,	[=](float _DeltaTime) {});
	SubState.SetUpdateFunction(PlayerSubState::intro,	std::bind(&APlayerBase::Intro, this, std::placeholders::_1));
	SubState.SetUpdateFunction(PlayerSubState::play,	std::bind(&APlayerBase::Play, this, std::placeholders::_1));
	SubState.SetUpdateFunction(PlayerSubState::replay,	std::bind(&APlayerBase::RePlay, this, std::placeholders::_1));
	SubState.SetUpdateFunction(PlayerSubState::outro,	std::bind(&APlayerBase::Outro, this, std::placeholders::_1));
	SubState.SetUpdateFunction(PlayerSubState::restart, std::bind(&APlayerBase::ReStart, this, std::placeholders::_1));

	// State End
	SubState.SetEndFunction(PlayerSubState::intro, [=]
		{
			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			PlayLevel->StateChange(PlayLevelState::play);
			Body->AnimationReset();
			State.ChangeState(PlayerState::idle);
			IsPlayValue = true;
			InputOn();
		}
	);
}

// 
void APlayerBase::IntroStart()
{
	SetMaxRunVel();
	Body->ChangeAnimation(Anim::player_run);
	IntroOrder = EIntroOrder::Run;
	DelayCallBack(0.5f, [=]
		{
			Velocity = FVector::Zero;
			Body->ChangeAnimation(Anim::player_run_to_idle);
			IntroOrder = EIntroOrder::RunToIdle;
		}
	);
}

void APlayerBase::Intro(float _DeltaTime)
{
	switch (IntroOrder)
	{
	case EIntroOrder::Run:
		PosUpdate(_DeltaTime);
		break;
	case EIntroOrder::RunToIdle:
		if (true == Body->IsCurAnimationEnd())
		{
			Body->ChangeAnimation(Anim::player_idle);
			State.ChangeState(PlayerState::idle);
			SubState.ChangeState(PlayerSubState::play);
			return;
		}
		break;
	case EIntroOrder::MusicOn:
		break;
	}
}

void APlayerBase::PlayStart()
{
}

void APlayerBase::Play(float _DeltaTime)
{
	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
	FloorNum = PlayLevel->FloorCheck(GetActorLocation().Y);

	// ¼öÁ¤ Debug
	{
		std::string Msg = std::format("PlayerFloor : {}\n", FloorNum);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	AttackDelayTimeUpdate(_DeltaTime);
	SetCroudEffectUpdate(_DeltaTime);
	Recording(_DeltaTime);
	DoorColCheck();

	AbilityCheck();
	AbilityUpdate(_DeltaTime);
}

void APlayerBase::ReplayStart()
{
	IsPlayValue = false;
	SetRecordingActive(false);
	SetReplayStart();
}

void APlayerBase::RePlay(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

void APlayerBase::OutroStart()
{
	SetOutroType();
	State.ChangeState(PlayerState::none);
}

void APlayerBase::Outro(float _DeltaTime)
{
	OutroUpdate(_DeltaTime);
}

void APlayerBase::ReStartStart()
{
	SetRewindStart();
	State.ChangeState(PlayerState::none);
}

void APlayerBase::ReStart(float _DeltaTime)
{
	Replaying(_DeltaTime);
}

//// Setting & Check & Update
void APlayerBase::AttackDelayTimeUpdate(float _DeltaTime)
{
	if (0.0f >= AttackDelayTimeCount)
	{
		CanAttack = true;
		return;
	}

	AttackDelayTimeCount -= _DeltaTime;
}

void APlayerBase::DoorColCheck()
{
	FrontCol->Collision(static_cast<int>(EColOrder::Door),
		[=](std::shared_ptr<UCollision> _Other) { IsColDoorValue = true; },
		nullptr,
		[=](std::shared_ptr<UCollision> _Other) { IsColDoorValue = false; }
	);
}

void APlayerBase::AbilityCheck()
{
	if (true == IsAbilityInputDown())
	{
		IsAbilityValue = true;
		float TimeScale = Const::player_ability_timescale;
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Fan, 0.05f);
		return;
	}

	if (true == IsAbilityInputUp() || false == IsAbilityValue)
	{
		IsAbilityValue = false;
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, 1.0f);
		GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, 1.0f);
		GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, 1.0f);
		GEngine->SetOrderTimeScale(EUpdateOrder::Fan, 1.0f);
		return;
	}
}


void APlayerBase::AbilityUpdate(float _DeltaTime)
{
	if (false == IsPlayValue)
	{
		return;
	}

	if (true == IsAbilityInputPress() && true == IsAbilityValue)
	{
		float TimeScale = Const::player_ability_timescale;
		AbilityTime -= _DeltaTime * (1 / TimeScale);

		if (0.0f > AbilityTime)
		{
			AbilityTime = 0.0f;
			IsAbilityValue = false;
		}

		APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
		PlayLevel->BatterPartUpdate(AbilityTime);
		return;
	}

	if (false == IsAbilityValue)
	{
		AbilityTime += _DeltaTime * 0.75f;

		if (Const::player_ability_time < AbilityTime)
		{
			AbilityTime = Const::player_ability_time;
		}

		APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
		PlayLevel->BatterPartUpdate(AbilityTime);
		return;
	}
}

void APlayerBase::SetOutroType()
{
	std::string CurMainState = State.GetCurStateName();

	if (PlayerState::run == CurMainState)
	{
		OutroType = EOutroType::Run;
		SetMaxRunVel();
		return;
	}

	if (PlayerState::idle_to_run == CurMainState)
	{
		OutroType = EOutroType::IdleToRun;
		return;
	}

	if (PlayerState::run_to_idle == CurMainState)
	{
		OutroType = EOutroType::RunToIdle;
		SetMaxRunVel();
		Body->ChangeAnimation(Anim::player_run);
		return;
	}

	if (PlayerState::jump == CurMainState)
	{
		OutroType = EOutroType::Jump;
		return;
	}

	if (PlayerState::fall == CurMainState)
	{
		OutroType = EOutroType::Fall;
		return;
	}

	if (PlayerState::roll == CurMainState)
	{
		OutroType = EOutroType::Roll;
		return;
	}

	if (PlayerState::attack == CurMainState)
	{
		OutroType = EOutroType::Attack;
		return;
	}
}

void APlayerBase::OutroUpdate(float _DeltaTime)
{
	PosUpdate(_DeltaTime);
	
	switch (OutroType)
	{
	case EOutroType::IdleToRun:
		if (true == Body->IsCurAnimationEnd())
		{
			SetMaxRunVel();
			Body->ChangeAnimation(Anim::player_run);
		}
		break;
	case EOutroType::Jump:
		if (true == IsColHeadToCeil(Body->GetDir()))
		{
			AddActorLocation({ 0.0f, -2.0f, 0.0f });
			Velocity.Y = 0.0f;
		}
		
		JumpGravityUpdate(_DeltaTime);

		if (0.0f > Velocity.Y)
		{
			Body->ChangeAnimation(Anim::player_fall);
			OutroType = EOutroType::Fall;
		}
		break;

	case EOutroType::Fall:
		FallGravityUpdate(_DeltaTime);
		break;

	case EOutroType::Roll:
		if (true == Body->IsCurAnimationEnd())
		{
			SetMaxRunVel();
			Body->ChangeAnimation(Anim::player_run);
		}
		break;

	case EOutroType::Attack:
		if (true == Body->IsCurAnimationEnd())
		{
			Body->ChangeAnimation(Anim::player_fall);
			OutroType = EOutroType::Fall;
		}
		FallGravityUpdate(_DeltaTime);
		break;
	}
}
