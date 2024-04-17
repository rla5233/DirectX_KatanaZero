#include "PreCompile.h"
#include "Widget.h"
#include "Level.h"

UWidget::UWidget()
{
}

UWidget::~UWidget()
{
}

void UWidget::AddToViewPort()
{
	GetWorld()->PushWidget(shared_from_this());
}

void UWidget::MaterialSettingEnd()
{
	Super::MaterialSettingEnd();
	if (true == Resources->IsConstantBuffer("FTransform"))
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
	}
}

void UWidget::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
{
	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
}