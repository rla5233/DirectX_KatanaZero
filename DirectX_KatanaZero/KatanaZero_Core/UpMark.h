#pragma once

// 설명 : Enemy 머리위 마크
class AUpMark : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AUpMark();
	~AUpMark();
	
	// delete Function
	AUpMark(const AUpMark& _Other) = delete;
	AUpMark(AUpMark&& _Other) noexcept = delete;
	AUpMark& operator=(const AUpMark& _Other) = delete;
	AUpMark& operator=(AUpMark&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;
	
	float PosY = 0.0f;
};

