#pragma once

// Ό³Έν :
class AEnemyBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AEnemyBase();
	~AEnemyBase();

	// delete Function
	AEnemyBase(const AEnemyBase& _Other) = delete;
	AEnemyBase(AEnemyBase&& _Other) noexcept = delete;
	AEnemyBase& operator=(const AEnemyBase& _Other) = delete;
	AEnemyBase& operator=(AEnemyBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

