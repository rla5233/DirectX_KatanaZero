#pragma once
#include "ContentsEnum.h"

// Ό³Έν :
class UContentsHelper
{
public:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();

	// delete Function
	UContentsHelper(const UContentsHelper& _Other) = delete;
	UContentsHelper(UContentsHelper&& _Other) noexcept = delete;
	UContentsHelper& operator=(const UContentsHelper& _Other) = delete;
	UContentsHelper& operator=(UContentsHelper&& _Other) noexcept = delete;

	static void ResetTimeScale();
	static void SetAbilityTimeScale();
	static void SetHitLaserTimeScale(EHitLaserType _Type);

protected:

private:

};

