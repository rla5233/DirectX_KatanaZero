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

	if (ColMap::GREEN == FB_PixelColor && ColMap::YELLOW == BB_PixelColor)
	{
		Result = true;
	}

	if (ColMap::YELLOW == FB_PixelColor && ColMap::GREEN == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsOnStairs(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
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

	IsStairsUpValue = false;

	if (ColMap::BLUE == FB_PixelColor && ColMap::BLUE != BB_PixelColor)
	{
		IsStairsUpValue = true;
		Result = true;
	}

	if (ColMap::BLUE != FB_PixelColor && ColMap::BLUE == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	bool Result = false;

	FVector FrontTop = _Pos;
	FVector FrontBot = _Pos;

	switch (_Dir)
	{
	case EEngineDir::Left:
		FrontTop += { -Top.X, Top.Y, 0.0f };
		FrontBot += { -Bot.X, Bot.Y, 0.0f };
		break;
	case EEngineDir::Right:
		FrontTop += {  Top.X, Top.Y, 0.0f };
		FrontBot += {  Bot.X, Bot.Y, 0.0f };
		break;
	}

	FVector MapTexScale = _MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;
	FrontBot.Y = MapTexScale.Y - FrontBot.Y;

	Color8Bit FT_PixelColor = _MapTex->GetColor(FrontTop, Color8Bit::Black);
	Color8Bit FB_PixelColor = _MapTex->GetColor(FrontBot, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor && ColMap::YELLOW == FB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColHeadToWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	bool Result = false;

	FVector FrontTop = _Pos;

	switch (_Dir)
	{
	case EEngineDir::Left:
		FrontTop += { -Top.X, Top.Y, 0.0f };
		break;
	case EEngineDir::Right:
		FrontTop += {  Top.X, Top.Y, 0.0f };
		break;
	}

	FVector MapTexScale = _MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;

	Color8Bit FT_PixelColor = _MapTex->GetColor(FrontTop, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor || ColMap::BLUE == FT_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColHeadToCeil(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir)
{
	bool Result = false;

	FVector FrontTop = _Pos;
	FVector BackTop  = _Pos;

	switch (_Dir)
	{
	case EEngineDir::Left:
		FrontTop += { -Top.X, Top.Y, 0.0f };
		BackTop  += {  Top.X, Top.Y, 0.0f };
		break;
	case EEngineDir::Right:
		FrontTop += {  Top.X, Top.Y, 0.0f };
		BackTop  += { -Top.X, Top.Y, 0.0f };
		break;
	}

	FVector MapTexScale = _MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;
	BackTop.Y  = MapTexScale.Y - BackTop.Y;

	Color8Bit FT_PixelColor = _MapTex->GetColor(FrontTop, Color8Bit::Black);
	Color8Bit BT_PixelColor = _MapTex->GetColor(BackTop, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor && ColMap::YELLOW == BT_PixelColor)
	{
		Result = true;
	}

	return Result;
}
