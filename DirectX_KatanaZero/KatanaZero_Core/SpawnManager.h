#pragma once

class APlayLevelBase;
class AEnemyBase;

// 설명 : 적 스폰 매니저
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

	template<typename EnemyType>
	std::shared_ptr<EnemyType> SpawnIdleEnemy(std::string_view _Name,	const FVector& _Pos, EEngineDir _Dir)
	{
		std::shared_ptr<AEnemyBase> NewEnemy = GameMode->GetWorld()->SpawnActor<EnemyType>(_Name);
		NewEnemy->SetActorLocation(_Pos);
		NewEnemy->SetRendererDir(_Dir);
		NewEnemy->StateChange("Idle");
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

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
		NewEnemy->SetRendererDir(_Dir);
		NewEnemy->SetPatrolTime(_WalkTime, _StopTime);
		NewEnemy->StateChange(_InitState);
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

protected:
	void SetGameMode(AGameMode* _GameMode)
	{
		GameMode = _GameMode;
	}

private:
	AGameMode* GameMode = nullptr;

	void PushEnemy(std::shared_ptr<AEnemyBase> _Enemy);

};

