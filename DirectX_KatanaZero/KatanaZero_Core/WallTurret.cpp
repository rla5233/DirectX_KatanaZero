#include "PreCompile.h"
#include "WallTurret.h"

AWallTurret::AWallTurret()
{
	Wall = CreateDefaultSubObject<USpriteRenderer>("Wall");
	Wall->SetOrder(ERenderOrder::MapComponent_Back);
	Wall->CreateAnimation(Anim::turret_wall_open, ImgRes::turret_wall_open, 0.07f, false);
	Wall->SetupAttachment(GetRoot());
	Wall->SetAutoSize(2.0f, true);
	Wall->SetActive(false);
}

AWallTurret::~AWallTurret()
{
}

void AWallTurret::BeginPlay()
{
	Super::BeginPlay();

	WallOpenAnimAdjust();

	State.ChangeState(WallTurretState::none);
	DelayCallBack(4.0f, [=]
		{
			State.ChangeState(WallTurretState::open);
		}
	);	
}

void AWallTurret::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(WallTurretState::none);
	State.CreateState(WallTurretState::open);

	
	// State Start
	State.SetStartFunction(WallTurretState::none, [=] {});
	State.SetStartFunction(WallTurretState::open, [=] 
		{
			Wall->ChangeAnimation(Anim::turret_wall_open);
			Wall->SetActive(true);
		}
	);


	// State Update
	State.SetUpdateFunction(WallTurretState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(WallTurretState::open, [=](float _DeltaTime) 
		{
			{
				std::string Msg = std::format("Wall_Idx: {}\n", Wall->GetCurAnimationFrame());
				UEngineDebugMsgWindow::PushMsg(Msg);
			}
		}
	);


}

void AWallTurret::WallOpenAnimAdjust()
{
	Wall->SetFrameCallback(Anim::turret_wall_open, 0,	[=] { Wall->SetPosition({ 0.0f, 0.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 1,	[=] { Wall->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 2,	[=] { Wall->SetPosition({ 0.0f, -10.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 3,	[=] { Wall->SetPosition({ 0.0f, -12.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 4,	[=] { Wall->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 5,	[=] { Wall->SetPosition({ 0.0f, -18.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 6,	[=] { Wall->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 7,	[=] { Wall->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 8,	[=] { Wall->SetPosition({ 0.0f, 1.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 14,	[=] { Wall->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 15,	[=] { Wall->SetPosition({ 0.0f, -5.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 16,	[=] { Wall->SetPosition({ 0.0f, -4.0f, 0.0f }); });
	Wall->SetFrameCallback(Anim::turret_wall_open, 19,	[=] { Wall->SetPosition({ 0.0f, 3.0f, 0.0f }); });
}

void AWallTurret::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

