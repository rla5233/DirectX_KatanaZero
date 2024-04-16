#pragma once
#include <EngineBase/NameObject.h>
#include "imgui.h"

// �츰 �̰͸� ����մϴ�.
// �����е��� ������ â�� ���� �;�.

// ���� :
class ULevel;
class UEngineEditorGUI;
class UEngineEditorWindow : public UNameObject
{
	friend UEngineEditorGUI;

public:
	// constrcuter destructer
	UEngineEditorWindow();
	~UEngineEditorWindow();

	// delete Function
	UEngineEditorWindow(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow(UEngineEditorWindow&& _Other) noexcept = delete;
	UEngineEditorWindow& operator=(const UEngineEditorWindow& _Other) = delete;
	UEngineEditorWindow& operator=(UEngineEditorWindow&& _Other) noexcept = delete;

	void On()
	{
		IsActive = true;
	}

	void Off()
	{
		IsActive = false;
	}

protected:
	virtual void Init() {}
	virtual void Tick(ULevel* Level, float _Delta);
	virtual void OnGui(ULevel* Level, float _Delta) = 0;

private:
	std::string Title;
	bool IsActive = true;

	void Begin();
	void End();
};

