#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

// 수정
#include "Factory_001.h"
#include "Factory_002.h"
#include "Factory_004.h"
#include "Factory_005.h"

#include "HeadHunter_Phase1.h"
#include "HeadHunter_Phase2.h"

//#define DEBUG

UKatanaZero_Core::UKatanaZero_Core()
{
}

UKatanaZero_Core::~UKatanaZero_Core()
{
}

void UKatanaZero_Core::Initialize()
{
	ResLoad();

	//GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	//GEngine->ChangeLevel("TitleLevel");

	GEngine->CreateLevel<AFactory_001>("Factory_001");
	GEngine->ChangeLevel("Factory_001");

#ifdef DEBUG
	GEngine->CreateLevel<AFactory_004>("Factory_004");
	GEngine->ChangeLevel("Factory_004");

	GEngine->CreateLevel<AFactory_005>("Factory_005");
	GEngine->ChangeLevel("Factory_005");

	GEngine->CreateLevel<AHeadHunter_Phase1>("HeadHunter_Phase1");
	GEngine->ChangeLevel("HeadHunter_Phase1");

	GEngine->CreateLevel<AHeadHunter_Phase2>("HeadHunter_Phase2");
	GEngine->ChangeLevel("HeadHunter_Phase2");
#endif // DEBUG
}

void UKatanaZero_Core::ResLoad()
{
	// Player 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
		Dir.Move("Player");

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}
	
	// Enemy 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

	// UI 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

	// Effect 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

	// TitleLevel 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

	// FactoryLevel 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

	// HeadHunterLevel 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("KatanaZeroResources");
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

}
