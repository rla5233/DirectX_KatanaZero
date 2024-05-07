#include "PreCompile.h"
#include "EngineClient.h"
#include "EngineDebug.h"

UEngineClient::UEngineClient() 
{
}

UEngineClient::~UEngineClient() 
{
}

void UEngineClient::ServerOpen(int _Port, int _BackLog)
{
	MsgBoxAssert("Ŭ���̾�Ʈ�� �����Ǿ��ִ� �ν��Ͻ��� ������ �ٽ� �����Ϸ��� �߽��ϴ�. �Ұ����մϴ�.");
}

void UEngineClient::Connect(std::string _Ip, int _Port)
{
	Session.Create();
	Session.SetAdd(_Ip, _Port);
	Session.Connect();
}