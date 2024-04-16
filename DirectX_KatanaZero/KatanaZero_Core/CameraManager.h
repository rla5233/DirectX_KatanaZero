#pragma once

// 설명 : 콘텐츠 카메라 추적 기능
class UCameraManager
{
public:
	// constrcuter destructer
	UCameraManager();
	~UCameraManager();

	// delete Function
	UCameraManager(const UCameraManager& _Other) = delete;
	UCameraManager(UCameraManager&& _Other) noexcept = delete;
	UCameraManager& operator=(const UCameraManager& _Other) = delete;
	UCameraManager& operator=(UCameraManager&& _Other) noexcept = delete;

	static void PlayLevelChaseActor(
		std::shared_ptr<UCamera> _MainCamera,
		std::shared_ptr<UEngineTexture> MapTex,
		const FVector& _ActorPos);

protected:


private:

};

