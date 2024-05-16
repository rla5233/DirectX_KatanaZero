#pragma once

// ���� : KatanaZero Debug ��
class UKatanaZeroDebugWindow : public UEngineEditorWindow
{
public:
	// constructor destructor
	UKatanaZeroDebugWindow();
	~UKatanaZeroDebugWindow();
	
	// delete Function
	UKatanaZeroDebugWindow(const UKatanaZeroDebugWindow& _Other) = delete;
	UKatanaZeroDebugWindow(UKatanaZeroDebugWindow&& _Other) noexcept = delete;
	UKatanaZeroDebugWindow& operator=(const UKatanaZeroDebugWindow& _Other) = delete;
	UKatanaZeroDebugWindow& operator=(UKatanaZeroDebugWindow&& _Other) noexcept = delete;

protected:

private:
	void OnGui(ULevel* Level, float _Delta) override;

};

