#pragma once

// 설명 : 픽셀 충돌 적용 액터 (4개 지점에서 체크, FT, FB, BT, BB)
class UPixelColObject_Base : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	UPixelColObject_Base();
	~UPixelColObject_Base();

	// delete Function
	UPixelColObject_Base(const UPixelColObject_Base& _Other) = delete;
	UPixelColObject_Base(UPixelColObject_Base&& _Other) noexcept = delete;
	UPixelColObject_Base& operator=(const UPixelColObject_Base& _Other) = delete;
	UPixelColObject_Base& operator=(UPixelColObject_Base&& _Other) noexcept = delete;

	void SetTop(const FVector& _Pos)
	{
		Top = _Pos;
	}

	void SetBot(const FVector& _Pos)
	{
		Bot = _Pos;
	}

public:
	bool IsOnGround(EEngineDir _Dir);
	bool IsOnPlatForm(EEngineDir _Dir);
	bool IsOnGP_Boundary(EEngineDir _Dir);
	bool IsOnStairs(EEngineDir _Dir);
	bool IsColWall(EEngineDir _Dir);
	bool IsColHeadToWall(EEngineDir _Dir);
	bool IsColHeadToCeil(EEngineDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	FVector Top = FVector::Zero;
	FVector Bot = FVector::Zero;

};

