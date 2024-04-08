#include "PreCompile.h"
#include "EngineShader.h"
#include "EngineShaderResources.h"

UEngineShader::UEngineShader()
{
	Resources = std::make_shared<UEngineShaderResources>();
}

UEngineShader::~UEngineShader()
{
	if (nullptr != ErrorCodeBlob)
	{
		ErrorCodeBlob->Release();
	}

	if (nullptr != ShaderCodeBlob)
	{
		ShaderCodeBlob->Release();
	}
}



void UEngineShader::ShaderResCheck()
{
	Resources->ShaderResourcesCheck(Type, EntryName, ShaderCodeBlob);
}