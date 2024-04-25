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

	Arrow->SetPosition({ 0.0f, -40.0f, 0.0f });
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

void AGo::StateInit()
{
	// State Create
	State.CreateState(GoState::repeat);
	State.CreateState(GoState::outro);

	// State Start
	State.SetStartFunction(GoState::repeat, [=]
		{ 
			Velocity.X = MaxSpeed;
			SetActorLocation(RepeatPos);
		}
	);

	State.SetStartFunction(GoState::outro, [=]
		{
			Go->SetActive(false);
			Arrow->SetActive(false);
		}
	);

	// State Update
	State.SetUpdateFunction(GoState::repeat, [=](float _DeltaTime)
		{
			Velocity += { -MaxSpeed * _DeltaTime, 0.0f, 0.0f };
			AddActorLocation(Velocity * _DeltaTime);
			if (1.0f > abs(Velocity.X))
			{
				SetActorLocation(RepeatPos);
				Velocity.X = MaxSpeed;
			}
		}
	);

	State.SetUpdateFunction(GoState::outro, [=](float _DeltaTime) {});
}
