#pragma once

// ���� : Factory 3��° ��������
class AFactory_003 
{
public:
	// constrcuter destructer
	AFactory_003();
	~AFactory_003();

	// delete Function
	AFactory_003(const AFactory_003& _Other) = delete;
	AFactory_003(AFactory_003&& _Other) noexcept = delete;
	AFactory_003& operator=(const AFactory_003& _Other) = delete;
	AFactory_003& operator=(AFactory_003&& _Other) noexcept = delete;

protected:

private:

};

