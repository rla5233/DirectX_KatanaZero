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
	const std::string_view player_headphones		= "player_headphones";
	const std::string_view player_remove_headphones	= "player_remove_headphones";

	// HeadHunter
	const std::string_view headhunter_idle			= "headhunter_idle";
	const std::string_view headhunter_takeup_rifle	= "headhunter_takeup_rifle";
	const std::string_view headhunter_hitfly		= "headhunter_hitfly";
	const std::string_view headhunter_recover		= "headhunter_recover";
	const std::string_view headhunter_exit_door		= "headhunter_exit_door";
	const std::string_view headhunter_roll			= "headhunter_roll";
	const std::string_view headhunter_prejump		= "headhunter_prejump";
	const std::string_view headhunter_jump			= "headhunter_jump";
	const std::string_view headhunter_wall_idle		= "headhunter_wallidle";
	const std::string_view headhunter_wall_jump		= "headhunter_walljump";
	const std::string_view headhunter_land			= "headhunter_land";
	const std::string_view headhunter_takeout_gun	= "headhunter_takeoutgun";
	const std::string_view headhunter_shoot_gun		= "headhunter_gunshoot";

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
	const std::string_view ui_playerdead_msg_0		= "spr_restart_0.png";

	const std::string_view ui_songtitle_background	= "spr_songtitle_background.png";
	const std::string_view ui_playingsong_0			= "spr_playingsong_0.png";
	const std::string_view ui_playingsong_1			= "spr_playingsong_1.png";
	const std::string_view ui_playingsong_title		= "spr_playingsong_title.png";
	const std::string_view ui_playingsong_underline	= "spr_playingsong_underline.png";
	const std::string_view ui_stagename0			= "spr_stagename0.png";
	const std::string_view ui_stagename1			= "spr_stagename1.png";

	const std::string_view ui_stage_clear0			= "spr_stage_clear_0.png";
	const std::string_view ui_stage_clear1			= "spr_stage_clear_1.png";

	const std::string_view ui_startmsg_0			= "spr_startmsg_0.png";
	const std::string_view ui_start_leftclick		= "spr_left_click";

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
	const std::string_view effect_laser				= "spr_laser_effect";
	const std::string_view effect_explosion			= "spr_explosion";

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

	const std::string_view compo_sliding_door_close		= "spr_sliding_door_close";
	const std::string_view compo_sliding_door_closed	= "spr_sliding_door.png";
	const std::string_view compo_sliding_door_redled	= "spr_sliding_door_redled";

	const std::string_view compo_ground_mine			= "spr_mine";

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
	const std::string_view headhunter_under_black	= "spr_under_headhunter1.png";

	const std::string_view headhunter_colmap1		= "spr_colmap_headhunter1.png";
	const std::string_view headhunter_colmap2		= "spr_colmap_headhunter2.png";

	// etc.
	const std::string_view black_point				= "spr_black.png";
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
	const std::string_view player_headphones		= "player_headphones";
	const std::string_view player_remove_headphones = "player_remove_headphones";

	// HeadHunter
	const std::string_view headhunter_idle			= "headhunter_idle";
	const std::string_view headhunter_takeup_rifle	= "headhunter_takeup_rifle";
	const std::string_view headhunter_putback_rifle	= "headhunter_putback_rifle";
	const std::string_view headhunter_hitfly		= "headhunter_hitfly";
	const std::string_view headhunter_recover		= "headhunter_recover";
	const std::string_view headhunter_exit_door		= "headhunter_exit_door";
	const std::string_view headhunter_roll			= "headhunter_roll";
	const std::string_view headhunter_prejump		= "headhunter_prejump";
	const std::string_view headhunter_jump			= "headhunter_jump";
	const std::string_view headhunter_wall_idle		= "headhunter_wallidle";
	const std::string_view headhunter_wall_jump		= "headhunter_walljump";
	const std::string_view headhunter_land			= "headhunter_land";
	const std::string_view headhunter_takeout_gun	= "headhunter_takeoutgun";
	const std::string_view headhunter_shoot_gun		= "headhunter_gunshoot";

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
	const std::string_view ui_start_leftclick		= "spr_left_click";

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

	const std::string_view effect_laser				= "spr_laser_effect";
	const std::string_view effect_explosion			= "spr_explosion";

	// Component
	const std::string_view compo_door_idle			= "door_idle";
	const std::string_view compo_door_open			= "door_open";
	const std::string_view compo_ceil_laser_idle	= "spr_laser_col_idle";
	const std::string_view compo_ceil_laser_attack	= "spr_laser_col_attack";
	const std::string_view compo_ceilgun_col_idle	= "spr_ceilgun_col_idle";
	const std::string_view compo_fan_blade			= "spr_fanblade";

	const std::string_view compo_scientist_chair	= "spr_scientist_chair";
	const std::string_view compo_scientist_explode	= "spr_scientist_explode";

	const std::string_view compo_sliding_door_close		= "spr_sliding_door_close";
	const std::string_view compo_sliding_door_redled	= "spr_sliding_door_redled";

	const std::string_view compo_ground_mine		= "spr_mine";

	// TitleLevel
	const std::string_view plants					= "plants";
}

