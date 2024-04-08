#pragma once
#include <map>
#include <string>
#include <memory>
#include <list>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineResources.h>

// #include�� �̷��� ����ϴ��� ������ �� �ڵ尡 ������� ������
// �����Ϸ��� �����Ѵ�.
#include "ThirdParty\DirectXTex\inc\DirectXTex.h"


#include "EngineSampler.h"

class UEngineTextureSetter;
class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	friend UEngineTextureSetter;
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->ResCreate(_Texture);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}


	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

protected:


private:

	// �̹��� �� ��ü.
	// Directx������ �޸𸮸� �ǹ��ϴ� �ڵ�
	// �׸��� �׷� �޸𸮰� �־�� �޸� ��������
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx������ �̹���(�޸�) ���� ����(���⿡ �׸��� �ִ� ����)
	ID3D11RenderTargetView* RTV = nullptr;
	// directx���� �̹����� ���̴��� �����Ҽ� �ִ� ����.
	ID3D11ShaderResourceView* SRV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	std::shared_ptr<UEngineSampler> Sampler;

	void ResCreate(ID3D11Texture2D* _Texture);

	void ResLoad();

	void CreateRenderTargetView();

	void Setting(EShaderType _Type, UINT _Slot);
};

