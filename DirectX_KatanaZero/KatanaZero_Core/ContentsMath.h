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

	static float LerpClampf(float p1, float p2, float d1)
	{
		if (0.0f >= d1)
		{
			d1 = 0.0f;
		}

		if (1.0f <= d1)
		{
			d1 = 1.0f;
		}

		return Lerpf(p1, p2, d1);
	}

	static float Lerpf(float p1, float p2, float d1)
	{
		return (p1 * (1.0f - d1)) + (p2 * d1);
	}

protected:

private:

};

