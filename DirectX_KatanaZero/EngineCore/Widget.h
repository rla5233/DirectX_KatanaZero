#pragma once
#include <EngineBase/TransformObject.h>
#include "RenderUnit.h"
#include "TickObject.h"
#include "EngineStruct.h"

// ���⼭ ��� �Ұųİ� �߿��ϴ�.

// ���� :

// �ڱ� �ڽĿ�����Ʈ�� �̷��͵��� �߰��Ҽ� �ֽ��ϴ�.
// �θ��ڽ� ���踦 �̸��� �־�� �Ѵ�.

// ȭ�鿡 UIó�� �����Ǿ ���̴� �ֵ��� �������ϴ� ����̴�.
// �Ϲ������� �̷� UI���� ������Ʈ���� ������ ��ũ����ǥ�踦 �������� ��´�.
// �׷��� �츮�� �׳� �Ϲ� ����ó�� �ϰڽ��ϴ�.
class ULevel;
class UWidget : 
	public UTransformObject, 
	public URenderUnit, 
	public UWorldObject, 
	public UTickObject, 
	public UNameObject,
	public std::enable_shared_from_this<UWidget>
{
public:
	GENERATED_BODY(URenderUnit)

	friend ULevel;
	// constrcuter destructer
	UWidget();
	virtual ~UWidget();

	// delete Function
	UWidget(const UWidget& _Other) = delete;
	UWidget(UWidget&& _Other) noexcept = delete;
	UWidget& operator=(const UWidget& _Other) = delete;
	UWidget& operator=(UWidget&& _Other) noexcept = delete;

	template<typename EnumType>
	void AddToViewPort(EnumType _Order)
	{
		AddToViewPort(static_cast<int>(_Order));
	}

	void AddToViewPort(int _Order);

	void SetHover(std::function<void()> _Hover)
	{
		Hover = _Hover;
	}

	void SetDown(std::function<void()> _Down)
	{
		Down = _Down;
	}

	void SetUnHover(std::function<void()> _UnHover)
	{
		UnHover = _UnHover;
	}



protected:
	void MaterialSettingEnd() override;
	void Tick(float _DeltaTime) override;

	void Reset()
	{
		IsHover = false;
	}

private:
	void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);

	bool IsHover = false;

	std::function<void()> UnHover;
	std::function<void()> Hover;
	std::function<void()> Down;
};

