#pragma once

class AEnemyBase;
class ARecMapCompoBase;
class UStairInfo;

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

	// Enemy 스폰 함수
	template<typename EnemyType>
	std::shared_ptr<EnemyType> SpawnEnemy(
		std::string_view _Name,	
		const FVector& _Pos, 
		EEngineDir _Dir,
		std::string_view _State,
		EUpdateOrder _Order = EUpdateOrder::Enemy)
	{
		std::shared_ptr<AEnemyBase> NewEnemy = GameMode->GetWorld()->SpawnActor<EnemyType>(_Name, _Order);
		NewEnemy->SetActorLocation(_Pos);
		NewEnemy->SetBodyDir(_Dir);
		NewEnemy->StateChange(_State);
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

	// Patrol 상태 Enemy 스폰 함수
	template<typename EnemyType>
	std::shared_ptr<EnemyType> SpawnPatrolEnemy(
		std::string_view _Name,
		const FVector& _Pos, 
		EEngineDir _Dir,
		float _WalkTime, float _StopTime,
		std::string_view _PatrolState,
		EUpdateOrder _Order = EUpdateOrder::Enemy)
	{
		std::shared_ptr<AEnemyBase> NewEnemy = GameMode->GetWorld()->SpawnActor<EnemyType>(_Name, _Order);
		NewEnemy->SetActorLocation(_Pos);
		NewEnemy->SetBodyDir(_Dir);
		NewEnemy->SetPatrolTime(_WalkTime, _StopTime);
		NewEnemy->StateChange(_PatrolState);
		PushEnemy(NewEnemy);
		return std::dynamic_pointer_cast<EnemyType>(NewEnemy);
	}

	// RecComponent 스폰 함수
	template<typename RecCompoType>
	std::shared_ptr<RecCompoType> SpawnRecComponent(
		std::string_view _Name, 
		const FVector& _Pos, 
		EEngineDir _Dir, 
		std::string_view _State,
		EUpdateOrder _Order = EUpdateOrder::RecComponent)
	{
		std::shared_ptr<ARecMapCompoBase> NewCompo = GameMode->GetWorld()->SpawnActor<RecCompoType>(_Name, _Order);
		NewCompo->SetActorLocation(_Pos);
		NewCompo->SetBodyDir(_Dir);
		NewCompo->StateChange(_State);
		PushRecComponent(NewCompo);
		return std::dynamic_pointer_cast<RecCompoType>(NewCompo);
	}

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

