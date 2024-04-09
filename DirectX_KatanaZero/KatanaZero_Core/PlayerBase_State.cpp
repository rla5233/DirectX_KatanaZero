#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase FSM ���� Ŭ����
void APlayerBase::StateInit()
{
	// State ����
	State.CreateState("Idle");
	//State.CreateState("Idle");
	//State.CreateState("Jump");
	//State.CreateState("Run");


	// State Start �Լ� ����
	State.SetStartFunction("Idle", std::bind(&APlayerBase::IdleStart, this));

	// State Update �Լ� ����
	State.SetUpdateFunction("Idle", std::bind(&APlayerBase::Idle, this, std::placeholders::_1));
}



void APlayerBase::IdleStart()
{
	Renderer->SetAutoSize(2.0f, true);
	Renderer->ChangeAnimation(Anim::player_idle_anim);
}

void APlayerBase::Idle(float _DeltaTime)
{
	void 
}
