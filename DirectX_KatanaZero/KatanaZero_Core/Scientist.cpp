#include "PreCompile.h"
#include "Scientist.h"

AScientist::AScientist()
{


}

AScientist::~AScientist()
{
}

void AScientist::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CollisionInit();
	CreateAnimation();
}

void AScientist::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AScientist::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(ScientistState::idle);
	State.CreateState(ScientistState::explode);

	// State Start
	State.SetStartFunction(ScientistState::idle, [=] 
		{
			GetBody()->ChangeAnimation(Anim::compo_scientist_chair);
		}
	);

	State.SetStartFunction(ScientistState::explode, [=] {});

	// State Update
	State.SetUpdateFunction(ScientistState::idle, [=](float _DeltaTime) {});
	State.SetUpdateFunction(ScientistState::explode, [=](float _DeltaTime) {});

}

void AScientist::RendererInit()
{
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetDir(EEngineDir::Left);
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetPivot(EPivot::BOT);
}

void AScientist::CollisionInit()
{

}

void AScientist::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::compo_scientist_chair, ImgRes::compo_scientist_chair, 0.1f, true);
	GetBody()->CreateAnimation(Anim::compo_scientist_explode, ImgRes::compo_scientist_explode, 0.1f, true);


}
