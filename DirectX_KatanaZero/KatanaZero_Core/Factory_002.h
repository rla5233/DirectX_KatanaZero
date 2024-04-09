#pragma once

// 설명 : Factory 2번째 스테이지
class Factory_002
{
public:
	// constrcuter destructer
	Factory_002();
	~Factory_002();

	// delete Function
	Factory_002(const Factory_002& _Other) = delete;
	Factory_002(Factory_002&& _Other) noexcept = delete;
	Factory_002& operator=(const Factory_002& _Other) = delete;
	Factory_002& operator=(Factory_002&& _Other) noexcept = delete;

protected:

private:

};

