#include "PreCompile.h"
#include "TileRenderer.h"
#include "SpriteRenderer.h"
#include "EngineShaderResources.h"
#include "EngineSprite.h"

UTileRenderer::UTileRenderer() 
{
	SetMesh("Rect");
	SetMaterial("2DImage");
}

UTileRenderer::~UTileRenderer() 
{
}

void UTileRenderer::BeginPlay()
{
	Super::BeginPlay();
	Resources->SettingConstantBuffer("ResultColorValue", ColorData);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
}

void UTileRenderer::CreateTileMap(std::string_view _TileSet, float4 _TileSize, int _X, int _Y, int _DefaultIndex)
{
	// 오로지 랜더링적 요소만 가진것.

	TileSprite = UEngineSprite::FindRes(_TileSet);

	TileSize = _TileSize;

	if (nullptr == TileSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 타일맵을 만들려고 했습니다.");
		return;
	}

	FSpriteInfo Info = TileSprite->GetSpriteInfo(0);

	Resources->SettingTexture("Image", Info.Texture, "POINT");

	Tiles.resize(_Y);
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		Tiles[i].resize(_X);
	}
}

void UTileRenderer::SetTile(int _X, int _Y, int _Index)
{
	Tiles[_Y][_X] = _Index;
}

void UTileRenderer::Render(float _DeltaTime)
{
	RenderingSetting();

	float4 StartPos = {0,0};

	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			FSpriteInfo Info = TileSprite->GetSpriteInfo(Tiles[y][x]);

			CuttingDataValue.CuttingPosition = Info.CuttingPosition;
			CuttingDataValue.CuttingSize = Info.CuttingSize;

			float4 CurPos = { TileSize.X* x, TileSize.Y* y };

			Transform.SetPosition(StartPos + CurPos);
			Transform.SetScale(TileSize);

			Resources->SettingAllShaderResources();

			GetMesh()->IndexedDraw();
		}
	}
}

