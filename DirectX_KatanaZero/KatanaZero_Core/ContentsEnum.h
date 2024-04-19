#pragma once

enum class ETitleState
{
	Intro,
	Select
};

enum class ETitleRenderOrder
{
	BackGround,
	Bottom,
	Mid,
	Top
};

enum class ERenderOrder
{
	ColMap,
	BackGround,
	MapComponent,
	EffectBack,
	Enemy,
	Player,
	Player2,
	EffectFront,
	UI
};

enum class EEnemyPatrol
{
	Walk,
	Turn,
	Stop
};

enum class EColOrder
{
	PlayerAttack,
	EnemyAttack,
	Player,
	Enemy,
	HitComponent
};