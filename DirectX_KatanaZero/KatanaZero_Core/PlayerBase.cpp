#include "PreCompile.h"
#include "PlayerBase.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"
#include "MouseAim.h"

APlayerBase::APlayerBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Renderer	= CreateDefaultSubObject<USpriteRenderer>("Player_Renderer");
	Front_Top	= CreateDefaultSubObject<USpriteRenderer>("Front_Top");
	Front_Bot	= CreateDefaultSubObject<USpriteRenderer>("Front_Bot");
	Back_Top	= CreateDefaultSubObject<USpriteRenderer>("Back_Top");
	Back_Bot	= CreateDefaultSubObject<USpriteRenderer>("Back_Bot");

	AttackCol = CreateDefaultSubObject<UCollision>("Player_Attack");

	Renderer->SetupAttachment(Root);
	Back_Top->SetupAttachment(Root);
	Back_Bot->SetupAttachment(Root);
	Front_Top->SetupAttachment(Root);
	Front_Bot->SetupAttachment(Root);
	AttackCol->SetupAttachment(Root);
	
	SetRoot(Root);
	InputOn();
}

APlayerBase::~APlayerBase()
{
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);

	RendererInit();
	CollisionInit();
	StateInit();

	SetRecordingSize(0.0f);
}

void APlayerBase::RendererInit()
{
	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetDir(EEngineDir::Right);
	Renderer->SetPivot(EPivot::BOT);

	Front_Top->SetSprite("RedPoint.png");
	Front_Top->SetOrder(ERenderOrder::Player2);
	Front_Top->SetAutoSize(4.0f, true);
	Front_Top->SetPosition(Top);

	Front_Bot->SetSprite("RedPoint.png");
	Front_Bot->SetOrder(ERenderOrder::Player2);
	Front_Bot->SetAutoSize(4.0f, true);
	Front_Bot->SetPosition(Bot);

	Back_Top->SetSprite("RedPoint.png");
	Back_Top->SetOrder(ERenderOrder::Player2);
	Back_Top->SetAutoSize(4.0f, true);
	Back_Top->SetPosition({ -Top.X, Top.Y, Top.Z });

	Back_Bot->SetSprite("RedPoint.png");
	Back_Bot->SetOrder(ERenderOrder::Player2);
	Back_Bot->SetAutoSize(4.0f, true);
	Back_Bot->SetPosition({ -Bot.X, Bot.Y, Bot.Z });
}

void APlayerBase::CollisionInit()
{
	AttackCol->SetCollisionGroup(EColOrder::PlayerAttack);
	AttackCol->SetCollisionType(ECollisionType::RotRect);
	AttackCol->SetScale({ 150.0f, 75.0f, 0.0f });
	AttackCol->SetActive(false);
}

