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

			AbilityUpdate(_DeltaTime);
			AbilityCheck();
		}
	);

	SubState.SetUpdateFunction("Replay", [=](float _DeltaTime)
		{
			Replaying(_DeltaTime);
		}
	);

	// State End
	SubState.SetEndFunction("Intro", [=]
		{
			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			PlayLevel->StateChange("Play");
			Body->AnimationReset();
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