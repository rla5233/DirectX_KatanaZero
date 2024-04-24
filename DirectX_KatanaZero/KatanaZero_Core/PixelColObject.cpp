#include "PreCompile.h"
#include "PixelColObject.h"

#include "PlayLevelBase.h"
#include "ColMapObject.h"

UPixelColObject::UPixelColObject()
{
	
}

UPixelColObject::~UPixelColObject()
{
}

void UPixelColObject::SetBodyInfo(const FVector& _BodyPos, const FVector& _BodyScale)
{
	BodyPos = _BodyPos;
	BodyScale = _BodyScale;
}

void UPixelColObject::SetMapTex()
{
	APlayLevelBase* Level = dynamic_cast<APlayLevelBase*>(Actor->GetWorld()->GetGameMode().get());
	MapTex = Level->GetColMap()->GetMapTex();
}

bool UPixelColObject::IsOnGround(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
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

bool UPixelColObject::IsOnPlatForm(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BackBot, Color8Bit::Black);

	if (ColMap::GREEN == FB_PixelColor && ColMap::GREEN == BB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsOnGP_Boundary(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BackBot, Color8Bit::Black);

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

bool UPixelColObject::IsOnStairs(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y - 1.0f;
	BackBot.Y  = MapTexScale.Y - BackBot.Y  - 1.0f;

	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);
	Color8Bit BB_PixelColor = MapTex->GetColor(BackBot, Color8Bit::Black);

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

bool UPixelColObject::IsColWall(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;
	FrontBot.Y = MapTexScale.Y - FrontBot.Y;

	Color8Bit FT_PixelColor = MapTex->GetColor(FrontTop, Color8Bit::Black);
	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor && ColMap::YELLOW == FB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColHeadToWall(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;

	Color8Bit FT_PixelColor = MapTex->GetColor(FrontTop, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor || ColMap::BLUE == FT_PixelColor)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColHeadToCeil(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontTop.Y = MapTexScale.Y - FrontTop.Y;
	BackTop.Y  = MapTexScale.Y - BackTop.Y;

	FVector FT_Pos2 = FrontTop;
	FVector BT_Pos2 = BackTop;

	switch (_Dir)
	{
	case EEngineDir::Left:
		FT_Pos2.X += 1.0f;
		BT_Pos2.X -= 1.0f;
		break;
	case EEngineDir::Right:
		FT_Pos2.X -= 1.0f;
		BT_Pos2.X += 1.0f;
		break;
	}

	Color8Bit FT_PixelColor1 = MapTex->GetColor(FrontTop, Color8Bit::Black);
	Color8Bit FT_PixelColor2 = MapTex->GetColor(FT_Pos2, Color8Bit::Black);

	Color8Bit BT_PixelColor1 = MapTex->GetColor(BackTop, Color8Bit::Black);
	Color8Bit BT_PixelColor2 = MapTex->GetColor(BT_Pos2, Color8Bit::Black);

	if (ColMap::YELLOW == FT_PixelColor1 && ColMap::YELLOW == FT_PixelColor2)
	{
		Result = true;
	}

	if (ColMap::YELLOW == BT_PixelColor1 && ColMap::YELLOW == BT_PixelColor2)
	{
		Result = true;
	}

	return Result;
}

bool UPixelColObject::IsColBotToWall(EEngineDir _Dir)
{
	bool Result = false;

	CalFourPoint(_Dir);

	FVector MapTexScale = MapTex->GetScale();
	FrontBot.Y = MapTexScale.Y - FrontBot.Y;

	Color8Bit FB_PixelColor = MapTex->GetColor(FrontBot, Color8Bit::Black);

	if (ColMap::YELLOW == FB_PixelColor || ColMap::BLUE == FB_PixelColor)
	{
		Result = true;
	}

	return Result;
}

void UPixelColObject::OnGroundPosAdjust(EEngineDir _Dir)
{
	while (true == IsOnGround(_Dir))
	{
		Actor->AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnGround(_Dir))
		{
			Actor->AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}
}

void UPixelColObject::UpStairPosAdjust(EEngineDir _Dir)
{
	while (true == IsOnStairs(_Dir))
	{
		Actor->AddActorLocation({ 0.0f, 1.0f, 0.0f });

		if (false == IsOnStairs(_Dir))
		{
			Actor->AddActorLocation({ 0.0f, -1.0f, 0.0f });
			break;
		}
	}
}

void UPixelColObject::CalFourPoint(EEngineDir _Dir)
{
	FrontTop = Actor->GetActorLocation() + BodyPos;
	FrontBot = Actor->GetActorLocation() + BodyPos;
	BackTop  = Actor->GetActorLocation() + BodyPos;
	BackBot  = Actor->GetActorLocation() + BodyPos;

	switch (_Dir)
	{
	case EEngineDir::Left:
		FrontTop += { -BodyScale.hX(),  BodyScale.hY(), 0.0f };
		FrontBot += { -BodyScale.hX(), -BodyScale.hY(), 0.0f };
		BackTop  += {  BodyScale.hX(),  BodyScale.hY(), 0.0f };
		BackBot  += {  BodyScale.hX(), -BodyScale.hY(), 0.0f };
		break;					 
	case EEngineDir::Right:		 
		FrontTop += {  BodyScale.hX(),  BodyScale.hY(), 0.0f };
		FrontBot += {  BodyScale.hX(), -BodyScale.hY(), 0.0f };
		BackTop  += { -BodyScale.hX(),  BodyScale.hY(), 0.0f };
		BackBot  += { -BodyScale.hX(), -BodyScale.hY(), 0.0f };
		break;
	}
}