#pragma once

namespace ColMap
{
	const Color8Bit YELLOW	= Color8Bit(255, 255, 0, 255);	//	Ground
	const Color8Bit GREEN	= Color8Bit(0, 255, 0, 255);	//	Platform
	const Color8Bit BLUE	= Color8Bit(0, 0, 255, 255);	//	Stair
	const Color8Bit RED		= Color8Bit(255, 0, 0, 255);	//	EndPoint
	const Color8Bit MAGENTA	= Color8Bit(255, 0, 255, 255);	//	Cliff
}

namespace ImgRes
{
	// Player
	const std::string_view player_idle				= "player_idle";
	const std::string_view player_idle_to_run		= "player_idle_to_run";
	const std::string_view player_run_to_idle		= "player_run_to_idle";
	const std::string_view player_jump				= "player_jump";
	const std::string_view player_fall				= "player_fall";
	const std::string_view player_run				= "player_run";
	const std::string_view player_postcrouch		= "player_postcrouch";
	const std::string_view player_precrouch			= "player_precrouch";
	const std::string_view player_roll				= "player_roll";
	const std::string_view player_attack			= "player_attack";
	const std::string_view player_wall_slide		= "player_wallslide";
	const std::string_view player_flip				= "player_flip";
	const std::string_view player_kick_door			= "player_kick_door";
	const std::string_view player_dead				= "player_dead";

	// Enemy
	const std::string_view enemy_grunt_idle			= "grunt_idle";
	const std::string_view enemy_grunt_attack		= "grunt_attack";
	const std::string_view enemy_grunt_run			= "grunt_run";
	const std::string_view enemy_grunt_turn			= "grunt_turn";
	const std::string_view enemy_grunt_walk			= "grunt_walk";
	const std::string_view enemy_grunt_hitfall		= "grunt_hitfall";
	const std::string_view enemy_grunt_dead			= "grunt_dead";

	const std::string_view enemy_gangster_idle		= "gangster_idle";
	const std::string_view enemy_gangster_run		= "gangster_run";
	const std::string_view enemy_gangster_turn		= "gangster_turn";
	const std::string_view enemy_gangster_hitfall	= "gangster_hitfall";
	const std::string_view enemy_gangster_dead		= "gangster_dead";
	const std::string_view enemy_gangster_shoot		= "spr_gangsteridle_0.png";

	// UI
	const std::string_view ui_cursor				= "spr_cursor_0.png";
	const std::string_view ui_up_hud_bar			= "spr_hud_0.png";
	const std::string_view ui_up_hud_battery		= "spr_hud_battery_0.png";
	const std::string_view ui_up_hud_battery_part1	= "spr_hud_battery_part_0.png";
	const std::string_view ui_up_hud_battery_part2	= "spr_hud_battery_part_1.png";
	const std::string_view ui_up_hud_timer			= "spr_hud_timer_0.png";
	const std::string_view ui_up_hud_timer_bar1		= "spr_hud_timer_1.png";
	const std::string_view ui_up_hud_timer_bar2		= "spr_hud_timer_2.png";
	const std::string_view ui_up_hud_weapon			= "spr_hud_weapon_0.png";
	const std::string_view ui_katana_icon			= "spr_katanaicons_0.png";
	const std::string_view ui_item_icon				= "spr_itemicons_0.png";
	const std::string_view ui_shift_up				= "spr_keyboard_shift_0.png";
	const std::string_view ui_shift_down			= "spr_keyboard_shift_1.png";
	const std::string_view ui_left_click			= "spr_left_click_0.png";
	const std::string_view ui_right_click			= "spr_right_click_0.png";

	const std::string_view ui_go					= "spr_go.png";
	const std::string_view ui_go_arrow				= "spr_go_arrow.png";

