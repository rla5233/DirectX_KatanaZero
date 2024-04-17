#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

// 수정
#include "Factory_002.h"
#include "Factory_003.h"
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

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<AFactory_002>("Factory_002");
	GEngine->CreateLevel<AFactory_003>("Factory_003");
	GEngine->CreateLevel<AFactory_004>("Factory_004");
	GEngine->CreateLevel<AFactory_005>("Factory_005");
	
	//GEngine->ChangeLevel("TitleLevel");
	
	GEngine->ChangeLevel("Factory_002");

	//GEngine->ChangeLevel("Factory_003");
	
	//GEngine->ChangeLevel("Factory_004");


#ifdef DEBUG
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