void APlayerBase::DefaultUpdate(float _DeltaTime)
{
	AttackDelayTimeUpdate(_DeltaTime);
	
	std::string CurState = State.GetCurStateName();

	if ("Replay" != CurState)
	{
		Recording(_DeltaTime);
	}
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

bool APlayerBase::IsDirChangeKeyDown()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsDown('D') || true == IsDown(VK_RIGHT)))
	{
		RendererDirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsDown('A') || true == IsDown(VK_LEFT)))
	{
		RendererDirChange(EEngineDir::Left);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsDirChangeKeyPress()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		RendererDirChange(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		RendererDirChange(EEngineDir::Left);
		Result = true;
	}

	if ((true == IsPress('D') || true == IsPress(VK_RIGHT))
	&&  (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = false;
	}

	return Result;
}

void APlayerBase::RendererDirChange(EEngineDir _Dir)
{
	switch (_Dir)
	{
	case EEngineDir::Left:
		Renderer->SetDir(EEngineDir::Left);
		Front_Top->SetPosition({ -Top.X, Top.Y, Top.Z });
		Front_Bot->SetPosition({ -Bot.X, Bot.Y, Bot.Z });
		Back_Top->SetPosition(Top);
		Back_Bot->SetPosition(Bot);
		break;
	case EEngineDir::Right:
		Renderer->SetDir(EEngineDir::Right);
		Front_Top->SetPosition(Top);
		Front_Bot->SetPosition(Bot);
		Back_Top->SetPosition({ -Top.X, Top.Y, Top.Z });
		Back_Bot->SetPosition({ -Bot.X, Bot.Y, Bot.Z });
		break;
	}
}

bool APlayerBase::IsOnGround()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FB_Pos = Front_Bot->GetWorldPosition();
	FVector BB_Pos = Back_Bot->GetWorldPosition();

	FB_Pos.Y = MapTexScale.Y - FB_Pos.Y - 1.0f;
	BB_Pos.Y = MapTexScale.Y - BB_Pos.Y - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FB_Pos, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BB_Pos, Color8Bit::Black);

	if (ColMap::YELLOW == FB_PixelColor && ColMap::YELLOW == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsOnPlatForm()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FB_Pos = Front_Bot->GetWorldPosition();
	FVector BB_Pos = Back_Bot->GetWorldPosition();

	FB_Pos.Y = MapTexScale.Y - FB_Pos.Y - 1.0f;
	BB_Pos.Y = MapTexScale.Y - BB_Pos.Y - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FB_Pos, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BB_Pos, Color8Bit::Black);

	if (ColMap::GREEN == FB_PixelColor && ColMap::GREEN == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsOnGP_Boundary()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FB_Pos = Front_Bot->GetWorldPosition();
	FVector BB_Pos = Back_Bot->GetWorldPosition();

	FB_Pos.Y = MapTexScale.Y - FB_Pos.Y - 1.0f;
	BB_Pos.Y = MapTexScale.Y - BB_Pos.Y - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FB_Pos, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BB_Pos, Color8Bit::Black);

	if (ColMap::GREEN == FB_PixelColor && ColMap::YELLOW == BB_PixelColor)
	{
		Result = true;
	}

	if (ColMap::YELLOW== FB_PixelColor && ColMap::GREEN == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsOnStairs()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FB_Pos = Front_Bot->GetWorldPosition();
	FVector BB_Pos = Back_Bot->GetWorldPosition();

	FB_Pos.Y = MapTexScale.Y - FB_Pos.Y - 1.0f;
	BB_Pos.Y = MapTexScale.Y - BB_Pos.Y - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FB_Pos, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BB_Pos, Color8Bit::Black);

	IsStairsUpValue = false;

	if (ColMap::BLUE == FB_PixelColor && ColMap::BLUE != BB_PixelColor)
	{
		IsStairsUpValue = true;
		Result = true;
	}

	if (ColMap::BLUE != FB_PixelColor && ColMap::BLUE == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsColWall()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FT_Pos = Front_Top->GetWorldPosition();
	FVector FB_Pos = Front_Bot->GetWorldPosition();

	FT_Pos.Y = MapTexScale.Y - FT_Pos.Y;
	FB_Pos.Y = MapTexScale.Y - FB_Pos.Y;

	Color8Bit FT_PixelColor = MapTex->GetColor(FT_Pos, Color8Bit::Black);
	Color8Bit FB_PixelColor = MapTex->GetColor(FB_Pos, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor && ColMap::YELLOW == FB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsColHeadToWall()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FT_Pos = Front_Top->GetWorldPosition();

	FT_Pos.Y = MapTexScale.Y - FT_Pos.Y;

	Color8Bit FT_PixelColor = MapTex->GetColor(FT_Pos, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor || ColMap::BLUE == FT_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsColHeadToCeil()
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FT_Pos = Front_Top->GetWorldPosition();
	FVector BT_Pos = Back_Top->GetWorldPosition();

	FT_Pos.Y = MapTexScale.Y - FT_Pos.Y;
	BT_Pos.Y = MapTexScale.Y - BT_Pos.Y;

	Color8Bit FT_PixelColor = MapTex->GetColor(FT_Pos, Color8Bit::Black);
	Color8Bit BT_PixelColor = MapTex->GetColor(BT_Pos, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor && ColMap::YELLOW == BT_PixelColor)
	{
		Result = true;
	}

	return Result;
}

void APlayerBase::OnGroundPosAdjust()
{
	while (true == IsOnGround())
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnGround())
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}
}

void APlayerBase::UpStairPosAdjust()
{
	while (true == IsOnStairs())
	{
		AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnStairs())
		{
			AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}	
}

////////////////////
// FSM Setting Start
void APlayerBase::SetMaxRunVel()
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X = -Const::player_max_speedx;
		break;
	case EEngineDir::Right:
		Velocity.X = Const::player_max_speedx;
		break;
	}
}

