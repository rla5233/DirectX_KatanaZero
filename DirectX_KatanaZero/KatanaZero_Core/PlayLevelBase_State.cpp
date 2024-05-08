#include "PreCompile.h"
#include "PlayLevelBase.h"

#include "DefaultPlayer.h"
#include "EnemyBase.h"
#include "MouseAim.h"
#include "ReplayUI.h"
#include "OutroMsg.h"
#include "Up_HUD.h"
#include "Door.h"
#include "Go.h"

#include "FailedMsg.h"

#include "GrayScaleEffect.h"
#include "WaveEffect.h"
#include "DiamondTransition.h"

void APlayLevelBase::StateInit()
{
	// State 생성
	State.CreateState(PlayLevelState::intro);
	State.CreateState(PlayLevelState::intro_effect);
	State.CreateState(PlayLevelState::intro_big_effect);
	State.CreateState(PlayLevelState::play);
	State.CreateState(PlayLevelState::clear);
	State.CreateState(PlayLevelState::outro);
	State.CreateState(PlayLevelState::replay);
	State.CreateState(PlayLevelState::player_dead);
	State.CreateState(PlayLevelState::restart);
	State.CreateState(PlayLevelState::transition_on);
	State.CreateState(PlayLevelState::transition_off);

	// State Start 함수 세팅
	State.SetStartFunction(PlayLevelState::intro,				std::bind(&APlayLevelBase::IntroStart, this));
	State.SetStartFunction(PlayLevelState::intro_effect,		std::bind(&APlayLevelBase::IntroEffectStart, this));
	State.SetStartFunction(PlayLevelState::intro_big_effect,	std::bind(&APlayLevelBase::IntroBigEffectStart, this));
	State.SetStartFunction(PlayLevelState::play,				std::bind(&APlayLevelBase::PlayStart, this));
	State.SetStartFunction(PlayLevelState::clear,				std::bind(&APlayLevelBase::ClearStart, this));
	State.SetStartFunction(PlayLevelState::outro,				std::bind(&APlayLevelBase::OutroStart, this));
	State.SetStartFunction(PlayLevelState::replay,				std::bind(&APlayLevelBase::ReplayStart, this));
	State.SetStartFunction(PlayLevelState::player_dead,			std::bind(&APlayLevelBase::PlayerDeadStart, this));
	State.SetStartFunction(PlayLevelState::restart,				std::bind(&APlayLevelBase::RestartStart, this));
	State.SetStartFunction(PlayLevelState::transition_on,		std::bind(&APlayLevelBase::TransitionOnStart, this));
	State.SetStartFunction(PlayLevelState::transition_off,		std::bind(&APlayLevelBase::TransitionOffStart, this));


	// State Update 함수 세팅
	State.SetUpdateFunction(PlayLevelState::intro,				std::bind(&APlayLevelBase::Intro, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::intro_effect,		std::bind(&APlayLevelBase::IntroEffect, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::intro_big_effect,	std::bind(&APlayLevelBase::IntroBigEffect, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::play,				std::bind(&APlayLevelBase::Play, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::clear,				std::bind(&APlayLevelBase::Clear, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::outro,				std::bind(&APlayLevelBase::Outro, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::replay,				std::bind(&APlayLevelBase::Replay, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::player_dead,		std::bind(&APlayLevelBase::PlayerDead, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::restart,			std::bind(&APlayLevelBase::Restart, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::transition_on,		std::bind(&APlayLevelBase::TransitionOn, this, std::placeholders::_1));
	State.SetUpdateFunction(PlayLevelState::transition_off,		std::bind(&APlayLevelBase::TransitionOff, this, std::placeholders::_1));

	// State End 함수 세팅
}

void APlayLevelBase::IntroStart()
{
}

void APlayLevelBase::Intro(float _DeltaTime)
{
}

void APlayLevelBase::IntroEffectStart()
{
	WaveEffect->SetEffectType(EWaveEffectType::Intro);
	WaveEffect->Active(true);

	DelayCallBack(0.2f, [=]
		{
			WaveEffect->ResetTime();
			WaveEffect->Active(false);

			Player->SubStateChange(PlayerSubState::play);
			Player->SetIsPlayValue(true);
			Player->InputOn();

			State.ChangeState(PlayLevelState::play);
		}
	);
}

void APlayLevelBase::IntroEffect(float _DeltaTime)
{
	WaveEffect->Update(_DeltaTime);
}

void APlayLevelBase::IntroBigEffectStart()
{
	WaveEffect->SetEffectType(EWaveEffectType::IntroBig);
	WaveEffect->Active(true);

	DelayCallBack(0.5f, [=]
		{
			WaveEffect->ResetTime();
			WaveEffect->Active(false);

			Player->SubStateChange(PlayerSubState::play);
			Player->SetIsPlayValue(true);
			Player->InputOn();

			State.ChangeState(PlayLevelState::play);
		}
	);
}

void APlayLevelBase::IntroBigEffect(float _DeltaTime)
{
	WaveEffect->Update(_DeltaTime);
}

void APlayLevelBase::PlayStart()
{
	if (nullptr == HUD)
	{
		HUD = GetWorld()->SpawnActor<AUp_HUD>("Up_HUD");
	}

	HUD->Reset();
	HUD->On();
	Player->SetRecordingActive(true);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetRecordingActive(true);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetRecordingActive(true);
	}

	Aim->StateChange(MouseAimState::play);

	PlayTimeCount = TotalPlayTime;
}

void APlayLevelBase::Play(float _DeltaTime)
{
	if (0.0f > PlayTimeCount)
	{
		Player->HitByEnemy(FVector::Zero, EEnemyType::TimeOut);
		return;
	}

	if (true == IsStageClear())
	{
		State.ChangeState(PlayLevelState::clear);
		return;
	}

	if (UEngineInput::IsDown('R'))
	{
		State.ChangeState(PlayLevelState::restart);
		return;
	}

	PlayTimeCount -= _DeltaTime;
}

void APlayLevelBase::ClearStart()
{
	if (nullptr == Go)
	{
		Go = GetWorld()->SpawnActor<AGo>("Go");
	}

	Go->On();
}

void APlayLevelBase::Clear(float _DeltaTime)
{
	if (0.0f > PlayTimeCount)
	{
		Player->HitByEnemy(FVector::Zero, EEnemyType::TimeOut);
		return;
	}

	if (true == IsRelayStart())
	{
		State.ChangeState(PlayLevelState::outro);
		return;
	}

	if (UEngineInput::IsDown('R'))
	{
		State.ChangeState(PlayLevelState::restart);
		return;
	}

	PlayTimeCount -= _DeltaTime;
}

void APlayLevelBase::OutroStart()
{
	Player->SubStateChange(PlayerSubState::outro);
	HUD->StateChange(HudState::outro);
	Go->StateChange(GoState::outro);

	OutroMsg->On();
	OutroMsg->StateChange(OutroMsgState::fade_in);
	UContentsHelper::ResetTimeScale();
}

void APlayLevelBase::Outro(float _DeltaTime)
{
}

void APlayLevelBase::ReplayStart()
{
	Player->SubStateChange(PlayerSubState::replay);
	Aim->StateChange(MouseAimState::replay);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->StateChange(EnemyState::replay);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->StateChange(RecCompoState::replay);
	}

	ReplayUI->On();	
	ReplayUI->StateChange(ReplayUIState::play);

	GrayScaleEffect->Active(true);
	InputOn();
}

void APlayLevelBase::Replay(float _DeltaTime)
{
	if (true == IsDown(VK_RBUTTON))
	{
		InputOff();
		State.ChangeState(PlayLevelState::transition_on);
		return;
	}
}

void APlayLevelBase::PlayerDeadStart()
{
	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetRecordingActive(false);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetRecordingActive(false);
	}

	EEnemyType EnemyType = Player->GetHitEnemyType();
	switch (EnemyType)
	{
	case EEnemyType::TimeOut:
		break;
	default:
		FailedMsg->StateChange(FailedMsgState::hit_end);
		break;
	}
}

void APlayLevelBase::PlayerDead(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_LBUTTON))
	{
		FailedMsg->Off();
		State.ChangeState(PlayLevelState::restart);
		return;
	}
}

void APlayLevelBase::RestartStart()
{
	if (nullptr != HUD)
	{
		HUD->Off();
	}

	if (nullptr != Go)
	{
		Go->Off();
	}

	Player->SubStateChange(PlayerSubState::restart);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->StateChange(EnemyState::restart);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->StateChange(RecCompoState::restart);
	}

	WaveEffect->SetEffectType(EWaveEffectType::Restart);
	WaveEffect->Active(true);

	UEngineSound::SoundPlay(SoundRes::stage_restart).SetVolume(0.75f);
}

void APlayLevelBase::Restart(float _DeltaTime)
{
	BrightnessUp(_DeltaTime);
	WaveEffect->Update(_DeltaTime);

	if (Player->IsRewindEnd())
	{
		LevelReEnd();
		LevelReStart();

		WaveEffect->Active(false);
		WaveEffect->ResetTime();

		UEngineSound::SoundPlay(SoundRes::stage_restartend).SetVolume(0.75f);
		State.ChangeState(PlayLevelState::intro_effect);
		return;
	}
}

void APlayLevelBase::TransitionOnStart()
{
	Player->SetReplayMode(EReplayMode::Stop);

	for (size_t i = 0; i < AllEnemy.size(); i++)
	{
		AllEnemy[i]->SetReplayMode(EReplayMode::Stop);
	}

	for (size_t i = 0; i < AllRecComponent.size(); i++)
	{
		AllRecComponent[i]->SetReplayMode(EReplayMode::Stop);
	}

	ReplayUI->Off();

	DiaTransition->StateChange(DiaTransitionState::on);
}

void APlayLevelBase::TransitionOn(float _DeltaTime)
{
	if (true == DiaTransition->IsTransitionEnd())
	{
		ChangeStage();
		return;
	}
}

void APlayLevelBase::TransitionOffStart()
{
	DiaTransition->StateChange(DiaTransitionState::off);
}

void APlayLevelBase::TransitionOff(float _DeltaTime)
{
	if (true == DiaTransition->IsTransitionEnd())
	{
		Player->StateChange(PlayerState::none);
		Player->SubStateChange(PlayerSubState::intro);

		State.ChangeState(PlayLevelState::intro);
		return;
	}
}