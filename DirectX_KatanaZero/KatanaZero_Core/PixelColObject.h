#pragma once

// 설명 : 픽셀 충돌 오브젝트
class UPixelColObject
{
public:
	// constrcuter destructer
	UPixelColObject();
	~UPixelColObject();

	// delete Function
	UPixelColObject(const UPixelColObject& _Other) = delete;
	UPixelColObject(UPixelColObject&& _Other) noexcept = delete;
	UPixelColObject& operator=(const UPixelColObject& _Other) = delete;
	UPixelColObject& operator=(UPixelColObject&& _Other) noexcept = delete;

	void SetTop(const FVector& _Pos)
	{
		Top = _Pos;
	}

	void SetBot(const FVector& _Pos)
	{
		Bot = _Pos;
	}

	bool IsOnGround(EEngineDir _Dir);
	bool IsOnPlatForm(EEngineDir _Dir);
	bool IsOnGP_Boundary(EEngineDir _Dir);
	bool IsOnStairs(EEngineDir _Dir);
	bool IsColWall(EEngineDir _Dir);
	bool IsColHeadToWall(EEngineDir _Dir);
	bool IsColHeadToCeil(EEngineDir _Dir);

protected:
	inline void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
		SetMapTex();
	}

private:
	FVector Top = { 10.0f, 10.0f, 0.0f };
	FVector Bot = { 10.0f, 0.0f, 0.0f };

	bool IsStairsUpValue = false;
	
	AActor* Actor = nullptr;
	std::shared_ptr<UEngineTexture> MapTex;

	void SetMapTex();
};

