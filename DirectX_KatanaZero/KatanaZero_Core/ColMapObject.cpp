#include "PreCompile.h"
#include "ColMapObject.h"

AColMapObject::AColMapObject()
{
	ColMap = CreateDefaultSubObject<USpriteRenderer>("ColMap");
}

AColMapObject::~AColMapObject()
{
}

void AColMapObject::BeginPlay()
{
	Super::BeginPlay();

	ColMap->SetOrder(ERenderOrder::ColMap);
}

void AColMapObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
