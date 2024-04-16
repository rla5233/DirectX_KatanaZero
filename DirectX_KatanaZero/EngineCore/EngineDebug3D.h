#pragma once
#include "EngineEnums.h"
#include <EngineBase/Transform.h>

// 작은 랜더러를 하나만든다고 생각하면 된다.
class DebugRenderInfo
{
	class UEngineMesh;
	class UEngineMaterial;

	std::shared_ptr<UEngineMesh> Mesh;
	std::shared_ptr<UEngineMaterial> Material;
};

class UEngineCore;
class UDebugRenderClass
{
	friend UEngineCore;
private:
	static void DebugRender();
};

namespace UEngineDebug
{

	void DebugRender(EDebugRenderType _DebugText, FTransform& _Transform);
}

