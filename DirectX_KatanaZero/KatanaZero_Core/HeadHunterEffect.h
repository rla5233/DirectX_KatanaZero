#pragma once

// Ό³Έν : HeadHunter RecoverEffect
class URecoverEffect
{
public:
	void SetEffectRotationDeg(const FVector& _Deg)
	{
		Spark->SetRotationDeg(_Deg);
		Smoke->SetRotationDeg(_Deg);
	}

	void SetEffectActive(bool _Value)
	{
		Spark->SetActive(_Value);
		Smoke->SetActive(_Value);
	}

public:
	USpriteRenderer* Spark = nullptr;
	USpriteRenderer* Smoke = nullptr;
};

