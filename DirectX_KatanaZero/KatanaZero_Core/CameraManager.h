#pragma once

// ���� : ������ ī�޶� ���� ���
class UCameraManager
{
public:
	// constrcuter destructer
	UCameraManager();
	~UCameraManager();

	// delete Function
	UCameraManager(const UCameraManager& _Other) = delete;
	UCameraManager(UCameraManager&& _Other) noexcept = delete;
	UCameraManager& operator=(const UCameraManager& _Other) = delete;
	UCameraManager& operator=(UCameraManager&& _Other) noexcept = delete;

	//void MainCameraChasePlayer(const FVector& _PlayerPos);

protected:


private:

};

