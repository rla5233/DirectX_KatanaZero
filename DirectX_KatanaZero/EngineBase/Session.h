#pragma once
#include <WinSock2.h>

// 설명 : 서버쪽 프레임워크에 가면 이 역할을 해주는 애들이 있다.
// 대부분 멀티플랫폼이다.
class USession
{
public:
	// constrcuter destructer
	USession();
	USession(SOCKET Socket);
	~USession();

	virtual void Create() = 0;
	virtual void Bind(int _Port) = 0;
	virtual void SetAdd(std::string _Ip, int _Port);

	SOCKET GetSocket()
	{
		return Socket;
	}

	SOCKADDR_IN GetAddress()
	{
		return Address;
	}

	SOCKADDR_IN& GetAddressRef()
	{
		return Address;
	}

	void Connect();


protected:
	SOCKET Socket = 0;
	SOCKADDR_IN Address = {};
	std::string IP = "127.0.0.1";
	int Port = 0;

private:
};

