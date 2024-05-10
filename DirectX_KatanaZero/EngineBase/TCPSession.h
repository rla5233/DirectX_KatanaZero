#pragma once
#include "Session.h"
#include "EngineSerializer.h"

// 설명 :
class UTCPSession : public USession
{
public:
	// constrcuter destructer
	UTCPSession();
	UTCPSession(SOCKET Socket);
	~UTCPSession();

	void Create() override;
	void Bind(int _Port) override;

	int Send(UEngineSerializer& _Ser) override;
	int Send(void* Data, int Size) override;
	// 주소 지정
	

protected:

private:
	// ip주소도 이녀석이 관리한다.

};

