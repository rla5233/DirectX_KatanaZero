#pragma once

class UKatanaZero_Core : public UserCore
{
public:
	// constructor destructor
	UKatanaZero_Core();
	~UKatanaZero_Core();
	
	// delete Function
	UKatanaZero_Core(const UKatanaZero_Core& _Other) = delete;
	UKatanaZero_Core(UKatanaZero_Core&& _Other) noexcept = delete;
	UKatanaZero_Core& operator=(const UKatanaZero_Core& _Other) = delete;
	UKatanaZero_Core& operator=(UKatanaZero_Core&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:
	void ResLoad();
	void CreateRes();
};

