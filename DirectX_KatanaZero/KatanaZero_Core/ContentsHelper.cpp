#include "PreCompile.h"
#include "ContentsHelper.h"

UContentsHelper::UContentsHelper()
{
}

UContentsHelper::~UContentsHelper()
{
}

void UContentsHelper::ResetTimeScale()
{
	GEngine->SetOrderTimeScale(EUpdateOrder::Player, 1.0f);
	GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, 1.0f);
	GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, 1.0f);
	GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, 1.0f);
	GEngine->SetOrderTimeScale(EUpdateOrder::Fan, 1.0f);
}

void UContentsHelper::SetAbilityTimeScale()
{
	float TimeScale = Const::player_ability_timescale;
	GEngine->SetOrderTimeScale(EUpdateOrder::Player, TimeScale);
	GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, TimeScale);
	GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, TimeScale);
	GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, TimeScale);
	GEngine->SetOrderTimeScale(EUpdateOrder::Fan, 0.05f);
}

void UContentsHelper::SetHitLaserTimeScale(EHitLaserType _Type)
{
	float TimeScale = Const::effect_hit_laser_dealy;

	switch (_Type)
	{
	case EHitLaserType::Default:
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Fan, TimeScale);
		break;
	case EHitLaserType::HeadHunterDash:
		GEngine->SetOrderTimeScale(EUpdateOrder::Player, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Enemy, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::HeadHunter, 0.0f);
		GEngine->SetOrderTimeScale(EUpdateOrder::RecComponent, TimeScale);
		GEngine->SetOrderTimeScale(EUpdateOrder::Fan, TimeScale);
		break;
	}
}