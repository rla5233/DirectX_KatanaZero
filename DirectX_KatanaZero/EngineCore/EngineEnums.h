#pragma once

enum class EShaderType
{
	NONE,
	Vertex,
	Pixel,
};


enum class ECameraType
{
	NONE,
	Perspective,
	Orthographic,
};

enum class ETextureSampling
{
	NONE,
	LINEAR,
	POINT,
};

enum class EPivot
{
	BOT,
	MAX,
};

enum class EEngineDir
{
	Left,
	Right,
	MAX,
};
