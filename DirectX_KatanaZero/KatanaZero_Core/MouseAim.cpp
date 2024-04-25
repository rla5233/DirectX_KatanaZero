#include "PreCompile.h"
#include "MouseAim.h"

#include "ColMapObject.h"

FVector AMouseAim::Location = FVector::Zero;

AMouseAim::AMouseAim()
{
	Aim = CreateDefaultSubObject<USpriteRenderer>("MouseAim");
	
	SetRoot(Aim);
}

AMouseAim::~AMouseAim()
{
}

void AMouseAim::BeginPlay()
{
	Super::BeginPlay();

	StateInit();

	Aim->SetSprite(ImgRes::ui_cursor);
	Aim->SetAutoSize(2.0f, true);
	Aim->SetOrder(ERenderOrder::UI);
	State.ChangeState(MouseAimState::play);
}

void AMouseAim::StateInit()
{
	// State
	State.CreateState(MouseAimState::play);

	// Start
	State.SetStartFunction(MouseAimState::play, [=]
		{
			//GEngine->EngineWindow.CursorOff();
			Aim->SetActive(true);
		}
	);

	// Update
	State.SetUpdateFunction(MouseAimState::play, [=](float _DeltaTime)
		{
			FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
			FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();

			FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
			FVector TargetPos =	FVector(CameraPos.X, CameraPos.Y, 0.0f) + FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 0.0f);
			SetActorLocation(TargetPos);
			Location = TargetPos;
		}
	);
}

void AMouseAim::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


