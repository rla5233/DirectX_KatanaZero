#pragma once

class AEnemyBase;
class ARecMapCompoBase;

// ���� : �� ���� �Ŵ���
class USpawnManager
{
public:
	// constrcuter destructer
	USpawnManager();
	~USpawnManager();

	// delete Function
	USpawnManager(const USpawnManager& _Other) = delete;
	USpawnManager(USpawnManager&& _Other) noexcept = delete;
	USpawnManager& operator=(const USpawnManager& _Other) = delete;
	USpawnManager& operator=(USpawnManager&& _Other) noexcept = delete;

	// Enemy ���� �Լ� (�ʱ� ���� : Idle)
	template<typename EnemyType>
	std::shared_ptr<EnemyType> SpawnIdleEnemy(std::string_view _Name,	const FVector& _Pos, EEngineDir _Dir)
	{
		std::shared_ptr<AEnemyBase> NewEnemy = GameMode->GetWorld()->SpawnActor<EnemyType>(_Name);
		NewEnemy->SetActorLocation(_Pos);
		NewEnemy->SetBodyDir(_Dir);
		NewEnemy->StateChange("Idle");
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

	// Patrol ���� Enemy ���� �Լ�
	template<typename EnemyType>
	std::shared_ptr<EnemyType> SpawnPatrolEnemy(
		std::string_view _Name,
		const FVector& _Pos, 
		EEngineDir _Dir,
		float _WalkTime, float _StopTime,
		std::string_view _InitState)
	{
		std::shared_ptr<AEnemyBase> NewEnemy = GameMode->GetWorld()->SpawnActor<EnemyType>(_Name);
		NewEnemy->SetActorLocation(_Pos);
		NewEnemy->SetBodyDir(_Dir);
		NewEnemy->SetPatrolTime(_WalkTime, _StopTime);
		NewEnemy->StateChange(_InitState);
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

	// RecComponent ���� �Լ� (�ʱ� ���� : Idle)
	template<typename RecCompoType>
	std::shared_ptr<RecCompoType> SpawnRecComponent(std::string_view _Name, const FVector& _Pos, EEngineDir _Dir)
	{
		std::shared_ptr<ARecMapCompoBase> NewCompo= GameMode->GetWorld()->SpawnActor<RecCompoType>(_Name);
		NewCompo->SetActorLocation(_Pos);
		NewCompo->SetBodyDir(_Dir);
		NewCompo->StateChange("Idle");
		PushRecComponent(NewCompo);
		return std::dynamic_pointer_cast<RecCompoType>(NewCompo);
	}

	void CreateBoundaryCol(const FVector& _Pos, const FVector& _Scale);

protected:
	void SetGameMode(AGameMode* _GameMode)
	{
		GameMode = _GameMode;
	}

private:
	AGameMode* GameMode = nullptr;

	void PushEnemy(std::shared_ptr<AEnemyBase> _Enemy);
	void PushRecComponent(std::shared_ptr<ARecMapCompoBase> _Component);

};

