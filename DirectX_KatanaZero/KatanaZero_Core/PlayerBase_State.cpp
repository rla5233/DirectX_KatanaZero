#include "PreCompile.h"
#include "PlayerBase.h"

// PlayerBase FSM 관련 클래스
void APlayerBase::StateInit()
{
	// State 생성
	State.CreateState("Idle");
	//State.CreateState("Idle");
	//State.CreateState("Jump");
	//State.CreateState("Run");


	// State Start 함수 세팅
	State.SetStartFunction("Idle", std::bind(&APlayerBase::IdleStart, this));

	// State Update 함수 세팅
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
