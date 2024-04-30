#include "PreCompile.h"
#include "Go.h"

AGo::AGo()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
}

AGo::~AGo()
{
}

void AGo::StateInit()
{
	// State Create
	State.CreateState(GoState::repeat);
	State.CreateState(GoState::outro);

	// State Start
	State.SetStartFunction(GoState::repeat, [=]
		{
			EEngineDir Dir = Arrow->GetDir();
			switch (Dir)
			{
			case EEngineDir::Left:
				Velocity.X = -MaxSpeed;
				break;
			case EEngineDir::Right:
				Velocity.X = MaxSpeed;
				break;
			}

			SetActorLocation(RepeatPos);
		}
	);

	State.SetStartFunction(GoState::outro, [=] { Off(); });

	// State Update
	State.SetUpdateFunction(GoState::repeat, [=](float _DeltaTime)
		{
			EEngineDir Dir = Arrow->GetDir();
			switch (Dir)
			{
			case EEngineDir::Left:
				Velocity += { MaxSpeed * _DeltaTime, 0.0f, 0.0f };
				if (-1.0f < Velocity.X)
				{
					SetActorLocation(RepeatPos);
					Velocity.X = -MaxSpeed;
				}
				break;
			case EEngineDir::Right:
				Velocity += { -MaxSpeed * _DeltaTime, 0.0f, 0.0f };
				if (1.0f > Velocity.X)
				{
					SetActorLocation(RepeatPos);
					Velocity.X = MaxSpeed;
				}
				break;
			}

			AddActorLocation(Velocity * _DeltaTime);
		}
	);

	State.SetUpdateFunction(GoState::outro, [=](float _DeltaTime) {});
}

void AGo::BeginPlay()
{
	Super::BeginPlay();
	
	Init();
	StateInit();
}

void AGo::Init()
{
	Go = CreateWidget<UImage>(GetWorld(), "Go");
	Arrow = CreateWidget<UImage>(GetWorld(), "Go_Arrow");

	Go->SetSprite(ImgRes::ui_go);
	Arrow->SetSprite(ImgRes::ui_go_arrow);

	Go->AddToViewPort(EWidgetOrder::Top);
	Arrow->AddToViewPort(EWidgetOrder::Top);

	Go->SetAutoSize(2.0f, true);
	Arrow->SetAutoSize(2.0f, true);
	SetArrowDir(EEngineDir::Right);
}


void AGo::SetArrowDir(EEngineDir _Dir)
{
	Arrow->SetDir(_Dir);
}

void AGo::SetActorLocation(const FVector& _Pos)
{
	FVector Pos = _Pos;
	Go->SetPosition(Pos);

	Pos.Y += -40.0f;
	Arrow->SetPosition(Pos);
}

void AGo::AddActorLocation(const FVector& _Pos)
{
	FVector Pos = _Pos;
	Go->AddPosition(Pos);
	Arrow->AddPosition(Pos);
}

void AGo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

