#pragma once
#include <EnginePlatform/EngineResources.h>

// 설명 : 텍스처랑 그리는 권한은 다르죠?
// 텍스처 => 이미지 그자체 수정기능은 없음 HBITMAP

// 랜더타겟 => 그 이미지를 편집하고 그리고 복사하는 기능을 가진 애. UWindowImage

class ULevel;
class UEngineTexture;
class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>
{
	friend ULevel;

public:
	// constrcuter destructer
	UEngineRenderTarget();
	~UEngineRenderTarget();

	// delete Function
	UEngineRenderTarget(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget(UEngineRenderTarget&& _Other) noexcept = delete;
	UEngineRenderTarget& operator=(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget& operator=(UEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineRenderTarget> Create(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
	{
		std::shared_ptr<UEngineRenderTarget> NewRes = CreateResUnName();
		NewRes->AddNewTexture(_Texture, _Color);
		return NewRes;
	}

	void Clear();

protected:

private:
	// 저 텍스처 여러개를 엮어서 사용할수 있게 할겁니다.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTVs;
	std::vector<float4> ClearColors;

	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color);

	void Setting();
};

