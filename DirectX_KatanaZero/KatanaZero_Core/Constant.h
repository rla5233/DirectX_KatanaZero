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

	// Effect
	const std::string_view effect_player_slash		= "player_slash";
	const std::string_view effect_player_dustcloud	= "player_dustcloud";
	const std::string_view effect_player_landcloud	= "player_landcloud";
	const std::string_view effect_player_jumpcloud	= "player_jumpcloud";

	// MapComponent
	const std::string_view compo_door				= "spr_door";

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

	// Effect Anim
	const std::string_view effect_player_slash		= "player_slash";
	const std::string_view effect_player_dustcloud	= "player_dustcloud";
	const std::string_view effect_player_landcloud	= "player_landcloud";
	const std::string_view effect_player_jumpcloud	= "player_jumpcloud";

	// MapComponent
	const std::string_view compo_door_idle			= "door_idle";
	const std::string_view compo_door_open			= "door_open";

	// TitleLevel
	const std::string_view plants					= "plants";
}

namespace Const
{
	// player
	const float default_gravity = -2000.0f;
	const float jump_gravity = -1100.0f;
	const float down_stair_gravity = -15000.0f;

	const float player_max_speedx = 425.0f;
	const float player_max_speedy = 425.0f;

	const float player_run_accx = 1000.0f;

	const float player_roll_speedx = 700.0f;

	const float player_jump_accx = 1000.0f;
	const float player_jump_start_speedx = player_max_speedx * 0.75f;
	const float player_jump_speedy = 500.0f;

	const float player_fall_accx = 1000.0f;
	const float player_fall_input_accy = -6000.0f;
	const float player_fall_max_speedy = 1200.0f;

	const float player_attack_delay = 0.25f;
	
	// replay
	const float recording_delay = 1 / 60.0f;

	// delay
	const float effect_cloud_delay = 0.02f;

}