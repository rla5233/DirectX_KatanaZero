#pragma once
#include "EngineEnums.h"
#include <EngineBase/Transform.h>

// ���� �������� �ϳ�����ٰ� �����ϸ� �ȴ�.
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

