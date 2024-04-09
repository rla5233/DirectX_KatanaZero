#pragma once

// Ό³Έν :
class Factory_005
{
public:
	// constrcuter destructer
	Factory_005();
	~Factory_005();

	// delete Function
	Factory_005(const Factory_005& _Other) = delete;
	Factory_005(Factory_005&& _Other) noexcept = delete;
	Factory_005& operator=(const Factory_005& _Other) = delete;
	Factory_005& operator=(Factory_005&& _Other) noexcept = delete;

protected:

private:

};

