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

	void Send(UEngineSerializer& _Ser);

	void Send(void* Data, int Size);
	// �ּ� ����
	

protected:

private:
	// ip�ּҵ� �̳༮�� �����Ѵ�.

};

