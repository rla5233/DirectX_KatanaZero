#include "PrecomPile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"

void APlayerBase::SubStateInit()
{
	// State Create
	SubState.CreateState("None");
	SubState.CreateState("Intro");
	SubState.CreateState("Play");
	SubState.CreateState("Replay");

	SubState.CreateState("RunOutro");


	// State Start
	SubState.SetStartFunction("None", [=] {});
	SubState.SetStartFunction("Play", [=] {});
	SubState.SetStartFunction("Intro", [=]
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
	);

	SubState.SetStartFunction("Replay", [=]
		{
			IsPlayValue = false;
			SetRecordingActive(false);
			SetReplayStart();
			State.ChangeState("None");
		}
	);

	SubState.SetStartFunction("RunOutro", [=] { State.ChangeState("None"); });

	// State Update
	SubState.SetUpdateFunction("None", [=](float _DeltaTime) {});
	SubState.SetUpdateFunction("Intro", [=](float _DeltaTime)
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
					State.ChangeState("Idle");
					SubState.ChangeState("Play");
					return;
				}
				break;
			case EIntroOrder::MusicOn:
				break;
			}
		}
	);

	SubState.SetUpdateFunction("Play", [=](float _DeltaTime) 
		{
			AttackDelayTimeUpdate(_DeltaTime);
			SetCroudEffectUpdate(_DeltaTime);
			Recording(_DeltaTime);
			DoorColCheck();

			AbilityCheck();
			AbilityUpdate(_DeltaTime);
		}
	);

	SubState.SetUpdateFunction("Replay", [=](float _DeltaTime)
		{
			Replaying(_DeltaTime);
		}
	);

	SubState.SetUpdateFunction("RunOutro", [=](float _DeltaTime)
		{

		}
	);

	// State End
	SubState.SetEndFunction("Intro", [=]
		{
			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			PlayLevel->StateChange("Play");
			Body->AnimationReset();
			State.ChangeState(PlayerState::idle);
			IsPlayValue = true;
			InputOn();
		}
	);

}

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
		return;
	}

	if (true == IsAbilityInputUp() || false == IsAbilityValue)
	{
		IsAbilityValue = false;
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, 1);
		GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, 1);
		GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, 1);
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