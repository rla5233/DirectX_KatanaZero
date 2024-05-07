#pragma once
#include <EngineCore/StateManager.h>

class ATitleScreen;
class AMainCamera;
class ATitleMenu;

// 설명 : Title 메뉴
class ATitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode);
public:
	// constructor destructor
	ATitleGameMode();
	~ATitleGameMode();
	
	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void InputCheck(int _Input);
	void MenuInputOff();

protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	UStateManager State;

	void StateInit();

private:
	std::shared_ptr<AMainCamera> MainCamera = nullptr;
	std::shared_ptr<ATitleScreen> Screen = nullptr;
	std::shared_ptr<ATitleMenu> Menu = nullptr;

	UEngineSoundPlayer TitleBGM;
};