namespace SoundRes
{
	// Player
	const std::string_view player_run_1				= "sound_player_running_1.wav";
	const std::string_view player_run_2				= "sound_player_running_2.wav";
	const std::string_view player_run_3				= "sound_player_running_3.wav";
	const std::string_view player_run_4				= "sound_player_running_4.wav";
	const std::string_view player_prerun			= "sound_player_prerun.wav";
	const std::string_view player_roll				= "sound_player_roll.wav";
	const std::string_view player_jump				= "sound_player_jump.wav";
	const std::string_view player_land				= "sound_player_land.wav";
	const std::string_view player_die				= "sound_player_die.wav";
	const std::string_view player_slash_1			= "sound_player_slash_1.wav";
	const std::string_view player_slash_2			= "sound_player_slash_2.wav";
	const std::string_view player_slash_3			= "sound_player_slash_3.wav";
	const std::string_view player_headphone			= "sound_playerheadphones.wav";
	const std::string_view player_casette_play		= "sound_playercasette_play.wav";
	const std::string_view player_casette_rewind	= "sound_playercasette_rewind.wav";
	const std::string_view player_punch_hit			= "sound_enemy_punch_hit.wav";
	const std::string_view player_wall_slide		= "sound_player_wallslide.wav";
	const std::string_view player_wall_kick1		= "sound_player_wallkick_1.wav";
	const std::string_view player_wall_kick2		= "sound_player_wallkick_2.wav";
	const std::string_view player_wall_kick3		= "sound_player_wallkick_3.wav";

	// UI
	const std::string_view title_menu_beep			= "sound_menu_beep.wav";
	const std::string_view title_menu_select		= "sound_menu_select.wav";
	const std::string_view title_menu_transition	= "sound_ui_transition.wav";
	const std::string_view transition_on			= "sound_transition_on.wav";
	const std::string_view transition_off			= "sound_transition_off.wav";
	const std::string_view replay_play				= "sound_replay_play.wav";
	const std::string_view replay_fastplay			= "sound_replay_fastplay.wav";

	// Sound
	const std::string_view stage_start				= "sound_stage_start.wav";
	const std::string_view stage_restart			= "sound_rewind.wav";
	const std::string_view stage_restartend			= "sound_tv_thump.wav";
	const std::string_view slomo_start				= "sound_slomo_start.ogg";
	const std::string_view slomo_end				= "sound_slomo_end.wav";
	const std::string_view enemy_dead_sword1		= "sound_enemy_death_sword_01.wav";
	const std::string_view enemy_dead_sword2		= "sound_enemy_death_sword_02.wav";
	const std::string_view enemy_bloodsplat1		= "sound_enemy_bloodsplat.wav";
	const std::string_view enemy_bloodsplat2		= "sound_enemy_bloodsplat2.wav";
	const std::string_view enemy_bloodsplat3		= "sound_enemy_bloodsplat3.wav";
	const std::string_view enemy_bloodsplat4		= "sound_enemy_bloodsplat4.wav";
	const std::string_view enemy_hitfloor			= "sound_enemy_hitfloor.wav";
	const std::string_view enemy_chest_ground		= "sound_enemy_chest_ground.wav";
	const std::string_view enemy_punch				= "sound_enemy_punch.wav";
	const std::string_view door_open				= "sound_door_open.wav";
	const std::string_view ceil_laser_shoot			= "sound_laser_explosion.wav";
	const std::string_view gun_fire1				= "sound_gun_fire_1.wav";
	const std::string_view gun_fire2				= "sound_gun_fire_2.wav";
	const std::string_view ceil_laser_on			= "sound_lasers_on.wav";
	const std::string_view ceil_laser_off			= "sound_lasers_off.wav";
	const std::string_view pull_switch				= "sound_pull_switch.wav";
	const std::string_view blastdoor_close			= "sound_blastdoor_close.wav";
		
