#include "PreCompile.h"
#include "HeadHunter_Phase1.h"

#include "ColMapObject.h"
#include "MainCamera.h"

AHeadHunter_Phase1::AHeadHunter_Phase1()
{
}

AHeadHunter_Phase1::~AHeadHunter_Phase1()
{
}

void AHeadHunter_Phase1::BeginPlay()
{
	Super::BeginPlay();	
}

void AHeadHunter_Phase1::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	TotalPlayTime = 100.0f;

	ColMap->SetColMapSprite(ImgRes::headhunter_colmap1, 2.0f, true);
	ColMap->SetBGSprite(ImgRes::headhunter_background1, 2.0f, true);
	
	MainCamera->SetActorLocation({ 336.0f, 180.0f, -100.0f });
	MainCamera->StateChange(MainCameraState::stop);
}

void AHeadHunter_Phase1::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

}

void AHeadHunter_Phase1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);



}
