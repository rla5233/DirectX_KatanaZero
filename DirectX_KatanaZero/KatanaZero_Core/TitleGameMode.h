#pragma once

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


protected:
	void BeginPlay();
	void Tick(float _DeltaTime);

private:

};

