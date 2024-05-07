#include "PreCompile.h"
#include "EngineNet.h"
#include "NetStartUpHelper.h"

UEngineNet::UEngineNet() 
{
	UNetStartUpHelper::NetStartUp();
	IsActiveValue = true;
}

UEngineNet::~UEngineNet() 
{
	IsActiveValue = false;
}

