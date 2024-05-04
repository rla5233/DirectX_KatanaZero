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
	AfterImage,
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
	CeilLaser,
	CeilGun,
	TimeOut,
	Fan
};

enum class EColOrder
{
	PlayerBody,
	PlayerFront,
	PlayerAttack,
	Enemy,
	DeadEnemy,
	EnemyAttack,
	Door,
	Stair,
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

enum class EStairType
{
	None,
	Up,
	Down
};

enum class EWaveEffectType
{
	BeginPlay,
	Restart
};

enum class EFactoryIntroOrder
{
	None,
	SongBackGround,
	SongText,
};