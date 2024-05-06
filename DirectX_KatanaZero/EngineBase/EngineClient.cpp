#include "PreCompile.h"
#include "EngineClient.h"
#include "EngineDebug.h"

UEngineClient::UEngineClient() 
{
}

UEngineClient::~UEngineClient() 
{
}

void UEngineClient::ServerOpen()
{
	MsgBoxAssert("클라이언트로 구현되어있는 인스턴스가 서버로 다시 오픈하려고 했습니다. 불가능합니다.");
}