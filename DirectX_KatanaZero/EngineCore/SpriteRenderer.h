#pragma once
#include "Renderer.h"
#include "EngineEnums.h"
#include "EngineSprite.h"

struct FCuttingData
{
	//       0, 0
	float4 CuttingPosition;
	//      0.5 0.5
	float4 CuttingSize;
};

class UEngineSprite;
class USpriteAnimation : public UNameObject
{

public:
	std::shared_ptr<UEngineSprite> Sprite;
	std::vector<float> Inter;
	std::vector<int> Frame;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = true;

	void Update(float _DeltaTime);

	FSpriteInfo GetCurSpriteInfo()
	{
		return Sprite->GetSpriteInfo(Frame[CurFrame]);
	}

	void Reset()
	{
		CurTime = 0.0f;
		CurFrame = 0;
	}
};

// Ό³Έν :
class UEngineTexture;
class USpriteRenderer : public URenderer
{
	GENERATED_BODY(URenderer);

public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetPlusColor(float4 _Color);
	void SetSamplering(ETextureSampling _Value);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, bool _Loop = true, int _Start = -1, int _End = -1);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<float> _Inter, std::vector<int> _Frame, bool _Loop = true);

	void ChangeAnimation(std::string_view _AnimationName);

	void SetAutoSize(float _ScaleRatio, bool _AutoSize);
	void SetSpriteInfo(const FSpriteInfo& _Info);

	void SetDir(EEngineDir _Dir);

protected:
	void Tick(float _DeltaTime) override;

private:
	bool AutoSize = false;
	float ScaleRatio = 1.0f;
	FSpriteInfo CurInfo;

	EEngineDir Dir = EEngineDir::MAX;

	FCuttingData CuttingDataValue;
	float4 PlusColor = float4::Zero;
	std::shared_ptr<UEngineTexture> CurTexture = nullptr;
	std::map<std::string, std::shared_ptr<USpriteAnimation>> Animations;
	std::shared_ptr<USpriteAnimation> CurAnimation = nullptr;
	ETextureSampling SamplingValue = ETextureSampling::POINT;

};

