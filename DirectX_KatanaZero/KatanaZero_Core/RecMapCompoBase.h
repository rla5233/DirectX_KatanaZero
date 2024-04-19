#pragma once
#include <EngineCore/StateManager.h>

#include "RecordingObject.h"

// ���� : �������� ���� ��ȭ�Ǵ� ������Ʈ Base
class ARecMapCompoBase : public AActor, public URecordingObject
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ARecMapCompoBase();
	~ARecMapCompoBase();

	// delete Function
	ARecMapCompoBase(const ARecMapCompoBase& _Other) = delete;
	ARecMapCompoBase(ARecMapCompoBase&& _Other) noexcept = delete;
	ARecMapCompoBase& operator=(const ARecMapCompoBase& _Other) = delete;
	ARecMapCompoBase& operator=(ARecMapCompoBase&& _Other) noexcept = delete;

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

	void StataChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;
	
protected:
	UStateManager State;

	virtual void StateInit();

};

