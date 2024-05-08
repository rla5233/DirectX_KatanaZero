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

	void Send(UEngineSerializer& _Ser);

	void Send(void* Data, int Size);
	// 주소 지정
	

protected:

private:
	// ip주소도 이녀석이 관리한다.

};

