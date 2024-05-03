#pragma once

// 설명 : 잔상 효과 오브젝트
class UAfterImageObject
{
public:
	// constrcuter destructer
	UAfterImageObject();
	~UAfterImageObject();

	// delete Function
	UAfterImageObject(const UAfterImageObject& _Other) = delete;
	UAfterImageObject(UAfterImageObject&& _Other) noexcept = delete;
	UAfterImageObject& operator=(const UAfterImageObject& _Other) = delete;
	UAfterImageObject& operator=(UAfterImageObject&& _Other) noexcept = delete;

protected:

private:
	USpriteRenderer* AfterImageRenderer = nullptr;

};