	const std::string_view ui_replay_RB_text		= "spr_replay_text_000.png";
	const std::string_view ui_replay_LT_play		= "spr_replay_text_001.png";
	const std::string_view ui_replay_LT_rewind		= "spr_replay_text_002.png";
	const std::string_view ui_replay_LT_stop		= "spr_replay_text_003.png";
	const std::string_view ui_replay_LT_fast		= "spr_replay_text_004.png";
	const std::string_view ui_replay_right_click	= "spr_right_click";
	const std::string_view ui_replay_x2				= "spr_replay_x2.png";
	const std::string_view ui_replay_x4				= "spr_replay_x4.png";
	const std::string_view ui_replay_x8				= "spr_replay_x8.png";
	const std::string_view ui_replay_x16			= "spr_replay_x16.png";
	const std::string_view ui_outro_msg				= "spr_outro_0.png";

	// Effect
	const std::string_view effect_player_slash		= "player_slash";
	const std::string_view effect_player_dustcloud	= "player_dustcloud";
	const std::string_view effect_player_landcloud	= "player_landcloud";
	const std::string_view effect_player_jumpcloud	= "player_jumpcloud";

	const std::string_view effect_gun_spark1		= "spr_gun_spark1";
	const std::string_view effect_gun_spark2		= "spr_gun_spark2";
	const std::string_view effect_gun_spark3		= "spr_gun_spark3";
	const std::string_view effect_gun_smoke1		= "spr_gun_smoke1";
	const std::string_view effect_gun_smoke2		= "spr_gun_smoke2";
	const std::string_view effect_gun_smoke3		= "spr_gun_smoke3";

	const std::string_view effect_blood_splatter1	= "spr_bloodsplatter1";
	const std::string_view effect_blood_splatter2	= "spr_bloodsplatter2";
	const std::string_view effect_blood_splatter3	= "spr_bloodsplatter3";

	const std::string_view effect_enemy_follow		= "spr_enemy_follow";
	const std::string_view effect_grunt_attack		= "grunt_attack_effect";

	const std::string_view effect_collar_explode	= "spr_collar_explode";
	const std::string_view effect_dia_transition	= "spr_transition";

	const std::string_view effect_hit_laser			= "spr_slash_laser.png";

	// Component
	const std::string_view compo_door				= "spr_door";
	const std::string_view compo_ceil_laser_on		= "spr_laser_on_0.png";
	const std::string_view compo_ceil_laser_off		= "spr_laser_off_0.png";
	const std::string_view compo_ceil_laser_idle	= "spr_laser_col_idle";
	const std::string_view compo_ceil_laser_attack	= "spr_laser_col_attack";
	const std::string_view compo_ceil_gun			= "spr_ceiling_gun_0.png";
	const std::string_view compo_ceilgun_col_idle	= "spr_ceilgun_col_idle";
	const std::string_view compo_panic_switch_on	= "spr_panic_switch_on.png";
	const std::string_view compo_panic_switch_off	= "spr_panic_switch_off.png";
	const std::string_view compo_fan_back			= "spr_fan_bg.png";
	const std::string_view compo_fan_front			= "spr_fan_fg.png";
	const std::string_view compo_fan_blade			= "spr_fanblade";

	const std::string_view compo_scientist_chair	= "spr_scientist_chair";
	const std::string_view compo_scientist_explode	= "spr_scientist_explode";

	const std::string_view compo_bullet				= "spr_bullet_0.png";

	// TitleLevel
	const std::string_view title_background			= "spr_title_background.png";
	const std::string_view title_black				= "spr_title_black.png";
	const std::string_view title_fence				= "spr_title_fence_0.png";
	const std::string_view title_grass				= "spr_title_grass_0.png";
	const std::string_view title_neon_zer			= "spr_titlegraphic_1.png";
	const std::string_view title_neon_o				= "spr_titlegraphic_2.png";
	const std::string_view title_neon_katana		= "spr_titlegraphic_3.png";
	const std::string_view title_plant				= "spr_plants";
	const std::string_view title_menu_text			= "spr_menu_text.png";
	const std::string_view title_menu_black_bar		= "spr_menu_black_bar.png";
	const std::string_view title_menu_white_bar		= "spr_menu_white_bar.png";

