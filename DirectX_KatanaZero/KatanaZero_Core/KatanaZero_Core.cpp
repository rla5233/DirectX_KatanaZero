#include "PreCompile.h"
#include "KatanaZero_Core.h"

#include "TitleGameMode.h"

#include "Factory_002.h"
#include "Factory_003.h"
#include "Factory_004.h"
#include "Factory_005.h"

#include "HeadHunterLevel_Phase1.h"
#include "HeadHunterLevel_Phase2.h"
#include "EndingLevel.h"

#include "KatanaZeroDebugWindow.h"

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

#ifdef _DEBUG
	UEngineEditorGUI::CreateEditorWindow<UKatanaZeroDebugWindow>("KatanaZeroDebugWindow");
#endif // DEBUG

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<AFactory_002>("Factory_002");
	GEngine->CreateLevel<AFactory_003>("Factory_003");
	GEngine->CreateLevel<AFactory_004>("Factory_004");
	GEngine->CreateLevel<AFactory_005>("Factory_005");
	GEngine->CreateLevel<AHeadHunterLevel_Phase1>("HeadHunter_Phase1");
	GEngine->CreateLevel<AHeadHunterLevel_Phase2>("HeadHunter_Phase2");
	GEngine->CreateLevel<AEndingLevel>("Ending");

	GEngine->ChangeLevel("TitleLevel");
}
