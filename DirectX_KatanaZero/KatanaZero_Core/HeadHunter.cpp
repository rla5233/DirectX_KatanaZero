#include "PreCompile.h"
#include "HeadHunter.h"

AHeadHunter::AHeadHunter()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("HeadHunter_Body");
	Body->SetupAttachment(Root);

	SetRoot(Root);
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
	StateInit();
}

void AHeadHunter::RendererInit()
{
	Body->SetOrder(ERenderOrder::HeadHunter);
	Body->SetAutoSize(2.0f, true);
	Body->SetPivot(EPivot::BOT);
}

void AHeadHunter::CollisionInit()
{
}

void AHeadHunter::CreateAnimation()
{
	Body->CreateAnimation(Anim::headhunter_idle, ImgRes::headhunter_idle, 0.1f, true);

}

void AHeadHunter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
