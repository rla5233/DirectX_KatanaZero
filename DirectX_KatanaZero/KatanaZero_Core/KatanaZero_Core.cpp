#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

// ¼öÁ¤
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
	CreateRes();

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<AFactory_002>("Factory_002");
	GEngine->CreateLevel<AFactory_003>("Factory_003");
	GEngine->CreateLevel<AFactory_004>("Factory_004");
	GEngine->CreateLevel<AFactory_005>("Factory_005");
	
	GEngine->ChangeLevel("TitleLevel");
	
	GEngine->ChangeLevel("Factory_002");

	//GEngine->ChangeLevel("Factory_003");
	
	//GEngine->ChangeLevel("Factory_004");
	
	//GEngine->ChangeLevel("Factory_005");


#ifdef DEBUG
	GEngine->CreateLevel<AHeadHunter_Phase1>("HeadHunter_Phase1");
	GEngine->ChangeLevel("HeadHunter_Phase1");

	GEngine->CreateLevel<AHeadHunter_Phase2>("HeadHunter_Phase2");
	GEngine->ChangeLevel("HeadHunter_Phase2");


#endif // DEBUG
}
