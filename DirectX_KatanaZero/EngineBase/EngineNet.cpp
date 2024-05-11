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

	UEngineDispatcher& Dis = _Net->Dispatcher;

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

		Ser.SetWriteOffset(Size);

		// �츰 16����Ʈ�� ���� ���� ������ �ƹ��� �ǹ̰� ���⶧��
		// ������ 16����Ʈ �̻��� ���������� ����Ѵ�.
		if (16 > Ser.GetWriteOffset())
		{
			continue;
		}

		UEngineProtocol Protocol;
		Protocol.DeSerialize(Ser);

		if (Protocol.GetPacketType() == -2)
		{
			_Session->TokenInitOn();
			_Session->SetToken(Protocol.GetSessionToken());
			if (true == IsClient)
			{
				// Ŭ���̾�Ʈ �϶��� ����
				_Session->Send(Protocol);
			}
			Ser.Reset();
			continue;
		}

		if (Protocol.GetPacketType() == -2)
		{
			MsgBoxAssert("���ѹ��� ��ȯ�Ǿ���� ��ū��Ŷ�� �� ��ȯ�Ǿ����ϴ�.");
		}

		Ser.ResetRead();

		std::shared_ptr<UEngineProtocol> Protocal = Dis.ConvertProtocol(Protocol.GetPacketType(), Ser);
		Dis.ProcessPacket(Protocal);


		Ser.Reset();
	}
}
