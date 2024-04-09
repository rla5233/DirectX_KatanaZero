#include "PreCompile.h"
#include "BackGroundObject.h"

ABackGroundObject::ABackGroundObject()
{
	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
}

ABackGroundObject::~ABackGroundObject()
{
}

void ABackGroundObject::BeginPlay()
{
	Super::BeginPlay();
}

void ABackGroundObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
