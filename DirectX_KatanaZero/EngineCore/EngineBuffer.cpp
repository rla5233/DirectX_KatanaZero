#include "PreCompile.h"
#include "EngineBuffer.h"

UEngineBuffer::UEngineBuffer()
{
}

UEngineBuffer::~UEngineBuffer()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
	}
}

