#include "PreCompile.h"
#include "WallTurret.h"

AWallTurret::AWallTurret()
{
	Wall = CreateDefaultSubObject<USpriteRenderer>("Wall");
	Wall->SetOrder(ERenderOrder::MapComponent_Back);
	Wall->CreateAnimation(Anim::turret_wall_open, ImgRes::turret_wall_open, 0.1f, false);
	Wall->SetupAttachment(GetRoot());
	Wall->SetAutoSize(2.0f, true);
}

AWallTurret::~AWallTurret()
{
}

void AWallTurret::BeginPlay()
{
	Super::BeginPlay();

}

void AWallTurret::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(WallTurretState::none);
	State.CreateState(WallTurretState::open);

	
	// State Start
	State.SetStartFunction(WallTurretState::none, [=] {});
	State.SetStartFunction(WallTurretState::open, [=] {});


	// State Update
	State.SetUpdateFunction(WallTurretState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(WallTurretState::open, [=](float _DeltaTime) {});


}

void AWallTurret::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

