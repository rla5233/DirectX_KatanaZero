#pragma once

// ���� : �ܻ� ȿ�� ������Ʈ
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

