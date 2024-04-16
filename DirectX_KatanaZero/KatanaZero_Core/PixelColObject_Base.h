#pragma once

// 설명 : 픽셀 충돌 적용 액터 (4개 지점에서 체크, FT, FB, BT, BB)
class APixelColObject_Base : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	APixelColObject_Base();
	~APixelColObject_Base();

	// delete Function
	APixelColObject_Base(const APixelColObject_Base& _Other) = delete;
	APixelColObject_Base(APixelColObject_Base&& _Other) noexcept = delete;
	APixelColObject_Base& operator=(const APixelColObject_Base& _Other) = delete;
	APixelColObject_Base& operator=(APixelColObject_Base&& _Other) noexcept = delete;

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

