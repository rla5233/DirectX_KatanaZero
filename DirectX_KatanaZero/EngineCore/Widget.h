#pragma once
#include <EngineBase/TransformObject.h>
#include "RenderUnit.h"
#include "TickObject.h"

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
	~UWidget();

	// delete Function
	UWidget(const UWidget& _Other) = delete;
	UWidget(UWidget&& _Other) noexcept = delete;
	UWidget& operator=(const UWidget& _Other) = delete;
	UWidget& operator=(UWidget&& _Other) noexcept = delete;

	void AddToViewPort();

protected:
	void MaterialSettingEnd() override;

private:
	void RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera);

};

