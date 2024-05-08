#pragma once
#include <EngineCore/StateManager.h>
#include "RecMapCompoBase.h"

// Ό³Έν : HeadHunter Phase1 Mine
class AMine : public ARecMapCompoBase
{
	GENERATED_BODY(ARecMapCompoBase);
public:
	// constrcuter destructer
	AMine();
	~AMine();

	// delete Function
	AMine(const AMine& _Other) = delete;
	AMine(AMine&& _Other) noexcept = delete;
	AMine& operator=(const AMine& _Other) = delete;
	AMine& operator=(AMine&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void RendererInit();
	void CreateAnimation();

private:
	std::vector<USpriteRenderer*> Explosion;
	const int ExplosionNum = 5;

// FSM
private:
	void StateInit() override;

};

