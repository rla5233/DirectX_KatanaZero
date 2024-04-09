#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

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

}
