#include "PreCompile.h"
#include "KatanaZero_Core.h"

void UKatanaZero_Core::CreateRes()
{
	// Material ����
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("GrayScale");
		Mat->SetPixelShader("GrayScaleEffectShader.fx");
		Mat->SetVertexShader("GrayScaleEffectShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Wave");
		Mat->SetPixelShader("WaveEffectShader.fx");
		Mat->SetVertexShader("WaveEffectShader.fx");
	}
}

void UKatanaZero_Core::ResLoad()
{
	// Shader ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Shader");
		UEngineShader::AutoCompile(Dir);
	}

	// Player ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("Player");

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// Enemy ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("Enemy");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// Enemy ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("Component");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// UI ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("UI");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// Effect ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("Effect");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// TitleLevel ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("TitleLevel");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// FactoryLevel ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("FactoryLevel");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// HeadHunterLevel ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("HeadHunterLevel");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// EndingLevel ���ҽ� �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("EndingLevel");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// Sound �ε�
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZero_Resources");
		Dir.Move("Sound");
		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".wav", ".mp3", ".ogg" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSound::Load(File.GetFullPath());
		}
	}
}