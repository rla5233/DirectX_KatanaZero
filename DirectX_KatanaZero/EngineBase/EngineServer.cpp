#include "PreCompile.h"
#include "EngineServer.h"

UEngineServer::UEngineServer() 
{
}

UEngineServer::~UEngineServer() 
{
}

void UEngineServer::ServerOpen(int _Port, int _BackLog /*= 512*/)
{
	Port = _Port;

	SOCKADDR_IN Add = {};
	Add.sin_family = AF_INET; // ip4를 사용하겠다.
	Add.sin_port = htons(Port);

	if (SOCKET_ERROR == inet_pton(AF_INET, "0.0.0.0", &Add.sin_addr))
	{
		assert(false);
	}

	SOCKET AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (INVALID_SOCKET == AcceptSocket)
	{
		assert(false);
	}

	if (INVALID_SOCKET == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}

	int BackLog = 1;
	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}
}