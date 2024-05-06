#include "PreCompile.h"
#include "SlidingDoor.h"

#include "HeadHunterLevel.h"
#include "MainCamera.h"
#include "Cloud.h"

ASlidingDoor::ASlidingDoor()
{
	DoorLED = CreateDefaultSubObject<USpriteRenderer>("SlidingDoor_LED");
	DoorLED->SetupAttachment(GetRoot());
}

ASlidingDoor::~ASlidingDoor()
{
}

void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CreateAnimation();
}

void ASlidingDoor::RendererInit()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetAutoSize(2.0f, true);

	DoorLED->SetOrder(ERenderOrder::MapComponent_Back);
	DoorLED->SetPosition({ -1.0f, 96.0f, 0.0f });
	DoorLED->SetAutoSize(2.0f, true);
}

void ASlidingDoor::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::compo_sliding_door_close, ImgRes::compo_sliding_door_close, 0.04f, false);
	GetBody()->SetLastFrameCallback(Anim::compo_sliding_door_close, [=]
		{
			for (int i = 0; i < 10; i++)
			{
				ACloud* NewCloud = GetWorld()->SpawnActor<ACloud>("Cloud").get();
				NewCloud->SetActorLocation(GetActorLocation() - FVector(0.0f, 80.0f, 0.0f));
			
				float SpeedX = UEngineRandom::MainRandom.RandomFloat(-140.0f, 140.0f);
				float SpeedY = UEngineRandom::MainRandom.RandomFloat(10.0f, 150.0f);

				NewCloud->SetVelocity({ SpeedX, SpeedY, 0.0f });
			}		

			AHeadHunterLevel* PlayLevel = dynamic_cast<AHeadHunterLevel*>(GetWorld()->GetGameMode().get());
			AMainCamera* MainCamera = PlayLevel->GetKZMainCamera();

			if (MainCameraState::ret_shaking != MainCamera->GetCurState())
			{
				MainCamera->StateChange(MainCameraState::ret_shaking);
			}
		}
	);
	
	DoorLED->CreateAnimation(Anim::compo_sliding_door_redled, ImgRes::compo_sliding_door_redled, 0.08f, false);
}

void ASlidingDoor::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(SlidingDoorState::close);

	// State Start
	State.SetStartFunction(SlidingDoorState::close, [=] 
		{
			GetBody()->ChangeAnimation(Anim::compo_sliding_door_close);
			DoorLED->ChangeAnimation(Anim::compo_sliding_door_redled);
			SetActive(true);
		}
	);

	// State Update
	State.SetUpdateFunction(SlidingDoorState::close, [=](float _DeltaTime) {});
}

void ASlidingDoor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ASlidingDoor::SetAllMulColor(const float4& _MulColor)
{
	Super::SetAllMulColor(_MulColor);

	DoorLED->SetMulColor(_MulColor);
}
