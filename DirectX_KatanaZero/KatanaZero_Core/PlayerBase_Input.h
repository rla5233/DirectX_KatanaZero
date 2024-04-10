#pragma once

// Ό³Έν :
class PlayerBase_Input
{
public:
	// constructor destructor
	PlayerBase_Input();
	~PlayerBase_Input();
	
	// delete Function
	PlayerBase_Input(const PlayerBase_Input& _Other) = delete;
	PlayerBase_Input(PlayerBase_Input&& _Other) noexcept = delete;
	PlayerBase_Input& operator=(const PlayerBase_Input& _Other) = delete;
	PlayerBase_Input& operator=(PlayerBase_Input&& _Other) noexcept = delete;


protected:

private:

};

