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
	// ���̷�Ʈ�� ���� 2��������
	
	// Device �޸�
	// contexts ������
	
	// ��� �׸��� Ŭ���� 

	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}
}

void UEngineRenderTarget::Setting()
{
	// ���̹��۴� ���߿�
	GEngine->GetDirectXContext()->OMSetRenderTargets(static_cast<UINT>(RTVs.size()), &RTVs[0], nullptr);
}