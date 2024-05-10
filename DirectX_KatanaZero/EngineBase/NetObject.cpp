#include "PreCompile.h"
#include "NetObject.h"

// 이 토큰을 부여해줄수 있는건 보통 서버입니다.
std::atomic<int> UNetObject::CurObjectToken = 0;

UNetObject::UNetObject() 
{
}

UNetObject::~UNetObject() 
{
}


void UNetObject::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	if (nullptr == Net)
	{
		return;
	}

	_Protocol->ObjectToken = Token;

	Net->Send(_Protocol);
}