	// FactoryLevel
	const std::string_view factory_background1		= "spr_background_factory_1.png";
	const std::string_view factory_background2		= "spr_background_factory_2.png";
	const std::string_view factory_background3		= "spr_background_factory_3.png";
	const std::string_view factory_background4	 	= "spr_background_factory_4.png";
	const std::string_view factory_background5		= "spr_background_factory_5.png";

	const std::string_view factory_colmap2			= "spr_colmap_factory_2.png";
	const std::string_view factory_colmap3			= "spr_colmap_factory_3.png";
	const std::string_view factory_colmap4			= "spr_colmap_factory_4.png";
	const std::string_view factory_colmap5			= "spr_colmap_factory_5.png";

	// HeadHunterLevel
	const std::string_view headhunter_background1	= "spr_background_headhunter1.png";
	const std::string_view headhunter_background2	= "spr_background_headhunter2.png";
}

namespace Anim
{
	// Default Player Anim
	const std::string_view player_idle				= "player_idle";
	const std::string_view player_idle_to_run		= "player_idle_to_run";
	const std::string_view player_run_to_idle		= "player_run_to_idle";
	const std::string_view player_jump				= "player_jump";
	const std::string_view player_fall				= "player_fall";
	const std::string_view player_run				= "player_run";
	const std::string_view player_postcrouch		= "player_postcrouch";
	const std::string_view player_precrouch			= "player_precrouch";
	const std::string_view player_roll				= "player_roll";
	const std::string_view player_attack			= "player_attack";
	const std::string_view player_wall_slide		= "player_wallslide";
	const std::string_view player_flip				= "player_flip";
	const std::string_view player_kick_door			= "player_kick_door";
	const std::string_view player_dead				= "player_dead";

	// Enemy
	const std::string_view enemy_grunt_idle			= "grunt_idle";
	const std::string_view enemy_grunt_attack		= "grunt_attack";
	const std::string_view enemy_grunt_walk			= "grunt_walk";
	const std::string_view enemy_grunt_run			= "grunt_run";
	const std::string_view enemy_grunt_turn			= "grunt_turn";
	const std::string_view enemy_grunt_hitfall		= "grunt_hitfall";
	const std::string_view enemy_grunt_dead			= "grunt_dead";

	const std::string_view enemy_gangster_idle		= "gangster_idle";
	const std::string_view enemy_gangster_run		= "gangster_run";
	const std::string_view enemy_gangster_turn		= "gangster_turn";
	const std::string_view enemy_gangster_hitfall	= "gangster_hitfall";
	const std::string_view enemy_gangster_dead		= "gangster_dead";

	// UI
	const std::string_view ui_replay_right_click	= "spr_right_click";

	// Effect
	const std::string_view effect_player_slash		= "player_slash";
	const std::string_view effect_player_dustcloud	= "player_dustcloud";
	const std::string_view effect_player_landcloud	= "player_landcloud";
	const std::string_view effect_player_jumpcloud	= "player_jumpcloud";

	const std::string_view effect_gun_spark1		= "spr_gun_spark1";
	const std::string_view effect_gun_spark2		= "spr_gun_spark2";
	const std::string_view effect_gun_spark3		= "spr_gun_spark3";
	const std::string_view effect_gun_smoke1		= "spr_gun_smoke1";
	const std::string_view effect_gun_smoke2		= "spr_gun_smoke2";
	const std::string_view effect_gun_smoke3		= "spr_gun_smoke3";
		
	const std::string_view effect_blood_splatter1	= "spr_bloodsplatter1";
	const std::string_view effect_blood_splatter2	= "spr_bloodsplatter2";
	const std::string_view effect_blood_splatter3	= "spr_bloodsplatter3";

