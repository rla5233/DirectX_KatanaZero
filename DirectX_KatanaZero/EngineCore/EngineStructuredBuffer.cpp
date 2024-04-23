#include "PreCompile.h"
#include "EngineStructuredBuffer.h"
#include "EngineCore.h"

std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineStructuredBuffer>>>> UEngineStructuredBuffer::StructuredBuffers;

UEngineStructuredBuffer::UEngineStructuredBuffer() 
{
}

UEngineStructuredBuffer::~UEngineStructuredBuffer() 
{
}

void UEngineStructuredBuffer::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("타입이 불분명한 텍스처 세팅입니다.");
		break;
	}
}

void UEngineStructuredBuffer::Reset(EShaderType _Type, UINT _Slot)
{
	ID3D11ShaderResourceView* NullptrSRV = nullptr;

	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("타입이 불분명한 텍스처 세팅입니다.");
		break;
	}
}

void UEngineStructuredBuffer::ChangeData(const void* _Data, UINT _Size)
{

}