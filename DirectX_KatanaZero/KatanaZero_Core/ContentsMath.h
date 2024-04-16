#pragma once

// Ό³Έν :
class UContentsMath
{
public:
	// constrcuter destructer
	UContentsMath();
	~UContentsMath();

	// delete Function
	UContentsMath(const UContentsMath& _Other) = delete;
	UContentsMath(UContentsMath&& _Other) noexcept = delete;
	UContentsMath& operator=(const UContentsMath& _Other) = delete;
	UContentsMath& operator=(UContentsMath&& _Other) noexcept = delete;

public:
	static float GetAngleToX_2D(const FVector& _Dir);
	static float GetVectorNorm(const FVector& _Vec);

protected:

private:

};

