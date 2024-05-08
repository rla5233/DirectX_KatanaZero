#include "PreCompile.h"
#include "Mine.h"

AMine::AMine()
{
}

AMine::~AMine()
{
}

void AMine::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	CreateAnimation();
	StateInit();
	
	State.ChangeState(MineState::none);
}

void AMine::RendererInit()
{
	GetBody()->SetAutoSize(2.0f, true);
	GetBody()->SetOrder(ERenderOrder::MapComponent_Back);
	GetBody()->SetActive(false);
}

void AMine::CreateAnimation()
{
	GetBody()->CreateAnimation(Anim::compo_ground_mine, ImgRes::compo_ground_mine, 0.1f, true);

}

void AMine::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(MineState::none);
	State.CreateState(MineState::on);
	State.CreateState(MineState::explode);
	
	// State Start
	State.SetStartFunction(MineState::none, [=] {});
	State.SetStartFunction(MineState::on, [=] 
		{
			GetBody()->ChangeAnimation(Anim::compo_ground_mine);
			GetBody()->SetActive(true);
		}
	);
	State.SetStartFunction(MineState::explode, [=] {});


	// State Update
	State.SetUpdateFunction(MineState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(MineState::on, [=](float _DeltaTime) {});
	State.SetUpdateFunction(MineState::explode, [=](float _DeltaTime) {});


}

void AMine::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}