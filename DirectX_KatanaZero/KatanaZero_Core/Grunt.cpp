#include "PreCompile.h"
#include "Grunt.h"

AGrunt::AGrunt()
{
}

AGrunt::~AGrunt()
{
}

void AGrunt::BeginPlay()
{
	Super::BeginPlay();

	CreateAnimation();
}

void AGrunt::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AGrunt::CreateAnimation()
{

}
