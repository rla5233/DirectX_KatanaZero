#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

// ���̺귯���� release�ų� debug�ų� �̸��� ���Ƽ�
// ���� #ifdef _DEBUG�� ������ �ʿ䰡 ����.
#pragma comment (lib, "DirectXTex.lib")

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
	if (nullptr != SRV)
	{
		SRV->Release();
	}

	if (nullptr != RTV)
	{
		RTV->Release();
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::ResCreate(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ���� �ؽ�ó �޸𸮿��� �̹����� �����Ҽ� �ִ� ������ �����
	// ���̷�Ʈ���� ������ �Ϸ��� �ٺ������� 2���� ���õǾ� �ֽ��ϴ�.
	// �޸� => Device
	// ������ => Context
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�� �� ������ �����߽��ϴ�.");
		return;
	}
}

void UEngineTexture::ResLoad()
{
	// 8196 ��������?
	// �ʹ� ũ�� �ȵɼ��� �ִ�.
	UEnginePath File = GetEnginePath();

	std::string Ext = UEngineString::ToUpper(File.GetExtension());

	std::wstring wPath = UEngineString::AnsiToUniCode(File.GetFullPath());

	if (Ext == ".DDS")
	{
		// Image �̹��� �ε� �����
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("DDS ���Ϸε忡 �����߽��ϴ�.");
		};
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("TGA ���Ϸε忡 �����߽��ϴ�.");
		};
	}
	else
	{
		// Png jpg ����� else
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("PNG ���Ϸε忡 �����߽��ϴ�.");
		};
	}

	// HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	// ���� ����� ������� ���� �Լ��� �ڽ��� �ε��� �����͸� ������ ���̴� ���ҽ� �並 ����� �ְ� ó���� �����ϴ�.
	// DirectX::CreateShaderResourceView 
	if (S_OK != DirectX::CreateShaderResourceView(
		GEngine->GetDirectXDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("�ؽ�ó ���̴� ���ñ��� ������ �����߽��ϴ�" + GetName());
		return;
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);

}

void UEngineTexture::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("Ÿ���� �Һи��� �ؽ�ó �����Դϴ�.");
		break;
	}
}

