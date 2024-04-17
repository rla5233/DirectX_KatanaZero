#include "PreCompile.h"
#include "RenderUnit.h"

URenderUnit::URenderUnit()
{
	Resources = std::make_shared<UEngineShaderResources>();
}

URenderUnit::~URenderUnit()
{
}

void URenderUnit::RenderingSetting()
{
	Mesh->InputAssembler1Setting();
	LayOut->Setting();

	// VertexShader
	Material->VertexShaderSetting();

	// InputAssembler2
	Mesh->InputAssembler2Setting();

	// Rasterizer
	Material->RasterizerSetting();

	// PixelShader
	Material->PixelShaderSetting();

	Material->BlendSetting();
}

void URenderUnit::Render(float _DeltaTime)
{
	// ������ ��������ϴ�.

	// ���⿡�� �̰� �ϴ� ������ �� 1���Դϴ�.
	// ���������� ������������������ ������ ���� �������ַ��� �ͻ�����
	// �� �Ʒ��� ������� ������ �ؾ߸� �������� �Ǵ°� �ƴϿ���.
	// Mesh->Setting()

	RenderingSetting();


	Resources->SettingAllShaderResources();

	// Draw
	Mesh->IndexedDraw();
}


void URenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}

	if (nullptr != Material)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::FindRes(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}

	if (nullptr != Mesh)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}

	Resources->Reset();
	ResCopy(Material->GetVertexShader().get());
	ResCopy(Material->GetPixelShader().get());

	//if (true == Resources->IsConstantBuffer("FTransform"))
	//{
	//	Resources->SettingConstantBuffer("FTransform", Transform);
	//}

	MaterialSettingEnd();

}

void URenderUnit::ResCopy(UEngineShader* _Shader)
{

	// ������� ����
	{
		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers
			= Resources->ConstantBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers
			= ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> Setter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][Setter.first] = Setter.second;
			}
		}
	}

	// �ؽ�ó ���� ����
	{
		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& RendererTexture
			= Resources->Textures;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineTextureSetter>>& ShaderTextures
			= ShaderResources->Textures;

		for (std::pair<const EShaderType, std::map<std::string, UEngineTextureSetter>> Setters : ShaderTextures)
		{
			for (std::pair<const std::string, UEngineTextureSetter> Setter : Setters.second)
			{
				RendererTexture[Setters.first][Setter.first] = Setter.second;
			}
		}
	}


	// ���÷� ���� ����
	{
		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& RendererSampler
			= Resources->Samplers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = _Shader->Resources;

		std::map<EShaderType, std::map<std::string, UEngineSamplerSetter>>& ShaderSamplers
			= ShaderResources->Samplers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineSamplerSetter>> Setters : ShaderSamplers)
		{
			for (std::pair<const std::string, UEngineSamplerSetter> Setter : Setters.second)
			{
				RendererSampler[Setters.first][Setter.first] = Setter.second;
			}
		}
	}


}

//
//void URenderUnit::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
//{
//	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
//}