#pragma once

namespace ColMap
{
	const Color8Bit YELLOW	= Color8Bit(255, 255, 0, 255);
	const Color8Bit GREEN	= Color8Bit(0, 255, 0, 255);
	const Color8Bit BLUE	= Color8Bit(0, 0, 255, 255);
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

	// UI
	const std::string_view ui_cursor				= "spr_cursor_0.png";
	const std::string_view ui_up_hud_bar			= "spr_hud_0.png";
	const std::string_view ui_up_hud_battery		= "spr_hud_battery_0.png";
	const std::string_view ui_up_hud_battery_part	= "spr_hud_battery_part_0.png";
	const std::string_view ui_up_hud_timer			= "spr_hud_timer_0.png";
	const std::string_view ui_up_hud_timer_bar		= "spr_hud_timer_1.png";
	const std::string_view ui_up_hud_weapon			= "spr_hud_weapon_0.png";
	const std::string_view ui_katana_icon			= "spr_katanaicons_0.png";
	const std::string_view ui_item_icon				= "spr_itemicons_0.png";
	const std::string_view ui_shift_up				= "spr_keyboard_shift_0.png";
	const std::string_view ui_shift_down			= "spr_keyboard_shift_1.png";
	const std::string_view ui_left_click			= "spr_left_click_0.png";
	const std::string_view ui_right_click			= "spr_right_click_0.png";

	// TitleLevel
	const std::string_view title_background			= "spr_title_background.png";
	const std::string_view title_fence				= "spr_title_fence_0.png";
	const std::string_view title_grass				= "spr_title_grass_0.png";
	const std::string_view title_neon_zer			= "spr_titlegraphic_1.png";
	const std::string_view title_neon_o				= "spr_titlegraphic_2.png";
	const std::string_view title_neon_katana		= "spr_titlegraphic_3.png";
	const std::string_view title_plant				= "spr_plants";

	// FactoryLevel
	const std::string_view factory_background1		= "spr_background_factory_1.png";
	const std::string_view factory_background2		= "spr_background_factory_2.png";
	const std::string_view factory_background3		= "spr_background_factory_3.png";
	const std::string_view factory_background4	 	= "spr_background_factory_4.png";
	const std::string_view factory_background5		= "spr_background_factory_5.png";

	const std::string_view factory_colmap2			= "spr_colmap_factory_2.png";

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

	// TitleLevel
	const std::string_view plants					= "plants";
}

namespace Const
{
	const float gravity = -2000.0f;
	const float jump_gravity = -1100.0f;
	const float run_gravity = -10000.0f;

	const FVector player_jump_vel = { 0.0f, 500.0f, 0.0f };

	const float player_max_speedx = 425.0f;
	const float player_max_speedy = 425.0f;

	const float player_run_accx = 1000.0f;

	const float player_roll_accx = -1000.0f;
	const float player_roll_speedx = 800.0f;

	const float player_fall_accx = 1000.0f;
	const float player_fall_max_speedy = 1000.0f;
}