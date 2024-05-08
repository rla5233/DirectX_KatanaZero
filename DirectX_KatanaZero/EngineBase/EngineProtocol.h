#pragma once
#include "EngineSerializer.h"
#include <memory>

// ���� :
class UNetObject;
class UEngineProtocol : public std::enable_shared_from_this<UEngineProtocol>
{
	friend UNetObject;

private:
	int PacketSize = 0; // ���� �������� ���ɼ� �ۿ� ����.
	int PacketType = 0; // ���� �����̴�. �׷��� int Enum�� �ɼ� ����.
	int Token = 0; // ���� ���� ��Ŷ�� �޾��� �ֵ�

public:
	template<typename PType>
	void SetType(PType _Type)
	{
		PacketType = static_cast<int>(_Type);
	}

	void SizeCal()
	{

	}
};

