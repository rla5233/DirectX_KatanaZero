#include "PreCompile.h"
#include "DefaultPlayer.h"

#include "PlayLevelBase.h"
#include "HeadHunterLevel_Phase1.h"
#include "Door.h"

ADefaultPlayer::ADefaultPlayer()
{
}

ADefaultPlayer::~ADefaultPlayer()
{
}

void ADefaultPlayer::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
	SoundSetting();
	SetAfterImagePlusColor(Const::player_afterimage_color);
	StateChange(PlayerState::none);
	SubStateChange(PlayerSubState::none);
}

void ADefaultPlayer::CollisionInit()
{
	Super::CollisionInit();

	FVector BodyPos	= { 0.0f, 40.0f, 0.0f };
	FVector BodyScale = { 60.0f, 80.0f, 1.0f };
	BodyCol->SetPosition(BodyPos);
	BodyCol->SetScale(BodyScale);
	BodyCol->SetActive(true);

	FVector FrontPos = { 0.0f, 40.0f, 0.0f };
	FVector FrontScale = { 5.0f, 80.0f, 1.0f };
	FrontCol->SetPosition(FrontPos);
	FrontCol->SetScale(FrontScale);
	FrontCol->SetActive(true);

	SetBodyInfo(BodyPos, BodyScale);
}

void ADefaultPlayer::CreateAnimation()
{
	// Player
	GetBody()->CreateAnimation(Anim::player_idle, ImgRes::player_idle, 0.1f, true);
	GetBody()->CreateAnimation(Anim::player_idle_to_run, ImgRes::player_idle_to_run, 0.03f, false);
	GetBody()->CreateAnimation(Anim::player_run_to_idle, ImgRes::player_run_to_idle, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_jump, ImgRes::player_jump, 0.1f, false);
	GetBody()->CreateAnimation(Anim::player_fall, ImgRes::player_fall, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_run, ImgRes::player_run, 0.08f, true);
	GetBody()->CreateAnimation(Anim::player_postcrouch, ImgRes::player_postcrouch, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_precrouch, ImgRes::player_precrouch, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_roll, ImgRes::player_roll, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_attack, ImgRes::player_attack, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_wall_slide, ImgRes::player_wall_slide, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_flip, ImgRes::player_flip, 0.02f, false);
	GetBody()->CreateAnimation(Anim::player_kick_door, ImgRes::player_kick_door, 0.06f, false);
	GetBody()->CreateAnimation(Anim::player_remove_headphones, ImgRes::player_remove_headphones, 0.1f, false);
	GetBody()->CreateAnimation
	(
		Anim::player_headphones, 
		ImgRes::player_headphones, 
		{ 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 1.95f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 },
		false
	);

	GetBody()->CreateAnimation(
		Anim::player_dead, 
		ImgRes::player_dead, 
		{ 0.2f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f, 0.02f },
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
		false
	);

	GetBody()->SetFrameCallback(Anim::player_kick_door, 9, [=] { StateChange(PlayerState::idle); });

	GetBody()->SetFrameCallback(Anim::player_kick_door, 4, [=]
		{
			FrontCol->CollisionStay(EColOrder::Door, [=](std::shared_ptr<UCollision> _Other)
				{
					ADoor* Door = dynamic_cast<ADoor*>(_Other->GetActor());
					Door->StateChange(DoorState::open);
				}
			);
		}
	);
}

