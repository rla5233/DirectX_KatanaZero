#include "PreCompile.h"
#include "BoundaryColObject.h"

ABoundaryColObject::ABoundaryColObject()
{
	Body = CreateDefaultSubObject<UCollision>("Boundary");
	SetRoot(Body);
}

ABoundaryColObject::~ABoundaryColObject()
{
}

void ABoundaryColObject::BeginPlay()
{
	Super::BeginPlay();

	Body->SetCollisionGroup(EColOrder::Boundary);
	Body->SetCollisionType(ECollisionType::Rect);
	Body->SetActive(true);
}

void ABoundaryColObject::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}