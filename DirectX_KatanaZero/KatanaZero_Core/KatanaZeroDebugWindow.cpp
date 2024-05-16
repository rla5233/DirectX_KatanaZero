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
