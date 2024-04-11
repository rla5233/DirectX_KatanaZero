#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase Input
bool APlayerBase::IsRunInputDown()
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

		if (true == IsPress('D') || true == IsPress(VK_RIGHT))
		{
			Result = false;
		}
	}

	if ((EEngineDir::Right == Dir) && (true == IsPress('D') || true == IsPress(VK_RIGHT)))
	{
		Result = true;

		if (true == IsPress('A') || true == IsPress(VK_LEFT))
		{
			Result = false;
		}
	}

	return Result;
}

bool APlayerBase::IsCrouchInputDown()
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

bool APlayerBase::IsRunToRollInputDown()
{
	bool Result = false;

	if (true == IsDown('S') || true == IsDown(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchToRollInputDown()
{
	bool Result = false;

	if (true == IsDown('D') || true == IsDown(VK_RIGHT))
	{
		Result = true;
	}

	if (true == IsDown('A') || true == IsDown(VK_LEFT))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsCrouchToRollInputPress()
{
	bool Result = false;

	if (true == IsPress('D') || true == IsPress(VK_RIGHT))
	{
		Result = true;
	}

	if (true == IsPress('A') || true == IsPress(VK_LEFT))
	{
		Result = true;
	}

	return Result;
}

bool APlayerBase::IsJumpInputDown()
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

bool APlayerBase::IsFallInputPress()
{
	bool Result = false;

	if (true == IsPress('S') || true == IsPress(VK_DOWN))
	{
		Result = true;
	}

	return Result;
}