	const std::string_view effect_enemy_follow		= "spr_enemy_follow";
	const std::string_view effect_grunt_attack		= "grunt_attack_effect";

	const std::string_view effect_collar_explode	= "spr_collar_explode";
	
	const std::string_view effect_dia_transition_on		= "spr_transition_on";
	const std::string_view effect_dia_transition_off	= "spr_transition_off";
	const std::string_view effect_dia_transition_idle	= "spr_transition_idle";

	// Component
	const std::string_view compo_door_idle			= "door_idle";
	const std::string_view compo_door_open			= "door_open";
	const std::string_view compo_ceil_laser_idle	= "spr_laser_col_idle";
	const std::string_view compo_ceil_laser_attack	= "spr_laser_col_attack";
	const std::string_view compo_ceilgun_col_idle	= "spr_ceilgun_col_idle";
	const std::string_view compo_fan_blade			= "spr_fanblade";

	const std::string_view compo_scientist_chair	= "spr_scientist_chair";
	const std::string_view compo_scientist_explode	= "spr_scientist_explode";

	// TitleLevel
	const std::string_view plants					= "plants";
}

namespace Const
{
	// Player
	const float default_gravity						= -2000.0f;
	const float jump_gravity						= -1800.0f;
	const float down_stair_gravity					= -15000.0f;

	const float player_max_speedx					= 425.0f;
	const float player_max_speedy					= 425.0f;

	const float player_run_accx						= 1000.0f;

	const float player_roll_speedx					= 550.0f;

	const float player_jump_accx					= 1000.0f;
	const float player_jump_start_speedx			= player_max_speedx * 0.75f;
	const float player_jump_speedy					= 500.0f;

	const float player_fall_accx					= 1000.0f;
	const float player_fall_input_accy				= -6000.0f;
	const float player_fall_max_speedy				= 1200.0f;

	const float player_attack_delay					= 0.25f;
	const float player_ability_time					= 6.0f;
	const float player_ability_timescale			= 0.2f;

	// Enemy
	const float enemy_patrol_walk_speed				= 100.0f;
	const float enemy_run_speed						= 350.0f;
	
	const float enemy_grunt_attack_delay			= 1.0f;
	const float enmey_gangster_attack_delay			= 3.0f;

	// Replay
	const float recording_delay						= 1 / 60.0f;

	// Delay
	const float effect_roll_cloud_delay				= 0.02f;
	const float effect_wallslide_cloud_delay		= 0.04f;
	const float effect_blood_splatter_delay			= 0.01f;
	const float effect_dia_transition_delay			= 0.005f;
	const float effect_hit_laser_dealy				= 0.5f;
}

//// State ////
// Player
namespace PlayerState
{
	const std::string_view none				= "None";
	const std::string_view idle				= "Idle";
	const std::string_view idle_to_run		= "IdleToRun";
	const std::string_view run				= "Run";
	const std::string_view run_to_idle		= "RunToIdle";
	const std::string_view postcrouch		= "PostCrouch";
	const std::string_view precrouch		= "PreCrouch";
	const std::string_view jump				= "Jump";
	const std::string_view fall				= "Fall";
	const std::string_view roll				= "Roll";
	const std::string_view attack			= "Attack";
	const std::string_view wallslide		= "WallSlide";
	const std::string_view flip				= "Flip";
	const std::string_view kickdoor			= "KickDoor";
	const std::string_view dead				= "Dead";
}

namespace PlayerSubState
{
	const std::string_view none				= "None";
	const std::string_view intro			= "Intro";
	const std::string_view play				= "Play";
	const std::string_view replay			= "Replay";
	const std::string_view outro			= "Outro";
	const std::string_view restart			= "Restart";
}


// Level
namespace TitleLevelState
{
	const std::string_view title = "Title";
	const std::string_view wait = "Wait";
	const std::string_view exit = "Exit";
}

