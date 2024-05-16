#include "PreCompile.h"
#include "KatanaZeroDebugWindow.h"

#include "PlayLevelBase.h"
#include "DefaultPlayer.h"

UKatanaZeroDebugWindow::UKatanaZeroDebugWindow()
{
}

UKatanaZeroDebugWindow::~UKatanaZeroDebugWindow()
{
}

void UKatanaZeroDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("TitleLevel"))
	{
		GEngine->ChangeLevel("TitleLevel");
	}

	if (true == ImGui::Button("Factory_001"))
	{
		GEngine->ChangeLevel("Factory_002");
	}

	if (true == ImGui::Button("Factory_002"))
	{
		GEngine->ChangeLevel("Factory_003");
	}

	if (true == ImGui::Button("Factory_003"))
	{
		GEngine->ChangeLevel("Factory_004");
	}

	if (true == ImGui::Button("Factory_004"))
	{
		GEngine->ChangeLevel("Factory_005");
	}

	if (true == ImGui::Button("Boss_Phase1"))
	{
		GEngine->ChangeLevel("HeadHunter_Phase1");
	}

	if (true == ImGui::Button("Boss_Phase2"))
	{
		GEngine->ChangeLevel("HeadHunter_Phase2");
	}

	APlayLevelBase* PlayLevel = dynamic_cast<APlayLevelBase*>(Level->GetGameMode().get());
	if (nullptr != PlayLevel)
	{
		if (true == ImGui::Button("CheatMode"))
		{
			PlayLevel->GetDefaultPlayer()->SwitchCheatMode();
		}

		{
			std::string Msg = std::format("CheatMode : {}\n", PlayLevel->GetDefaultPlayer()->IsCheatMode());
			UEngineDebugMsgWindow::PushMsg(Msg);
		}
	}
}
