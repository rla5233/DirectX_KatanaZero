#include "PreCompile.h"
#include "EngineNetWindow.h"
#include <EngineBase/EngineServer.h>

UEngineNetWindow::UEngineNetWindow() 
{
	IP.resize(100);
}

UEngineNetWindow::~UEngineNetWindow() 
{
}

void UEngineNetWindow::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("ServerOpen"))
	{
		if (nullptr != ServerOpenFunction)
		{
			ServerOpenFunction();
		}
	}

	ImGui::InputText("IP", &IP[0], IP.size());
	ImGui::SameLine();
	ImGui::InputInt("PORT", &PORT);
	if (true == ImGui::Button("Connect"))
	{
		if (nullptr != ServerOpenFunction)
		{
			ClientConnectFunction(IP, PORT);
		}
	}
}
