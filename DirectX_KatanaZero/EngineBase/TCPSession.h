#pragma once
#include "Session.h"

// ���� :
class UTCPSession : public USession
{
public:
	// constrcuter destructer
	UTCPSession();
	UTCPSession(SOCKET Socket);
	~UTCPSession();

	void Create() override;
	void Bind(int _Port) override;
	// �ּ� ����
	

protected:

private:
	// ip�ּҵ� �̳༮�� �����Ѵ�.

};

