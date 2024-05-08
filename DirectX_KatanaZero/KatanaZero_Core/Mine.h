#pragma once
#include <EngineCore/StateManager.h>

// Ό³Έν : HeadHunter Phase1 Mine
class AMine : public AActor
{
	GENERATED_BODY(AActor);
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



// FSM
private:
	UStateManager State;
	void StateInit();

};