namespace PlayLevelState
{
	const std::string_view transition_on	= "Transition_On";
	const std::string_view transition_off	= "Transition_Off";
	const std::string_view intro			= "Intro";
	const std::string_view beginplay_effect	= "BeginPlay_Effect";
	const std::string_view play				= "Play";
	const std::string_view clear			= "Clear";
	const std::string_view outro			= "Outro";
	const std::string_view replay			= "Replay";
	const std::string_view player_dead		= "PlayerDead";
	const std::string_view restart			= "Restart";
}


// Object
namespace TitleScreenState
{
	const std::string_view none				= "None";
	const std::string_view begin			= "Begin";
	const std::string_view newgame			= "NewGame";
	const std::string_view exit				= "Exit";
}

namespace TitleMenuState
{
	const std::string_view title_enter		= "TitleEnter";
	const std::string_view wait				= "Wait";
}

namespace EnemyState
{
	const std::string_view idle				= "Idle";
	const std::string_view hitfall			= "HitFall";
	const std::string_view dead				= "Dead";
	const std::string_view patrol_walk		= "Patrol_Walk";
	const std::string_view patrol_turn		= "Patrol_Turn";
	const std::string_view patrol_stop		= "Patrol_Stop";
	const std::string_view chase_run		= "Chase_Run";
	const std::string_view chase_stop		= "Chase_Stop";
	const std::string_view chase_turn		= "Chase_Turn";
	const std::string_view chase_stair_up	= "Chase_Stair_Up";
	const std::string_view chase_stair_down	= "Chase_Stair_Down";
	const std::string_view chase_stair_turn	= "Chase_Stair_Turn";
	const std::string_view chase_attack		= "Chase_Attack";

	const std::string_view turn				= "Turn";

	const std::string_view none				= "None";
	const std::string_view replay			= "Replay";
	const std::string_view restart			= "Restart";
}

namespace RecCompoState
{
	const std::string_view replay			= "Replay";
	const std::string_view restart			= "Restart";
}

namespace DoorState
{
	const std::string_view close			= "Close";
	const std::string_view open				= "Open";
	const std::string_view opened			= "Opened";
}

namespace GoState
{
	const std::string_view repeat			= "Repeat";
	const std::string_view outro			= "Outro";
}

namespace HudState
{
	const std::string_view wait				= "Wait";
	const std::string_view play				= "Play";
	const std::string_view outro			= "Outro";
}

namespace MouseAimState
{
	const std::string_view play				= "Play";
	const std::string_view replay			= "RePlay";
}

namespace ReplayUIState
{
	const std::string_view play				= "Play";
	const std::string_view stop				= "Stop";
	const std::string_view rewind			= "Rewind";
	const std::string_view fastplay			= "FastPlay";
}

namespace CeilLaserState
{
	const std::string_view on				= "On";
	const std::string_view off				= "Off";
	const std::string_view shoot			= "Shoot";
}

namespace CeilGunState
{
	const std::string_view on				= "On";
	const std::string_view off				= "Off";
	const std::string_view shoot			= "Shoot";
}

namespace PanicSwitchState
{
	const std::string_view on				= "On";
	const std::string_view off				= "Off";
}

namespace OutroMsgState
{
	const std::string_view fade_in			= "FadeIn";
	const std::string_view fade_out			= "FadeOut";
	const std::string_view wait				= "Wait";
}

namespace FanState
{
	const std::string_view idle				= "Idle";
}

namespace ScientistState
{
	const std::string_view idle				= "Idle";
	const std::string_view explode			= "Explode";
}

namespace DiaTransitionState
{
	const std::string_view none				= "None";
	const std::string_view on				= "On";
	const std::string_view off				= "Off";
}

namespace MainCameraState
{
	const std::string_view title_in			= "Title_In";
	const std::string_view chaseplayer		= "ChasePlayer";
	const std::string_view shaking			= "Shaking";
}