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

	bool IsOnGround(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsOnPlatForm(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsOnGP_Boundary(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsOnStairs(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsColWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsColHeadToWall(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);
	bool IsColHeadToCeil(const std::shared_ptr<UEngineTexture> _MapTex, const FVector& _Pos, EEngineDir _Dir);

protected:

private:
	FVector Top = FVector::Zero;
	FVector Bot = FVector::Zero;

	bool IsStairsUpValue = false;
};

