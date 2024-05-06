#pragma once

// ���� : �ȼ� �浹 ������Ʈ
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

	void SetBodyInfo(const FVector& _BodyPos, const FVector& _BodyScale);

	// ����
	FVector GetFTFromActor()
	{
		return FrontTop - Actor->GetActorLocation();
	}

	FVector GetFBFromActor()
	{
		return FrontBot - Actor->GetActorLocation();
	}

	FVector GetBTFromActor()
	{
		return BackTop - Actor->GetActorLocation();
	}

	FVector GetBBFromActor()
	{
		return BackBot - Actor->GetActorLocation();
	}
	// ����

	// �浹 üũ �Լ�
	bool IsOnGround(EEngineDir _Dir);
	bool IsOnGroundBoundary(EEngineDir _Dir);
	bool IsOnPlatForm(EEngineDir _Dir);
	bool IsOnGP_Boundary(EEngineDir _Dir);
	bool IsOnStairs(EEngineDir _Dir);
	bool IsOnCliff(EEngineDir _Dir);
	bool IsColWall(EEngineDir _Dir);
	bool IsColHeadToWall(EEngineDir _Dir);
	bool IsColHeadToCeil(EEngineDir _Dir);
	bool IsColBotToWall(EEngineDir _Dir);
	bool IsColBackToWall(EEngineDir _Dir);

	bool IsStairsUp() const
	{
		return IsStairsUpValue;
	}

	// ��ġ ����
	void OnGroundPosAdjust(EEngineDir _Dir);
	void UpStairPosAdjust(EEngineDir _Dir);
	void OnCliffPosAdjust(EEngineDir _Dir);
	void OnPlatFormPosAdjust(EEngineDir _Dir);
	void OnGP_BoundaryPosAdjust(EEngineDir _Dir);
	void CeilColPosAdjust(EEngineDir _Dir);

protected:
	inline void SetActor(AActor* _Actor)
	{
		Actor = _Actor;
		SetMapTex();
	}

	void CalFourPoint(EEngineDir _Dir);

private:
	FVector FrontTop = FVector::Zero;
	FVector FrontBot = FVector::Zero;
	FVector BackTop = FVector::Zero;
	FVector BackBot = FVector::Zero;

	FVector BodyPos = FVector::Zero;
	FVector BodyScale = FVector::Zero;

	bool IsStairsUpValue = false;
	
	AActor* Actor = nullptr;
	std::shared_ptr<UEngineTexture> MapTex;

	void SetMapTex();
};

