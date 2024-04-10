#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase Input
bool APlayerBase::IsRunInputStart()
{
	bool Result = false;

	if (true == IsDown('A') || true == IsDown(VK_LEFT))
	{
		Renderer->SetDir(EEngineDir::Left);
		Result = true;
	}

	if (true == IsDown('D') || true == IsDown(VK_RIGHT))
	{
		Renderer->SetDir(EEngineDir::Right);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsRunInputPress()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsRunDirChange()
{
	bool Result = false;
	EEngineDir Dir = Renderer->GetDir();

	if ((EEngineDir::Left == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		Renderer->SetDir(EEngineDir::Right);
		Result = true;
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('A') || true == IsPress(VK_LEFT)))
	{
		Renderer->SetDir(EEngineDir::Left);
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchInputStart()
{
	bool Result = false;

	if (true == IsDown('S') || true == IsDown(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchInputPress()
{
	bool Result = false;

	if (true == IsPress('S') || true == IsPress(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsRollInputStart()
{
	bool Result = false;




	return Result;
}

bool APlayerBase::IsJumpInputStart()
{
	bool Result = false;

	if (true == IsDown('W') || true == IsDown(VK_UP))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsJumpInputPress()
{
	bool Result = false;

	if (true == IsPress('W') || true == IsPress(VK_UP))
	{
		Result = true;
	}

	return Result;
}