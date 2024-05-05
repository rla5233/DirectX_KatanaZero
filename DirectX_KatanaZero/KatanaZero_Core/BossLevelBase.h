#pragma once

// Ό³Έν :
class BossLevelBase
{
public:
	// constructor destructor
	BossLevelBase();
	~BossLevelBase();
	
	// delete Function
	BossLevelBase(const BossLevelBase& _Other) = delete;
	BossLevelBase(BossLevelBase&& _Other) noexcept = delete;
	BossLevelBase& operator=(const BossLevelBase& _Other) = delete;
	BossLevelBase& operator=(BossLevelBase&& _Other) noexcept = delete;


protected:

private:

};

