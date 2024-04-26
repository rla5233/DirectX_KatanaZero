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
	MapComponent_Back,
	EffectBack,
	Enemy,
	Player,
	Player2,
	EffectFront,
	MapComponent_Front,
	UI
};

enum class EUpdateOrder
{
	Default,
	Player,
	Enemy,
	RecComponent,
	Fan
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

enum class EEnemyType
{
	Default,
	CeilGun,
	TimeOut,
	Fan
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
	InteractionComponent
};

enum class EReplayMode
{
	Rewind,
	Stop,
	Play
};

enum class EIntroOrder
{
	Run,
	RunToIdle,
	MusicOn,
};

enum class EOutroType
{
	Run,
	IdleToRun,
	RunToIdle,
	Jump,
	Fall,
	Roll,
	Attack
};