#include "PreCompile.h"
#include "EngineCore.h"
#include "EngineGraphicDevice.h"

#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineTexture.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineBlend.h"
#include "EngineMaterial.h"
#include "EngineSprite.h"

#include "EngineRenderTarget.h"

void UEngineGraphicDevice::EngineResourcesRelease()
{
	// 어차피 자동으로 지워지는 리소스들을 왜 굳이 여기서 클리어를 직접 해주지?
	// 엔진이 종료되는 시점에 텍스처를 모두다 삭제한다.

	UEngineSound::ResourcesRelease();
	UEngineSprite::ResourcesRelease();
	UEngineRenderTarget::ResourcesRelease();
	UEngineTexture::ResourcesRelease();


	// Mesh
	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();

	// 머티리얼
	UEngineVertexShader::ResourcesRelease();
	UEnginePixelShader::ResourcesRelease();
	UEngineRasterizer::ResourcesRelease();
	UEngineBlend::ResourcesRelease();


	UEngineMaterial::ResourcesRelease();
}

// 인풋어셈블러 1과 인풋어셈블러 2의 리소스들을 만들어내는 이니셜라이즈
void MeshInit()
{
	FEngineVertex::Info.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	FEngineVertex::Info.AddInputLayOut("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);

		{
			// 00   10
			// 0    1
			// 01   11
			// 3    2

			VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f, 1.0f} };
			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);
		}

		// 삼각형을 어떻게 그릴지에 대한 순서.
		std::vector<UINT> IndexData = { 0, 1, 2, 0, 2, 3 };

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");

		{
			VertexData[0] = { {-1.0f, 1.0f, 0.0f, 1.0f} , {0.0f, 0.0f} };
			VertexData[1] = { {1.0f, 1.0f, 0.0f, 1.0f} , {1.0f, 0.0f} };
			VertexData[2] = { {1.0f, -1.0f, 0.0f, 1.0f}, {1.0f, 1.0f} };
			VertexData[3] = { {-1.0f, -1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} };
			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("FullRect", VertexData);
		}

		UEngineMesh::Create("FullRect", "FullRect", "Rect");
	}

	// 인풋레이아웃 정보
	// GEngine->GetDirectXDevice()->CreateInputLayout()


}

// 픽셀 및 버텍스쉐이더를 이니셜라이즈
void ShaderInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineShader");
	UEngineShader::AutoCompile(Dir);
}

void SettingInit()
{
		//D3D11_FILL_MODE FillMode;
		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;

	{
		D3D11_RASTERIZER_DESC Desc = {};

		// 면으로 그려라
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		// 선으로 그려라.
		// Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

		// 앞면이건 뒷면이건 다 그려라.
		// 우리 외적으로 앞
		// 앞면 그리지마

		// Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		// 뒷면 그리지마
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// 앞면과 뒷면
		// 시계방향이면 뒷면으로 봅니다.

		Desc.AntialiasedLineEnable = TRUE;
		Desc.DepthClipEnable = TRUE;

		// 레스터라이저 세팅
		UEngineRasterizer::Create("EngineBase", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.AntialiasedLineEnable = TRUE;
		Desc.DepthClipEnable = TRUE;
		UEngineRasterizer::Create("Debug", Desc);
	}


	{
		D3D11_SAMPLER_DESC Desc = {};

		// 옵션바꾸면서 설명드리겠습니다.
		// 가로
		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

		// MIP MAP
		// MIN_MAG_MIP 나보다 클때든 작을때는 
		// MIP 나보다 작을때
		// MAG 나보다 클때
		// MIN 확대할때
		// 언제나 POINT로 샘플링히라
		// POINT 보간을 하지 않고 색깔을 추출해라.
		// Liner 는 보간을 하고 추출해라.
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;

		// 밉맵의 개념에 대해서 이해해야한다.
		Desc.MipLODBias = 0.0f; // 보간하지 않는다.
		Desc.MaxAnisotropy = 1;
		// 특정 값의 비교를 통해서 색깔을 출력해야할때 여러곳에서 사용되는 옵션인데.
		// 이건 그냥 무조건 비교하지 말고 출력해라.
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;

		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		// 필터

		UEngineSampler::Create("POINT", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};

		Desc.AddressW = Desc.AddressV = Desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.MipLODBias = 0.0f; // 보간하지 않는다.
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;
		UEngineSampler::Create("LINEAR", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = {};

		// true 투명처리가 투명이 될것인데.
		// 이게 연산량이 높아서 false로 처리할 겁니다.
		// directx의 기본공식으로 처리하는데 아무
		Desc.AlphaToCoverageEnable = false;

		// SV_Target0 0번타겟에 출력하겠다.
		// false == 0번세팅으로 모두 통일
		// true == 각기 넣어준 세팅 0번세팅으로 모두 통일
		Desc.IndependentBlendEnable = false;

		// float4 DestColor = 0011;
		// float4 SrcColor = 0000;
		
		// float4 DestFilter = 0011;
		// float4 SrcFilter = 0000;
		// Result = DestColor * DestFilter (+) SrcColor * SrcFilter;

		// D3D11_BLEND_OP_ADD             +
		// D3D11_BLEND_OP_SUBTRACT        -


		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// Result = DestColor * DestFilter (+) SrcColor * SrcFilter;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		// Result = DestColor * DestFilter (+) SrcColor * (SrcFilter);
		// SRCColor = 000(0)
		// 1110 * 0000 = 0000
		// SrcFilter = 0000
		// 
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

		// DestColor = 001(1)
		// SRCColor = 000(1)
		// DestFilter =  1 - 1
		// DestColor *DestFilter ; 
		
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		//              D3D11_BLEND_INV_SRC_ALP                      D3D11_BLEND_SRC_ALPHA
		// 0011    *       0000             +      100(0.5) *        1111
		// (0011 * 0. 5 0.5 0.5 0.5 ) + (1001 * 0.5 0.5 0.5 0.5 ) => 1001

		//      R   G    B   A
		//      0   0   0.5  1
		//  +   0.5 0    0   1
		//      0.5 0   0.5  2


		UEngineBlend::Create("EngineBase", Desc);
	}


	{
		D3D11_BLEND_DESC Desc = {};
		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		UEngineBlend::Create("Overlay", Desc);
	}


}

void MaterialInit()
{

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
		Mat->SetPixelShader("ImageShader.fx");
		Mat->SetVertexShader("ImageShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Debug");
		Mat->SetPixelShader("DebugShader.fx");
		Mat->SetVertexShader("DebugShader.fx");
		Mat->SetRasterizer("Debug");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TargetCopy");
		Mat->SetPixelShader("TargetCopyShader.fx");
		Mat->SetVertexShader("TargetCopyShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Blur");
		Mat->SetPixelShader("BlurEffectShader.fx");
		Mat->SetVertexShader("BlurEffectShader.fx");
	}


}

void EngineTextureInit()
{
	{
		// 파일의 헤더
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("EngineResources");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineTexture::Load(File.GetFullPath());
		}
	}

}

// 엔진에서 박스하나도 지원안해주면 
void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit();
	ShaderInit();
	SettingInit();
	MaterialInit();
	EngineTextureInit();

	UEngineRenderTarget::RenderTargetInit();
}