void ADefaultPlayer::SoundSetting()
{
	// Sound Setting
	GetBody()->SetFrameCallback(Anim::player_idle_to_run, 3,		[=] { UEngineSound::SoundPlay(SoundRes::player_prerun).SetVolume(0.25f); });
	GetBody()->SetFrameCallback(Anim::player_headphones, 16,		[=] { USoundManager::GetInst().GetFactoryBGM().On(); });
	GetBody()->SetFrameCallback(Anim::player_headphones, 2,			[=] { UEngineSound::SoundPlay(SoundRes::player_headphone).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_headphones, 12,		[=] { UEngineSound::SoundPlay(SoundRes::player_casette_rewind).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_headphones, 15,		[=] { UEngineSound::SoundPlay(SoundRes::player_casette_play).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_remove_headphones, 11,	[=] { UEngineSound::SoundPlay(SoundRes::player_headphone).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_remove_headphones, 3,	[=] { UEngineSound::SoundPlay(SoundRes::player_casette_play).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_roll, 16,				[=] { USoundManager::GetInst().GetFactoryBGM().On(); });
	GetBody()->SetFrameCallback(Anim::player_roll, 1,				[=] { UEngineSound::SoundPlay(SoundRes::player_roll).SetVolume(0.25f); });
	GetBody()->SetFrameCallback(Anim::player_run, 1,				[=] { USoundManager::SoundPlay_PlayerRun(); });
	GetBody()->SetFrameCallback(Anim::player_jump, 0,				[=] { UEngineSound::SoundPlay(SoundRes::player_jump).SetVolume(0.5f); });
	GetBody()->SetFrameCallback(Anim::player_attack, 2,				[=] { USoundManager::SoundPlay_PlayerSlash(); });
	GetBody()->SetFrameCallback(Anim::player_flip, 0,				[=] { UEngineSound::SoundPlay(SoundRes::player_roll).SetVolume(0.25f); });
	GetBody()->SetFrameCallback(Anim::player_flip, 1,				[=] { USoundManager::SoundPlay_WallKick(); });
}

void ADefaultPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

// State
void ADefaultPlayer::IdleStart()
{
	Super::IdleStart();

	GetBody()->AnimationReset();
	GetBody()->ChangeAnimation(Anim::player_idle);
}

void ADefaultPlayer::IdleToRunStart()
{
	Super::IdleToRunStart();

	GetBody()->ChangeAnimation(Anim::player_idle_to_run);
}

void ADefaultPlayer::RunStart()
{
	Super::RunStart();

	GetBody()->ChangeAnimation(Anim::player_run);
}

void ADefaultPlayer::RunToIdleStart()
{
	Super::RunToIdleStart();

	GetBody()->ChangeAnimation(Anim::player_run_to_idle);
}

void ADefaultPlayer::PostCrouchStart()
{
	Super::PostCrouchStart();

	GetBody()->ChangeAnimation(Anim::player_postcrouch);
}

void ADefaultPlayer::PreCrouchStart()
{
	Super::PreCrouchStart();

	GetBody()->ChangeAnimation(Anim::player_precrouch);
}

void ADefaultPlayer::RollStart()
{
	Super::RollStart();

	GetBody()->ChangeAnimation(Anim::player_roll);
}

void ADefaultPlayer::JumpStart()
{
	Super::JumpStart();

	GetBody()->ChangeAnimation(Anim::player_jump);
}

void ADefaultPlayer::FallStart()
{
	Super::FallStart();

	GetBody()->ChangeAnimation(Anim::player_fall);
}

void ADefaultPlayer::AttackStart()
{
	Super::AttackStart();

	GetBody()->ChangeAnimation(Anim::player_attack);
}

void ADefaultPlayer::WallSlideStart()
{
	Super::WallSlideStart();

	GetBody()->ChangeAnimation(ImgRes::player_wall_slide);
}

void ADefaultPlayer::FlipStart()
{
	Super::FlipStart();

	GetBody()->ChangeAnimation(Anim::player_flip);
}

void ADefaultPlayer::KickDoorStart()
{
	Super::KickDoorStart();

	GetBody()->ChangeAnimation(Anim::player_kick_door);
}

void ADefaultPlayer::DeadStart()
{
	Super::DeadStart();

	GetBody()->ChangeAnimation(Anim::player_dead);
	UEngineSound::SoundPlay(SoundRes::player_die).SetVolume(0.75f);
}

void ADefaultPlayer::OnlyFallStart()
{
	Super::OnlyFallStart();

	GetBody()->ChangeAnimation(Anim::player_fall);
}

void ADefaultPlayer::IntroStart()
{
	Super::IntroStart();

	switch (IntroType)
	{
	case EIntroType::HeadHunter2:
		GetBody()->ChangeAnimation(Anim::player_fall);
		Velocity.X = 0.0f;
		Velocity.Y = (-0.8f) * Const::player_fall_max_speedy;
		SetIntroOrder(EIntroOrder::Fall);
		break;
	default:
		GetBody()->ChangeAnimation(Anim::player_run);
		DelayCallBack(IntroRunTime, [=]
			{
				Velocity = FVector::Zero;
				GetBody()->ChangeAnimation(Anim::player_run_to_idle);
				SetIntroOrder(EIntroOrder::RunToIdle);
			}
		);
		break;
	}	
}

void ADefaultPlayer::Intro(float _DeltaTime)
{
	Super::Intro(_DeltaTime);

	switch (GetIntroOrder())
	{
	case EIntroOrder::Run:
		PosUpdate(_DeltaTime);
		break;
	case EIntroOrder::RunToIdle:
		if (true == GetBody()->IsCurAnimationEnd())
		{
			switch (IntroType)
			{
			case EIntroType::Default:
				GetBody()->ChangeAnimation(Anim::player_idle);
				StateChange(PlayerState::idle);
				SubStateChange(PlayerSubState::none);
				break;
			case EIntroType::FactoryBegin:
				DelayCallBack(0.5f, [=]
					{
						GetBody()->ChangeAnimation(Anim::player_headphones);
					}
				);
				SetIntroOrder(EIntroOrder::MusicOn);
				break;
			case EIntroType::HeadHunter1:
				DelayCallBack(0.5f, [=]
					{
						GetBody()->ChangeAnimation(Anim::player_remove_headphones);
					}
				);

				AHeadHunterLevel_Phase1* PlayLevel = dynamic_cast<AHeadHunterLevel_Phase1*>(GetWorld()->GetGameMode().get());
				PlayLevel->AllSlidingDoorClose();
				SetIntroOrder(EIntroOrder::MusicOff);
				break;
			}
		}
		break;
	case EIntroOrder::Fall:
		PosUpdate(_DeltaTime);
		if (true == IsOnGround(GetBody()->GetDir()))
		{
			UEngineSound::SoundPlay(SoundRes::player_land).SetVolume(0.5f);
			GetBody()->ChangeAnimation(Anim::player_postcrouch);
			OnGroundPosAdjust(GetBody()->GetDir());
			SetIntroOrder(EIntroOrder::None);
			DelayCallBack(0.5f, [=] 
				{
					GetBody()->ChangeAnimation(Anim::player_precrouch);
					SetIntroOrder(EIntroOrder::PreCrouch);
				}
			);
		}
		break;
	case EIntroOrder::PreCrouch:
	case EIntroOrder::MusicOn:
	case EIntroOrder::MusicOff:
		if (true == GetBody()->IsCurAnimationEnd())
		{
			GetBody()->ChangeAnimation(Anim::player_idle);
		}
		break;
	}
}

void ADefaultPlayer::OutroTypeInit()
{
	std::string CurMainState = GetCurMainState();

	if (PlayerState::run == CurMainState)
	{
		SetOutroType(EOutroType::Run);
		SetMaxRunVel();
		return;
	}

	if (PlayerState::idle_to_run == CurMainState)
	{
		SetOutroType(EOutroType::IdleToRun);
		return;
	}

	if (PlayerState::run_to_idle == CurMainState)
	{
		SetOutroType(EOutroType::RunToIdle);
		SetMaxRunVel();
		GetBody()->ChangeAnimation(Anim::player_run);
		return;
	}

	if (PlayerState::jump == CurMainState)
	{
		SetOutroType(EOutroType::Jump);
		return;
	}

	if (PlayerState::fall == CurMainState)
	{
		SetOutroType(EOutroType::Fall);
		return;
	}

	if (PlayerState::roll == CurMainState)
	{
		SetOutroType(EOutroType::Roll);
		return;
	}

	if (PlayerState::attack == CurMainState)
	{
		SetOutroType(EOutroType::Attack);
		return;
	}
}

void ADefaultPlayer::OutroUpdate(float _DeltaTime)
{
	Super::OutroUpdate(_DeltaTime);

	switch (GetOutroType())
	{
	case EOutroType::IdleToRun:
		if (true == GetBody()->IsCurAnimationEnd())
		{
			SetMaxRunVel();
			GetBody()->ChangeAnimation(Anim::player_run);
		}
		break;
	case EOutroType::Jump:
		if (true == IsColHeadToCeil(GetBody()->GetDir()))
		{
			AddActorLocation({ 0.0f, -2.0f, 0.0f });
			Velocity.Y = 0.0f;
		}

		JumpGravityUpdate(_DeltaTime);

		if (0.0f > Velocity.Y)
		{
			GetBody()->ChangeAnimation(Anim::player_fall);
			SetOutroType(EOutroType::Fall);
		}
		break;

	case EOutroType::Fall:
		FallGravityUpdate(_DeltaTime);
		break;

	case EOutroType::Roll:
		if (true == GetBody()->IsCurAnimationEnd())
		{
			SetMaxRunVel();
			GetBody()->ChangeAnimation(Anim::player_run);
		}
		break;

	case EOutroType::Attack:
		if (true == GetBody()->IsCurAnimationEnd())
		{
			GetBody()->ChangeAnimation(Anim::player_fall);
			SetOutroType(EOutroType::Fall);
		}
		FallGravityUpdate(_DeltaTime);
		break;
	}
}
