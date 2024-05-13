#include "PreCompile.h"
#include "Head.h"

AHead::AHead()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Head");
	Body->SetOrder(ERenderOrder::HeadHunter);
	Body->SetAutoSize(2.0f, true);
	Body->SetupAttachment(Root);

	Body->CreateAnimation(Anim::headhunter_head_hurtfly, ImgRes::headhunter_head_hurtfly, 0.1f, true);

	Test = CreateDefaultSubObject<UCollision>("Test");
	Test->SetCollisionGroup(EColOrder::HeadHunter);
	Test->SetCollisionType(ECollisionType::Rect);
	Test->SetupAttachment(Root);

	SetRoot(Root);
}

AHead::~AHead()
{
}

void AHead::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsObject::SetActor(this);
	UPixelColObject::SetActor(this);

	FVector BodyPos = { 0.0f, 0.0f, 0.0f };
	FVector BodyScale = { 38.0f, 38.0f, 1.0f };
	SetBodyInfo(BodyPos, BodyScale);
	Test->SetScale({ 38.0f, 38.0f, 1.0f });

	StateInit();
}

void AHead::StateInit()
{
	// State Create
	State.CreateState(HeadState::hurtfly);
	State.CreateState(HeadState::hurtground);

	// State Start
	State.SetStartFunction(HeadState::hurtfly, [=] 
		{
			Body->ChangeAnimation(Anim::headhunter_head_hurtfly);
			Velocity = { 100.0f, 0.0f, 0.0f };
		}
	);

	State.SetStartFunction(HeadState::hurtground, [=] 
		{
		}
	);

	// State Update
	State.SetUpdateFunction(HeadState::hurtfly, [=](float _DeltaTime) 
		{
			// 위치 업데이트
			PosUpdate(_DeltaTime);

		}
	);
	
	State.SetUpdateFunction(HeadState::hurtground, [=](float _DeltaTime) 
		{
		}
	);

}

void AHead::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}


