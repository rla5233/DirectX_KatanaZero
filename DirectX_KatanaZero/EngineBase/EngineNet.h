#pragma once
#include "EngineSerializer.h"
#include "EngineDispatcher.h"

// 설명 : 내가 뭔지는 중요하지 않다. 


class USession;
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

	// std::string _Ip 어떤 컴퓨터에 접속할거냐.
	// int _Port 그 컴퓨터에 켜져있는 어떤 프로그램에 접속할거냐.
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

	static void RecvThreadFunction(USession* _Session, UEngineNet* _Net);

	// 값형으로 쓸때만 보통 public으로 둡니다..
	UEngineDispatcher Dispatcher;

protected:
	int SessionToken = -1;

private:
	std::atomic_bool IsActiveValue = true;
};

