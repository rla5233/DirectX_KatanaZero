#include "PreCompile.h"
#include "WallTurret.h"

#include "PlayLevelBase.h"

AWallTurret::AWallTurret()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->CreateAnimation(Anim::turret_wall_open, ImgRes::turret_wall_open, 0.07f, false);
	GetBody()->SetupAttachment(GetRoot());
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetActive(false);
	
	AllHolder.reserve(HolderNum);
	float InterY = 100.0f;
	for (int i = 0; i < HolderNum; i++)
	{
		AllHolder.push_back(CreateDefaultSubObject<USpriteRenderer>("Holder"));
		AllHolder[i]->SetOrder(ERenderOrder::Enemy);
		AllHolder[i]->CreateAnimation(Anim::turret_fromwall, ImgRes::turret_fromwall, 0.07f, false);
		AllHolder[i]->SetupAttachment(GetRoot());
		AllHolder[i]->SetAutoSize(2.0f, true);
		AllHolder[i]->SetActive(false);
		AllHolder[i]->SetPivot(EPivot::LEFTBOTTOM);

		AllHolder[i]->SetPosition({ -19.0f, 5.0f - InterY * i, 0.0f });
	}

	AllHead.reserve(HeadNum);
	for (int i = 0; i < HeadNum; i++)
	{
		AllHead.push_back(CreateDefaultSubObject<USpriteRenderer>("Holder"));
		AllHead[i]->SetOrder(ERenderOrder::Enemy);
		AllHead[i]->SetSprite(ImgRes::turret_head);
		AllHead[i]->SetupAttachment(GetRoot());
		AllHead[i]->SetAutoSize(2.0f, true);
		AllHead[i]->SetActive(false);

		AllHead[i]->SetPosition({ 39.0f, 73.0f - InterY * i, 0.0f });
	}
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
	State.CreateState(WallTurretState::active);

	// State Start
	State.SetStartFunction(WallTurretState::none, [=] {});
	State.SetStartFunction(WallTurretState::open, [=] 
		{
			GetBody()->ChangeAnimation(Anim::turret_wall_open);
			GetBody()->SetActive(true);
			Order = 0;
		}
	);

	State.SetStartFunction(WallTurretState::active, [=] {});
	
	// State Update
	State.SetUpdateFunction(WallTurretState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(WallTurretState::open, [=](float _DeltaTime) 
		{
			switch (Order)
			{
			case 0:
				if (true == GetBody()->IsCurAnimationEnd())
				{
					for (size_t i = 0; i < AllHolder.size(); i++)
					{
						AllHolder[i]->ChangeAnimation(Anim::turret_fromwall);
						AllHolder[i]->SetActive(true);
					}

					++Order;
				}
				break;
			case 1:
				if (true == AllHolder[0]->IsCurAnimationEnd())
				{
					State.ChangeState(WallTurretState::active);
					return;
				}
				break;
			}
		}
	);

	State.SetUpdateFunction(WallTurretState::active, [=](float _DeltaTime) 
		{
			APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());
			FVector PlayerPos = PlayLevel->GetPlayerLocation();

			for (size_t i = 0; i < AllHead.size(); i++)
			{
				FVector HeadPos = AllHead[i]->GetWorldPosition();
				FVector HeadDir = PlayerPos - HeadPos;
				
				float Deg =  UContentsMath::GetAngleToX_2D(HeadDir.Normalize2DReturn());
				if (HeadDeg_Min > Deg)
				{
					if (HeadPos.Y < PlayerPos.Y)
					{
						Deg = 0.0f;
					}
					else
					{
						Deg = HeadDeg_Min;
					}
				}

				AllHead[i]->SetRotationDeg({ 0.0f, 0.0f, Deg });

				std::string Msg = std::format("Deg : {}\n", Deg);
				UEngineDebugMsgWindow::PushMsg(Msg);
			}
		}
	);
}

void AWallTurret::WallOpenAnimAdjust()
{
	// Wall
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 0,	[=] { GetBody()->SetPosition({ 0.0f, 0.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 1,	[=] { GetBody()->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 2,	[=] { GetBody()->SetPosition({ 0.0f, -10.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 3,	[=] { GetBody()->SetPosition({ 0.0f, -12.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 4,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 5,	[=] { GetBody()->SetPosition({ 0.0f, -18.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 6,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 7,	[=] { GetBody()->SetPosition({ 0.0f, -15.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 8,	[=] { GetBody()->SetPosition({ 0.0f, 1.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 14,	[=] { GetBody()->SetPosition({ 0.0f, -2.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 15,	[=] { GetBody()->SetPosition({ 0.0f, -5.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 16,	[=] { GetBody()->SetPosition({ 0.0f, -4.0f, 0.0f }); });
	GetBody()->SetFrameCallback(Anim::turret_wall_open, 19,	[=] { GetBody()->SetPosition({ 0.0f, 3.0f, 0.0f }); });

	// Holder
	for (size_t i = 0; i < AllHolder.size(); i++)
	{
		AllHolder[i]->SetLastFrameCallback(Anim::turret_fromwall, [=] { AllHead[i]->SetActive(true); });
	}
}

void AWallTurret::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

