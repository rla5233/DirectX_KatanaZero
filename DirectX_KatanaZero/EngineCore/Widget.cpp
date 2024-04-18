#include "PreCompile.h"
#include "Widget.h"
#include "Level.h"
#include "EngineSprite.h"
#include "EngineCore.h"
#include "EngineDebugMsgWindow.h"

UWidget::UWidget() 
{
}

UWidget::~UWidget() 
{
}

void UWidget::AddToViewPort(int _Order)
{
	SetOrder(_Order);
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


void UWidget::Tick(float _DeltaTime)
{
	float4 Mouse = GEngine->EngineWindow.GetScreenMousePos();
	float4 UIPos = GetWorld()->GetUICamera()->ScreenPosToWorldPos(Mouse);

	FTransform Trans;
	Trans.SetPosition(UIPos);

	float4x4 UIView = GetWorld()->GetUICamera()->GetView();
	float4x4 UIProjection = GetWorld()->GetUICamera()->GetProjection();
	Trans.CalculateViewAndProjection(UIView, UIProjection);

	if (true == Transform.Collision(ECollisionType::Rect, ECollisionType::Point, Trans))
	{
		IsHover = true;
		if (nullptr != Hover)
		{
			Hover();
		}

		if (true == UEngineInput::IsDown(VK_LBUTTON) && nullptr != Down)
		{
			Down();
		}
	}
	else 
	{
		if (true == IsHover)
		{
			IsHover = false;

			if (nullptr != UnHover)
			{
				UnHover();
			}
		}
	}

	// GEngine->EngineWindow.mouse
}