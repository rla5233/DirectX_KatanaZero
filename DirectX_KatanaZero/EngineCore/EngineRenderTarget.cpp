#include "PreCompile.h"
#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineCore.h"

UEngineRenderTarget::UEngineRenderTarget() 
{
}

UEngineRenderTarget::~UEngineRenderTarget() 
{
}


void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVs.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}


void UEngineRenderTarget::Clear()
{
	// 다이렉트의 모든건 2가지에서
	
	// Device 메모리
	// contexts 랜더링
	
	// 어떠한 그림의 클리어 

	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}
}

void UEngineRenderTarget::Setting()
{
	// 깊이버퍼는 나중에
	GEngine->GetDirectXContext()->OMSetRenderTargets(static_cast<UINT>(RTVs.size()), &RTVs[0], nullptr);
}