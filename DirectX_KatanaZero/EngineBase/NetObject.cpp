#include "PreCompile.h"
#include "NetObject.h"

// �� ��ū�� �ο����ټ� �ִ°� ���� �����Դϴ�.
std::atomic<int> UNetObject::CurToken = 0;

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

	_Protocol->Token = Token;

	Net->Send(_Protocol);
}
