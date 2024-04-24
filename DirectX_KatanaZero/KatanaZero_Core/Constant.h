#pragma once

namespace ColMap
{
	const Color8Bit YELLOW	= Color8Bit(255, 255, 0, 255);
	const Color8Bit GREEN	= Color8Bit(0, 255, 0, 255);
	const Color8Bit BLUE	= Color8Bit(0, 0, 255, 255);
	const Color8Bit RED		= Color8Bit(255, 0, 0, 255);
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
	const std::string_view enemy_gangster_hitfall	= "gangster_hitfall";
	const std::string_view enemy_gangster_dead		= "gangster_dead";

	// UI
	const std::string_view ui_cursor				= "spr_cursor_0.png";
	const std::string_view ui_up_hud_bar			= "spr_hud_0.png";
	const std::string_view ui_up_hud_battery		= "spr_hud_battery_0.png";
	const std::string_view ui_up_hud_battery_part	= "spr_hud_battery_part_0.png";
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

	// MapComponent
	const std::string_view compo_door				= "spr_door";
	const std::string_view compo_ceil_laser_on		= "spr_laser_on_0.png";
	const std::string_view compo_ceil_laser_off		= "spr_laser_off_0.png";
	const std::string_view compo_ceil_laser_idle	= "spr_laser_col_idle";
	const std::string_view compo_ceil_laser_attack	= "spr_laser_col_attack";
	const std::string_view compo_ceil_gun			= "spr_ceiling_gun_0.png";
	const std::string_view compo_ceilgun_col_idle	= "spr_ceilgun_col_idle";
	const std::string_view compo_panic_switch_on	= "spr_panic_switch_on.png";
	const std::string_view compo_panic_switch_off	= "spr_panic_switch_off.png";

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
	const std::string_view enemy_grunt_walk			= "grunt_walk";
	const std::string_view enemy_grunt_run			= "grunt_run";
	const std::string_view enemy_grunt_turn			= "grunt_turn";
	const std::string_view enemy_grunt_hitfall		= "grunt_hitfall";
	const std::string_view enemy_grunt_dead			= "grunt_dead";

	const std::string_view enemy_gangster_idle		= "gangster_idle";
	const std::string_view enemy_gangster_hitfall	= "gangster_hitfall";
	const std::string_view enemy_gangster_dead		= "gangster_dead";

	// UI
	const std::string_view ui_replay_right_click	= "spr_right_click";

	// Effect Anim
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

	// MapComponent
	const std::string_view compo_door_idle			= "door_idle";
	const std::string_view compo_door_open			= "door_open";
	const std::string_view compo_ceil_laser_idle	= "spr_laser_col_idle";
	const std::string_view compo_ceil_laser_attack	= "spr_laser_col_attack";
	const std::string_view compo_ceilgun_col_idle	= "spr_ceilgun_col_idle";

	// TitleLevel
	const std::string_view plants					= "plants";
}

namespace Const
{
	// player
	const float default_gravity						= -2000.0f;
	const float jump_gravity						= -1100.0f;
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
	
	// replay
	const float recording_delay						= 1 / 60.0f;

	// delay
	const float effect_roll_cloud_delay				= 0.02f;
	const float effect_wallslide_cloud_delay		= 0.04f;

}