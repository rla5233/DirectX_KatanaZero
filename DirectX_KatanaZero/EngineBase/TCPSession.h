#pragma once
#include "Session.h"
#include "EngineSerializer.h"

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

	int Send(UEngineSerializer& _Ser) override;
	int Send(void* Data, int Size) override;
	// �ּ� ����
	

protected:

private:
	// ip�ּҵ� �̳༮�� �����Ѵ�.

};