void APlayerBase::SetAttackDir()
{
	FVector AimPos = AMouseAim::GetMouseAimLocation();
	FVector CurPos = GetActorLocation();
	AttackDir = AimPos - CurPos;

	if (0.0f > AttackDir.X)
	{
		RendererDirChange(EEngineDir::Left);
	}
	else
	{
		RendererDirChange(EEngineDir::Right);
	}

	AttackDir.Normalize2D();
}
// FSM Setting End
//////////////////

////////////////////
// FSM Update Start
void APlayerBase::GravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::default_gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::DownStairGravityUpdate(float _DeltaTime)
{
	if (true == IsOnGround() || true == IsOnPlatForm() || true == IsOnStairs() || true == IsOnGP_Boundary())
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += Const::down_stair_gravity * _DeltaTime;
}

void APlayerBase::RollDownStairGravityUpdate(float _DeltaTime)
{
	if (true == IsOnGround() || true == IsOnStairs() || true == IsOnGP_Boundary())
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity.Y += 5.0f * Const::down_stair_gravity * _DeltaTime;
}

void APlayerBase::JumpGravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::jump_gravity * _DeltaTime;

	if (-Const::player_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_max_speedy;
	}
}

void APlayerBase::FallGravityUpdate(float _DeltaTime)
{
	Velocity.Y += Const::default_gravity * _DeltaTime;

	if (-Const::player_fall_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_fall_max_speedy;
	}
}

void APlayerBase::WallGravityUpdate(float _DeltaTime)
{
	Velocity.Y += 0.75f * Const::default_gravity * _DeltaTime;

	if (-Const::player_fall_max_speedy > Velocity.Y)
	{
		Velocity.Y = -Const::player_fall_max_speedy;
	}
}

void APlayerBase::JumpVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_jump_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_jump_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < Velocity.X)
	{
		Velocity.X = Const::player_max_speedx;
	}

	if (-Const::player_max_speedx > Velocity.X)
	{
		Velocity.X = -Const::player_max_speedx;
	}
}

void APlayerBase::FallVelXUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_fall_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_fall_accx * _DeltaTime;
		break;
	}

	if (Const::player_max_speedx < Velocity.X)
	{
		Velocity.X = Const::player_max_speedx;
	}

	if (-Const::player_max_speedx > Velocity.X)
	{
		Velocity.X = -Const::player_max_speedx;
	}
}

void APlayerBase::IdleToRunVelUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();
	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += -Const::player_run_accx * _DeltaTime;
		break;
	case EEngineDir::Right:
		Velocity.X += Const::player_run_accx * _DeltaTime;
		break;
	}

	// max speedx üũ
	if (Const::player_max_speedx < std::abs(Velocity.X))
	{
		SetMaxRunVel();
	}
}

void APlayerBase::RunToIdleVelUpdate(float _DeltaTime)
{
	EEngineDir Dir = Renderer->GetDir();
	float FrictionAcc = 3000.0f;

	switch (Dir)
	{
	case EEngineDir::Left:
		Velocity.X += FrictionAcc * _DeltaTime;
		if (0.0f < Velocity.X)
		{
			Velocity.X = 0.0f;
		}
		break;
	case EEngineDir::Right:
		Velocity.X += -FrictionAcc * _DeltaTime;
		if (0.0f > Velocity.X)
		{
			Velocity.X = 0.0f;
		}
		break;
	}
}

void APlayerBase::PosUpdate(float _DeltaTime)
{
	AddActorLocation(Velocity * _DeltaTime);
}

void APlayerBase::ColCheckUpdate()
{
	Front_Top->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Front_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Back_Top->SetPlusColor({ 0.0f, 0.0f, 0.0f });
	Back_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });

	// ColWall
	if (true == IsColWall())
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// OnGround
	if (true == IsOnGround())
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		OnGroundPosAdjust();
	}

	// OnStairs
	if (true == IsOnStairs())
	{
		if (true == IsStairsUpValue)
		{
			Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
			Back_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			UpStairPosAdjust();
		}
		else
		{
			Front_Bot->SetPlusColor({ 0.0f, 0.0f, 0.0f });
			Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		}
	}

	// Platform
	if (true == IsOnPlatForm())
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// GP_Boundary
	if (true == IsOnGP_Boundary())
	{
		Front_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Bot->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// ColHeadToWall
	if (true == IsColHeadToWall())
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}

	// ColHeadToCeil
	if (true == IsColHeadToCeil())
	{
		Front_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
		Back_Top->SetPlusColor({ 1.0f, 1.0f, 1.0f });
	}
}
// FSM Update End
//////////////////

void APlayerBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	DefaultUpdate(_DeltaTime);
}

