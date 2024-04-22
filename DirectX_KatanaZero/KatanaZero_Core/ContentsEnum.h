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
	Top,
	Text,
	UpText
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

enum class EWidgetOrder
{
	Bottom,
	Mid,
	Top
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
	PlayerFront,
	PlayerBody,
	Door,
	Enemy,
	DeadEnemy,
	HitComponent
};

enum class EReplayMode
{
	Rewind,
	Stop,
	Play
};