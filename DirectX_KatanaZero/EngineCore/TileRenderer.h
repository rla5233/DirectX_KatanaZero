#pragma once
#include "Renderer.h"
#include "EngineEnums.h"
#include "EngineSprite.h"
#include "EngineStruct.h"

// Ό³Έν :
class UTileRenderer : public URenderer
{
public:
	GENERATED_BODY(URenderer)
	// constrcuter destructer
	UTileRenderer();
	~UTileRenderer();

	// delete Function
	UTileRenderer(const UTileRenderer& _Other) = delete;
	UTileRenderer(UTileRenderer&& _Other) noexcept = delete;
	UTileRenderer& operator=(const UTileRenderer& _Other) = delete;
	UTileRenderer& operator=(UTileRenderer&& _Other) noexcept = delete;

	void CreateTileMap(std::string_view _TileSetSprite, float4 _TileSize, int _X, int _Y, int _DefaultIndex);
	void SetTile(int _X, int _Y, int _Index);

protected:
	void BeginPlay() override;
	void Render(float _DeltaTime) override;

	ResultColorValue ColorData;
	FCuttingData CuttingDataValue;
	std::vector<std::vector<int>> Tiles;
	std::shared_ptr<UEngineSprite> TileSprite;
	float4 TileSize = {64, 64};

private:
};

