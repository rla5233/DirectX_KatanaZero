#include "PreCompile.h"
#include "PixelColObject.h"

UPixelColObject::UPixelColObject()
{
}

UPixelColObject::~UPixelColObject()
{
}

bool UPixelColObject::IsOnGround(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	bool Result = false;

	FVector FrontBot = _Pos;
	FVector BackBot  = _Pos;

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

	FVector MapTexScale = _MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = _MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = _MapTex->GetColor(BackBot, Color8Bit::Black);

	if (ColMap::YELLOW == FB_PixelColor && ColMap::YELLOW == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsOnPlatForm(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	bool Result = false;

	FVector FrontBot = _Pos;
	FVector BackBot  = _Pos;

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

	FVector MapTexScale = _MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = _MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = _MapTex->GetColor(BackBot, Color8Bit::Black);

	if (ColMap::GREEN == FB_PixelColor && ColMap::GREEN == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsOnGP_Boundary(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject::IsOnStairs(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject::IsColWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject::IsColHeadToWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	return false;
}

bool UPixelColObject::IsColHeadToCeil(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	return false;
}
