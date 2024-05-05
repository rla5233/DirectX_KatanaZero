#include "PreCompile.h"
#include "HeadHunter.h"

AHeadHunter::AHeadHunter()
{
}

AHeadHunter::~AHeadHunter()
{
}

void AHeadHunter::BeginPlay()
{
	Super::BeginPlay();

	URecordingObject::SetActor(this);
	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	RendererInit();
	CollisionInit();
	CreateAnimation();

}

void AHeadHunter::RendererInit()
{
}

void AHeadHunter::CollisionInit()
{
}

void AHeadHunter::CreateAnimation()
{
}

void AHeadHunter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
