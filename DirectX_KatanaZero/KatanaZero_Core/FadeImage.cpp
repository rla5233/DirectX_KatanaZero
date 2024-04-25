#include "PreCompile.h"
#include "FadeImage.h"

UFadeImage::UFadeImage()
{
	UFadeObject::SetImage(this);
}

UFadeImage::~UFadeImage()
{
}

void UFadeImage::BeginPlay()
{
	Super::BeginPlay();	
}

void UFadeImage::Tick(float _DelatTime)
{
	Super::Tick(_DelatTime);
}
