#pragma once

// ���� : Msg Ŭ����
class AMsg
{
public:
	// constrcuter destructer
	AMsg();
	~AMsg();

	// delete Function
	AMsg(const AMsg& _Other) = delete;
	AMsg(AMsg&& _Other) noexcept = delete;
	AMsg& operator=(const AMsg& _Other) = delete;
	AMsg& operator=(AMsg&& _Other) noexcept = delete;

protected:

private:

};

