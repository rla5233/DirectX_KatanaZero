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
	MapComponent_Mid,
	EffectBack,
	AfterImage,
	Enemy,
	HeadHunter,
	HeadHunterHead,
	Player,
	EffectFront,
	MapComponent_Front,
	UI
};

enum class EUpdateOrder
{
	Default,
	Player,
	Enemy,
	HeadHunter,
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
	HeadHunterLaser,
	HeadHunterDash,
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
	HeadHunter,
	EnemyAttack,
	Door,
	Stair,
	InteractionComponent
};

enum class EReplayMode
{
	Restart,
	Rewind,
	Stop,
	Play
};

enum class EIntroOrder
{
	None,
	Run,
	RunToIdle,
	Fall,
	PreCrouch,
	MusicOn,
	MusicOff
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
	Intro,
	IntroBig,
	Restart
};

enum class EFactoryIntroOrder
{
	None,
	SongBackGround,
	PlayingSongText,
	PlayingSongTitle,
	StageName,
	StartWaiting
};

enum class EFactoryClearOrder
{
	None,
	FactoryClearStart,
	FactoryClearEnd
};

enum class EIntroType
{
	Default,
	FactoryBegin,
	HeadHunter1,
	HeadHunter2
};

enum class EHitLaserType
{
	Default,
	HeadHunterDash
};