#pragma once

// 설명 : 클리어 AGo
class AGo : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AGo();
	~AGo();
	
	// delete Function
	AGo(const AGo& _Other) = delete;
	AGo(AGo&& _Other) noexcept = delete;
	AGo& operator=(const AGo& _Other) = delete;
	AGo& operator=(AGo&& _Other) noexcept = delete;

	void SetActorLocation(const FVector& _Pos);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Init();

private:
	UImage* Go = nullptr;
	UImage* Arrow = nullptr;


};

