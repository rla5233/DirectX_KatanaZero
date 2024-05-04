#include "PreCompile.h"
#include "KZImage.h"

UKZImage::UKZImage()
{
	UFadeObject::SetImage(this);
}

UKZImage::~UKZImage()
{
}

void UKZImage::SetPosition(const FVector& _Pos)
{
	switch (SortType)
	{
	case ESortType::Left:
		UImage::SetPosition({ _Pos.X + GetLocalScale().hX(), _Pos.Y, _Pos.Z });
		break;
	default:
		UImage::SetPosition(_Pos);
		break;
	}
}

void UKZImage::SetSortType(ESortType _SortType)
{
	if (SortType != _SortType)
	{
		switch (SortType)
		{
		case ESortType::Left:
			AddPosition({ GetLocalScale().hX(), 0.0f, 0.0f });
			break;
		default:
			break;
		}
	}

	SortType = _SortType;
}

void UKZImage::BeginPlay()
{
	Super::BeginPlay();	
}

void UKZImage::Tick(float _DelatTime)
{
	Super::Tick(_DelatTime);

	FadeUpdate(_DelatTime);
}