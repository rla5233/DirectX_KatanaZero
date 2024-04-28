#pragma once

// Ό³Έν :
class Stair
{
public:
	// constructor destructor
	Stair();
	~Stair();
	
	// delete Function
	Stair(const Stair& _Other) = delete;
	Stair(Stair&& _Other) noexcept = delete;
	Stair& operator=(const Stair& _Other) = delete;
	Stair& operator=(Stair&& _Other) noexcept = delete;


protected:

private:

};

