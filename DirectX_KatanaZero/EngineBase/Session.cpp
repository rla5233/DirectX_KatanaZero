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
	// ���� ����
	if (Socket != 0)
	{
		closesocket(Socket);
	}
}

void USession::Create()
{
	MsgBoxAssert("���� ������ ���� �ʾҽ��ϴ�.");
	// Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void USession::Bind(int _Port)
{
	MsgBoxAssert("���� ������ ���� �ʾҽ��ϴ�.");
}

void USession::SetAdd(std::string _Ip, int _Port)
{
	Address.sin_family = AF_INET;
	Address.sin_port = htons(_Port);

	IP = _Ip;

	if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &Address.sin_addr))
	{
		MsgBoxAssert("�ּ� �Է¿� �����߽��ϴ�.");
		return;
	}

}

void USession::Connect()
{
	if (SOCKET_ERROR == connect(Socket, (const sockaddr*)&Address, sizeof(SOCKADDR_IN)))
	{
		MsgBoxAssert("Ŀ��Ʈ�� �����߽��ϴ�.");
		return;
	}
}