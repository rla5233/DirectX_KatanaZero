#include "PreCompile.h"
#include "PixelColObject_Base.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"

UPixelColObject_Base::UPixelColObject_Base()
{
}

UPixelColObject_Base::~UPixelColObject_Base()
{
}

void UPixelColObject_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UPixelColObject_Base::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

bool UPixelColObject_Base::IsOnGround(EEngineDir _Dir)
{
	bool Result = false;

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(GetWorld()->GetGameMode().get());

	std::shared_ptr<UEngineTexture> MapTex = PlayLevel->GetColMap()->GetMapTex();
	FVector MapTexScale = MapTex->GetScale();

	FVector FrontBot = GetActorLocation();
	FVector BackBot  = GetActorLocation();

	switch (_Dir)
	{
	case EEngineDir::Left:
		FrontBot += { -Bot.X, Bot.Y, 0.0f };
		BackBot  += {  Bot.X, Bot.Y, 0.0f };
		break;
	case EEngineDir::Right:
		FrontBot += {  Bot.X, Bot.Y, 0.0f };
		BackBot  += { -Bot.X, Bot.Y, 0.0f };
		break;
	}

	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BackBot, Color8Bit::Black);

	if (ColMap::YELLOW == FB_PixelColor && ColMap::YELLOW == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject_Base::IsOnPlatForm(EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject_Base::IsOnGP_Boundary(EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject_Base::IsOnStairs(EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject_Base::IsColWall(EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject_Base::IsColHeadToWall(EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject_Base::IsColHeadToCeil(EEngineDir _Dir)
{
	return false;
}

