#include "PreCompile.h"
#include "EngineDebugMsgWindow.h"

std::vector<std::string> UEngineDebugMsgWindow::Msg;

UEngineDebugMsgWindow::UEngineDebugMsgWindow() 
{
}

UEngineDebugMsgWindow::~UEngineDebugMsgWindow() 
{
}

void UEngineDebugMsgWindow::Init()
{
	
}

void UEngineDebugMsgWindow::PushMsg(std::string_view _Msg)
{
	Msg.push_back(_Msg.data());
}

void UEngineDebugMsgWindow::OnGui(float _Delta)
{
	// imgui�� ������ �޼����� �̿��Ѵ�.
	// ���� ���ο� �ϰ� ������ ġ�� �ȴ�.
	for (size_t i = 0; i < Msg.size(); i++)
	{
		ImGui::Text(Msg[i].c_str());
	}

	Msg.clear();
}