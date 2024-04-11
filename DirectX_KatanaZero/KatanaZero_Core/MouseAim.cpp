#include "PreCompile.h"
#include "MouseAim.h"

#include "ColMapObject.h"

AMouseAim::AMouseAim()
{
	Aim = CreateDefaultSubObject<USpriteRenderer>("MouseAim");
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
	State.ChangeState("Play");
}

void AMouseAim::StateInit()
{
	// State
	State.CreateState("Play");

	// Start
	State.SetStartFunction("Play", [=]
		{
			Aim->SetActive(true);
		}
	);

	// Update
	State.SetUpdateFunction("Play", [=](float _DeltaTime)
		{
			std::shared_ptr<UEngineTexture> MapTex = AColMapObject::GetMapTex();
			FVector MapTexScale = MapTex->GetScale();

			FVector CurPos = GEngine->EngineWindow.GetScreenMousePos();
			CurPos.Y = MapTexScale.Y - CurPos.Y;
			SetActorLocation(CurPos);
		}
	);

}

void AMouseAim::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


