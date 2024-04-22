#include "PreCompile.h"
#include "ReplayUI.h"

AReplayUI::AReplayUI()
{
}

AReplayUI::~AReplayUI()
{
}

void AReplayUI::BeginPlay()
{
	Super::BeginPlay();

	CreateImage();


	StateInit();

}

void AReplayUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AReplayUI::CreateImage()
{
	LeftBottomText = CreateWidget<UImage>(GetWorld(), "LeftBottom_Text");
	RightTopText = CreateWidget<UImage>(GetWorld(), "RightTop_Text");
}

void AReplayUI::StateInit()
{
}
