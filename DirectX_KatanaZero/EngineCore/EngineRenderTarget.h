#pragma once
#include <EnginePlatform/EngineResources.h>

// ���� : �ؽ�ó�� �׸��� ������ �ٸ���?
// �ؽ�ó => �̹��� ����ü ��������� ���� HBITMAP

// ����Ÿ�� => �� �̹����� �����ϰ� �׸��� �����ϴ� ����� ���� ��. UWindowImage

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
	// �� �ؽ�ó �������� ��� ����Ҽ� �ְ� �Ұ̴ϴ�.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTVs;
	std::vector<float4> ClearColors;

	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color);

	void Setting();
};