	// BGM
	const std::string_view bgm_title				= "song_title_bgm.ogg";
	const std::string_view bgm_factory				= "song_youwillneverknow.ogg";
	const std::string_view bgm_headhunter1			= "song_bossbattle.ogg";
}

namespace Const
{
	// Player
	const float default_gravity						= -2000.0f;
	const float jump_gravity						= -1800.0f;
	const float down_stair_gravity					= -15000.0f;

	const float player_max_speedx					= 400.0f;
	const float player_max_speedy					= 425.0f;

	const float player_run_accx						= 1000.0f;

	const float player_roll_speedx					= 500.0f;

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

	// Effect
	const float4 player_afterimage_color = { 0.426f, 0.502f, 0.752f, 1.0f };

	// Delay
	const float recording_delay						= 1 / 60.0f;
	const float restart_speed_delay					= 0.02f;

	const float effect_roll_cloud_delay				= 0.02f;
	const float effect_wallslide_cloud_delay		= 0.04f;
	const float effect_blood_splatter_delay			= 0.01f;
	const float effect_dia_transition_delay			= 0.005f;
	const float effect_hit_laser_dealy				= 0.1f;
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

	const std::string_view onlyfall			= "OnlyFall";
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

// HeadHunter
namespace HeadHunterState
{
	const std::string_view none					= "None";
	const std::string_view idle					= "Idle";
	const std::string_view hitfly				= "HitFly";
	const std::string_view recover				= "Recover";
	const std::string_view roll					= "Roll";
	const std::string_view exitdoor				= "ExitDoor";
	const std::string_view pattern_rifle1		= "Pattern_Rifle1";
	const std::string_view pattern_airrifle1	= "Pattern_AirRifle1";
	
	// Phase2
	const std::string_view pattern_gunshoot1	= "Pattern_GunShoot1";
}

namespace HeadHunterSubState
{
	const std::string_view wait				= "Wait";
	const std::string_view play				= "Play";
	const std::string_view restart			= "Restart";
}

// Level
namespace TitleLevelState
{
	const std::string_view title			= "Title";
	const std::string_view wait				= "Wait";
	const std::string_view exit				= "Exit";
}

namespace PlayLevelState
{
	const std::string_view transition_on	= "Transition_On";
	const std::string_view transition_off	= "Transition_Off";
	const std::string_view intro			= "Intro";
	const std::string_view intro_effect		= "Intro_Effect";
	const std::string_view intro_big_effect	= "Intro_Big_Effect";
	const std::string_view play				= "Play";
	const std::string_view clear			= "Clear";
	const std::string_view outro			= "Outro";
	const std::string_view replay			= "Replay";
	const std::string_view player_dead		= "PlayerDead";
	const std::string_view restart			= "Restart";
}

namespace BossLevelState
{
	const std::string_view transition_on	= "Transition_On";
	const std::string_view transition_off	= "Transition_Off";
	const std::string_view intro			= "Intro";
	const std::string_view intro_effect		= "Intro_Effect";
	const std::string_view intro_big_effect	= "Intro_Big_Effect";
	const std::string_view play				= "Play";
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
	const std::string_view stop				= "Stop";
	const std::string_view title_in			= "Title_In";
	const std::string_view chaseplayer		= "ChasePlayer";
	const std::string_view shaking			= "Shaking";
	const std::string_view ret_shaking		= "Return_Shaking";
}

namespace FailedMsgState
{
	const std::string_view hit_end			= "HitEnd";
	const std::string_view time_out			= "Time_Out";
}

namespace FactoryIntroUIState
{
	const std::string_view intro			= "Intro";
}

namespace FactoryClearUIState
{
	const std::string_view clear			= "Clear";
}

namespace SlidingDoorState
{
	const std::string_view close			= "Close";
	const std::string_view closed			= "Closed";
}

namespace MineState
{
	const std::string_view none				= "None";
	const std::string_view on				= "On";
	const std::string_view explode			= "Explode";
}

namespace UnderBlackState
{
	const std::string_view none				= "None";
	const std::string_view on				= "On";
}

// Info.
namespace HH_Phase1_RefPos
{
	const std::string_view leftfirst		= "LeftFirst";
	const std::string_view leftsecond		= "LeftSecond";
	const std::string_view mid				= "Mid";
	const std::string_view rightfirst		= "RightFirst";
	const std::string_view rightsecond		= "RightSecond";
}