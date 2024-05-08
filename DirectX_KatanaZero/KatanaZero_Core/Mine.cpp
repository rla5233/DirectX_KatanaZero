#include "PreCompile.h"
#include "Mine.h"

AMine::AMine()
{
	Explosion.reserve(ExplosionNum);
	for (size_t i = 0; i < ExplosionNum; i++)
	{
		USpriteRenderer* NewExplosion = CreateDefaultSubObject<USpriteRenderer>("Root");
		NewExplosion->SetOrder(ERenderOrder::EffectFront);
		NewExplosion->SetupAttachment(GetRoot());
		NewExplosion->SetAutoSize(2.0f, true);
		NewExplosion->SetActive(false);

		NewExplosion->CreateAnimation(Anim::effect_explosion, ImgRes::effect_explosion, 0.08f, true);
		NewExplosion->SetLastFrameCallback(Anim::effect_explosion, [=] { NewExplosion->SetActive(false); });

		Explosion.push_back(NewExplosion);
	}
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
	State.SetStartFunction(MineState::explode, [=] 
		{
			for (size_t i = 0; i < Explosion.size(); i++)
			{
				Explosion[i]->ChangeAnimation(Anim::effect_explosion);

				float Deg = UEngineRandom::MainRandom.RandomFloat(0.0f, 360.0f);
				Deg *= UEngineMath::DToR;
				FVector Pos = { cosf(Deg), sinf(Deg), 0.0f };
				
				float PosScale = UEngineRandom::MainRandom.RandomFloat(0.0f, 60.0f);
				Explosion[i]->SetPosition({ PosScale * Pos.X, PosScale * Pos.Y, 0.0f });

				Explosion[i]->SetActive(true);
			}
		}
	);

	// State Update
	State.SetUpdateFunction(MineState::none, [=](float _DeltaTime) {});
	State.SetUpdateFunction(MineState::on, [=](float _DeltaTime) {});
	State.SetUpdateFunction(MineState::explode, [=](float _DeltaTime) {});

}

void AMine::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}