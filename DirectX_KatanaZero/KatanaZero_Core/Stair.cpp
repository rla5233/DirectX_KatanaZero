#include "PreCompile.h"
#include "Stair.h"

AStair::AStair()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
	//BodyCol = CreateDefaultSubObject<UCollision>("Stair");
	//SetRoot(BodyCol);
}

AStair::~AStair()
{
}

void AStair::BeginPlay()
{
	Super::BeginPlay();

	//BodyCol->SetCollisionGroup(EColOrder::Stair);
	//BodyCol->SetCollisionType(ECollisionType::Rect);
	//BodyCol->SetScale({ 20.0f, 20.0f, 1.0f });
}

void AStair::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
