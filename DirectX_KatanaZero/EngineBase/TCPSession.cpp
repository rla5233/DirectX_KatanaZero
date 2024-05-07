#include "PreCompile.h"
#include "TCPSession.h"
#include "EngineDebug.h"

UTCPSession::UTCPSession() 
{
}

UTCPSession::UTCPSession(SOCKET Socket)
	: USession(Socket)
{
	
}

UTCPSession::~UTCPSession() 
{
}

void UTCPSession::Create()
{
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == Socket)
	{
		MsgBoxAssert("���� ������ �����߽��ϴ�.");
	}
}

void UTCPSession::Bind(int _Port)
{
	Port = _Port;
	Address.sin_family = AF_INET; // ip4�� ����ϰڴ�.
	Address.sin_port = htons(Port);

	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Address.sin_addr))
	{
		assert(false);
	}

	if (INVALID_SOCKET == bind(Socket, (const sockaddr*)&Address, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}

}