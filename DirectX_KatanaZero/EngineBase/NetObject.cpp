#include "PreCompile.h"
#include "NetObject.h"

// �� ��ū�� �ο����ټ� �ִ°� ���� �����Դϴ�.
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
