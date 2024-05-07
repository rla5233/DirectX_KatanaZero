#pragma once
#include "Session.h"

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
	// 주소 지정
	

protected:

private:
	// ip주소도 이녀석이 관리한다.

};

