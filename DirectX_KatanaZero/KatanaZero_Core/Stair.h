#pragma once

// 설명 : 계단 역할 Actor
class AStair : public AActor
{
	GENERATED_BODY(AActor);
public:
	// constructor destructor
	AStair();
	~AStair();
	
	// delete Function
	AStair(const AStair& _Other) = delete;
	AStair(AStair&& _Other) noexcept = delete;
	AStair& operator=(const AStair& _Other) = delete;
	AStair& operator=(AStair&& _Other) noexcept = delete;

	void SetStairType(EStairType _StairType)
	{
		StairType = _StairType;
	}

	EStairType GetStairType() const
	{
		return StairType;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* BodyCol = nullptr;
	EStairType StairType = EStairType::None;

};

