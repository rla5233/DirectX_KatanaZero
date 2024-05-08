#pragma once
#include "EngineSerializer.h"

// ���� : ���� ������ �߿����� �ʴ�. 

class UEngineProtocol;
class UEngineNet
{
public:
	// constrcuter destructer
	UEngineNet();
	~UEngineNet();

	// delete Function
	UEngineNet(const UEngineNet& _Other) = delete;
	UEngineNet(UEngineNet&& _Other) noexcept = delete;
	UEngineNet& operator=(const UEngineNet& _Other) = delete;
	UEngineNet& operator=(UEngineNet&& _Other) noexcept = delete;

	//virtual void Send(UEngineSerializer& _Data);
	//virtual void Recv(UEngineSerializer& _Data);

	//virtual void Send(void* _Ptr, int _Size);
	//virtual void Recv(void* _Ptr, int _Size);

	virtual void ServerOpen(int _Port, int _BackLog)	{	}

	// std::string _Ip � ��ǻ�Ϳ� �����Ұų�.
	// int _Port �� ��ǻ�Ϳ� �����ִ� � ���α׷��� �����Ұų�.
	virtual void Connect(std::string _Ip, int _Port) {};

	std::atomic_bool& IsActive()
	{
		return IsActiveValue;
	}

	void End()
	{
		IsActiveValue = false;
	}

	virtual void Send(std::shared_ptr<UEngineProtocol> _Protocol) {};

protected:

private:
	std::atomic_bool IsActiveValue = true;
};

