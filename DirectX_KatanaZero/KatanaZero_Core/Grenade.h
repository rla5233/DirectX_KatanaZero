#pragma once

// Ό³Έν :
class Grenade
{
public:
	// constrcuter destructer
	Grenade();
	~Grenade();

	// delete Function
	Grenade(const Grenade& _Other) = delete;
	Grenade(Grenade&& _Other) noexcept = delete;
	Grenade& operator=(const Grenade& _Other) = delete;
	Grenade& operator=(Grenade&& _Other) noexcept = delete;

protected:

private:

};

