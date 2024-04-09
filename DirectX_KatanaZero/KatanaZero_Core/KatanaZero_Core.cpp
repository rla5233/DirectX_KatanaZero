#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

// ¼öÁ¤
#include "Factory_001.h"
#include "Factory_002.h"
#include "Factory_004.h"
#include "Factory_005.h"

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
	GEngine->ChangeLevel("TitleLevel");

	GEngine->CreateLevel<AFactory_001>("Factory_001");
	GEngine->ChangeLevel("Factory_001");

	GEngine->CreateLevel<AFactory_004>("Factory_004");
	GEngine->ChangeLevel("Factory_004");

	GEngine->CreateLevel<AFactory_005>("Factory_005");
	GEngine->ChangeLevel("Factory_005");
}

void UKatanaZero_Core::ResLoad()
{
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
}
