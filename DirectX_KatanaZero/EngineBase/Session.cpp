#include "PreCompile.h"
#include "Session.h"
#include "EngineDebug.h"

USession::USession() 
{
}

USession::USession(SOCKET Socket)
{
}

USession::~USession() 
{
	// 연결 끊기
	if (Socket != 0)
	{
		closesocket(Socket);
	}
}

void USession::Create()
{
	MsgBoxAssert("세션 구현이 되지 않았습니다.");
	// Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void USession::Bind(int _Port)
{
	MsgBoxAssert("세션 구현이 되지 않았습니다.");
}

void USession::SetAdd(std::string _Ip, int _Port)
{
	Address.sin_family = AF_INET;
	Address.sin_port = htons(_Port);

	IP = _Ip;

	if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &Address.sin_addr))
	{
		MsgBoxAssert("주소 입력에 실패했습니다.");
		return;
	}

}

void USession::Connect()
{
	if (SOCKET_ERROR == connect(Socket, (const sockaddr*)&Address, sizeof(SOCKADDR_IN)))
	{
		MsgBoxAssert("커넥트에 실패했습니다.");
		return;
	}
}