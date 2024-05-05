#include "PreCompile.h"
#include "MainCamera.h"

#include "PlayerBase.h"

AMainCamera::AMainCamera()
{
}

AMainCamera::~AMainCamera()
{
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	SetMainCamera();
	ULerpObject::SetActor(MainCamera);

	StateInit();
}

void AMainCamera::StateInit()
{
	// State Create
	State.CreateState(MainCameraState::stop);
	State.CreateState(MainCameraState::title_in);
	State.CreateState(MainCameraState::chaseplayer);
	State.CreateState(MainCameraState::shaking);

	// State Start
	State.SetStartFunction(MainCameraState::stop, [=] {});
	State.SetStartFunction(MainCameraState::title_in,		std::bind(&AMainCamera::TitleInStart, this));
	State.SetStartFunction(MainCameraState::chaseplayer,	std::bind(&AMainCamera::ChasePlayerStart, this));
	State.SetStartFunction(MainCameraState::shaking,		std::bind(&AMainCamera::ShakingStart, this));

	// State Update
	State.SetUpdateFunction(MainCameraState::stop, [=](float _DeltaTime) {});
	State.SetUpdateFunction(MainCameraState::title_in,		std::bind(&AMainCamera::TitleIn, this, std::placeholders::_1));
	State.SetUpdateFunction(MainCameraState::chaseplayer,	std::bind(&AMainCamera::ChasePlayer, this, std::placeholders::_1));
	State.SetUpdateFunction(MainCameraState::shaking,		std::bind(&AMainCamera::Shaking, this, std::placeholders::_1));

}

void AMainCamera::TitleInStart()
{
	FVector CameraStartPos = { 0.0f, 0.0f, -100.0f };
	FVector CameraTargetPos = { 0.0f, -360.0f, -100.0f };
	SetLerpMovePos(CameraStartPos, CameraTargetPos);
	TitleInTimeWeight = 2.0f;
}

void AMainCamera::TitleIn(float _DeltaTime)
{
	LerpMoveUpdate(_DeltaTime, TitleInTimeWeight);
	TitleInTimeWeight -= 2.0f * _DeltaTime;
}

void AMainCamera::ChasePlayerStart()
{
	ChasePlayer(0.0f);
}

void AMainCamera::ChasePlayer(float _DeltaTime)
{
	FVector CurPos = Player->GetActorLocation();
	FVector NextPos = MapRangeCheck(CurPos);
	SetActorLocation(NextPos);
}

void AMainCamera::ShakingStart()
{
	DelayCallBack(0.2f, [=]
		{
			State.ChangeState(MainCameraState::chaseplayer);
			return;
		}
	);
}

void AMainCamera::Shaking(float _DeltaTime)
{
	ChasePlayer(_DeltaTime);
	FVector CurPos = GetActorLocation();
	
	CurPos.X += UEngineRandom::MainRandom.RandomFloat(-20.0f, 20.0f);
	CurPos.Y += UEngineRandom::MainRandom.RandomFloat(-10.0f, 10.0f);

	FVector NextPos = MapRangeCheck(CurPos);
	SetActorLocation(NextPos);
}

void AMainCamera::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

FVector AMainCamera::MapRangeCheck(const FVector& _Pos)
{
	FVector Result = _Pos;

	FVector WinScale = GEngine->EngineWindow.GetWindowScale();
	FVector TexScale = MapTex->GetScale();

	if (0.0f > Result.X - WinScale.hX())
	{
		Result.X = WinScale.hX();
	}

	if (TexScale.X < Result.X + WinScale.hX())
	{
		Result.X = TexScale.X - WinScale.hX();
	}

	if (0.0f > Result.Y - WinScale.hY())
	{
		Result.Y = WinScale.hY();
	}

	if (TexScale.Y < Result.Y + WinScale.hY())
	{
		Result.Y = TexScale.Y - WinScale.hY();
	}

	Result.Z = -100.0f;

	return	Result;
}