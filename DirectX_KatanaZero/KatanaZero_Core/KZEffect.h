#pragma once

// Ό³Έν :
class UKZEffect : public UEffect
{
public:
	// constrcuter destructer
	UKZEffect();
	~UKZEffect();

	// delete Function
	UKZEffect(const UKZEffect& _Other) = delete;
	UKZEffect(UKZEffect&& _Other) noexcept = delete;
	UKZEffect& operator=(const UKZEffect& _Other) = delete;
	UKZEffect& operator=(UKZEffect&& _Other) noexcept = delete;

	void SetTemp0(float _Value)
	{
		BaseValue.Temp0 = _Value;
	}

protected:

private:

};

