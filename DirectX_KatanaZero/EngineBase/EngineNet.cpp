#include "PreCompile.h"
#include "EngineNet.h"
#include "NetStartUpHelper.h"
#include "Session.h"
#include "EngineClient.h"
#include "EngineDebug.h"
#include "EngineProtocol.h"

UEngineNet::UEngineNet() 
{
	UNetStartUpHelper::NetStartUp();
	IsActiveValue = true;
}

UEngineNet::~UEngineNet() 
{
	IsActiveValue = false;
}


void UEngineNet::RecvThreadFunction(USession* _Session, UEngineNet* _Net)
{
	UEngineSerializer Ser;
	Ser.BufferResize(1024);

	bool IsClient = false;

	if (nullptr != dynamic_cast<UEngineClient*>(_Net))
	{
		IsClient = true;
	}

	while (_Net->IsActiveValue)
	{
		int Size = recv(_Session->GetSocket(), Ser.DataCharPtr(), Ser.BufferSize(), 0);

		if (SOCKET_ERROR == Size)
		{
			return;
		}

		if (true == IsClient && false == _Session->IsTokenInit())
		{
			if (16 != Size)
			{
				MsgBoxAssert("Token 패킷에 문제가 있습니다.");
			}


			USessionTokenPacket TokenPacket;
			TokenPacket.DeSerialize(Ser);
			_Session->SetToken(TokenPacket.GetSessionToken());
			Ser.ResetWrite();
			continue;
		}

		// 클라이언트도 이제부터 정상패킷
	}
}
