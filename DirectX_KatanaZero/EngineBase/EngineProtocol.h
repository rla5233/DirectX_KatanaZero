#pragma once
#include "EngineSerializer.h"
#include <memory>

// 설명 :
class UNetObject;
class UEngineProtocol : public std::enable_shared_from_this<UEngineProtocol>
{
	friend UNetObject;

private:
	int PacketSize = 0; // 가장 마지막에 계산될수 밖에 없다.
	int PacketType = 0; // 내가 공격이다. 그래서 int Enum이 될수 없다.
	int Token = 0; // 내가 보낸 패킷을 받아할 애들

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

