#pragma once
#include <WinSock2.h>

// ���� : ������ �����ӿ�ũ�� ���� �� ������ ���ִ� �ֵ��� �ִ�.
// ��κ� ��Ƽ�÷����̴�.
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

